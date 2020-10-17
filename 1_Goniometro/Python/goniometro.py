# 10/13/2020 Lozano Garcia Eduardo Alejandro 

#### Read module #####
def read_from_arduino(COM="COM4",angle=180,pase=10):
    data  =  dict()                                         # Intialize empty dictionary
    #angle                                                  # Start angle 
    #pase                                                   # Set pase for angle capturing
    ser =  serial.Serial(COM,baudrate=9600, timeout=50)     # Create serial object to listen to Bus (time is imporant)
    angle = angle + pase                                    # Add pase so that wecan substract it at the begining of the program
    print("Program will end when you reach 0")              # Tell user how this program works 
    while 1:                                                # Iterate while True     
        arduinoData = ser.readline()                        # Read data 
        arduinoData = arduinoData.decode().rstrip()         # Decode data 
        angle =  angle - pase                               # Set angle 
        data[str(angle)] = arduinoData                      # Save data
        print(f"angle :{angle}, value {arduinoData}")       # Print Value
        if angle == 0:                                      # if angle  is 0
            ser.close()                                     # Close buz
            break                                           # break 
    return data
        
# Note: time is the amount o time that serial waits to recive data, if it does not recive data it returns blank and continues 




### Excel module ###

def save_to_excel(name,data,c1="Voltage",c2="Angle"):
    """ Save data to excel 
        c1:   name of first column
        c2:   name of second column
        name: name of file
    """
    
    with open(name+".csv","w") as handler:         # Open file with context manager
        head= c1 + "," + c2 + "\n"                 # Set head row
        handler.write(head)                        # Write head
        
        ### Iterate over data and append it ###
        for a,v in zip(data.keys(),data.values()): # Iterate over data
            row = v + "," + a + "\n"               # Set current row
            handler.write(row)                     # Write current row 
    print(f"file written as {name}.csv ")          # Tell user the data has been saved

def read_from_excel(file,c1="Voltage",c2="Angle"):
    """ Read file from excel"""
    data_frame = pd.read_csv("name.csv")
    x =   data_frame.loc[:,c1].to_numpy()         # Get x
    y =   data_frame.loc[:,c2].to_numpy()         # Get y
    
    return x,y
    

def raw_data(data):
    ''' Work with Raw data (without saving it to Excel, this method is not recomended)'''
    x = []
    y = []
    for xi,yi in  zip(data.values(),data.keys()):
        x.append(float(xi))
        y.append(int(yi))
    x = np.array(x)
    y = np.array(y)
    return x,y


#### Preprocessing moduel ###

### L1 + L2 NORM ###
def L1_2_Norm(X,y,W,b):
    N = len(X)
    L1 = 1/N*(np.abs(X.dot(W) - y)).sum()
    L2 = 1/N*((X.dot(W) - y)**2).sum()
    return  b*L2 + (1-b)*L1

def L1_2_Norm_gradient(X,y,W,b):
    N = len(X)
    L1 = (1/N)*(X.T).dot(np.sign(X.dot(W) - y))
    L2 = (2/N)*(X.T).dot(X.dot(W) - y)
    return b*L2 + (1-b)*L1

def L1_2_Norm_Gradient_descent(X,y,W,a,b,epochs):
    """ X: Matirx of Data
        y: Tags
        W: Inital weihgts
        a: Learning Rate 
        b: Weight for L1 and L2 norms
        epochs: Epochs 
    """
    loss=[]
    N = len(y)
    for i in range(0,epochs):
         ### Compute gradient ###
        dW = L1_2_Norm_gradient(X,y,W,b)
        
        ### Gradient Descent ###
        W = W - a*dW
        
        loss.append(a*L1_2_Norm(X,y,W,b))
    
    y_hat = X.dot(W)
    y_mean = y.sum()/N
    st = ((y-y_mean)**2).sum()   # Standar deviation  of data
    sr = ((y-y_hat)**2 ).sum()   # standard deviation of prediction
    r2   = (st-sr)/st            # R2 coefficient
    
    return W,loss,r2

def plot_loss(loss,X,y,W,r2,name="L2"):
   
    fig,ax = plt.subplots(ncols=2,nrows=1,figsize=(15,7))
    
    ### PLOT LOSS ###
    iterations = list(range(0,len(loss)))
    ax[0].plot(iterations,loss,"b--",label ="loss")
    ax[0].legend(loc="lower right")
    ax[0].set_xlabel("iterations")
    ax[0].set_ylabel("loss ")
    ax[0].set_title(f"Linear Regression with {name} Norm loss={loss[-1]:2f}")
    ax[0].grid("on")
    
    ### PLOT  Data ###
    y_hat = X.dot(W)
    x = X[:,1]
    ax[1].plot(x,y_hat,"b--",label ="prediction")
    ax[1].plot(x,y,"r*",label='data')
    ax[1].legend(loc="lower right")
    ax[1].set_xlabel("x")
    ax[1].set_ylabel("y")
    ax[1].set_title(f"Linear Regression with r2={r2:2f}")
    plt.grid("on")
    plt.show()