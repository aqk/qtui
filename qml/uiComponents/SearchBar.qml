import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "#ffffff"
    property string searchFont: ""

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
            Rectangle {
                width: 19
                height: 5
                radius: 2
                color: "#E8E8E8"
             }
            }
        }

        TextInput {
            id: textInput
            color: "#323542"
            Layout.fillWidth: true
            Layout.preferredWidth: 400
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 20
            font.bold: true
            font.family: searchFont
            text: "Filter ..."
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
            Text {
                color: "#FDFDFD"
                anchors.centerIn: parent
                text: "LOAD TORRENT"
                font.family: searchFont
                font.bold: true
                font.pixelSize: 10
            }
        }
    }
}

