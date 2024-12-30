import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    Layout.preferredWidth: 200
    Layout.preferredHeight: 50
    
    background: Rectangle {
        color: parent.down ? "#d0d0d0" : "#f0f0f0"
        border.color: "#808080"
        border.width: 1
        radius: 5
    }
}