import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import org.burbokop.cpp_palette_generator 1.0 as PG

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    PG.Palette {
        id: palette
    }

    //    required property PG.Palette palette

    function generate() {
        palette.generate(
            countSlider.value,
            lSlider.value,
            aSlider.first.value,
            aSlider.second.value,
            bSlider.first.value,
            bSlider.second.value)
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Text {
                text: 'N'
            }

            Slider {
                id: countSlider
                from: 0
                to: 16
                stepSize: 1
                onValueChanged: root.generate()
            }

            Text {
                text: countSlider.value
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                Layout.preferredWidth: 200
                text: 'Count'
            }
        }

        RowLayout {
            Text {
                text: 'L'
            }

            Slider {
                id: lSlider
                from: 0
                to: 1
                onValueChanged: root.generate()
            }

            Text {
                text: lSlider.value.toFixed(2)
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                Layout.preferredWidth: 200
                text: 'Lightness'
            }
        }

        RowLayout {
            Text {
                text: 'A'
            }

            RangeSlider {
                id: aSlider
                from: -0.4
                to: 0.4

                first.value: 0
                second.value: 0

                first.onValueChanged: root.generate()
                second.onValueChanged: root.generate()
            }

            Text {
                text: `${aSlider.first.value.toFixed(2)} - ${aSlider.second.value.toFixed(2)}`
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                Layout.preferredWidth: 200
                text: 'Green–red component'
            }
        }

        RowLayout {
            Text {
                text: 'B'
            }

            RangeSlider {
                id: bSlider
                from: -0.4
                to: 0.4

                first.value: 0
                second.value: 0

                first.onValueChanged: root.generate()
                second.onValueChanged: root.generate()
            }

            Text {
                text: `${bSlider.first.value.toFixed(2)} - ${bSlider.second.value.toFixed(2)}`
            }

            Item {
                Layout.fillWidth: true
            }

            Text {
                Layout.preferredWidth: 200
                text: 'Blue–yellow component'
            }
        }

        PG.PaletteView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            palette: palette
        }
    }
}
