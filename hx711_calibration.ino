#include "HX711.h"

#define DOUT    A1                  //Analog pin A1 assigned to DOUT
#define CLK     A0                  //Analog pin A0 assigned to CLK

HX711 scale(DOUT, CLK);

float calibration_factor = -10000; //Take some values to start calibrating
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();                                  //Reset the scale to 0

  long zero_factor = scale.read_average();      //Get a baseline reading
  Serial.print("Zero factor: ");               //This can be used to remove the need to tare the scale. Useful in permanent scale projects
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor);      //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" lbs");                   //Change this to kg and re-adjust the calibration factor if you follow SI units
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')         //To increase calibration facrtor by 10 units
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')     //To decrease calibration factor by 10 units
      calibration_factor -= 10;
  }
}
