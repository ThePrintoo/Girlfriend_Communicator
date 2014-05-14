/**********************************************************************
* © 2014 YD Ynvisible, S.A.
*
* FileName:        Girlfriend_Communicator.ino
* Dependencies:    SoftwareSerial.h, CapacitiveSensor.h
* Processor:       ATmega328
* IDE:             Arduino 1.0.5
*
* Description:
* Sending messages to your girlfriend via Bluetooth 4.0 to her smartphone
* 
**********************************************************************/

#include <CapacitiveSensor.h>
#include <SoftwareSerial.h> //Software Serial Port
#define RxD A0
#define TxD A1
SoftwareSerial blueToothSerial(RxD,TxD);

CapacitiveSensor   cs_19_18 = CapacitiveSensor(19,18);       // 10M resistor between pins 19 & 18, pin A4 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_19_0 = CapacitiveSensor(19,0);         // 10M resistor between pins 19 & 0, pin 0 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_19_2 = CapacitiveSensor(19,2);         // 10M resistor between pins 19 & 2, pin 2 is sensor pin, add a wire and or foil if desired

char a[10] = "#Miss You";
char b[14] = "#Leaving work";
char c[36] = "#I'm Sorry I forgot our anniversary";
char recvChar;
int x=0, touch=0, touch2=0, touch3=0;

void setup()
{
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  cs_19_18.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate
  cs_19_0.set_CS_AutocaL_Millis(0xFFFFFFFF);     
  cs_19_2.set_CS_AutocaL_Millis(0xFFFFFFFF);    
}
void loop()
{
  long start = millis(); 
  long total1 =  cs_19_18.capacitiveSensor(30);
  long total2 =  cs_19_0.capacitiveSensor(30);    
  long total3 =  cs_19_2.capacitiveSensor(30);    
    
  if(blueToothSerial.available()){            //check if the pipe is free
    
    if(total1>10){
      touch=1;
      cs_19_18.reset_CS_AutoCal();
    }   
    if(touch==1){
      touch=0;
      x++;
      a[10]=char(x+'0');      
      blueToothSerial.print(a);               //sending the whole vector through bluetooth
    }
    
    if(total2>10){
      touch2=1;
      cs_19_0.reset_CS_AutoCal();
    }   
    if(touch2==1){
      touch2=0;
      x++;
      b[14]=char(x+'0');      
      blueToothSerial.print(b);               //sending the whole vector through bluetooth
    }     
    
    if(total3>10){
      touch3=1;
      cs_19_2.reset_CS_AutoCal();
    }   
    if(touch3==1){
      touch3=0;
      x++;
      c[36]=char(x+'0');      
      blueToothSerial.print(c);               //sending the whole vector through bluetooth
    }     
  }
}  
  
void setupBlueToothConnection(){
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 9600
  delay(10); // This delay is required.
  blueToothSerial.print("AT+RENEW"); //Restore all setup value to factory setup
  delay(10);  // This delay is required.
  blueToothSerial.print("AT+ROLE0"); //make it a slave   
  delay(10);  // This delay is required.
}
