import time
import picamera
import picamera.array
import numpy as np
import requests
import json
import base64

with picamera.PiCamera() as camera:
	print("Camera running")
	camera.resolution = (100, 100)
	time.sleep(2)

	while True:
		camera.capture("picture.jpg")
		image = np.empty((112*128*3), dtype=np.uint8)
		camera.capture(image, 'bgr')
		image = image.reshape((112, 128, 3))
		image = image[:100, :100, :]
		print("Image taken")
		url = 'http://192.168.87.163:9000/platePicture'

		imageAsString = np.array2string(image)
		imageBytes = imageAsString.encode('UTF-8')
		base64Bytes = base64.b64encode(imageBytes)
		base64String = base64Bytes.decode('UTF-8')
		obj = {
			"picture": base64String
		}
		response = requests.post(url, data = json.dumps(obj))
		print(response)
		print("Picture taken and sent, 10 seconds until next picture")
		time.sleep(10)
