import QtQuick 2.0

Rectangle {
    color: mouseArea.containsMouse ? navButtonColorHover : navButtonColorUnselected
    property string navText: "..."
    property string navFont: Arial
    property color navButtonColorUnselected: "#323542"
    property color navButtonColorSelected: "#1E202B"
    property color navButtonColorHover: "#262833"
    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30
        anchors.verticalCenter:  parent.verticalCenter
        Rectangle {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -1
            width: 7
            height: 8
            radius:2
            color: "#989BA2"
        }

        Text {
            id: text
            text: navText
            anchors.verticalCenter: icon.anchors.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 3
            font.pixelSize:12
            font.bold: true
            font.family: navFont
            color: "#989BA2"
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            color: navButtonColorSelected
        }
    }


    states: State {
       name: "hovered"; when: mouseArea.containsMouse
       PropertyChanges { target: icon; color: "#59ACBF" }
       PropertyChanges { target: text; color: "#ffffff" }
    }

    transitions: Transition {
        ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 300; target: icon }
        ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 300; target: text }

    }

}
