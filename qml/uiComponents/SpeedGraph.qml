import QtQuick 2.0
import "../jbQuick/Charts"



Chart {
    property variant context
    chartOptions: {
                    'animationSteps': 100,
                    'bezierCurve': true,
                    'bezierCurveTension': 0.95,
                    'datasetFill': true,
                    'scaleGridLineColor': "rgba(0, 0, 0, 0.02)",
                    'scaleGridLineWidth': 1,
                    'pointDotRadius':2,
                    'pointDotStrokeWidth': 0,
                    'datasetStroke': false,
                    'scaleLabel':"<%= Number(value/1024).toFixed(1) + 'KB/s' %>"

    }

    property var graphDatapoint: 0;
    property var graphData: [0, 0, 0, 0, 0, 0, 0]
    function bytesReceived(bytes) {
        graphDatapoint = bytes;
        console.log("Received: Bytes:", bytes)
    }

    chartAnimated: true
    chartAnimationEasing: Easing.InOutElastic
    chartType: Charts.ChartType.LINE
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            if (graphDatapoint !== -1) {
                // take value
                var len = graphData.unshift(graphDatapoint);
                graphData.pop();
                // set value
                graphDatapoint = 0;
            }
            repaint();
        }
    }

    Component.onCompleted: {
        chartData = {
            labels: ["0s","-5s","-10s","-15s","-20s","-25s","-30s"],
            datasets: [{
                    fillColor: "rgba(63, 173, 190, 0.70)",
                    strokeColor: "rgba(138, 204, 214)",
                    pointColor: "rgba(120,120,120,1)",
                    pointStrokeColor: "#ffffff",
                    data: graphData

                }]
        }

    }
    Connections {
        target: context
        onBytesReceived: {
            bytesReceived(bytes);
        }
    }
}

