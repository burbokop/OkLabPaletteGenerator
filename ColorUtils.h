#pragma once

#include <QColor>
#include "3rdparty/farver/farver/src/ColorSpace.h"
#include <cmath>
#include <ranges>
#include <sstream>
#include <string>

inline bool isRGBValid(ColorSpace::Rgb color)
{
    return color.r >= 0 && color.r <= 255 && color.g >= 0 && color.g <= 255 && color.b >= 0
           && color.b <= 255;
};

inline bool isOkLabInBox(ColorSpace::OkLab color)
{
    return color.l >= 0 && color.l <= 1 && color.a >= -0.4 && color.a <= 0.4 && color.b >= -0.4
           && color.b <= 0.4;
}

inline bool isOkLabInCylinder(ColorSpace::OkLab color)
{
    return color.l >= 0 && color.l <= 1
           && std::pow(color.a, 2) + std::pow(color.b, 2) < std::pow(0.4, 2);
}

inline ColorSpace::Rgb okLabToRGB(ColorSpace::OkLab l)
{
    ColorSpace::Rgb result;
    l.ToRgb(&result);
    return result;
}

inline std::string rgbToGLSLExpression(const ColorSpace::Rgb &color)
{
    return (std::ostringstream() << "vec3(" << color.r / 0xff << ", " << color.g / 0xff << ", "
                                 << color.b / 0xff << ")")
        .str();
}

inline std::string okLabToPrettyString(ColorSpace::OkLab color)
{
    return (std::ostringstream() << "{ l: " << color.l << ", a: " << color.a << ", " << color.b
                                 << " }")
        .str();
}

inline std::optional<QColor> rgbToQColor(ColorSpace::Rgb color)
{
    if (isRGBValid(color)) {
        return qRgb(static_cast<int>(color.r), static_cast<int>(color.g), static_cast<int>(color.b));
    } else {
        return std::nullopt;
    }
}

inline QColor rgbToCapQColor(ColorSpace::Rgb color)
{
    color.Cap();
    return qRgb(static_cast<int>(color.r), static_cast<int>(color.g), static_cast<int>(color.b));
}

inline std::vector<ColorSpace::OkLab> harmonicLerp(std::size_t count,
                                                   ColorSpace::OkLab from,
                                                   ColorSpace::OkLab to)
{
    if (count == 0) {
        return {};
    }

    const auto dl = (to.l - from.l) / count;
    const auto da = (to.a - from.a) / count;
    const auto db = (to.b - from.b) / count;

    const auto colors = std::views::iota(0, static_cast<int>(count))
                        | std::views::transform([from, dl, da, db](auto i) {
                              return ColorSpace::OkLab(from.l + dl * i,
                                                       from.a + da * i,
                                                       from.b + db * i);
                          });

    return std::vector(colors.begin(), colors.end());
}

/*

    const auto colors = std::views::iota(0, static_cast<int>(count))
                        | std::views::transform([begin, c](auto i) {
                              return ColorSpace::OkLab(begin.l,
                                                       begin.a + c[0] * i,
                                                       begin.b + c[1] * i);
                          });
*/

//inline void validateColors(const std::vector<ColorSpace::OkLab> &colors)
//{
//    for (const auto &c : colors) {
//        const auto cc = rgb(c);
//        if (isRgbValid(cc)) {
//            qDebug().nospace() << rgbToGLSLExpression(cc);
//        } else {
//            qDebug().nospace() << rgbToGLSLExpression(cc) << " !!!INVALID !!! " << rgbToQCOlor(cc);
//        }
//    }
//}
