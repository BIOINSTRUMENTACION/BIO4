import cv2                  # Import python-opencv
import numpy as np          # Import numpy 
import imutils              # Import imutils 
from time import sleep      # Good Night
import matplotlib.pyplot as plt

"""Countour detection  """




#### Functions ###
def empty(a):
    """Tracbars need a function in order to work, we will feed it a fucntion that does nothing """
    pass

def getContours(frame,frameContour):
    """ finds contours of frames"""
    global approx
    global cnt
    global RGBLIST
    global RGB_Box 
    global RGB_value
    mode   = cv2.RETR_EXTERNAL                               # Mode for find contours
    method = cv2.CHAIN_APPROX_NONE                           # Method for fund contours
    contours,hierarchy = cv2.findContours(frame,mode,method) # Find contours (Returns contours and hierarchy order)
    
    MinArea = cv2.getTrackbarPos("Area","Parameters") # Get min Area from TrackBar (user)
    Contour_Color = (255, 0, 0)                       # Define Contour Color
    Text_Color    =  (0, 255, 0)                      # Define Text Color
    Font = cv2.FONT_HERSHEY_COMPLEX                   # Define Font Color
    Thickness = 1                                     # Define Font Thickness
    Font_size = 0.1
    ### ITerate over contours ###
    RGBLIST = []
    i=0
    
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area > MinArea :
             i+=1
             framecolor = frameContour.copy()                         # Copy frame in order to analyze colors
             cv2.drawContours(frameContour, cnt, -1,Contour_Color, 7) # Draw Contour
             perimeter = cv2.arcLength(cnt,True)                      # Get Perimter
             approx = cv2.approxPolyDP(cnt, 0.02 * perimeter, True)   # Approximate polygon
             x , y , w, h = cv2.boundingRect(approx)                  # Get Bounding box for polygon
             framecolor = cv2.cvtColor(framecolor ,cv2.COLOR_BGR2RGB) # Transform BGR to RGB
             RGB_Box    = framecolor[y:y+h, x:x+w, :]
             RGB_value  = np.average(RGB_Box, axis = (0,1)).astype(np.uint8) 
            # RGB_value = framecolor[int((x + w)/2),int((y+h)/2)]      # Get the RGB Value 
             RGBLIST.append(RGB_value)                                # Append to RGB LIST
             cv2.rectangle(frameContour, (x , y ), (x + w , y + h ), (0, 255, 0), 5) # Draw Bounding Box
             
             ## Iterate over polygon points and plot them ##
             for app in approx:
                cv2.circle(frameContour,(app[0][0],app[0][1]),5,(0,0,255),cv2.FILLED)       # Draw the points 

            ## plot metadata ##
             sRGB =  "(" + str(i) +") "+ str(RGB_value[0]) + "," + str(RGB_value[1]) + "," + str(RGB_value[2])   # Get points
             area   =  str(int(area))     # Get Area 
             cv2.putText(frameContour, sRGB, (int((x + x+ w)/2)-40, int((y+y+h)/2)),Font,0.5,(0,0,0),Thickness ) # Draw text telling number of points
         


def mousePoints(event,x,y,flags,params):
    """ Function to detect leftbutton click, stores pixels """
    global  frameContour
    global  END
    if event == cv2.EVENT_LBUTTONDOWN:              # if event is click button
      cv2.imshow("Image transfromed", frameContour) # Show image 
      END = 1                                       # Set END to 1
   


    
 
        
