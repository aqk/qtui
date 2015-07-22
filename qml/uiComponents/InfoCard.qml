import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {
    color: "#ffffff"
    radius: 4
    property string cardTitle
    property variant cardModel
    property string cardFont
    property string cardFontBold
    font.family: uiFontBold.name

    ColumnLayout {
        anchors.fill: parent
        spacing: 3
        Text {
            id: title
            text: cardTitle
            font.pixelSize: 13
            font.family: cardFontBold
            font.bold: true
            color: "#c1c1c1"
            Layout.preferredHeight: 15
            Layout.fillHeight: true
            Layout.maximumHeight: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.topMargin: 10

        }
        Rectangle {
            id: sep
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.top: title.bottom
            anchors.topMargin: 5
            height: 1.5
            radius: 1
            color: "#eaeaea"
        }

        Component {
                id: cardDelegate
                Item {
                    width: 180; height: 40
                    Row {
                        // Status
                        Column {
                           Rectangle {
                               id: statusButton
                               width: 60
                               height: 15
                               radius: 4
                               color: "#D0EAF3"
                               Text {
                                   text: "WAITING"
                                   color: "white"
                                   font.bold: true
                                   scale: 0.8
                                   font.family: uiFontBold.name
                                   anchors.centerIn: parent
                               }
                           }
                           Text {
                               text: Qt.formatDateTime(dateTimeAdded, "ddd dd")

                           }
                           Text {
                               text: Qt.formatDateTime(dateTimeAdded, "hh mm AP")

                           }
                        }

                        // Content
                        Column {
                            Text { text: name }
                            Text { text: bytesDownloaded }
                        }
                    }
                }
            }

        ListView {
            Layout.fillHeight: true
            Layout.preferredHeight: 300
            anchors.top: sep.bottom
            anchors.topMargin: 10
            anchors.left: sep.left
            anchors.right: sep.right
            model: cardModel
            delegate: cardDelegate
        }
    }
}

