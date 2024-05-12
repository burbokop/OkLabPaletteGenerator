#pragma once

#include <QObject>
#include <QQuickPaintedItem>

class Palette;

class PaletteView : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(Palette *palette READ palette WRITE setPalette NOTIFY paletteChanged FINAL)
public:
    PaletteView();
    Palette *palette() const;
    void setPalette(Palette *newPalette);

signals:
    void paletteChanged();

    // QQuickPaintedItem interface
public:
    void paint(QPainter *painter) override;

private:
    Palette *m_palette = nullptr;
    QMetaObject::Connection m_connection;
};