def stackImages(scale,imgArray):
    """ Function to stack frames into a single frame (used to display all frames in 1 window) """
    rows = len(imgArray)
    cols = len(imgArray[0])
    rowsAvailable = isinstance(imgArray[0], list)
    width = imgArray[0][0].shape[1]
    height = imgArray[0][0].shape[0]
    if rowsAvailable:
        for x in range ( 0, rows):
            for y in range(0, cols):
                if imgArray[x][y].shape[:2] == imgArray[0][0].shape [:2]:
                    imgArray[x][y] = cv2.resize(imgArray[x][y], (0, 0), None, scale, scale)
                else:
                    imgArray[x][y] = cv2.resize(imgArray[x][y], (imgArray[0][0].shape[1], imgArray[0][0].shape[0]), None, scale, scale)
                if len(imgArray[x][y].shape) == 2: imgArray[x][y]= cv2.cvtColor( imgArray[x][y], cv2.COLOR_GRAY2BGR)
        imageBlank = np.zeros((height, width, 3), np.uint8)
        hor = [imageBlank]*rows
        hor_con = [imageBlank]*rows
        for x in range(0, rows):
            hor[x] = np.hstack(imgArray[x])
        ver = np.vstack(hor)
    else:
        for x in range(0, rows):
            if imgArray[x].shape[:2] == imgArray[0].shape[:2]:
                imgArray[x] = cv2.resize(imgArray[x], (0, 0), None, scale, scale)
            else:
                imgArray[x] = cv2.resize(imgArray[x], (imgArray[0].shape[1], imgArray[0].shape[0]), None,scale, scale)
            if len(imgArray[x].shape) == 2: imgArray[x] = cv2.cvtColor(imgArray[x], cv2.COLOR_GRAY2BGR)
        hor= np.hstack(imgArray)
        ver = hor

    return ver



def main():
    global  frameContour
    global  END
    global RGBLIST
    global RGB_Box 
    global RGB_value
    END = 0                     # Variable to END Camara once color has been seleceted
    frameWidth  = 640           # Frame Width
    frameHeight = 480           # Frame Height 
    cap = cv2.VideoCapture(0)   # Intialize Webcam object
    ### use celphone camara  via IP WebCam###
    use = input("Use Celphone Camara via IP WebCam? y/n ")
    if use == "y": 
        address = "http://192.168.1.65:8080/video" # IP ADRESS FOR CELPHONE WEBCAM
        cap.open(address)                          # OPEN ADDRESS WITH cap object

    else:
        pass

    cap.set(3,frameWidth)       # Set Frame Width
    cap.set(4,frameHeight)      # Set Frame Height 
    ### TRACKBAR ###
    cv2.namedWindow("Parameters")                               # Name window for parameters
    cv2.resizeWindow("Parameters",640,240)                      # Resize window
    cv2.createTrackbar("Threshold1","Parameters",45,255,empty)  # Threshold1 varaible for canny filter
    cv2.createTrackbar("Threshold2","Parameters",74,255,empty)  # Threshold2 varaible for canny filter
    cv2.createTrackbar("Area","Parameters",1000,50000,empty)    # Area to delete noise 


    while True:                                     # Iterate while True

        
        status,frame = cap.read()                   # Read  Webcam
        if use == "y":
            frame = imutils.resize(frame, width=540)    # Resize frame
        frameContour = frame.copy()                 # Make a copy of frame
        frameBlur = cv2.GaussianBlur(frame,(7,7),1) # Apply Gaussian Blur (this will reduce noise)
        frameGray = cv2.cvtColor(frameBlur,cv2.COLOR_BGR2GRAY) # Apply transformation from BGR TO GRAY

        ### GET TRACK VARAIABLES ###
        Threshold1 = cv2.getTrackbarPos("Threshold1","Parameters")
        Threshold2 = cv2.getTrackbarPos("Threshold2","Parameters")

        ### Apply filter ###
        frameCanny = cv2.Canny(frameGray,Threshold1,Threshold2)  # Canny Filter

        ### Morphological operations ###
        kernel = np.ones((2,2))                                     # Kernel for morhpological operations
        ### OPENING (EROSION FOLLOWED BY OPENING ) ###
        frameDilation = cv2.dilate(frameCanny,kernel,iterations=1 ) # Dilation
        getContours(frameDilation,frameContour)
        ### Stack frames and show tem
        Stack = stackImages(0.8,([frame,frameCanny],[frameDilation ,frameContour ]))

     
        
        cv2.imshow("Original",Stack)                    # Show frame
        cv2.setMouseCallback("Original",mousePoints)     # Set callbak 

        if cv2.waitKey(1) & 0xff == ord('q'):   # q as waitkey
            break                               # break if usere presses q

        if END:
            sleep(10)
            print(RGBLIST)
            print(RGB_Box)
            print(RGB_value)
            plt.imshow(RGB_Box)
            plt.show()
            break


    cap.release()           # Relase cap object
    cv2.destroyAllWindows() # Destroy Windows

    return RGBLIST    