# License Plate Detection

### IMPORTS ###
import numpy as np
import cv2
import imutils
import os
import glob
import cv2
import utils_our
from matplotlib import pyplot as plt
from log4python.Log4python import log

current_directory = None
TestLog = log("LogDemo")
TestLog.info("Image Processing Log Initialized")

def get_training_licenses():
    global TestLog
    print('\n ##### Starting License Plate Analyser ##### \n')
    current_directory = os.path.dirname(os.path.realpath(__file__))

    # Check for training data
    training_data = False
    for dirname, _, filenames in os.walk(current_directory):
        if dirname == (current_directory + '\License Plates'):
            print('Training data localized')
            training_data = True
            break
    if training_data == False:
        print('Training data could not be localized')
        print('##### TERMINATING APPLICATION #####')
        exit()

    # Gather training data
    print('.Gathering training data...')
    print('..This can take a few seconds')
    image_data = []
    files = glob.glob(current_directory + "\License Plates\images\*.jpg")
    for file in files:
        image = cv2.imread(file)
        image_data.append(image)

    print('...Training data gathered')

    # Show images of all the license plates
    
    do_image_detection(image_data)

def do_image_detection(images):
    utils_our.get_model()
    for image in images:
        licenseplate_image = utils_our.identify_license_plate(image)
        if licenseplate_image != 'ERROR':
            licenseplate_characters = utils_our.performe_character_segmentation(licenseplate_image)
            if licenseplate_characters != 'ERROR':
                print('Jaaah Bitch!')
                chars = ''
                for i in range(len(licenseplate_characters)):
                    utils_our.show_image(licenseplate_characters[i])
                    cv2.imwrite('char{}.jpg'.format(i), licenseplate_characters[i])
                    char = utils_our.predict(licenseplate_characters[i])
                    chars = chars + format(char)

                TestLog.info('Nummerplade billede behandlet \n Nummerpladen  er: {}'.format(chars))

            else:
                print('!!!!! --- NO LICENSE PLATE DETECTED --- !!!!!')
                TestLog.info("Ukendt nummerplade - id: 000000001")
                raise Exception("Couldn't detect any characters")
        else:
            print('!!!!! --- NO LICENSE PLATE DETECTED --- !!!!!')
            TestLog.info("Ukendt nummerplade - id: 000000001")
            raise Exception("Couldn't detect any license plate")
        
get_training_licenses()
    





