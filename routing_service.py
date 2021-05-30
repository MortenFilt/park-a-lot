import flask
from flask.globals import request
from flask.wrappers import Response
import license_plate_detection
import utils_our
import base64
import io
from PIL import Image
import numpy as np
import cv2


app = flask.Flask(__name__)
app.config["DEBUG"] = False



@app.route('/', methods=['GET'])
def home():
    return "<h1> THIS IS A GOD DAMN HEADING </h1><p>THIS PARAGRAPH STATES THAT I WORK!</p>"

@app.route('/licenseplate', methods=['POST'])
def analyse_license_plate():
    print (request.is_json)
    try:
        #images = []
        #content = request.get_json()
        #image_received = content['picture']
        #print(image_received)

        #message_bytes = image_received.encode('ascii')
        #base64_bytes = base64.b64decode(message_bytes)
        #print(base64_bytes)
        
        #image_data = np.frombuffer(base64_bytes, dtype=np.uint8)
        #image = cv2.imdecode(image_data, 1)
        #print(image)

        #utils_our.show_image(image)
        #images.append(image)
        #license_plate_detection.do_image_detection(image)
        
        license_plate_detection.get_training_licenses()

    except Exception as e:
        print(e)
        return Response(status = 404)
    response = 'very nice '
    return response

@app.route('/parkingArea', methods=['POST'])
def analyse_parking_area():
    print (request.is_json)
    try:
        #images = []
        #content = request.get_json()
        #image_received = content['picture']

        #message_bytes = image_received.encode('ascii')
        #base64_bytes = base64.b64decode(message_bytes)
        
        #image_data = np.frombuffer(base64_bytes, dtype=np.uint8)
        #image = cv2.imdecode(image_data, 1)
        #utils_our.show_image(image)
        #images.append(image)
        #characters = license_plate_detection.do_image_detection(image)
        
        import area_recognition

    except Exception as e:
        print(e)
        return Response(status = 404)
    response = 'very nice '
    return response

app.run(host='192.168.255.41', port=5000)