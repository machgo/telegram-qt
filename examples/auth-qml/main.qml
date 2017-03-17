import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Flickable {
        id: view
        anchors.fill: parent
        anchors.margins: 20
        Column {
            width: window.width - view.anchors.margins * 2
            TelegramAddAccount {
            }
        }
    }

}
