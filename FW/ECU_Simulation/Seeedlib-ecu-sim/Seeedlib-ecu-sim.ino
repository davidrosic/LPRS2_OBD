#include <mcp_can.h>
#include <SPI.h>
#include "mcp2515_can.h"

mcp2515_can CAN(10);                                      // Set CS to pin 10


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

    
    unsigned char BuildMessage[8] ="2,1,12,0,0,0,0,0,";

    sendPid(BuildMessage, rpm);

    
    
}

void sendPid(unsigned char __pid, char temp[]) {
    unsigned char tmp[8] = {0x02, 0x01, __pid, 0, 0, 0, 0, 0};
    SERIAL_PORT_MONITOR.print("SEND PID: 0x");
    SERIAL_PORT_MONITOR.println(__pid, HEX);
    CAN.sendMsgBuf(__pid, 0, 8, temp);
}
