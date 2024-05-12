#pragma once

#include <QColor>
#include <QObject>
#include <QtQmlIntegration>

#include <3rdparty/farver/farver/src/ColorSpace.h>

class Palette : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    Palette(QObject *parent = nullptr)
        : QObject(parent)
    {}

    Q_INVOKABLE void generate(std::size_t count, qreal l, qreal aFrom, qreal aTo, qreal bFrom, qreal bTo);

    const auto &colors() const { return m_colors; }

signals:
    void colorsChanged();

private:
    std::vector<ColorSpace::OkLab> m_colors;
};
