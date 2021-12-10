//============
//Webpage Code
//============
String webpage2Code = R"***(
<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <title>Page Title</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>

    <style>
        *{margin:0; padding: 0;}

        body{
            background: rgb(240,240,240);
            background: linear-gradient(90deg, rgba(240,240,240,1) 0%, rgba(171,171,171,1) 100%);
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif ;
        }

        .top{
            background: linear-gradient(90deg, rgb(84, 0, 153) 0%, rgba(0,151,255,1) 100%);
            height: 150px;
        }

        .conttop{
            padding-top: 30px;
            width: 400px;
            margin-left: auto;
            margin-right: auto;
            align-items: center;
        }

        .conttop img{
            margin-left: 50px;
            padding-top: 15px;
            width: 300px;
            text-align: center;
        }

        h1{
            text-align: center;
            font-size: 24px;
            margin-top: 20px;
            margin-bottom: 20px;
            color: rgb(29, 19, 117);
        }

        h4{
            color: rgb(63, 63, 63);
        }

        h2{
            margin-left: 15PX;
        }

        h3{
            text-align: center;
            font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
            color: rgb(46, 79, 185);
        }

        hr{
            margin: 20px;
        }

        main{
            margin-left: auto;
            margin-right: auto;
            width: 360px;
            padding-left: 20px;
            padding-right: 20px;
        }

        h5{
            text-align: center;
            font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
        }

    </style>

</head>
<body onload="cargarnombre()">
    <div class="top">
        <div class="conttop">
            <a href="http://www.frn.utn.edu.ar/"><img src="https://i.ibb.co/6RTCp2m/LOGO2-blanco.png" alt=""></a>
        </div>
    </div>
    <main>
        <h1>DIPLOMATURA EN PROGRAMACIÓN APLICADA AL INTERNET DE LAS COSAS (IOT)</h1>
        <h3>Proyecto Grupo 3</h3>
        <hr>
        <h4>Id del dispositivo:</h4>
        <h2><span id="name">NOMBRE</span></h2>
        <br>
        <h4>Valor de la temperatura actual:</h4>
        <h2><span id="Tempe">0</span></h2>
        <br>
        <h4>Estado de la temperatura:</h4>
        <h2><span id="estado">ESTADO</span></h2>
        <hr>
        <br>
        <h5>ESP EN MODO STATION</h5>
    </main>
</body>

<script>
function cargarnombre() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("name").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/readname", true);
  xhttp.send();
}
</script>

<script>
var tempeShow;
setInterval(function ( )
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
    if (this.readyState == 4 && this.status == 200)
    {
        var x = (new Date()).getTime();
        x= x- 3*3600*1000; // para Argentina
        y = parseFloat(this.responseText);
        tempeShow=y;
        contador=contador+1;       
        if((contador==frecuencia) && (continuar==1))
        {    
            if(chartT.series[0].data.length > 100)
            {
              chartT.series[0].addPoint([x, y], true, true, true);
            }
            else
            {
              chartT.series[0].addPoint([x, y], true, false, true);
            }  
            contador=0;
        }
    }
    };
    xhttp.open("GET", "/readPOT", true);
    xhttp.send();
    document.getElementById("Tempe").innerHTML = tempeShow;
  
    

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200)
        {
        document.getElementById("estado").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "/readestado", true);
    xhttp.send();


}, 1000 );
</script>


</html>
)***";
