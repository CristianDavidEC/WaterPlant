import {chartT} from './chart';

setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperature").innerHTML = this.responseText;
            var x = (new Date()).getTime(),
                y = parseFloat(this.responseText);

            if (chartT.series[0].data.length > 40) {
                chartT.series[0].addPoint([x, y], true, true, true);
            } else {
                chartT.series[0].addPoint([x, y], true, false, true);
            }
        }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
}, 1000);

/*var chartH = new Highcharts.Chart({
    chart: { renderTo: 'chart-humidity' },
    title: { text: 'BME280 Humidity' },
    series: [{
        showInLegend: false,
        data: []
    }],
    plotOptions: {
        line: {
            animation: false,
            dataLabels: { enabled: true }
        }
    },
    xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
        title: { text: 'Humidity (%)' }
    },
    credits: { enabled: false }
});*/

setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("humidity").innerHTML = this.responseText;
            var x = (new Date()).getTime(),
                y = parseFloat(this.responseText);
            
            if (chartH.series[0].data.length > 40) {
                chartH.series[0].addPoint([x, y], true, true, true);
            } else {
                chartH.series[0].addPoint([x, y], true, false, true);
            }
        };
        xhttp.open("GET", "/humidity", true);
        xhttp.send();
    }
}, 1000);

/**
 * Mide la humedad en tierra
 */
setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("humidityeart").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/humidityeart", true);
    xhttp.send();
}, 1000);

/**
 * Verifica los valores de humedad y temperatura si 
 * se encunetran en tre los rangos, de lo contrario renderiza 
 * un elemento que indica que hay que aplicarle agua a la planta
 */
setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == "1") {
                console.log("1, hechele agua");
            }
            else {
                console.log("0, no hechele agua");
            }
        }
    };
    xhttp.open("GET", "/verificar", true);
    xhttp.send();
}, 1000);