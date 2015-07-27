import QtQuick 2.0

Rectangle {
    color: (mouseArea.containsMouse || selected )? navButtonColorHover : navButtonColorUnselected
    property string navText: "..."
    property color navButtonColorUnselected: "#323542"
    property color navButtonColorSelected: "#1E202B"
    property color navButtonColorHover: "#262833"
    property bool selected: false
    signal buttonClicked

    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30
        anchors.verticalCenter:  parent.verticalCenter
        Rectangle {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
            width: 7
            height: 8
            radius:2
            color: "#989BA2"
        }

        UIText {
            id: text
            text: navText
            anchors.verticalCenter: icon.anchors.verticalCenter
            anchors.left: icon.right
            anchors.leftMargin: 3
            font.pixelSize:12
            font.bold: true
            color: "#989BA2"
        }
    }


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            color: navButtonColorSelected
            buttonClicked();
        }
    }

    states: State {
       name: "hovered"; when: mouseArea.containsMouse || selected
       PropertyChanges { target: icon; color: "#59ACBF" }
       PropertyChanges { target: text; color: "#ffffff" }
    }

    transitions: Transition {
        ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 600; target: icon }
        ColorAnimation { properties: "color"; easing.type: Easing.InOutQuad; duration: 700; target: text }
        ColorAnimation { properties: "color"; easing.type: Easing.InOutBounce; duration: 500; target: parent }
    }

}
