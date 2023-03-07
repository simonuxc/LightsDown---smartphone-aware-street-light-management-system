# LightsDown - smartphone-aware street light management system
A prototype that would help reduce the energy consumption on street lightning by 60%, created in hackathon "Rethinking hardware", Vilnius 

## The idea

During hackathon, we were given a task to come up with a way to reduce abundant lightning on the streets. Me and my team came up with a solution that judges found to be worthy of a second place. 

Just in three days we managed to not only provide a theoretical solution, but also created a working prototype where you only need your phone for the lamps to light up near you (creating so called “light tunnel”), while everywhere else energy is saved by using a small amount of power and dim lighting. Our team developed a prototype of the product called "LightsDown".

## The prototype

The prototype was created using LEDs, arduino uno and ESP8266. As devices with internet are constantly "spitting out" probe requests, it is possible for the ESP8266 to detect nearby devices. Sadly, there was enough time to find a way of detecting hotspots instead of WI-FI search requests, so for the prototype to work, we used one phone with its hotspot turned on and filtered it out from the rest of devices (as there were quite many of them). 

On a large scale (street) it would be sufficient to detect any device and turn on the closest lamp, but in the hackathon the scale was small, so to represent individual street lamps, we divided the led stripe into two sectors. The role of ESP8266 is to measure the distance from the phone to itself and based on that turn the sector that is closer to the person. There's a specific formula for that, as the strength isn't measured linearly.

Without filtering the phone and measuring the distance, another problem shows up: hotspot sygnal strenght fluctuation. To account for that, I choose the smallest distance from 30 distances arrays that is updated with each probe. Why the smallest? When you think about it, hotspot/wifi and all other sygnals can only get "weaker", so the smallest distance (strongest sygnal) is usually the correct one.

[A video of the prototype.](https://youtu.be/y2Le5ER7QN4)

Lots of credit goes to [kalanda and their ESP8266-sniffer project](https://github.com/kalanda/esp8266-sniffer)
