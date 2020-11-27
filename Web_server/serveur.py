from flask import Flask
from flask import render_template
import requests 

app = Flask(__name__)

#list of robots IP adresses :

class robot:
	name = ""
	ip=""

robots=[]

@app.route("/")
def index():
	#Generate the robots web page & retrun to the client :
    return render_template("robots.html",robots=robots)


# the route for a bot to declare itself : 
@app.route("/newbot/<ipadd>/<name>")
def newbot(ipadd,name):
	# A new bot gateway send it IP adress !
	# store it in the list : 
	r = robot()
	r.name= name
	r.ip = ipadd
	robots.append(r)
	return("Welcome  " + name )

# the route to send GO (f) to a given robot (ip):
@app.route("/sendgo/<ip>")
def go(ip):
		sendmessage(ip,"f")

# the route to send STOP (X) to a given robot (ip):
@app.route("/sendstop/<ip>")
def stop(ip):
		sendmessage(ip,"X")

# the route to send a message to all robots :
@app.route("/sendall/<message>")
def sendall():
	for robot in robots : 
   		sendmessage(robot.ip,message)


# a function to send a message to a given IP 
def sendmessage(ip,message):
	url = "http://"+ip+"/"+message
	response = requests.get(url)
   

if __name__=="__main__":
    app.run(host='0.0.0.0',debug=True)
