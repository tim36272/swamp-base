#include <Manchester.h>
#include <SwampController.h>
/*

  Manchester Transmitter example
  
  In this example transmitter will send one byte of data and 4bit sender ID per transmittion
  message also contains a checksum and receiver can check if the data has been transmited correctly

  try different speeds using this constants, your maximum possible speed will 
  depend on various factors like transmitter type, distance, microcontroller speed, ...

  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7


*/

#define TX_PIN 5  //pin where your transmitter is connected
#define COMMAND_PIN 11


void setup() {
  //man.workAround1MhzTinyCore(); //add this in order for transmitter to work with 1Mhz Attiny85/84
  man.setupTransmit(TX_PIN, MAN_1200);
}



commandState_t pumpState = COMMAND_STATE_IDLE;
unsigned long pumpTimestamp;
commandState_t fanState = COMMAND_STATE_IDLE;
unsigned long fanTimestamp;
commandState_t powerState = COMMAND_STATE_IDLE;
unsigned long powerTimestamp;

void loop() {
  checkForPinSignal(10,&powerState, &powerTimestamp);
  checkForPinSignal(11,&fanState, &fanTimestamp);
  checkForPinSignal(12,&pumpState, &pumpTimestamp);
  if(powerState == COMMAND_STATE_ENGAGE) {
    transmitCommand(SWAMP_POWER,5000);
    powerState = COMMAND_STATE_IDLE;
  }
  if(fanState == COMMAND_STATE_ENGAGE) {
    transmitCommand(SWAMP_FAN,5000);
    fanState = COMMAND_STATE_IDLE;
  }
  if(pumpState == COMMAND_STATE_ENGAGE) {
    transmitCommand(SWAMP_PUMP,5000);
    pumpState = COMMAND_STATE_IDLE;
  }
}
