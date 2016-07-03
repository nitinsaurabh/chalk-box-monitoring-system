
/* 
 * 
 * @author: Nitin
 */
 #include<SoftwareSerial.h> //To make Digital pins act as Tx and Rx pins
 #include <HX711.h> 
 #define THRESHOLD 100
 HX711 cell(3,2);
 SoftwareSerial mySerial(9,10); //Rx and Tx pins for GSM Module
 int led = 13;
 long val;
 void turnonled()     // Function to turn ON the notification LED
{
  digitalWrite(led, HIGH);
}
void turnoffled()   // Function to turn OFF the notification LED
{
  digitalWrite(led, LOW);
}

void setup() 
{
 // This function runs only once and is used to setup the Arduino */
 pinMode(led,OUTPUT)
 Serial.begin(19200);   //Setting the serial port at baud rate of 19200
 mySerial.begin(19200); //Software Serial and Serial has to have same Baud Rate
}

void SMS()
{
  /* This funcction sends text to the specified authority*/
  mySerial.println("AT+CMGF=1");    //Sets the GSM module to Text Mode
  delay(1000);                     //Delay of 1000 milli second or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r");  //AT command for sending an SMS
  delay(1000);
  mySerial.println("Chalk box is about to finish. Get a new box asap!"); // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);       // ASCII code for CTRL+Z
  delay(10000);
}

void loop() 
{ /* This code runs continuously. */
  val=cell.read();
  Serial.println("Weight cell reads: "+val);  //weight as read by load cell
  delay(1000);
  if(val<THRESHOLD)    //if weight is less than THRESHOLD weight, then send the message
  {
    SMS();      //send message to attender
    while(1)
    {
      turnonled();  //show notification LED as high
    }
  } 
  else
  {
    turnoffled();   //show notification LED as low
  }
}
