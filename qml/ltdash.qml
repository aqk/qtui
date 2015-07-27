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

    property bool mainView:true

    color: "#f1eeee"


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

                UIText {
                    id: prodName
                    anchors.left: logoDisk.right
                    anchors.leftMargin: 10
                    anchors.verticalCenter: logoDisk.verticalCenter
                    anchors.verticalCenterOffset: -5
                    text: "LTDASH"
                    font.bold: true
                    font.pixelSize: 15
                    color: "#f6f2fd"
                }
                UIText {
                    id: revision
                    anchors.top: prodName.bottom
                    anchors.left: prodName.left
                    text: "DEV"
                    font.bold: true
                    font.pixelSize: 10
                    color: "lightgrey"
                }
            }


            NavButton {
                id:navBtnDash
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: root.navColItemHeight
                Layout.preferredWidth: root.navColWidth
                navText: "DASHBOARD"
                selected: mainView
                onButtonClicked: {
                    mainView = true;
                    topPeerCard.visible = false;
                    mainDownloadList.visible = true;
               }
            }

            NavButton {
                id: navBtnPeers
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: root.navColItemHeight
                Layout.preferredWidth: root.navColWidth
                navText: "PEERS"
                selected: !mainView
                onButtonClicked: {
                    mainView = false;
                    topPeerCard.visible = true;
                    mainDownloadList.visible = false;

                }
            }

            Rectangle {
                id: progress
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "#2b2d39"
                UIText {
                    id: progressPercentage
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    font.bold: true
                    color: navTextColor
                    text: getSize()
                }
                UIText {
                    id: completedText
                    anchors.horizontalCenter: progressPercentage.horizontalCenter
                    anchors.top: progressPercentage.bottom
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
                buttonHandler: argoContext
                defaultText: "FILTER ..."
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
                    cardTitle: "TOP PEERS"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 300
                    cardModel: topPeersModel
                    visible: false
                }

                InfoCard {
                    id: mainDownloadList
                    cardTitle: "TORRENT ACTIVITY"
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 400
                    Layout.preferredHeight: 300
                    cardModel: downloadListModel
                    visible:true
                }

                Component.onCompleted: state = "visible"
                states: State {
                   name: "visible"
                   PropertyChanges { target: cardLayout; x: 100 }
                }

                transitions: Transition {
                    PropertyAnimation { duration: 3000; easing.type: Easing.InOutQuad}
                }
            }


            SpeedGraph {
                id: speedGraph
                Layout.fillWidth: true
                Layout.minimumWidth: 650
                Layout.preferredHeight: 200
                context: argoContext
            }



        }


    }
}
