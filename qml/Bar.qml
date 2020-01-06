import QtQuick 2.11
import QtQuick.Controls 2.4

Rectangle {
    id: titleBar
    anchors.fill: parent
    color: "gray"
    border.color: "gray"
    border.width: 3

    Rectangle {
        width: parent.width + parent.height
        height: width
        rotation: 90
        anchors.centerIn: parent
        gradient: Gradient {
            GradientStop { position: 0.00000; color: "#00b000"; }
            GradientStop { position: 0.33333; color: "#4c83c3"; }
            GradientStop { position: 0.33334; color: "#fdbb30"; }
            GradientStop { position: 0.66667; color: "#fdbb30"; }
            GradientStop { position: 0.66668; color: "#b22c1b"; }
            GradientStop { position: 1.00000; color: "#b22c1b"; }
        }
    }

    MouseArea {
        anchors.fill: parent;
        property point lastMousePos: Qt.point(0, 0)
        onPressed: lastMousePos = Qt.point(mouse.x, mouse.y)
        onPositionChanged: {
            var delta = Qt.point(mouse.x - lastMousePos.x, mouse.y - lastMousePos.y)
            var new_x = window.x + delta.x
            var new_y = window.y + delta.y
            var posMouse = Qt.point(window.x + mouse.x, window.y + mouse.y)
            if (posMouse.x <= 0 && posMouse.y <= 0) {
                window.visibility = ApplicationWindow.Maximized
                window.width = window.screen.width / 2
                window.height = window.screen.height / 2
                window.update()
            }
            else if (posMouse.x + 1 >= window.screen.width && posMouse.y <= 0) {
                window.visibility = ApplicationWindow.Maximized
                window.x = window.screen.width / 2
                window.width = window.screen.width / 2
                window.height = window.screen.height / 2
                window.update()
            }
            else if (posMouse.x <= 0) {
                window.visibility = ApplicationWindow.Maximized
                window.width = window.screen.width / 2
                window.update()
            }
            else if (posMouse.x + 1 >= window.screen.width) {
                window.visibility = ApplicationWindow.Maximized
                window.x = window.screen.width / 2
                window.width = window.screen.width / 2
                window.update()
            }
            else if (posMouse.y <= 0) {
                window.visibility = ApplicationWindow.Maximized
                window.update()
            }
            else
            {
                if (window.visibility === ApplicationWindow.Maximized)
                    window.visibility = ApplicationWindow.Windowed
                window.x = new_x
                window.y = new_y
            }
        }
    }

    AbstractButton {
        id: closeButton
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        height: 36
        width: 36
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            Label {
                text: "X"
                fontSizeMode: Text.FixedSize
                font.pixelSize: 29
                font.family: "Arial Rounded MT Bold"
                color: "#ed0d0d"
                anchors.centerIn: parent
            }
        }
        MouseArea {
            anchors.fill: closeButton
            onClicked: Qt.quit()
        }
    }
}
