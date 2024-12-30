import QtQuick
import QtQuick.Controls
import QtQuick.Window

Item {
    id: _screenTools

    //-- The point and pixel font size values are computed at runtime

    property real defaultFontPointSize:     10
    property real platformFontPointSize:    10

    /// You can use this property to position ui elements in a screen resolution independent manner. Using fixed positioning values should not
    /// be done. All positioning should be done using anchors or a ratio of the defaultFontPixelHeight and defaultFontPixelWidth values. This way
    /// your ui elements will reposition themselves appropriately on varying screen sizes and resolutions.
    property real defaultFontPixelHeight:   10

    /// You can use this property to position ui elements in a screen resolution independent manner. Using fixed positioning values should not
    /// be done. All positioning should be done using anchors or a ratio of the defaultFontPixelHeight and defaultFontPixelWidth values. This way
    /// your ui elements will reposition themselves appropriately on varying screen sizes and resolutions.
    property real defaultFontPixelWidth:    10

    /// QFontMetrics::descent for default font at default point size
    property real defaultFontDescent:       0

    /// The default amount of space in between controls in a dialog
    property real defaultDialogControlSpacing: defaultFontPixelHeight / 2

    property real smallFontPointSize:       10
    property real mediumFontPointSize:      10
    property real largeFontPointSize:       10

    property real toolbarHeight:            50

    readonly property real smallFontPointRatio:      0.75
    readonly property real mediumFontPointRatio:     1.25
    readonly property real largeFontPointRatio:      1.5

    readonly property real minTouchMillimeters:     10      ///< Minimum touch size in millimeters
    property real minTouchPixels:                   0       ///< Minimum touch size in pixels

    property real implicitButtonWidth:              Math.round(defaultFontPixelWidth *  5.0)
    property real implicitButtonHeight:             Math.round(defaultFontPixelHeight * 1.6)

    property real radius:                       10
    property real border_size:                  5
    property real default_margin:               5
    property real default_label_width:          120
    property real default_label_height:         40
    readonly property string label_text_color:  "white"
    readonly property string label_back_color:  "#354956"
}
