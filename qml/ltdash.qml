import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import "uiComponents/"

Window {
    id: root
    width: layout.implicitWidth
    height: layout.implicitHeight
    visible: true

    // Center window
    x: (Screen.desktopAvailableWidth - width) / 2
    y: (Screen.desktopAvailableHeight - height) / 2

    property int navColWidth: 150
    property int navColItemHeight: 50
    property color navTextColor: "white"

    color: "#f1eeee"

    // Load some fonts
    FontLoader {
        id: cousineFont
        source: "uiComponents/Cousine-Regular.ttf"
    }
    FontLoader {
        id: cousineFontBold
        source: "uiComponents/Cousine-Bold.ttf"
    }

    function getSize() {
        return "0%";
    }


    RowLayout {
        id: layout
        anchors.fill: parent
        spacing: 0

        ColumnLayout {
            id: navColumn
            spacing: 0
            Rectangle {
                color: "#A48CD2"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: root.navColItemHeight + 20
                Layout.preferredWidth: root.navColWidth
                Rectangle {
                    id: logoDisk
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.horizontalCenterOffset: -30
                    width: 40
                    height: 40
                    color: "#fdfdfd"
                    gradient: Gradient {
                        GradientStop {
                            position: 0.00;
                            color: "#e9e4f1";
                        }
                        GradientStop {
                            position: 1.00;
                            color: "#fbe7fa";
                        }
                    }

                    radius: 20
                }

                Text {
                    id: prodName
                    anchors.left: logoDisk.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: logoDisk.verticalCenter
                    anchors.verticalCenterOffset: -5
                    text: "LTDASH"
                    font.family: cousineFontBold.name
                    font.bold: true
                    font.pixelSize: 15
                    color: "#f6f2fd"
                }
                Text {
                    id: revision
                    anchors.top: prodName.bottom
                    anchors.left: prodName.left
                    text: "DEV"
                    font.family: cousineFont.name
                    font.bold: true
                    font.pixelSize: 10
                    color: "lightgrey"
                }
            }

            Repeater {
                model: ["DASHBOARD", "PEERS"]
                NavButton {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumHeight: root.navColItemHeight
                    Layout.preferredWidth: root.navColWidth
                    navText: modelData
                    navFont: cousineFont.name
                }

            }
            Rectangle {
                id: progress
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "#2b2d39"
                Text {
                    id: progressPercentage
                    anchors.centerIn: parent
                    font.family: cousineFontBold.name
                    font.pixelSize: 30
                    font.bold: true
                    color: navTextColor
                    text: getSize()
                }
                Text {
                    id: completedText
                    anchors.horizontalCenter: progressPercentage.horizontalCenter
                    anchors.top: progressPercentage.bottom
                    font.family: cousineFont.name
                    font.pixelSize: 10
                    font.bold: true
                    color: "white"
                    text: "COMPLETED"
                }
            }

        }

        ColumnLayout {
            id: contentColumn
            spacing: 12
            SearchBar {
                id: searchBar
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: root.navColItemHeight + 20
                Layout.maximumHeight: root.navColItemHeight + 20
                Layout.minimumWidth: 650
                searchFont: cousineFontBold.name
                buttonHandler: argoContext
            }


            RowLayout {
                id: cardLayout
                spacing: 20
                anchors.left: searchBar.left
                anchors.right:searchBar.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                InfoCard {
                    id: topPeerCard
                    title: "TOP PEERS"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 300
                    cardModel: topPeersModel
                }

                InfoCard {
                    id: mainDownloadList
                    title: "TORRENT ACTIVITY"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 400
                    Layout.preferredHeight: 300
                    cardModel: downloadListModel

                }
            }


            Item {
                id: speedGraph
                Layout.fillWidth: true
                Layout.minimumWidth: 650
                Layout.preferredHeight: 200
                Rectangle {
                    color: "#666666"
                    anchors.fill: parent
                    height: 100
                }

            }



        }


    }

}
