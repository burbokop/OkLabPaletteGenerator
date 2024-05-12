#include "PaletteView.h"

#include <QPainter>
#include "ColorUtils.h"
#include "Palette.h"

QLineF shrinkLine(QLineF line, qreal t)
{
    return QLineF(line.center() + (line.p1() - line.center()) * t,
                  line.center() + (line.p2() - line.center()) * t);
}

PaletteView::PaletteView()
{
}

Palette *PaletteView::palette() const
{
    return m_palette;
}

void PaletteView::setPalette(Palette *newPalette)
{
    if (m_palette == newPalette)
        return;

    m_palette = newPalette;

    disconnect(m_connection);
    m_connection = connect(m_palette, &Palette::colorsChanged, this, [this]() { update(); });
    update();

    emit paletteChanged();
}

QRgb invColor(QRgb c)
{
    return qRgb(255 - qRed(c), 255 - qGreen(c), 255 - qBlue(c));
}

//QColor invColor(QColor c)
//{
//    return c.rgba()
//}

void PaletteView::paint(QPainter *painter)
{
    if (!m_palette)
        return;

    qreal x = 0;
    for (const auto &color : m_palette->colors()) {
        const auto rgb = okLabToRGB(color);

        painter->setBrush(rgbToCapQColor(rgb));
        painter->setPen(QPen({}, 0));
        painter->drawRect(
            QRectF(QPointF(x, 0),
                   QPointF(x + size().width() / m_palette->colors().size(), size().height())));

        const auto indicatorsColor = QColor(invColor(rgbToCapQColor(rgb).rgb()));
        const auto indicatorsLineWidth = std::max(std::min(width(), height()) / 100, 1.);

        if (!isRGBValid(rgb)) {
            painter->setBrush(Qt::transparent);
            painter->setPen(QPen(indicatorsColor, indicatorsLineWidth));
            painter->drawLine(
                shrinkLine(QLineF(QPointF(x, size().width() / m_palette->colors().size() * 0),
                                  QPointF(x + size().width() / m_palette->colors().size(),
                                          size().width() / m_palette->colors().size() * 1)),
                           0.5));
            painter->drawLine(
                shrinkLine(QLineF(QPointF(x + size().width() / m_palette->colors().size(),
                                          size().width() / m_palette->colors().size() * 0),
                                  QPointF(x, size().width() / m_palette->colors().size() * 1)),
                           0.5));
        }

        if (!isOkLabInCylinder(color)) {
            painter->setBrush(Qt::transparent);
            painter->setPen(QPen(indicatorsColor, indicatorsLineWidth));
            painter->drawEllipse(QRectF(QPointF(x, size().width() / m_palette->colors().size()),
                                        QPointF(x + size().width() / m_palette->colors().size(),
                                                size().width() / m_palette->colors().size() * 2))
                                 - QMarginsF(10, 10, 10, 10));
        }

        if (!isOkLabInBox(color)) {
            painter->setBrush(Qt::transparent);
            painter->setPen(QPen(indicatorsColor, indicatorsLineWidth));
            painter->drawRect(QRectF(QPointF(x, size().width() / m_palette->colors().size() * 2),
                                     QPointF(x + size().width() / m_palette->colors().size(),
                                             size().width() / m_palette->colors().size() * 3))
                              - QMarginsF(10, 10, 10, 10));
        }

        x += size().width() / m_palette->colors().size();
    }
}
