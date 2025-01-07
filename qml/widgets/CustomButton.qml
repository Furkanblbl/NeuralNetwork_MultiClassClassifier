import QtQuick
import QtQuick.Controls
import QtQuick.Window

import ScreenTools 1.0

Button {
    id: _customButton

    ScreenTools {
        id: _screen_tools
    }

    property string _text: ""

    Rectangle {
        id: lbl_rect
        color: "#c6c5c3"
        anchors.fill: parent
        border.color: _screen_tools.default_widget_border_color
        border.width: _screen_tools.default_widget_border_size
        Text {
            id: lbl_text
            text: _customButton._text
            color: _screen_tools.default_widget_text_color
            anchors.centerIn: parent
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: _screen_tools.default_widget_margin
        }
    }
    onClicked: {
    }
}
