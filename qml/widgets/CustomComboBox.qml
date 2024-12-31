import QtQuick
import QtQuick.Controls
import QtQuick.Window

import ScreenTools 1.0

ComboBox {
    id: _custom_combobox

    ScreenTools {
        id: _screen_tools
    }

    model: ["Default Item 1", "Default Item 2", "Default Item 3", "Default Item 4"]

    background: Rectangle {
        color: "#626270"
        border.color: "#626270"
        border.width: _screen_tools.border_size
        radius: _screen_tools.radius
    }

    contentItem: Text {
        text: _custom_combobox.displayText
        font: _custom_combobox.font
        color: _screen_tools.default_text_color
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        rightPadding: _screen_tools.default_margin
    }

    popup: Popup {
        y: _custom_combobox.height
        width: _custom_combobox.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: _custom_combobox.popup.visible ? _custom_combobox.delegateModel : null
            currentIndex: _custom_combobox.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: _screen_tools.default_back_color
            radius: _screen_tools.radius
        }
    }

    onCurrentIndexChanged: {

    }
}
