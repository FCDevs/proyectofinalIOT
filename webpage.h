//============
//Webpage Code
//============
String webpageCode = R"***(
<!DOCTYPE html>
<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <title>Page Title</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>

    <style>
        *{margin:0; padding: 0;}

        #LOGO{
            color: white;
            font-size: 50px;
        }

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
            text-align: center;
        }

        .formulario{
            margin-top: 20px;
            
            font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
            padding: 5px;
            text-align: center;
        }

        .formulario p{
            font-weight: bold;
            color: rgb(49, 49, 49);
            font-size: smaller;
        }

        .button {
            
            background-color: #4a2ec7;
            border: none;
            color: white;
            padding: 10px 15px;
            text-align: center;
            text-decoration: none;
            font-size: 16px;   
            cursor: pointer;
            -webkit-transition-duration: 0.4s;
            transition-duration: 0.4s;
            border-radius: 18px;

        }

        .button2:hover {
             box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24),0 17px 50px 0 rgba(0,0,0,0.19);
        }

        h5{
            text-align: center;
            font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
        }

    </style>

</head>
<body>
    <div class="top">
        <div class="conttop">
            <h1 id="LOGO"> UTN FRN</h1>
        </div>
    </div>
    <main>
        <h1>DIPLOMATURA EN PROGRAMACI??N APLICADA AL INTERNET DE LAS COSAS (IOT)</h1>
        <h3>Proyecto Grupo 3</h3>
        <hr>
        <form action="/get">
        <p style="text-align: center;"> <B>Parametros conexion WIFI</B> </p>
        <div class="formulario" >
            <p>SSID de Wifi</p>
            <input name="ssid" type="text" placeholder="Usuario">
        </div>
        <div class="formulario">
            <p>Contrase??a</p>
            <input name="pass" type="text" placeholder="Contrase??a de wifi">
        </div>
        <br>
        <p style="text-align: center;"> <B>Parametros conexion MQTT</B> </p>
        <div class="formulario">
            <p>ID del dispositivo</p>
            <input name="iddispositivo" type="text" placeholder="ESP 4">
        </div>
        <div class="formulario">
            <p>IP del servidor</p>
            <input name="ipserver" type="text" placeholder="XXX.XXX.XXX.XXX">
        </div>
        <br>
        <button type="submit" class="button" value="Submit"><B>ACEPTAR</B></button>
        </form>
        <hr>
        <h5>ESP EN MODO ACCES POINT</h5>
        <br>
    </main>
</body>

</html>
)***";
