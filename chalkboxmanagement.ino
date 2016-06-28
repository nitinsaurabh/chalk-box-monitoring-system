/*
 * 
 * @author: Nitin
 */
 #include<SoftwareSerial.h>
 int weight=A5;
 int ledNotify=5;
 SoftwareSerial mySerial(9,10);

 
void setup() {
  // put your setup code here, to run once:

pinMode(weight,INPUT)
pinMode(ledNotify,OUTPUT)
Serial.begin(19200);
mySerial.begin(19200);
}

void SMS()
{
  mySerial.println("AT+CMGF=1");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919600577607\"\r");
  delay(1000);
  mySerial.println("Chalk box is about to finish. Get a new box asap!");
  delay(100);
  mySerial.println((char)26);
  delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
int i=0;
int loadcell=analogRead(weight);
Serial.println("Weight cell reads: "+loadcell);
delay(1000);
if(weight>100)
  {
    SMS();
    while(1)
      {
        digitalWrite(ledNotify,HIGH);
      }
  }
else
  {
    digitalWrite(ledNotify,LOW);
  }
}

