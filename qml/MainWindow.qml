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
    width: _screen_tools._width
    height: _screen_tools._height
    title: "410447 Muhammet Enes EMIR - Neural Network"

    color: "#edebe9"

    RowLayout {
        id: main_layout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin:  10 * _screen_tools.default_widget_margin
        anchors.leftMargin: 2 * _screen_tools.default_widget_margin

        Rectangle {
            id: coordinateSystem
            width: 640
            height: 480
            color: "#f3f2f1"
            border.width: 2
            border.color: _screen_tools.default_widget_border_color

            property var clicked_color: ["red", "green", "blue", "#c931c9", "#c96b00", "#56024d"]
            property string point_color: ""
            property int selected_class: -1
            property int selected_epoch: -1
            property double learning_rate: -1

            Canvas {
                id: canvas
                anchors.fill: parent
                property var clickedPoints: []
                property var cs: CoordinateSystem {
                    id: coordSys
                }

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0, 0, width, height);
                    ctx.strokeStyle = "black";

                    ctx.beginPath();
                    ctx.moveTo(width / 2, 0);
                    ctx.lineTo(width / 2, height);
                    ctx.moveTo(0, height / 2);
                    ctx.lineTo(width, height / 2);
                    ctx.stroke();

                    for (var i = 0; i < clickedPoints.length; i++) {
                        var point = clickedPoints[i];
                        ctx.strokeStyle = coordinateSystem.clicked_color[point.color];
                        ctx.beginPath();
                        ctx.moveTo(point.x - 5, point.y);
                        ctx.lineTo(point.x + 5, point.y);
                        ctx.moveTo(point.x, point.y - 5);
                        ctx.lineTo(point.x, point.y + 5);
                        ctx.stroke();
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var clickedX = mouse.x;
                        var clickedY = mouse.y;

                        canvas.clickedPoints.push({x: clickedX, y: clickedY, color: coordinateSystem.selected_class});
                        coordSys.clickedPoints = canvas.clickedPoints;
                        canvas.requestPaint();
                    }
                }
            }
        } // end of coordinateSystem

        Rectangle {
            id: configurations
            width: mainWindow.width - coordinateSystem.width - 20
            height: coordinateSystem.height
            color: "#edebe9"
            border.color: _screen_tools.default_widget_border_color
            border.width: 2

            ColumnLayout {
                id: configuration_layout
                anchors.top: parent.top
                anchors.left: parent.left
                spacing: 10

                RowLayout {
                    id: crow1
                    Layout.topMargin: 2 * _screen_tools.default_widget_margin
                    Layout.leftMargin: 2 * _screen_tools.default_widget_margin
                    Layout.rightMargin: 2 * _screen_tools.default_widget_margin
                    CustomLabel {
                        Layout.minimumWidth: _screen_tools.default_widget_width
                        Layout.minimumHeight: _screen_tools.default_widget_height
                        text: "Class"
                    }

                    CustomComboBox {
                        id: cmbox_class
                        Layout.minimumWidth: configurations.width - _screen_tools.default_widget_width - 20
                        Layout.minimumHeight: _screen_tools.default_widget_height
                        model: ["Class 1", "Class 2", "Class 3", "Class 4"]
                        onCurrentIndexChanged: {
                            coordinateSystem.selected_class = currentIndex
                            coordinateSystem.point_color = coordinateSystem.clicked_color[coordinateSystem.selected_class]
                            // console.log("coordinateSystem.point_color:", coordinateSystem.point_color)
                        }
                    }
                }

                RowLayout {
                    id: crow2
                    Layout.topMargin: 2 * _screen_tools.default_widget_margin
                    Layout.leftMargin: 2 * _screen_tools.default_widget_margin
                    Layout.rightMargin: 2 * _screen_tools.default_widget_margin
                    CustomLabel {
                        Layout.minimumWidth: _screen_tools.default_widget_width
                        Layout.minimumHeight: _screen_tools.default_widget_height
                        text: "Epoc"
                    }
                    CustomComboBox {
                        Layout.minimumWidth: configurations.width - _screen_tools.default_widget_width - 20
                        Layout.minimumHeight: _screen_tools.default_widget_height
                        model: ["1", "9", "99", "999", "9999", "99999", "999999", "9999999"]
                        onCurrentIndexChanged: {
                            coordinateSystem.selected_epoch = model[currentIndex]
                            coordSys.epocSize = coordinateSystem.selected_epoch;
                            // console.log("coordinateSystem.selected_epoch:", model[currentIndex])
                        }
                    }
                }
                RowLayout {
                    id: crow3
                    Layout.topMargin: 2 * _screen_tools.default_widget_margin
                    Layout.leftMargin: 2 * _screen_tools.default_widget_margin
                    Layout.rightMargin: 2 * _screen_tools.default_widget_margin
                    CustomLabel {
                        Layout.minimumWidth: _screen_tools.default_widget_width
                        Layout.minimumHeight: _screen_tools.default_widget_height
                        text: "Learning Rate"
                    }

                    TextField {
                        id: tfield_lrate
                        Layout.minimumWidth: configurations.width - _screen_tools.default_widget_width - 20
                        Layout.minimumHeight: _screen_tools.default_widget_height
                        placeholderText: "Example: 0.01"
                        onTextChanged: {
                            coordinateSystem.learning_rate = tfield_lrate.text;
                            coordSys.learningRate = coordinateSystem.learning_rate;
                            // console.log("coordinateSystem.learning_rate ", tfield_lrate.text)
                        }
                    }
                }
            }
        } // end of configurations

    } // end of main Layout
}
