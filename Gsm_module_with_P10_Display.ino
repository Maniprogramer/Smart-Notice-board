#include <SPI.h>       
#include <DMD.h>    
#include <TimerOne.h>  
#include "Arial_black_16.h"
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

const int BUTTON_PIN1 = 2;
int buttonState1 = 0;

char *Text = "";
char startup[] = "Starting GSM Module"; 

void ScanDMD() { 
  dmd.scanDisplayBySPI();
} 


int led=13;
 
int temp=0,i=0,x=0,k=0,sent=0,first=0;
char str[200],msg[64];


void setup(void) {
  
  Timer1.initialize(5000);          
  Timer1.attachInterrupt(ScanDMD);   
  dmd.clearScreen(true);   
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  Serial.begin(115200);
  
  Serial.println("GSM Initilizing...");
  gsm_init();                           //calling the gsm_initialising funtion
  
  Serial.println("Wireless Notice");
  delay(200);
  Serial.println("    Board      ");
  delay(200);
  Serial.println("System Ready");
  Serial.println("AT+CNMI=2,2,0,0,0");    //Gsm module is set to receiving mode
  delay(500);
  Serial.println("AT+CMGF=1");            //Gsm module is set to the text mode
  delay(500);

  strcpy (msg,startup);
  p10();
  
}

void loop(void) {
  buttonState1 = digitalRead(BUTTON_PIN1);
  
  if(buttonState1 == LOW){
    p10();
    Serial.println("Button clicked");
   }

  for(unsigned int t=0; t<60000; t++) {
    serialEvent(); //calling serial event funtion
    if(temp==1) {
      dmd.clearScreen (true); 
      x=0, k=0, temp=0;
      while(x < i) {
        while(str[x] == '#') { // checks for #(hash) in the message if it is present it starts storing the message
          x++;
          while(str[x] != '*') { // checks for *(asterisk) in the message if it is present it stops storing the message
            msg[k++] = str[x++];
          }
        }
        x++;
      }
      msg[k] = '\0';
 
//       Text = msg; 
      if(msg==""){
        strcpy (msg,"No Recent Messages");
        p10();
      }
      Serial.println("Str:");
      Serial.print(str);
      Serial.println("Msg:");
      Serial.println(msg); //print the received message in the serial monitor
      
      if(sent == 1) {
        if(msg!=""){
          sent = 0;
           SendMessage(); //calling the send message funtion to send msg when the message is received from the receiver || someone
         }else{
          Serial.println ("Sending Message");
          Serial.println("AT+CMGF=1");        //Sets the GSM Module in Text Mode
          delay(1000);
          Serial.println ("Set SMS Number");
          Serial.println("AT+CMGS=\"+918686873899\"\r"); //Mobile phone number to send message
          delay(1000);
          Serial.println("Message not Received");   // Messsage content
          delay(1000);
          }
      }
      
      p10();
//      delay(1000);

      temp=0;
      i=0;
      x=0;
      k=0;
    }
  }

}

void p10(){
        dmd.selectFont(Arial_Black_16);
        dmd.drawMarquee(msg,strlen(msg),(32*DISPLAYS_ACROSS)-1,0);
        boolean ret=false;
        while(!ret){
          ret=dmd.stepMarquee(-1,0);
          delay(100);
    }
  }

void serialEvent()      //This funtion checks *(astrix) if it is present it declares as message received
{
  while(Serial.available())
  {
    char ch=(char)Serial.read();
    str[i++]=ch;
    if(ch == '*')
    {
      temp=1;
      sent=1;

      Serial.println("Message Received");     //This message is printed in serial monitor
      delay(500);                             //waits for a half second
    }
  }
}

void gsm_init()               //This funtion is to initialise the gsm module
{
  Serial.println("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    while(Serial.available()>0)     //if gsm connected and availabe it enters the loop
    {
      if(Serial.find("OK"))         //finds for ok message if true continues the next commands
      at_flag=0;
    }
    delay(1000);
  }

  Serial.println("Module Connected..");
  delay(1000);
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))     //again checks for ok message
      echo_flag=0;
    }
    delay(2000);
  }

  delay(2000);
  Serial.println("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");     
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))       //trying to find the signal 
      net_flag=0;
    }
    delay(1000);
  }
  Serial.println("Network Found..");
  delay(1000);
  
}

 void SendMessage()
{
  Serial.println ("Sending Message");
  Serial.println("AT+CMGF=1");        //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  Serial.println("AT+CMGS=\"+918686873899\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println("Message Received :");   // Messsage content
  Serial.print(msg);   // Messsage content
  delay(1000);
}
