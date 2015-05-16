var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  // we will request the weather here
  console.log(pos.coords.latitude);
  console.log(pos.coords.longitude);
  var url = "http://api.openweathermap.org/data/2.5/weather?lat=" + 
      pos.coords.latitude + "&lon=" + pos.coords.longitude;// + "&callback=responseText";
  console.log(url);
  
  //send request ti OpenWeatherMap
  xhrRequest(url, 'GET',
    function(responseText) {
      //response Text contains a JSON object with weather info
      console.log(responseText);
      var json = JSON.parse(responseText);
      
      //Temperature in Kelvin requeres adjustment
      var temperature = Math.round(json.main.temp - 273.15);
      console.log('Temperature is ' + temperature);
      
      //Conditions
      var conditions = json.weather[0].main;
      console.log('Conditions are ' + conditions);
      
      //Windspeed
      var windspeed = Math.round(json.wind.speed / 1.150777155); //Windspeed in kts
      console.log("Windspeed is " + windspeed);
      
      //Winddirection
      var winddirection = json.wind.deg;
      console.log("Winddirection is " + winddirection);
      console.log("Winddirectiontype is " + typeof(winddirection));
      console.log("Winddirectiontype is " + typeof(292.5));       
      var winddir = "";
      if(337.5<winddirection<22.5) {
        winddir = "N";
      } else if(22.5<winddirection<67.5) {
        winddir = "NE";
      } else if(67.5<winddirection<112.5) {
        winddir = "E";
      } else if(112.5<winddirection<157.5) {
        winddir = "SE";
      } else if(157.5<winddirection<202.5) {
        winddir = "S";
      } else if(202.5<winddirection<247.5) {
        winddir = "SW";
      } else if(247.5<winddirection<292.5) {
        winddir = "W";
      } else if(292.5<winddirection<337.5) {
        winddir = "NW";
      } else {
        winddir = "NA";
      }
      console.log("winddir is " + winddir);
      //Assemble dictionary using our keys
      var dictionary = {
        "KEY_TEMPERATURE": temperature,
        "KEY_CONDITIONS": conditions,
        "KEY_WINDSPEED": windspeed,
        "KEY_WINDDIRECTION": winddir
      };
      
      //Send to Pebble
      Pebble.sendAppMessage(dictionary, 
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }
  );
}

function locationError(err) {
  console.log("Error requesting location!");
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready',
  function(e) {
    console.log("PebbleKit JS ready!");
                         
    // Get the initial weather
    getWeather();
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log("AppMessage received!");
    getWeather();
  }
);

//show configuration listener
Pebble.addEventListener('showConfiguration', function(e) {
  // Show config page
  Pebble.openURL('http://xmanzaix.github.io/settings-fin-watch');
});

//further config interaction

Pebble.addEventListener("webviewclosed", function(e){
	console.log("Configuration closed");
    console.log("Response = " + e.response.length + "   " + e.response);
    if (e.response !== undefined && e.response !== '' && e.response !== 'CANCELLED') {
		console.log("User hit save");
		var values = JSON.parse(decodeURIComponent(e.response));
		console.log("stringified options: " + JSON.stringify((values)));
		Pebble.sendAppMessage(
			values
		);
	}
});