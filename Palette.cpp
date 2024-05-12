#include "Palette.h"

#include "ColorUtils.h"

#include <QClipboard>
#include <QGuiApplication>
#include <iostream>

bool replace(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string stripMargin(const std::string &input, char margin = '|')
{
    std::istringstream iss(input);
    std::ostringstream oss;
    std::string line;

    while (std::getline(iss, line)) {
        auto pos = line.find_first_not_of(" \t"); // find the first non-whitespace character
        if (pos != std::string::npos && line[pos] == margin) {
            oss << line.substr(pos + 1) << '\n'; // append substring after the margin character
        } else {
            oss << line << '\n'; // append the original line if no margin character found
        }
    }

    return oss.str();
}

std::string generateQFunction(const std::vector<ColorSpace::OkLab> &colors)
{
    std::string q = stripMargin(R"(
        |vec3 palette(float g) {
        |    const int size = ${size};
        |    vec3 values[size] = vec3[size](
        |${values}
        |    );
        |    return values[int(g * float(size)) % size];
        |}
    )");

    auto ok = replace(q, "${size}", std::to_string(colors.size()));
    assert(ok);

    std::ostringstream ss;
    std::size_t i = 0;
    for (const auto &c : colors) {
        ss << "        " << rgbToGLSLExpression(okLabToRGB(c));
        if (++i < colors.size()) {
            ss << "," << std::endl;
        }
    }

    ok = replace(q, "${values}", ss.str());
    assert(ok);

    return q;
}

void Palette::generate(std::size_t count, qreal l, qreal aFrom, qreal aTo, qreal bFrom, qreal bTo)
{
    Q_ASSERT(aFrom <= aTo);
    Q_ASSERT(bFrom <= bTo);
    m_colors = harmonicLerp(count,
                            ColorSpace::OkLab(l, aFrom, bFrom),
                            ColorSpace::OkLab(l, aTo, bTo));

    const auto clipboard = QGuiApplication::clipboard();
    Q_ASSERT(clipboard);
    clipboard->setText(QString::fromStdString(generateQFunction(m_colors)));

    //    std::cout << generateQFunction(m_colors) << std::endl;

    emit colorsChanged();
}
