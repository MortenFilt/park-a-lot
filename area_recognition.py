from scipy.spatial import distance as dist
from matplotlib import pyplot as plt
from imutils import perspective
from imutils import contours
import numpy as np
import argparse
import imutils
import cv2
import utils_our
from log4python.Log4python import log

current_directory = None
TestLog = log("LogDemo")

# Actual width of object in centimeters
object_width = 5.5

# Helper method (The Midpoint Formula)
# Compute midpoint between two sets of (x, y)-coordinates
# https://www.purplemath.com/modules/midpoint.htm

def calculate_midpoint(pointA, pointB):
    return (((pointA[0] + pointB[0]) / 2), ((pointA[1] + pointB[1]) / 2))

def show_image_jupyter(image):
    utils_our.show_image(image)

image = cv2.imread('.\Size Recognition\Stoerrelse.jpg')
print("Done getting image \n Showing it now...")
show_image_jupyter(image)

gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
gray = cv2.GaussianBlur(gray, (7, 7), 0)
print("Done prepping image for analysis \n Showing it now...")
show_image_jupyter(gray)

edged = cv2.Canny(gray, 50, 125)
edged = cv2.dilate(edged, None, iterations = 1)
edged = cv2.erode(edged, None, iterations = 1)

print("Done doing edge detection \n Showing it now...")
show_image_jupyter(edged)

cntrs = cv2.findContours(edged.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cntrs = imutils.grab_contours(cntrs)

(cntrs, _) = contours.sort_contours(cntrs)

pixel_per_centimer = None

for contour in cntrs:
    # Sorting away all leftover contours from the image that are just noise
    if cv2.contourArea(contour) < 300:
        continue
        
    original_image  = image.copy()
    box = cv2.minAreaRect(contour)
    box = cv2.boxPoints(box)
    box = np.array(box, dtype = 'int')
    
    box = perspective.order_points(box)
    cv2.drawContours(original_image, [box.astype('int')], -1, (0, 255, 0), 2)
    
    for (x, y) in box:
        cv2.circle(original_image, (int(x), int(y)), 5, (0, 0, 255), -1)
        
    # Get coordinates from boundix box
    (top_left, top_right, bottom_right, bottom_left) = box
    
    # Caluclate midpoints
    (tl_tr_X, tl_tr_Y) = calculate_midpoint(top_left, top_right)
    (bl_br_X, bl_br_Y) = calculate_midpoint(bottom_left, bottom_right)
    
    (tl_bl_X, tl_bl_Y) = calculate_midpoint(top_left, bottom_left)
    (tr_br_X, tr_br_Y) = calculate_midpoint(top_right, bottom_right)
    
    # Draw midpoints on image
    cv2.circle(original_image, (int(tl_tr_X), int(tl_tr_Y)), 5, (255, 0, 0), -1)
    cv2.circle(original_image, (int(bl_br_X), int(bl_br_Y)), 5, (255, 0, 0), -1)
    cv2.circle(original_image, (int(tl_bl_X), int(tl_bl_Y)), 5, (255, 0, 0), -1)
    cv2.circle(original_image, (int(tr_br_X), int(tr_br_Y)), 5, (255, 0, 0), -1)
    
    # Draw lines between midpoints
    cv2.line(original_image, (int(tl_tr_X), int(tl_tr_Y)), (int(bl_br_X), int(bl_br_Y)),
             (255, 0, 255), 2)
    cv2.line(original_image, (int(tl_bl_X), int(tl_bl_Y)), (int(tr_br_X), int(tr_br_Y)),
             (255, 0, 255), 2)
    
    # Calculate Euclidean distance between midpoints
    distance_A = dist.euclidean((tl_tr_X, tl_tr_Y), (bl_br_X, bl_br_Y))
    distance_B = dist.euclidean((tl_bl_X, tl_bl_Y), (tr_br_X, tr_br_Y))
    
    # Calulate PPM
    # Check if it's still None so the PPM value is only set by the first object
    if pixel_per_centimer is None:
        pixel_per_centimer = distance_B / object_width #Initialized in the beginning
        
    # Calculate size of object
    dimension_A = distance_A / pixel_per_centimer
    dimension_B = distance_B / pixel_per_centimer
    
    # These objects are to small for it to be actual object
    # but they might still be calulated
    if dimension_A < 2.5 or dimension_B < 2.5:
        continue
        
    print('Height: {}'.format(dimension_A))
    print('Width: {}'.format(dimension_B))
    
    # Draw the objects sizes on the image
    cv2.putText(original_image, "{:.1f}cm".format(dimension_A),
               (int(tl_tr_X - 15), int(tl_tr_Y - 10)), cv2.FONT_HERSHEY_SIMPLEX,
                0.65, (255, 255, 255), 2)
    cv2.putText(original_image, "{:.1f}cm".format(dimension_B),
               (int(tr_br_X + 10), int(tr_br_Y)), cv2.FONT_HERSHEY_SIMPLEX,
               0.65, (255, 255, 255), 2)
    
    show_image_jupyter(original_image)
    cv2.imshow("Image", original_image)
    cv2.waitKey(0)
TestLog.info('Parkerings Areal registreret')