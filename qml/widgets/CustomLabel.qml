import QtQuick
import QtQuick.Controls
import QtQuick.Window

import ScreenTools 1.0

Label {
    id: custom_label

    ScreenTools {
        id: _screen_tools
    }

    text: "Default Text"

    Rectangle {
        id: lbl_rect
        color: _screen_tools.label_back_color
        radius: _screen_tools.radius
        anchors.fill: parent
        border.color: _screen_tools.label_back_color
        border.width: _screen_tools.border_size
        Text {
            id: lbl_text
            text: custom_label.text
            color: _screen_tools.label_text_color
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: _screen_tools.default_margin
        }
    }
}
