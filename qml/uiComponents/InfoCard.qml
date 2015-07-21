import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "#ffffff"
    radius: 4
    property string title: "..."
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

        ListView {
            Layout.fillHeight: true
            Layout.preferredHeight: 300
            model: ListModel {}
        }
    }
}

