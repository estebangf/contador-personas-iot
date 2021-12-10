String WebpageCode = R"***(
<!DOCTYPE html>
<html lang="es">

<head>
  <title>Configuracion de Estacionamiento</title>
  <meta charset="utf-8" />
  <meta name="viewport" content="initial-scale=1, width=device-width" />
  <script src="https://unpkg.com/react@latest/umd/react.production.min.js" crossorigin="anonymous"></script>
  <script src="https://unpkg.com/react-dom@latest/umd/react-dom.production.min.js"></script>
  <script src="https://unpkg.com/@mui/material@latest/umd/material-ui.production.min.js"
    crossorigin="anonymous"></script>
  <script src="https://unpkg.com/babel-standalone@latest/babel.min.js" crossorigin="anonymous"></script>
  <!-- Fonts to support Material Design -->
  <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700&display=swap" />
  <!-- Icons to support Material Design -->
  <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons" />
</head>
<style>
  html {
    height: 100%;
  }

  body {
    /* height: 100%; */
    padding: 50px 5px;
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: center;
    background-image: url(https://drive.google.com/uc?export=view&id=1YYG90Hlv2h17WDtnORxy72zzb1rwD2To);
    /* background: url("https://images.idgesg.net/images/article/2017/09/wireless_mobile_network_iot_internet_of_things_edge_computing_thinkstock_613880046_3x2_1200x800-100736484-large.jpg?auto=webp&quality=85,70"); */
    background-size: cover;
  }

  .ToHome {
    top: 24px;
    color: #9360ff;
    display: flex;
    flex-direction: column;
    align-items: center;
    cursor: pointer;
    width: fit-content;
    margin: auto;
  }

  .Settings {
    padding: 32px;
    background-size: contain;
    padding-top: 100px;
    padding-bottom: 12px;
    background-repeat: no-repeat;
    text-align: center;
    cursor: pointer;
  }

  .Broker {
    background-image: url(https://drive.google.com/uc?export=view&id=1bHwtofKMUy_BnAD2PiocInSRbDOzSWKy);
    /* background-image: url(https://iotechonline.com/wp-content/uploads/2021/01/mosquitto.webp); */
  }

  .WiFi {
    background-image: url(https://drive.google.com/uc?export=view&id=18dUrKcivXyiFDzclSiV8R_0eZ2exj7Q9);
    /* background-image: url(https://ak.picdn.net/shutterstock/videos/26317781/thumb/10.jpg); */
  }

  .Estacion {
    background-image: url(https://drive.google.com/uc?export=view&id=1U81DOTpaEL3zFCqWPN1mMJE8Ed7p6gkD);
    /* background-image: url(https://ak.picdn.net/shutterstock/videos/26317781/thumb/10.jpg); */
  }
</style>

<body>
  <div id="root"></div>
  <script type="text/babel">

    const rootElement = document.getElementById('root')

    const {
      colors,
      CssBaseline,
      ThemeProvider,
      Typography,
      Button,
      Container,
      createTheme,
      Box,
      SvgIcon,
      Link,
      TextField,
      Stack,
      Paper,
      Grid,
      FormControl,
      InputLabel,
      Select,
      MenuItem
    } = MaterialUI;
    const {
      useState,
      useEffect
    } = React;



    function newParam(key, val) {
      return { key, val }
    }

    function sendToServer(baseURL, params) {
      return new Promise((resolve, reject) => {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState === XMLHttpRequest.DONE && this.status === 200) {
            const response = JSON.parse(this.responseText);
            console.log("RESPONSE => ", response);
            if (!!response.error) {
              reject(response)
            } else {
              resolve(response)
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
      })
    }


    // Create a theme instance.
    const theme = createTheme({
      palette: {
        primary: {
          main: "#556cd6"
        },
        secondary: {
          main: "#19857b"
        },
        error: {
          main: colors.red.A400
        }
      }
    });


    function LightBulbIcon(props) {
      return (
        <SvgIcon {...props}>
          <path d="M9 21c0 .55.45 1 1 1h4c.55 0 1-.45 1-1v-1H9v1zm3-19C8.14 2 5 5.14 5 9c0 2.38 1.19 4.47 3 5.74V17c0 .55.45 1 1 1h6c.55 0 1-.45 1-1v-2.26c1.81-1.27 3-3.36 3-5.74 0-3.86-3.14-7-7-7zm2.85 11.1l-.85.6V16h-4v-2.3l-.85-.6C7.8 12.16 7 10.63 7 9c0-2.76 2.24-5 5-5s5 2.24 5 5c0 1.63-.8 3.16-2.15 4.1z" />
        </SvgIcon>
      );
    }

    function ProTip() {
      return (
        <Typography sx={{ mt: 6, mb: 3 }} color="text.secondary">
          <LightBulbIcon sx={{ mr: 1, verticalAlign: "top" }} />
          Nota: revisar en {" "}
          <Link target="_blank" href="https://github.com/estebangf/contador-personas-iot">
            GitHub
          </Link>{" "}
          para mas información.
        </Typography>
      );
    }

    function Copyright() {
      return (
        <Typography variant="body2" color="text.secondary" align="center">
          {"Copyright © "}
          <Link target="_blank" color="inherit" href="https://github.com/estebangf/contador-personas-iot/src/index.html">
            Proyecto IOT
          </Link>{" "}
          {new Date().getFullYear()}
          {"."}
        </Typography>
      );
    }


    function Login(props) {
      const [username, setUsername] = useState('');
      const [password, setPassword] = useState('');


      function iniciarSesion() {
        let baseURL = "login";
        let params = [
          newParam("username", username),
          newParam("password", password)
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          props.setPage("home")
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }


      return (
        <Stack
          component="form"
          noValidate
          autoComplete="off"
          spacing={2}
          sx={{ my: 4 }}>
          <Typography variant="h4" component="h1" gutterBottom>
            Login
          </Typography>
          <TextField label="Usuario" variant="outlined" fullWidth value={username} onChange={e => setUsername(e.target.value)} />
          <TextField type="password" label="Contraseña" variant="outlined" fullWidth value={password} onChange={e => setPassword(e.target.value)} />
          <Button onClick={e => iniciarSesion()}>Iniciar Sesion</Button>
        </Stack>
      )
    }



    function Home(props) {
      function cerrarSesion() {
        props.setPage("login")
      }


      return (
        <Stack
          component="form"
          noValidate
          autoComplete="off"
          spacing={2}
          sx={{ my: 4 }}>
          <Typography variant="h4" component="h1" gutterBottom>
            Bienvenid@!!
          </Typography>
          <p>¿Qué desea configurar?</p>
          <Grid container spacing={2} sx={{ width: "calc(100% - 16px)" }}>
            <Grid item xs={6}>
              <Paper onClick={e => props.setPage("estacion")} className="Settings Estacion">
                Estacion
              </Paper>
            </Grid>
            <Grid item xs={6}>
              <Paper onClick={e => props.setPage("broker")} className="Settings Broker">
                Broker
              </Paper>
            </Grid>
            <Grid item xs={6}>
              <Paper onClick={e => props.setPage("wifi")} className="Settings WiFi">
                WiFi
              </Paper>
            </Grid>
          </Grid>
          <Button color="error" onClick={e => cerrarSesion()}>Cerrar Sesion</Button>
        </Stack>
      )
    }


    function WiFi(props) {
      const [ssid, setSsid] = useState('');
      const [password, setPassword] = useState('');

      function sendWiFi() {
        let baseURL = "setwifi";
        let params = [
          newParam("ssid", ssid),
          newParam("password", password)
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          props.setPage("home")
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }

      useEffect(() => {
        let baseURL = "getconfigs";
        let params = [
          newParam("section", "wifi"),
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          setSsid(r.configs.ssid)
          setPassword(r.configs.password)
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }, [])
      return (
        <Stack
          component="form"
          noValidate
          autoComplete="off"
          spacing={2}
          sx={{ my: 4 }}>
          <Typography variant="h4" component="h1" gutterBottom>
            Configuración del WiFi
          </Typography>
          <TextField label="SSID" variant="outlined" fullWidth value={ssid} onChange={e => setSsid(e.target.value)} />
          <TextField type="password" label="Contraseña" variant="outlined" fullWidth value={password} onChange={e => setPassword(e.target.value)} />
          <Button onClick={e => sendWiFi()}>Guardar WiFi</Button>
        </Stack>
      )
    }




    function Broker(props) {
      const [domain, setDomain] = useState('');
      const [port, setPort] = useState(0);
      const [username, setUsername] = useState('');
      const [password, setPassword] = useState('');

      function sendBroker() {
        let baseURL = "setbroker";
        let params = [
          newParam("domain", domain),
          newParam("port", port),
          newParam("username", username),
          newParam("password", password),
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          props.setPage("home")
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }


      useEffect(() => {
        let baseURL = "getconfigs";
        let params = [
          newParam("section", "broker"),
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          setDomain(r.configs.domain);
          setPort(r.configs.port);
          setUsername(r.configs.username);
          setPassword(r.configs.password);
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }, [])
      return (
        <Stack
          component="form"
          noValidate
          autoComplete="off"
          spacing={2}
          sx={{ my: 4 }}>
          <Typography variant="h4" component="h1" gutterBottom>
            Configuración del Broker
          </Typography>
          <TextField label="Domain" variant="outlined" fullWidth value={domain} onChange={e => setDomain(e.target.value)} />
          <TextField label="PORT" variant="outlined" fullWidth value={port} onChange={e => setPort(parseInt(e.target.value))} />
          <TextField label="Username" variant="outlined" fullWidth value={username} onChange={e => setUsername(e.target.value)} />
          <TextField type="password" label="Contraseña" variant="outlined" fullWidth value={password} onChange={e => setPassword(e.target.value)} />
          <Button onClick={e => sendBroker()}>Guardar Broker</Button>
        </Stack>
      )
    }

    function Estacion(props) {
      const [sucursal, setSucursal] = useState(0);
      const [cupo, setCupo] = useState(0);
      const [puerta, setPuerta] = useState('');

      function sendBroker() {
        let baseURL = "setestacion";
        let params = [
          newParam("sucursal", sucursal),
          newParam("cupo", cupo),
          newParam("puerta", puerta),
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          props.setPage("home")
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }

      useEffect(() => {
        let baseURL = "getconfigs";
        let params = [
          newParam("section", "estacion"),
        ];
        sendToServer(baseURL, params).then(r => {
          console.log("R => ", r)
          setSucursal(parseInt(r.configs.sucursal))
          setCupo(parseInt(r.configs.cupo))
          setPuerta(r.configs.puerta)
        }).catch(e => {
          console.log("E => ", e)
          alert(e.message)
        })
      }, [])
      return (
        <Stack
          component="form"
          noValidate
          autoComplete="off"
          spacing={2}
          sx={{ my: 4 }}>
          <Typography variant="h4" component="h1" gutterBottom>
            Configuración del Broker
          </Typography>
          <TextField type="number" label="Sucursal" variant="outlined" fullWidth value={sucursal} onChange={e => setSucursal(parseInt(e.target.value))} />
          <TextField type="number" label="Cupo" variant="outlined" fullWidth value={cupo} onChange={e => setCupo(parseInt(e.target.value))} />
          <FormControl fullWidth>
            <InputLabel id="label-puerta">Puerta</InputLabel>
            <Select
              labelId="label-puerta"
              value={puerta}
              label="Puerta"
              onChange={e => setPuerta(e.target.value)}
            >
              <MenuItem value="ingresos">Ingreso/Entrada</MenuItem>
              <MenuItem value="egresos">Egreso/Salida</MenuItem>
            </Select>
          </FormControl>
          <Button onClick={e => sendBroker()}>Guardar Broker</Button>
        </Stack>
      )
    }


    function App() {
      const [page, setPage] = useState("login");

      const Pages = {
        login: <Login setPage={setPage} />,
        home: <Home setPage={setPage} />,
        wifi: <WiFi setPage={setPage} />,
        broker: <Broker setPage={setPage} />,
        estacion: <Estacion setPage={setPage} />
      }

      function PageComponent() {
        return Pages[page]
      }
      function HomeIcon(props) {
        return (
          <div className="ToHome" onClick={() => setPage("home")}>
            <SvgIcon {...props} >
              <path d="M10 20v-6h4v6h5v-8h3L12 3 2 12h3v8z" />
            </SvgIcon>
            Home
          </div>
        );
      }
      return (
        <Container maxWidth="sm">
          <Paper sx={{ padding: 4 }}>
            {page != "home" && page != "login" && <HomeIcon />}
            <PageComponent />
            <Box sx={{ my: 4 }}>
              <Typography variant="h5" component="h1" gutterBottom>
                Información
              </Typography>
              <ProTip />
              <Copyright />
            </Box>
          </Paper>
        </Container>
      );
    }

    ReactDOM.render(
      <ThemeProvider theme={theme}>
        {/* CssBaseline kickstart an elegant, consistent, and simple baseline to build upon. */}
        <CssBaseline />
        <App />
      </ThemeProvider>,
      document.querySelector("#root")
    );
  </script>
</body>

</html>
)***";