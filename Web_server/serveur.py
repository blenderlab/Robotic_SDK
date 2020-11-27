from flask import Flask
from flask import render_template
import requests 

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("robots.html")

@app.route("/sendgo1")
def sendgo1():
    response = requests.get("http://ipdurobot1/go")
    return("Send message 1")

@app.route("/sendgo2")
def sendgo2():
    response = requests.get("http://ipdurobot2/go")
    return("Send message 2")

@app.route("/sendgoall")
def sendall():
    response = requests.get("http://ipdurobot1/go")
    response = requests.get("http://ipdurobot2/go")
    return("All robots should go !")

@app.route("/newbot/<ipadd>")
def newbot(ipadd):
    return("a New bot arrives : %s" % ipadd)
    return("All robots should go !")

if __name__=="__main__":
    app.run(host='0.0.0.0',debug=True)
