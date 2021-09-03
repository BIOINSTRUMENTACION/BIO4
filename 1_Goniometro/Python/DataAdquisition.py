import time                     # Defualt python library
import serial                   # pip install pyserial
import matplotlib.pyplot as plt # pip install matplotlib 
import numpy as np              # pip install numpy
import xlrd                     # pip install xlrd
import xlsxwriter               # pip install xlscwriter
import cv2                      # pip install pyton-cv

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    
class DataAdquisition:
    def __init__(self,com="COM12",baudrate=9600,timeout=1):
        self.com      = com
        self.baudrate = baudrate
        self.timeout  = timeout
    
    def initiateSerialCommunication(self,wait=2) -> bool:
        ''' estabilsh Serial communication with microcontroller'''
        Status = False
        try:
            print("[CPU]   Initializing Serial Communication")            # Tell user comunication wil open
            self.microcontroller = serial.Serial(self.com,self.baudrate)  # Open Serial port
            time.sleep(wait)                                              # Waite 3 seconds for stable connection  
            print("[Micro] Communication has been Established")           # Tell user comunication has been established
            print("."*50)         
            Status = True
        except:
            print("[Micro] Could not establish communication, make sure device is connected") 
        return Status

    def CloseSerialCommunication(self,eastergg=False):
        """Close Serial communication """
        try:
            self.microcontroller.close()
            print("."*50)
            if eastergg:
                print("[Micro] Communication has been closed, bye bye :)")
            else:
                print("[Micro] Communication has been closed")
        except:
            print("[CPU] Can not close serial port of unopened ports")
        
        
    def Dynamicprotocol(self,duration:int = 2,message: str = "Hello",keys: list = ["s1"],printfreq: int = 10,sendiglabel: str = "s") -> dict:
        ''' duration (int) time in seconds
            message  (str) message to tell user adquisition has started
            keys     (list) list with keys for dictinary (number of sensors that will be retrived)
        '''
    
        
        ### Create Datatype (HasMap) for storing Data ###
        Data = dict()         # Initate empty dictionary
        for key in keys:      # Iterate over keys
            Data[key]    = [] # Append an empty list to every key
        Data["time"] = [] # Add a data value for time 

        ### Retirve times and calculate final time ###
        PythonTime  = 0                        # Set Python time to 0
        InitialTime = time.time()              # Retrive time 
        FinalTime   = InitialTime + duration   # Duration of protocol
        i = 0                                  # Variable to set printing frecuency 
        print("[CPU]   "  + message)            # Print inital message
        print("[CPU]  ",end=" ")

        while PythonTime  < FinalTime :               # While Time of protocol is still active
            PythonTime = time.time()                  # Get python Time
            ### Try and except: there tends to be a corrupted intial communciation with Tiva C series micocontrollers ###
            try:
                i +=1
                if i == printfreq:
                    i = 0               # Reset i
                    print(".",end=" ")  # Print point 
                    
                value = self.microcontroller.readline()                    # Read Value
                cad   = value.decode()                                     # Decode to Ascii
                cad   = cad.strip()                                        # Remove \n and \r
                position = cad.index(":")                                  # Get the index of lable/status separation
                label  = cad[:position]                                    # Get label
                SensorValueList = cad[position+1:].split(",")              # Retrive sensor values
                
                if label  ==sendiglabel:
                    for key,retirvedValue in zip(keys,SensorValueList):
                        Data[key].append(retirvedValue)                    # Append Sensor Value 
                        
                    Data["time"].append(PythonTime-InitialTime)            # Append time
        
            except:
                print("[CPU]   Error Retrieving Data")
        print()
        print("[CPU]   Subprotocol rutine finished")
    
        return Data

def UserInputValidator(message:str) -> bool: 
    """Wait for user input and validate"""
    print("[CPU]   "+message)
    UserInput   = str(input("[CPU]   Ready to engange in protocol? y/n ")) # Get UserInput
    UserInput   = UserInput.lower()                                        # lower userinput
    Status      = False                                                    # Default Status set to False
    if (UserInput == "y") or (UserInput == "yes") or (UserInput == "1"):
        Status = True
        
        
    return Status
        
  
def MainLoopProtocol():
    """Practical Example"""
    keys = ["sensor_0","sensor_1","sensor_2","sensor_3","sensor_4","sensor_5"] # List containig number of sensors
    Data1,Data2,Data3 = [" ", " ", " "]                                        # Intialize empty values to prevent error
    Microcontrolador  = DataAdquisition(com="COM12",baudrate=9600,timeout=1)   # instantiate Communication with protocol
    Microcontrolador.initiateSerialCommunication()                             # initate Communication with protocol

    ### First Adquisition ###
    message = bcolors.OKGREEN + "Instruction: Balance the weight on both legs Duration: 20s"+ bcolors.ENDC
    Forward = UserInputValidator(message) # Wait for user input 
    if Forward: 
        Data1 = Microcontrolador.Dynamicprotocol(duration=20,message="Adquiring Data",keys=keys)

    print(" ")
    ### Second Adquisition ###
    message= bcolors.OKGREEN + "Instrucion: Stand on the prosthesis Duration: 20s" + bcolors.ENDC
    Forward = UserInputValidator(message)            # Wait for user input 
    if Forward: 
        Data2 = Microcontrolador.Dynamicprotocol(duration=20,message="Adquiring Data",keys=keys)
    print(" ")   

    ### Third Adquisition ###
    message =  bcolors.OKGREEN + "Instrucion: Balance the weight on both legs Duration: 20s" + bcolors.ENDC
    Forward = UserInputValidator(message)            # Wait for user input 
    if Forward: 
        Data3 = Microcontrolador.Dynamicprotocol(duration=20,message="Adquiring Data",keys=keys)
    print(" ")  
    Microcontrolador.CloseSerialCommunication()
    
    return Data1,Data2,Data3