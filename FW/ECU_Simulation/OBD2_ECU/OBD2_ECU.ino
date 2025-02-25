#include <mcp_can.h>
#include <SPI.h>
#include "mcp2515_can.h"
mcp2515_can CAN(10);                                    // Set CS to pin 10

int32_t canId = 0x000;

unsigned char len = 0;
unsigned char buf[8];
char str[20];

String BuildMessage="";
int MSGIdentifier=0;


void setup() {
  Serial.begin(115200);

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

void loop()
{
    char rndCoolantTemp=random(1,200);
    char rndRPM=random(1000,1500);
    char rndSpeed=random(0,255);
    char rndIAT=random(0,255);
    char rndMAF=random(0,255);



    
    char rndAmbientAirTemp=random(0,200);
    char rndCAT1Temp=random(1,55);
    char vehicle_Vin[17] = "1WK58FB1111111111";
    //GENERAL ROUTINE
    unsigned char SupportedPID[8] =       {1,2,3,4,5,7,8,9};
    unsigned char MilCleared[7] =         {4, 65, 63, 34, 224, 185, 147}; 
    
    //SENSORS
    unsigned char CoolantTemp[7] =        {4, 65, 5, rndCoolantTemp, 0, 185, 147};  
    unsigned char rpm[7] =                {4, 65, 12, rndRPM, 224, 185, 147};
    unsigned char vspeed[7] =             {4, 65, 13, rndSpeed, 224, 185, 147};
    unsigned char IATSensor[7] =          {4, 65, 15, rndIAT, 0, 185, 147};
    unsigned char MAFSensor[7] =          {4, 65, 16, rndMAF, 0, 185, 147};
    unsigned char AmbientAirTemp[7] =     {4, 65, 70, rndAmbientAirTemp, 0, 185, 147};
    unsigned char CAT1Temp[7] =           {4, 65, 60, rndCAT1Temp, 224, 185, 147};
    unsigned char CAT2Temp[7] =           {4, 65, 61, rndCAT1Temp, 224, 185, 147};
    unsigned char CAT3Temp[7] =           {4, 65, 62, rndCAT1Temp, 224, 185, 147};
    unsigned char CAT4Temp[7] =           {4, 65, 63, rndCAT1Temp, 224, 185, 147};
    unsigned char frame1[8] = {16, 20, 73, 2, 1, vehicle_Vin[0], vehicle_Vin[1], vehicle_Vin[2]};
    unsigned char frame2[8] = {33, vehicle_Vin[3], vehicle_Vin[4], vehicle_Vin[5], vehicle_Vin[6], vehicle_Vin[7], vehicle_Vin[8], vehicle_Vin[9]};
    unsigned char frame3[8] = {34, vehicle_Vin[10], vehicle_Vin[11], vehicle_Vin[12], vehicle_Vin[13], vehicle_Vin[14], vehicle_Vin[15], vehicle_Vin[16]};

    if(CAN_MSGAVAIL == CAN.checkReceive())  
    {
      
      CAN.readMsgBuf(&len, buf); 
        canId = CAN.getCanId();
        Serial.print("<");Serial.print(canId);Serial.print(",");

        for(int i = 0; i<len; i++)
        {  
          BuildMessage = BuildMessage + buf[i] + ",";
        }
        Serial.println(BuildMessage);
        
        //Check wich message was received.
        if(BuildMessage=="2,1,0,0,0,0,0,0,") {CAN.sendMsgBuf(0x7E8, 0, 8, SupportedPID);}
        if(BuildMessage=="2,1,1,0,0,0,0,0,") {CAN.sendMsgBuf(0x7E8, 0, 7, MilCleared);}
        
        //SEND SENSOR STATUSES
        if(BuildMessage=="2,1,5,0,0,0,0,0,") {CAN.sendMsgBuf(0x7E8, 0, 7, CoolantTemp);}
        if(BuildMessage=="2,1,12,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, rpm);}
        if(BuildMessage=="2,1,13,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, vspeed);}
        if(BuildMessage=="2,1,15,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, IATSensor);}
        if(BuildMessage=="2,1,16,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, MAFSensor);}
        if(BuildMessage=="2,1,70,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, AmbientAirTemp);}
        if(BuildMessage=="2,1,60,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT1Temp);}
        if(BuildMessage=="2,1,61,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT2Temp);}
        if(BuildMessage=="2,1,62,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT3Temp);}
        if(BuildMessage=="2,1,63,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 7, CAT4Temp);}
        if(BuildMessage=="2,9,2,0,0,0,0,0,"){CAN.sendMsgBuf(0x7E8, 0, 8,frame1);CAN.sendMsgBuf(0x7E8, 0, 8,frame2);CAN.sendMsgBuf(0x7E8, 0, 8,frame3);}
        BuildMessage="";
    }
}