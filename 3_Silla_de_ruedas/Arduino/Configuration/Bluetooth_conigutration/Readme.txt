INSTRUCTIONS:
UPLOAD Bluetooth_configuration to SLAVE and MASTER.
BEFORE conecting arduino push the button of the HC05, connect arduino and let go the button
after 5 seconds (It should blink slowly) 


SLAVE Configuration:
AT+UART=38400,0,0     // Set BAUD RATE
AT+ROLE=0             // Set Role to Slave (0=Slave, 1=Master)
AT+NAME= "NAME"       // Set the name you wish to have
AT+PSWD=1234          // Set Pin

AT+ADDR?              // Retrive the MAC Adress of the Slave 
(EXAMPLE ADDRESS)      
+ADDR:21:13:5d5f2     // SLAVE ADDRES   (0021,13,05d5f2) Remember to add 00's
AT+RESET              // Finish Slave setup
 
MASTER Configuration
AT+UART=38400,0,0      // Set BAUD RATE
AT+ROLE=1              // Set Role to Master (0=Slave, 1=Master)
AT+CMODE=0             // Set Conectivity by STATIC ADDRES
AT+BIND=0021,13,05d5f2 // PUT MAC Slave's MAC Address with "," instead of ":" and add 0's
AT+RESET               // Finish Master setup

Notice that if we connect by a static addresss we will not require the name and the password of the device in order to establish conection

CODE OVERVIEW (ADD ? to make query add =value to set parameter)
AT+ADDR     RETRURNS default address
AT+VERSION  RETURNS version 
AT+NAME     RETURNS NAME
AT+PSWD     RETRUNS Device Password
AT+UART     RETRUNS BAUD RATE
AT+ROLE     RETURNS ROLE
AT+RESET    EXISTS CONFIGURATION
AT+ORGL     ESTABLISH FACTORY  VALUES (BACK TO NEW) 


