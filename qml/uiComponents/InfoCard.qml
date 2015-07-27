import QtQuick 2.0
import QtQuick.Layouts 1.1


Rectangle {
    color: "#ffffff"
    radius: 2
    property string cardTitle
    property variant cardModel
    property int itemHeight: 65
    property color separatorColor: "#eaeaea"

    ColumnLayout {
        anchors.fill: parent
        spacing: 3
        UIText {
            id: title
            text: cardTitle
            font.pixelSize: 12
            color: "#c1c1c1"
            Layout.preferredHeight: 15
            Layout.fillHeight: true
            Layout.maximumHeight: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.topMargin: 20

        }
        Rectangle {
            id: sep
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            anchors.top: title.bottom
            anchors.topMargin: 5
            height: 1
            radius: 1
            color: separatorColor
        }

        Component {
            id: cardDelegate
            Item {
                id: listItem
                anchors.left: parent.left
                anchors.right: parent.right
                height: itemHeight

                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    spacing: 5
                    // Status
                    ColumnLayout {
                        id: statusColumn
                        Rectangle {
                            id: statusButton
                            width: 60
                            height: 20
                            radius: 2
                            color: "#2bcaff"
                            UIText {
                                text: status
                                color: "white"
                                font.bold: true
                                font.pixelSize: 10
                                anchors.centerIn: parent
                            }
                        }
                        UIText {
                            text: Qt.formatDateTime(dateTimeAdded, "ddd dd")
                            font.pixelSize: 10
                            anchors.left: statusButton.left
                            anchors.leftMargin: 3
                            color: "#bababa"
                        }
                        UIText {
                            text: Qt.formatDateTime(dateTimeAdded, "hh:mm AP")
                            font.pixelSize: 10
                            anchors.left: statusButton.left
                            anchors.leftMargin: 3
                            color: "#bababa"
                        }
                    }
                    // Vertical separator
                    Rectangle {
                        width: 1
                        height: itemHeight
                        color: separatorColor
                    }

                    // Content
                    RowLayout {
                        id: contentColumn
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.preferredHeight: itemHeight
                            Layout.preferredWidth: 200
                            Layout.minimumWidth: 100
                            UIText {
                                text: name
                                clip: true
                                color: "#3a3a3a"
                                font.pixelSize: 16
                                anchors.left: parent.left
                                anchors.leftMargin: 5
                                anchors.top: parent.top
                                anchors.topMargin: 10
                            }
                        }
                        DLProgressBar {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Layout.minimumWidth: 50
                            Layout.preferredWidth: 250
                            Layout.preferredHeight: itemHeight
                            anchors.right: parent.right
                            total: totalBytes
                            completed: bytesDownloaded
                            pbWidth: 250
                            anchors.top: parent.top
                            anchors.topMargin: 10
                        }

                    }
                }

                // Horiz separator
                Rectangle {
                    anchors.left: parent.left
                    anchors.right: parent.right

                    color: separatorColor
                    height: 1
                    visible: index !== 0 ? true : false
                }

                MouseArea {
                    anchors.fill:parent
                    onClicked: listItem.ListView.view.currentIndex = index
                }
            }

        }


        Component {
            id: highlightItem
            Rectangle {
                width: listView.currentItem.width
                height: 2
                z: 4
                color: "#88eaff"
                // Set highlight bar at the bottom
                y: listView.currentItem.y + listView.currentItem.height
                Behavior on y { SpringAnimation { spring: 2; damping: 0.1} }
            }
        }

        ListView {
            id: listView
            Layout.fillHeight: true
            Layout.preferredHeight: 300
            anchors.top: sep.bottom
            anchors.topMargin: 10
            anchors.left: sep.left
            anchors.right: sep.right
            model: cardModel
            delegate: cardDelegate
            highlight: highlightItem
            highlightFollowsCurrentItem: false
            focus: true
        }


    }
    Rectangle {
        z: -1
        x: -1
        radius: 2
        color: "#e0e0e0"
        opacity: 0.3
        width: parent.width + 2
        height: parent.height + 1
    }


}

