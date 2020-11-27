# Robotic SDK 


Templates to use a Car Robot Kit (with Arduino & BtLE 4.0 interface)

Each Robot comes with a Gateway (ESP32) to send order to the bot. The ESP32 runs a Webserver to handle incoming requests and transfers it to the Bot.

The ESP32s will connect to the WebServer (Python + Flask) to have a Web interface.

A lot of ESP32 GW can connect to the server. The delcares themselves.

# Dependencies 

Webserver runs in flask : so Flask & Requests are needed :

pip install flask

pip install requests

then just run 

python server.py 

and connect to localhost:5000 through a webbrowser. 
