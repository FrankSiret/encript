import QtQuick 2.11
import QtQuick.Controls 2.4
import "./qml"

ApplicationWindow {
    id: window
    visible: true
    width: 500
    height: 200
    title: qsTr("Encrypter Files")

    flags: Qt.MSWindowsFixedSizeDialogHint | Qt.FramelessWindowHint
    Bar { id: bar }
    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        anchors.topMargin: 40
        color: window.color
    }

    FontLoader { id: openSans; source: "qrc:/font/OpenSans-Regular.ttf" }

    Button {
        id: load
        text: "Select Folder"
        onClicked: {
            openFolder.show()
        }
    }

}
