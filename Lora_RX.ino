#include <LoRa.h>
#include <PCF8574.h>

PCF8574 PCF(0x20);

//define the pins used by the transceiver module
#define ss D0    //D0
#define rst D1   //D1
#define dio0 D2  //D2

String LoRaData;

void setup() {
  Serial.begin(9600);
  Serial.println("Role: Receiver");

  LoRa_setup();
  PCF8574_setup();

  //if init succeeded!
  PCF.digitalWrite(P4, LOW);
  PCF.digitalWrite(P5, LOW);
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.println(LoRaData + " || RSSI: " + LoRa.packetRssi()); 
    }
    
    // print RSSI of packet
    // Serial.print(" -> with RSSI ");
    // Serial.println(LoRa.packetRssi());

  }
}

void LoRa_setup(){
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    // Serial.println("Starting LoRa failed!..");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSpreadingFactor(10);           // ranges from 6-12,default 7 see API docs
  LoRa.setSignalBandwidth(125E3);           // for -139dB (page - 112)
  LoRa.setCodingRate4(5);                   // for -139dB (page - 112)
  LoRa.setSyncWord(0x31);

  // Serial.println("LoRa init succeeded!");
}

void PCF8574_setup(){
  //Active LOW (Pull down)

  // PCF.pinMode(P0, OUTPUT);
  // PCF.pinMode(P1, OUTPUT);
  // PCF.pinMode(P2, OUTPUT);
  // PCF.pinMode(P3, OUTPUT);
  PCF.pinMode(P4, OUTPUT);
  PCF.pinMode(P5, OUTPUT);
  // PCF.pinMode(P6, OUTPUT);
  // PCF.pinMode(P7, OUTPUT);

  PCF.begin();
}



