import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Rectangle {
    color: "#ffffff"
    id: searchBar
    property variant buttonHandler
    property string defaultText: ""
    property color barColor: "grey"

    RowLayout {
        spacing: 10
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        Column {
            id: tripleBars
            spacing: 2
            Repeater {
                model: 3
                delegate: Component {
                    Rectangle {
                        width: 10
                        height: 3
                        radius: 1
                        color: barColor
                    }
                }
            }
        }
        MouseArea {
            id: tripleBarsMouseArea
            hoverEnabled: true
            anchors.fill: tripleBars
        }
        states: State {
            name: "hover"; when: tripleBarsMouseArea.containsMouse;
            PropertyChanges {target: searchBar; barColor:"black"; }
        }
        transitions: Transition {
            ColorAnimation { target: searchBar; properties: "barColor"; easing.type: Easing.InOutQuad; duration: 500}
        }

        TextInput {
            id: textInput
            color: "#323542"
            Layout.fillWidth: true
            Layout.preferredWidth: 400
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 20
            text: defaultText
            clip:true
            cursorVisible: true

        }
        Rectangle {
            id: loadButton
            anchors.verticalCenter: parent.verticalCenter
            Layout.preferredWidth: 70
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            color: "#333643"
            radius: 3
            ColorAnimation on color {
                duration: 3000
            }

            UIText {
                id: loadTorrentText
                color: "#FDFDFD"
                anchors.centerIn: parent
                text: "ADD TORRENT"
                font.bold: true
                font.pixelSize: 10
            }
            MouseArea {
                id: mouseArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    // Launch the file selection dialog
                    fileDialog.visible = true
                }
            }

            FileDialog {
                id: fileDialog
                title: "Select a torrent"
                folder: "."
                onAccepted: {
                    var path = fileDialog.fileUrl.toString()
                    // remove prefixed "file:///"
                    path = path.replace(/^(file:\/{3})/, "")
                    // Call into the C++ side
                    buttonHandler.loadTorrentClicked(path)
                }
            }

            states: State {
               name: "hovered"; when: mouseArea.containsMouse
               PropertyChanges { target: loadButton; color: "#636363" }
               PropertyChanges { target: loadTorrentText; color: "#ffffff" }
            }
            transitions: [
                Transition {
                ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 700; target: loadTorrentText }
            }, Transition {
                ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 2000; target: loadButton }
            }]

        }
    }
}

