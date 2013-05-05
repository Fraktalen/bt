/*
BluetoothShield Demo Code Slave.pde. This sketch could be used with
Master.pde to establish connection between two Arduino. It can also
be used for one slave bluetooth connected by the device(PC/Smart Phone)
with bluetooth function.
2011 Copyright (c) Seeed Technology Inc.  All right reserved.
 
Author: Steve Chang
 
This demo code is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
 
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
For more details about the product please check http://www.seeedstudio.com/depot/
 
*/
 
 
/* Upload this sketch into Seeeduino and press reset*/
 
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 0
#define TxD 1
 
#define DEBUG_ENABLED  1
 
SoftwareSerial blueToothSerial(RxD,TxD);

int motor = 13;

int ledPinOne = 3;  //LED Channel 1
int ledPinTwo = 5;  //LED Channel 2


 
void setup() 
{ 
  pinMode(motor, OUTPUT); // to make motor spin
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();

//analogWrite(ledPinOne, 255);   
//analogWrite(ledPinTwo, 255); 

} 

void setupBlueToothConnection()
{
  blueToothSerial.begin(115200); //Set BluetoothBee BaudRate to default baud rate 38400
  
   digitalWrite(motor, HIGH);
   delay(500);
   digitalWrite(motor, LOW); 
  
  blueToothSerial.println("hello world");
  delay(2000); // This delay is required.
 
  blueToothSerial.print("---\n");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}
 
void loop() 
{ 
  char recvChar;  //Indkomne karakterer
  String content = ""; //En tekststreng der indeholder indkomne karakterer.
  String Channelstring =""; //En tekststreng der indeholder kanalnummer som tekststreng
  String PWMString = ""; //En tekststreng der indeholder den PWM værdi der skal sættes.
  
  int channelStartIndex;
  int channelEndIndex;  
  int TextStringLength;  
  int ChannelNumber;
  int PwmValue; 

  while(1){
    if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
      if (blueToothSerial.available()){
          recvChar = blueToothSerial.read();
      }
      Serial.print(recvChar);

      if (recvChar == 'A'){ //hvis vi har modtaget en enter karakter (13):  
               digitalWrite(motor, HIGH);
                    delay(1000);
                    digitalWrite(motor, LOW);     

      channelStartIndex = content.indexOf('C'); //Søg om der er angivet en kanal i tekststrengen (C for channel)
      
      if (channelStartIndex >= 0){ //Karakteren C blev fundet...
       channelEndIndex = content.indexOf('P'); //Find P i tekststrengen. Det er mellem karakteren C og P at kanalnummeret står.
             if (channelEndIndex >= 0){ //Karakteren P blev fundet...
                 Channelstring = content.substring(channelStartIndex+1, channelEndIndex);  //Klip den del af den modtagne tekststreng ud som indeholder kanalnummer.

                  TextStringLength = 0;
                  TextStringLength = content.length(); //Find den samlede længde af den modtagne tekststreng.
                  PWMString = content.substring(channelEndIndex+1,TextStringLength);//Klip den del af den modtagne tekststreng ud som indeholder PWM værdi.

                  //Nu indeholder Channelstring den kanal som skal styres i ASCII
                  //og
                  //PWMString indeholder den PWM værdi der skal sættes i ASCII
                  //De to værdier skal nu konverteres til tal:
                  
                  ChannelNumber = Channelstring.toInt();
                  PwmValue = PWMString.toInt();
                  
                  blueToothSerial.print("Setting channel ");
                  blueToothSerial.print(ChannelNumber);
                  blueToothSerial.print(" to PWM value ");
                  blueToothSerial.println(PwmValue);
                  
                  if(ChannelNumber==1){
                  //analogWrite(ledPinOne, PwmValue);  
                    digitalWrite(motor, HIGH);
                    delay(1000);
                    digitalWrite(motor, LOW); 
                  }else if (ChannelNumber == 2){
                 // analogWrite(ledPinTwo, PwmValue); 
                     digitalWrite(motor, HIGH);
                    delay(1000);
                    digitalWrite(motor, LOW);
                  }else if (ChannelNumber == 13){
                    digitalWrite(motor, HIGH);
                    delay(1000);
                    digitalWrite(motor, LOW);
                  }else{
                  blueToothSerial.println("Command not understood. Channel or PWM value not defined");
                  blueToothSerial.println("Use Syntax: C1P100 (for channel 1 PWM 100)");                  
                  }
                  
            }else{
                   blueToothSerial.println("Command not understood. Channel or PWM value not defined");
                   blueToothSerial.println("Use Syntax: C1P100 (for channel 1 PWM 100)");
             }
      }else{
      blueToothSerial.println("Command not understood");
      blueToothSerial.println("Use Syntax: C1P100 (for channel 1 PWM 100)");
      }
      
      content=""; //Tøm indholdet af den modtagne tekststreng.
      }else{ //Hvis vi ikke har modtaget en enter karakter:      
      content.concat(recvChar); //Tilføj den indkomne karakter til tekststrengen content.
      }

      

      //pwmval = recvChar  - '0';  //Omregn fra datatypen character til tal. Eks. tastes 1 på keyboardet har dette tal ascii værdien 49
      
      //analogWrite(ledPin, pwmval);  //Sæt LED pin til PWM værdi
    
      }
    }

}
 





