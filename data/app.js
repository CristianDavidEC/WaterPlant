setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperature").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
}, 300);


setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("humidity").innerHTML = this.responseText;
        };
        xhttp.open("GET", "/humidity", true);
        xhttp.send();
    }
}, 500);

setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("humidityeart").innerHTML = this.responseText;
            console.log(this.responseText);
        };
        xhttp.open("GET", "/humidityeart", true);
        xhttp.send();
    }
}, 1000);


/*setInterval(function () {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            if (this.responseText == "1") {
                document.getElementById("informacion").innerHTML = 
                `<h3> La planta necesita agua</h3>`;
            }
            else {
                document.getElementById("informacion").innerHTML =
                `<h3> La planta no necesita agua</h3>`;;
            }
        }
    };
    xhttp.open("GET", "/verificar", true);
    xhttp.send();
}, 1500);*/
