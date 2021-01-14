import pyrebase         # Firebase Wraper for python
from time import sleep  # Sleep
import serial           # used for UART connection with arduino
import struct           # used in order to send arrays to arduino
import color_picker     # Color picker


def unpack(p):
    """ Unpack Data from Firebase (works with pyrebase objects)"""
    BA,BB,BC,BD,GA,GB,GC,GD,RA,RB,RC,RD,Time = [ int(pu.val()) for pu in  p.each() ] # Unpack Data
    return  RA,GA,BA,RB,GB,BB,RC,GC,BC,RD,GD,BD,Time                                 # Return with correct order 


################################# FIREBASE CREDENTIALS ############################################

firebaseConfig = {
    "apiKey": "AIzaSyDLFJQw1bzvfPULmzugEW6onW9BIy2bXdM",
    "authDomain": "led-gui-e2cef.firebaseapp.com",
    "databaseURL": "https://led-gui-e2cef-default-rtdb.firebaseio.com",
    "projectId": "led-gui-e2cef",
    "storageBucket": "led-gui-e2cef.appspot.com",
    "messagingSenderId": "663397186788",
    "appId": "1:663397186788:web:33edf4c3edfdeb1a3f00f1",
    "measurementId": "G-98W5LGTWB9"
  }

###################################################################################################

firebase = pyrebase.initialize_app(firebaseConfig)  # Initialize App
db = firebase.database()                            # Initialize Real Time Database    
TimeLimit = 30                                      # Time Limit 
count = 0                                           # Initiate Counter (Program will stop once counter reaches TimeLimit)
waitupdate = 10                                     # Time for waitting till next update 

while True:                                         # Iterate While True

    switch = db.child("Switch").get().each()[0].val() # Retrive Status of pattern 1 (1 if uppdated 0 if used)
    if switch:
        RGBLIST=color_picker.main()         # Retrive colors 
        try:
            ser = serial.Serial('COM5', 9600)   # Connect to Arduino
            sleep(2)                            # Sleep 2 seconds so that arduino boots

            Time = 5 # 5 seconds
            RA,GA,BA = RGBLIST[0][0],RGBLIST[0][1],RGBLIST[0][2]
            RB,GB,BB = RGBLIST[1][0],RGBLIST[2][1],RGBLIST[1][2]
            RC,GC,BC = RGBLIST[2][0],RGBLIST[3][1],RGBLIST[2][2]
            RD,GD,BD = RGBLIST[3][0],RGBLIST[3][1],RGBLIST[3][2]

            ser.write(struct.pack('>BBBBBBBBBBBBB',RA,GA,BA,RB,GB,BB,RC,GC,BC,RD,GD,BD,Time)) # Send data to arduino
            ser.write(struct.pack('>BBBBBBBBBBBBB',0,0,0,0,0,0,0,0,0,0,0,0,1)) # Turn off all leds
            ser.close()                                                        # Close connection


        except:
            print('Arduino is not connected')

        db.child("Switch").set({"switch":0})          # Set switch 

    else:
        s1 = db.child("Statusp1").get().each()[0].val() # Retrive Status of pattern 1 (1 if uppdated 0 if used)
        s2 = db.child("Statusp2").get().each()[0].val() # Retrive Status of pattern 2 (1 if uppdated 0 if used)
        s3 = db.child("Statusp3").get().each()[0].val() # Retrive Status of pattern 3 (1 if uppdated 0 if used)
        s4 = db.child("Statusp4").get().each()[0].val() # Retrive Status of pattern 4 (1 if uppdated 0 if used)


        if s1*s2*s3*s4:                             # If all status were updated (All are 1)
            db.child("Statusp1").set({"status":0})  # Set status for pattern 1 to 0
            db.child("Statusp2").set({"status":0})  # Set status for pattern 2 to 0
            db.child("Statusp3").set({"status":0})  # Set status for pattern 3 to 0
            db.child("Statusp4").set({"status":0})  # Set status for pattern 4 to 0

            p1 = db.child("p1").get()  # Get Pattern 1
            p2 = db.child("p2").get()  # Get Pattern 2
            p3 = db.child("p3").get()  # Get Pattern 3
            p4 = db.child("p4").get()  # Get Pattern 4

            
            try:
                ###T############################ his chunck of code assumes arduino is connected ##############################
                ### CHANGE COM AND BAUDRATE ACCORDINGLY TO YOUR ARDUINO ###
                ser = serial.Serial('COM5', 9600)   # Connect to Arduino
                sleep(2)                            # Sleep 2 seconds so that arduino boots

                for i in range(1,5):                # Iterate over number of patterns (1,2,3,4)
                    RA,GA,BA,RB,GB,BB,RC,GC,BC,RD,GD,BD,Time  = unpack(eval("p"+str(i)))               # Unpack patterns
                    ser.write(struct.pack('>BBBBBBBBBBBBB',RA,GA,BA,RB,GB,BB,RC,GC,BC,RD,GD,BD,Time)) # Send data to arduino
                
                ### This runs once we have sent all patterns ###
                ser.write(struct.pack('>BBBBBBBBBBBBB',0,0,0,0,0,0,0,0,0,0,0,0,1)) # Turn off all leds
                ser.close()                                                        # Close connection
                count -= 1                                                         # Substract 1 to count
                ################################################################################################################
                
            except:
                #### EXCEPT: ARDUINO IS NOT CONNECTED ####
                print("Arduino is not connected, Plesae Connect Arduino in order to see pattern")#Tell user arduino is not connectec
                ##########################################

        
        else:           # (s1*s2*s3*s4 = 0 this means that all patterns have not been updated jet)
            count += 1  # Increment count
            sleep(waitupdate)   # Sleep 10 seconds
            
        print(count)    # Print Count
        if count == TimeLimit: #  IF Count is equal to TimeLimit
            print("Bye bye ")  # Tell user farewell
            break              # Break main While