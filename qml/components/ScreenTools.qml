import QtQuick
import QtQuick.Controls
import QtQuick.Window

Item {
    id: _screenTools

    /// main window settings
    property real _width: 1040
    property real _height: 540
    readonly property string default_window_back_color: "#222222"
    

    /// Widgets default settings
    property real default_widget_width: 120
    property real default_widget_height: 40
    property real default_widget_radius: 10
    property real default_widget_margin: 5
    property real default_widget_border_size: 2
    readonly property string default_widget_text_color: "#5c56c9"
    readonly property string default_widget_back_color: "#edebe9"
    readonly property string default_widget_border_color: "#5c56c9"
}
