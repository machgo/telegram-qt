import QtQuick 2.5
import QtQuick.Controls 2.0

import TelegramQtTheme 1.0

TextField {
    id: textField
    property bool errorHighlight: false
    selectByMouse: true
    property string label
    property string iconSource: ""
    background: Rectangle {
        color: "transparent"
        border.color: textField.errorHighlight ? "#ff0000" : "#bdbebf"
    }

    Row {
        visible: iconSource
        anchors {
            right: parent.right
            rightMargin: 6
            verticalCenter: parent.verticalCenter
        }

        Image {
            id: applyButton
            source: iconSource
            height: Math.min(textField.height * 0.8, Theme.iconSizeSmall)
            width: height
            opacity: textField.errorHighlight ? 0 : 1
            visible: opacity > 0
            Behavior on opacity {
                NumberAnimation {
                    duration: Theme.longDuration
                    easing.type: Easing.InOutQuad
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: textField.accepted()
            }
        }
    }
}
