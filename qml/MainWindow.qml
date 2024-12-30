import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

import CoordinateSystem 1.0
import ScreenTools 1.0
import CustomWidgets 1.0

Window {
    id: mainWindow

    ScreenTools {
        id: _screen_tools
    }

    visible: true
    width: 1000
    height: 800
    title: "Koordinat Sistemi"

    RowLayout {
        id: main_layout
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: 10

        Rectangle {
            id: coordinateSystem
            width: 640
            height: 480
            color: "lightgray"

            Canvas {
                id: canvas
                anchors.fill: parent
                property var clickedPoints: []  // Koordinatlar buraya kaydedilecek
                property var cs: CoordinateSystem { // C++ sınıfını burada kullanıyoruz
                    id: coordSys
                }

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0, 0, width, height);
                    ctx.strokeStyle = "black";

                    // X ve Y eksenlerini çiz
                    ctx.beginPath();
                    ctx.moveTo(width / 2, 0); // Y ekseni
                    ctx.lineTo(width / 2, height);
                    ctx.moveTo(0, height / 2); // X ekseni
                    ctx.lineTo(width, height / 2);
                    ctx.stroke();

                    // Tıklanan her noktada '+' işareti çiz
                    for (var i = 0; i < clickedPoints.length; i++) {
                        var point = clickedPoints[i];
                        ctx.beginPath();
                        ctx.moveTo(point.x - 5, point.y); // Sol yatay çizgi
                        ctx.lineTo(point.x + 5, point.y); // Sağ yatay çizgi
                        ctx.moveTo(point.x, point.y - 5); // Üst dikey çizgi
                        ctx.lineTo(point.x, point.y + 5); // Alt dikey çizgi
                        ctx.stroke();
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var clickedX = mouse.x;
                        var clickedY = mouse.y;

                        // Koordinatları clickedPoints listesine ekle
                        canvas.clickedPoints.push(Qt.point(clickedX, clickedY));

                        // Koordinatları C++ sınıfına gönder
                        coordSys.clickedPoints = canvas.clickedPoints;

                        // Koordinatları konsola yazdır
                        console.log("Koordinatlar: X = " + clickedX + ", Y = " + clickedY);

                        // Canvas'ı yeniden çiz
                        canvas.requestPaint();
                    }
                }
            }
        } // end of coordinateSystem

        Rectangle {
            id: configurations
            width: mainWindow.width - coordinateSystem.width - 20
            height: coordinateSystem.height
            color: "#faf0f0"
            ColumnLayout {
                id: configuration_layout
                anchors.top: parent.top
                anchors.left: parent.left
                spacing: 10

                RowLayout {
                    id: crow1
                    CustomLabel {
                        Layout.minimumWidth: _screen_tools.default_label_width
                        Layout.minimumHeight: _screen_tools.default_label_height
                        text: "Class"
                    }

                    // ComboBox (Seçenek kutusu)
                    ComboBox {
                        id: cmbx_class
                        width: configurations.width / 3
                        model: ListModel {
                            ListElement { name: "Class 1" }
                            ListElement { name: "Class 2" }
                        }
                        onCurrentIndexChanged: {
                        }
                    }
                }

                RowLayout {
                    id: crow2
                    CustomLabel {
                        Layout.minimumWidth: _screen_tools.default_label_width
                        Layout.minimumHeight: _screen_tools.default_label_height
                        text: "Epoc"
                    }
                    ComboBox {
                        id: cmbx_epoc
                        width: configurations.width / 3
                        model: ListModel {
                            ListElement { name: "1" }
                            ListElement { name: "9" }
                            ListElement { name: "99" }
                            ListElement { name: "999" }
                            ListElement { name: "9999" }
                            ListElement { name: "99999" }
                            ListElement { name: "999999" }
                            ListElement { name: "9999999" }
                        }
                        onCurrentIndexChanged: {
                        }
                    }
                }
                RowLayout {
                    id: crow3
                    CustomLabel {
                        Layout.minimumWidth: _screen_tools.default_label_width
                        Layout.minimumHeight: _screen_tools.default_label_height
                        text: "Learning Rate"
                    }

                    TextField {
                        id: cmbx_learn
                        width: configurations.width / 3
                    }
                }
            }
        } // end of configurations

    } // end of main Layout
}
