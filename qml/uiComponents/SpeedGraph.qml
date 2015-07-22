import QtQuick 2.0
import "../jbQuick/Charts"

Chart {
    chartOptions: {
                    'bezierCurve': true,
                    'bezierCurveTension': 0.95,
                    'datasetFill': true,
                    'scaleGridLineColor': "rgba(0, 0, 0, 0.02)",
                    'scaleGridLineWidth': 1,
                    'pointDotRadius':2,
                    'pointDotStrokeWidth': 0,
                    'datasetStroke': false
    }
    chartAnimated: true
    chartAnimationEasing: Easing.InOutElastic
    chartType: Charts.ChartType.LINE
    Component.onCompleted: {
        chartData = {
            labels: ["January","February","March","April","May","June","July"],
            datasets: [{
                    fillColor: "rgba(220,220,220,0.98)",
                    strokeColor: "rgba(220,220,220,1)",
                    pointColor: "rgba(120,120,120,1)",
                    pointStrokeColor: "#ffffff",
                    data: [65,59,90,81,56,55,40],

                }, {
                    fillColor: "rgba(151,187,205,0.98)",
                    strokeColor: "rgba(151,187,205,1)",
                    pointColor: "rgba(151,187,205,1)",
                    pointStrokeColor: "#ffffff",
                    data: [28,48,40,19,96,27,100]
                }]
        }
    }

}

