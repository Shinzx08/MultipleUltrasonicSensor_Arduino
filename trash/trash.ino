#include <SoftwareSerial.h>
#include <Ultrasonic.h>


int data;
Ultrasonic ultrasonic(3, 2);
SoftwareSerial sim800l(4, 5);



void setup(){
  Serial.begin( 9600 );
  sim800l.begin(9600);
  delay(500);
}
void loop(){
  data =   ultrasonic.read(CM);
  if (data >= 71) { //change condition to the height of your trashbin
    Serial.println("Trashbin is full");
    delay(100);   

    SendSMS(); 
  }  
   if (sim800l.available()){            
    Serial.write(sim800l.read()); 
  }
delay(10000);
}

void SendSMS() {
  Serial.println("Sending SMS...");              
  sim800l.print("AT+CMGF=1\r");                 
  delay(100);
  sim800l.print("AT+CMGS=\"+*********\"\r"); //change to target number
  delay(500);
  sim800l.print("Trashbin is full");       
  delay(500);
  sim800l.print((char)26);
  delay(500);
  sim800l.println();
  Serial.println("SMS Sent.");
  delay(500);
}

 
