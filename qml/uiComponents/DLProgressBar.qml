import QtQuick 2.4
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0


Item {
    id: progressBar
    property real progress: 0
    property int pbHeight: 8
    property int pbWidth: 70

    property int total
    property int completed
    property var completedString: completed
    property var totalString: total
    property var separatorString: "/"

    Rectangle {
        id: progressBG
        color: "#eeeded"
        width: progressBar.pbWidth
        height: progressBar.pbHeight + 2.5
        radius: 2
        z: 0
    }
    Rectangle {
        id: progressFG
        color: "#59bf99"
        y: 1
        z: 2
        height: progressBar.pbHeight
        width: 0
        radius: 2

    }
    Rectangle {
        id: progress2
        color: Qt.lighter(progressFG.color, 1.25)

        x: 1
        y: 2
        z: 1
        height: progressBar.pbHeight
        width: progressFG.width
        radius: 2
    }

    Text {
        id: totalText
        text: progressBar.totalString
        font.pixelSize: 9
        anchors.top: progressBG.bottom
        anchors.right: progressBG.right

    }

    Text {
        id: separator
        text: separatorString
        font.pixelSize: 9
        anchors.top: progressBG.bottom
        anchors.right: totalText.left
    }

    Text {
        id: completedText
        text: progressBar.completedString
        font.pixelSize: 9
        anchors.top: progressBG.bottom
        anchors.right: separator.left
        anchors.rightMargin: 2
        anchors.verticalCenter: totalText.verticalCenter
        color: "black"
    }


    onCompletedChanged:   {
        // Update progress bar
        progressFG.width = Qt.binding(function() { return updateProgressBar()})
        completedString = formatBytes(completed)
        totalString = formatBytes(total)
        separatorString = "/"
    }

    function formatBytes(bytes) {
        return bytes/(1024 * 1024) + "MB"
    }

    function updateProgressBar() {
        var clamp = function(v, l, h) {
            return Math.max(l, Math.min(v, h))
        }
        return clamp((this.completed/this.total)*progressBar.pbWidth, 0, progressBar.pbWidth)
    }
    Component.onCompleted: {
        total = 100
        completedString = ""
        totalString = ""
        separatorString =""
    }
}





