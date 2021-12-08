//============
//Webpage Code
//============
String webpageCode = R"***(
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

        input{
            margin-left: 15PX;
            margin-top: 10px;
            width: 70px;
            height: 25px;
        }

    </style>

</head>
<body>
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
        <h2>NOMBRE</h2>
        <br>
        <h4>Valor de la temperatura actual:</h4>
        <h2>VALOR</h2>
        <br>
        <h4>Encender LED</h4>
        <input type="button" value="ON">
        <br><hr>
    </main>
</body>
</html>
)***";