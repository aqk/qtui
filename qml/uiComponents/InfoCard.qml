import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "#ffffff"
    radius: 4
    property string title: "..."
    property variant cardModel
    ColumnLayout {
        anchors.fill: parent
        Text {
            text:title
            font.pixelSize: 12
            font.bold: true
            color: "#C1C1C1"
            Layout.preferredHeight: 15
            Layout.fillHeight: true
            Layout.maximumHeight: 15
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.topMargin: 10

        }
        Rectangle {
            id: sep
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: title.bottom
            anchors.topMargin:10
            height: 2
            radius: 2
            color: "#C1C1C1"
        }
        Component {
                id: cardDelegate
                Item {
                    width: 180; height: 40
                    Column {
                        Text { text: '<b>Name:</b> ' + name }
                        Text { text: '<b>Bytes DLed:</b> ' + downloadedBytes }
                    }
                }
            }

        ListView {
            Layout.fillHeight: true
            Layout.preferredHeight: 300
            model: cardModel
            delegate: cardDelegate
        }
    }
}

