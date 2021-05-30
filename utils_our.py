# Our Utilities for image manipulation

### IMPORTS ###
import numpy as np
import cv2
import imutils
from matplotlib import pyplot as plt
import joblib

model = None
print('Utility module has been imported correctly')

def get_model():
    global model
    if model == None:
        model = joblib.load('model_licenseplate.sav')

def predict(image):
    global model
    print('Predicting........')
    print('size of input')
    print(len(image))
    result = model.predict(image.reshape(1,-1))
    return result

# Method for preparing image for Edge Detection \w Canny Edge Method
# Input:    image (cv2.image)
# Output:   image (cv2.image)
def prep_for_edge_detection(image):
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    gray_blurred_image = cv2.bilateralFilter(gray_image, 11, 25, 25)
    
    return gray_blurred_image

# Method for performing Edge Detection \w Canny Edge Method
# Input:    image (cv2.image)
# Output:   image (cv2.image)
def perform_edge_detection(image):
    # Compute median og pixel intensities
    v = np.median(image)

    lower_thresh = int(max(0, (1.0 - 0.25) * v))
    upper_thresh = int(min(255, (1.0 + 0.25) * v))
    edged = cv2.Canny(image, lower_thresh, upper_thresh)
    return edged

# Method for identifying contours and sorting them from big to small
# Input:    image (cv2.image)
# Output:   contours (Numpy Array (x,y))
def identify_and_sort_contours(image):
    contours = cv2.findContours(image,
                        cv2.RETR_EXTERNAL,
                        cv2.CHAIN_APPROX_SIMPLE)
    contours = imutils.grab_contours(contours)
    contours = sorted(contours, key=cv2.contourArea, reverse=True) [:10]
    return contours

# Method for identifying a rectangular contour with a closed figure
# Input:    contours (Numpy Array (x,y))
# Output:   approx (Numpy Array (x,y))
def search_for_rectangular_and_filled_contour(contours):
    for contour in contours:
        peri = cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, 0.018 * peri, True)
    
        if len(approx) == 4:
            return approx

# Method for masking everything else than the approximated contour (License Plate)
# and converting it into a new image only containing the License Plate in gray scale and blurred
# Input:    image (cv2.image)
# Input:    approx (Numpy Array (x,y))
# Output:   image (cv2.image)
def create_license_plate_image(image, image_edged, approx):
    mask = np.zeros(image_edged.shape, np.uint8)
    cv2.drawContours(mask, [approx], 0, 225, -1, )
    cv2.bitwise_and(image, image, mask=mask)

    (x, y) = np.where(mask == 225)
    (topx, topy) = (np.min(x), np.min(y))
    (bottomx, bottomy) = (np.max(x), np.max(y))
    cropped = image[topx:bottomx+1, topy:bottomy+1]
    return cropped

def read_image(image):
    return cv2.imread(image)

# Method for masking everything else than the approximated contour (License Plate)
# and converting it into a new image only containing the License Plate in gray scale and blurred
# Input:    image (cv2.image)
# Output:   void
def show_image(image):
    img_to_show = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    #plt.imshow(img_to_show)
    #plt.show()
    cv2.imshow('Image',image)
    cv2.waitKey(0)

# Method for identifyting a license plate
# Input:    image (cv2.image)
# Output:   image (cv2.image)
def identify_license_plate(image):
    image_edged = None
    contours = None
    approximation = None
    license_plate_image = None
    print('..Preparing image for Edge Detection')
    image_prepped = prep_for_edge_detection(image)
    show_image(image)
    cv2.imwrite('original.jpg', image)
    print('....Performing Edge Detection')
    image_edged = perform_edge_detection(image_prepped)
    show_image(image_prepped)
    cv2.imwrite('prepped.jpg', image_prepped)
    print('......Identifying contours')
    contours = identify_and_sort_contours(image_edged)
    show_image(image_edged)
    cv2.imwrite('edged.jpg', image_edged)
    print('.......Searching for license plate')
    approximation = search_for_rectangular_and_filled_contour(contours)
    
    try:
        print('..........Creating license plate image')
        license_plate_image = create_license_plate_image(image, image_edged, approximation)
        print('License plate image created!')
        return license_plate_image
    except Exception:
        return 'ERROR'

def resize_char_image_to_model_pref(image):
    new_char_image = cv2.copyMakeBorder(image, 4, 4, 19, 19, cv2.BORDER_CONSTANT, None, [0, 0, 0])
    resized = cv2.resize(new_char_image, dsize = (28, 28))
    print(len(resized.reshape(1,-1)))
    return resized

def create_binary_representation(image):
    V = cv2.split(cv2.cvtColor(image, cv2.COLOR_BGR2HSV))[2]
    T = cv2.threshold(V, 180, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)[1]
    thresh = (V > T).astype("uint8") * 255
    thresh = cv2.bitwise_not(thresh)

    # Resize
    image = imutils.resize(image, width=400)
    thresh = imutils.resize(thresh, width=400)
    # show_image(T)
    return T

def sort_character_contours(contours, reverse=False):
    i = 0
    bounding_boxes = [cv2.boundingRect(contour) for contour in contours]
    (contours, bounding_boxes) = zip(*sorted(zip(contours, bounding_boxes),
                                            key=lambda b: b[1][i], 
                                            reverse=reverse))
    return contours

def identify_characters_binary_image(image, image_binary):
    contours, _ = cv2.findContours(image_binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Resize original image (debuggin purpose only)
    width, height = image_binary.shape
    dimension = (height, width)
    image = cv2.resize(image, dimension ,interpolation = cv2.INTER_AREA)

    image_w_chars = image.copy()
    crop_characters = []

    digit_w, digit_h = 30, 60

    for contour in sort_character_contours(contours):
        (x, y, w, h) = cv2.boundingRect(contour)

        # Character Characteristics
        aspect_ratio = w / float(h)
        solidity = cv2.contourArea(contour) / float(w * h)
        height_ratio = h / float(image.shape[0])
    
        keep_aspect_ratio = aspect_ratio < 1.0
        keep_solidity = solidity > 0.15
        keep_height = height_ratio > 0.2 and height_ratio < 0.95

        # Actual identification
        if keep_aspect_ratio and keep_solidity and keep_height:
            image_w_chars = cv2.rectangle(image_w_chars, (x, y), (x + w, y + h), (0, 255, 0), 1)
            current_character = image_binary[y:y+h,x:x+w]
            current_character = cv2.resize(current_character, dsize=(digit_w, digit_h))
            _, current_character = cv2.threshold(current_character, 220, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
            resize_char_image_to_model_pref(current_character)
            crop_characters.append(current_character)

    print("Detected {} letters".format(len(crop_characters)))
    if len(crop_characters) > 0 :
        # Only for debug purpose
        show_image(image_w_chars)
        cv2.imwrite('licenseplate.jpg', image_w_chars)
        return crop_characters
    else:
        return 'ERROR'

            

def performe_character_segmentation(image):
    print('Performing character segmentation')
    image_binary = create_binary_representation(image)
    license_plate_characters = identify_characters_binary_image(image, image_binary)
    if license_plate_characters != 'ERROR':
        for i in range(len(license_plate_characters)):
            cv2.imwrite('char_noprop{}.jpg'.format(i), license_plate_characters[i])
            license_plate_characters[i] = resize_char_image_to_model_pref(license_plate_characters[i])
        return license_plate_characters
    else:
        return 'ERROR'


