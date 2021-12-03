/*
//============
//Webpage Code
//============
#define _GLIBCXX_USE_CXX11_ABI 0

#include <iostream>
#include <fstream>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostringstream;
using std::string;


string readFileIntoString(const string &path);

string readFileIntoString(const string &path)
{
  ifstream input_file(path);
  if (!input_file.is_open())
  {
    cerr << "Could not open the file - '"
         << path << "'" << endl;
    exit(EXIT_FAILURE);
  }
  return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>(input_file));
}

string filename("index.html");


String webpageCode = (String)(readFileIntoString(filename).c_str());
*/
//============
//Webpage Code
//============

String WebpageCode = R"***(
<!DOCTYPE HTML>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
   <title>Grafica con ESP32</title>
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <style>
    body {
      min-width: 310px;
      max-width: 1000px;
      height: 400px;
      margin: 0 auto;
      background-color: rgb(180, 205, 228);
    }
    h2 {
      font-family: Arial;
      font-size: 2.0rem;
      text-align: center;
    }

   #reloj
   {
     color:blue;
     text-align: right;
     font-size: 24px;
   }
   

.btn {
  border: none;
  background-color: inherit;
  padding: 14px 28px;
  font-size: 16px;
  cursor: pointer;
  display: inline-block;
}

.btn:hover {background: #eee;}

.limpiar {color: green;}
.parar {color: dodgerblue;}
.continuar {color: orange;}

    
  </style>
</head>
<body>
  <h2>Lectura de variables analogicas</h2>
    <button class="button" onclick="send(1)">LED ON</button>
  <button class="button" onclick="send(0)">LED OFF</button>
  <h2>LED State: <span id="stateLED">NA</span></h2>


  <span id="fecha" style="font-size:20px;"> </span>
  <span id="reloj" >                       </span>

  
  <div id="chart-air" class="container"> </div>

     <h2>
      Temperatura: <span style="color:green" id="Tempe">0</span> <span>&#176C</span>
      <label>   </label>
      <label id="activo" style="background-color:green; color:white" > ON </label>
    </h2>
   
    
      <label for="Tsamp">Tiempo entre puntos:</label>
      <select name="Tsamp" id="Tsamp" onchange="Sampling(this.value)" >
        <option value="1">1</option>
        <option value="5">5</option>
        <option value="10">10</option>
        <option value="30">30</option>
        <option value="60">60</option>
      </select>
      <label> Seg </label>



<button id="bc" class="btn limpiar" onclick="openFullscreen();">Pantalla Completa</button>
<button id="bp" class="btn parar">Parar</button>
<button id="bg" class="btn continuar">Continuar</button>



</body>



<script>



var elem = document.documentElement;
function openFullscreen() {
  if (elem.requestFullscreen) {
    elem.requestFullscreen();
  } else if (elem.webkitRequestFullscreen) { /* Safari 
    elem.webkitRequestFullscreen();
  } else if (elem.msRequestFullscreen) { /* IE11 
    elem.msRequestFullscreen();
  }
}




var mydate=new Date()
var year=mydate.getYear()
if (year < 1000)
year+=1900
var day=mydate.getDay()
var month=mydate.getMonth()
var daym=mydate.getDate()
if (daym<10)
daym="0"+daym
var dayarray=new Array("Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado")
var montharray=new Array("Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre",
"Octubre","Noviembre","Diciembre")
//document.write("<large><font color='0000FF' face='verdana'>"+dayarray[day]+" "+daym+" de "+montharray[month]+" de "+year+"</font></small>")
document.getElementById("fecha").innerHTML = "<large><font color='0000FF' face='verdana'>"+dayarray[day]+" "+daym+" de "+montharray[month]+" de "+year+"</font></small>";
</script>


<script>

     var continuar=1;
     var frecuencia=1;
     var contador=0;
         function Sampling(val) {
          //alert("el nuevo valor es : " + val);
          frecuencia=parseInt(val, 10); // seteo el nuevo intervalo de muestreo
           alert("El muestreo es: " + frecuencia.toString()+  " segundos");
          contador=0;
        }
   



var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-air' },
  title: { text: 'Monitor Temperatura' },
  series: [{
    showInLegend: false,
    data: []
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#059e8a' }
  },
  xAxis: { type: 'datetime',
    dateTimeLabelFormats: { second: '%H:%M:%S' }
  },
  yAxis: {
    title: { text: 'Conversion 12 bits' },
    max: 4096,
    min: 0
  },
  credits: { enabled: false }
});

 var tempeShow;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        var x = (new Date()).getTime();
         x= x- 3*3600*1000; // para Argentina
          y = parseFloat(this.responseText);
          tempeShow=y;
      contador=contador+1;       
      if((contador==frecuencia) && (continuar==1))
      {    
            if(chartT.series[0].data.length > 100) {
              chartT.series[0].addPoint([x, y], true, true, true);
            } else {
              chartT.series[0].addPoint([x, y], true, false, true);
            }  
            contador=0;
      }
      
    
  }
   };
  xhttp.open("GET", "/readPOT", true);
  xhttp.send();
  document.getElementById("Tempe").innerHTML = tempeShow;
  
 
  
}, 1000 );




    document.getElementById("bp").addEventListener("click", funcionStop);

    function funcionStop() {
        
         var activo = document.getElementById("activo");
        document.getElementById("activo").innerHTML = "OFF";
         activo.style.backgroundColor="red";   
        
         continuar=0;      
    }

    document.getElementById("bg").addEventListener("click", funcionContinuar);

    function funcionContinuar() {

        var activo = document.getElementById("activo");
        continuar=1;
        contador=0;
        document.getElementById("activo").innerHTML = "ON ";
        
        activo.style.backgroundColor="green";     
    }
    

   </script>
   

        <script type="text/javascript">
          function startTime(){
          today=new Date();
          h=today.getHours();
          m=today.getMinutes();
          s=today.getSeconds();
          m=checkTime(m);
          s=checkTime(s);
          document.getElementById('reloj').innerHTML=h+":"+m+":"+s;
          t=setTimeout('startTime()',500);}

          function checkTime(i)
          {if (i<10) {i="0" + i;}return i;}

          window.onload=function(){startTime();}
     </script>

     <script>
               function send(led_sts) 
                {
                  var xhttp = new XMLHttpRequest();
                  xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                      document.getElementById("stateLED").innerHTML = this.responseText;
                    }
                  };
                  xhttp.open("GET", "led_set?state="+led_sts, true);
                  xhttp.send();
              }

     </script>

     </html>
)***";