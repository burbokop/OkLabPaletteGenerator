#include <QColor>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Palette.h"
#include <ranges>

int main(int argc, char *argv[])
{
    //    const auto colors = generatePalette();

    //    validateColors(colors);

    //    const auto qColors = colors | std::views::transform([](auto c) { return rgbToQCOlor(rgb(c)); });

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //    Palette palette(QList<QColor>{qColors.begin(), qColors.end()}, &app);

    //    engine.setInitialProperties({{"palette", QVariant::fromValue(&palette)}});

    QGuiApplication::setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    const QUrl url(u"qrc:/org/burbokop/cpp_palette_generator/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
