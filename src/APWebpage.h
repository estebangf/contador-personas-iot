String APWebpageCode = R"***(
<!DOCTYPE html>
<html lang="es">

<head>
  <title>Configuracion de Estacion</title>
  <meta charset="utf-8" />
  <meta name="viewport" content="initial-scale=1, width=device-width" />
</head>
<style>
  html {
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: center;
    background: blueviolet;
  }

  body{
    background-color: #fff;
    color: rgba(0, 0, 0, 0.87);
    -webkit-transition: box-shadow 300ms cubic-bezier(0.4, 0, 0.2, 1) 0ms;
    transition: box-shadow 300ms cubic-bezier(0.4, 0, 0.2, 1) 0ms;
    border-radius: 4px;
    box-shadow: 0px 2px 1px -1px rgb(0 0 0 / 20%), 0px 1px 1px 0px rgb(0 0 0 / 14%), 0px 1px 3px 0px rgb(0 0 0 / 12%);
    padding: 42px;
  }

  header {
    text-align: center;
  }

  label {
    color: #5b5b5b;
  }

  input {
    margin-top: 12px;
    margin-bottom: 12px;
    background-color: #ffffff;
    color: #000000;
    -moz-box-sizing: border-box;
    box-sizing: border-box;
    display: block;
    border: 1px solid #a2a9b1;
    border-radius: 2px;
    padding: 6px 8px;
    box-shadow: inset 0 0 0 1px transparent;
    font-family: inherit;
    font-size: inherit;
    line-height: 1.28571429em;
    width: 100%;
    vertical-align: middle;
  }

  button {
    margin-top: 32px;
    background-color: #3366cc;
    color: #fff;
    border-color: #3366cc;
    min-height: 32px;
    min-width: 4em;
    max-width: 28.75em;
    padding: 5px 12px;
    display: block;
    width: 100%;
    border: none;
  }
</style>

<body>
  <header>
    <h1>Access Point</h1>
    <h2>Configuracion de Wifi</h2>
  </header>
  <label>Usuario</label>
  <input id="ssid" type="text" placeholder="Ingresa el SSID" />
  <label>Usuario</label>
  <input id="password" type="password" placeholder="Ingresa el Password" />

  <button onclick="sendWifi()">Guardar WiFi</button>
  <script>
    function newParam(key, val) {
      return { key, val }
    }
    
    function sendWifi() {
      let ssid = document.getElementById("ssid").value
      let password = document.getElementById("password").value

      let baseURL = "setwifi";
      let params = [
        newParam("ssid", ssid),
        newParam("password", password)
      ];


      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
          const response = JSON.parse(this.responseText);
          console.log("RESPONSE => ", response);
          if (!!response.error) {
            alert(response.message)
          } else {
            alert(response.message)
          }
        }
      };
      let uri = baseURL + "?";
      params.forEach((param, index) => {
        if (index > 0) uri += "&"
        uri += `${param.key}=${param.val}`;
      });
      console.log("URI => ", uri)
      xhttp.open("GET", uri, true);
      xhttp.send();
    }
  </script>
</body>

</html>
)***";