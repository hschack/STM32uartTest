#include <Arduino.h>

#include <Arduino.h>
#define MODEM_TX PA2
#define MODEM_RX PA3
#define UC_RESET PA7
#define UC_WAKEUP_1 PB0
#define UC_WAKEUP_2 PB1
//HardwareSerial Serial2(PA3, PA2);
HardwareSerial SerialAT( MODEM_RX, MODEM_TX );

//String SettdcAPN = "\""IP"\",nbiot.tdc.dk";

void setup()
{
  Serial.begin(115200);
  SerialAT.begin(115200);
// Power up "recive"
// LoadVerifyImageHead read(len=272), Time(ms)->0.
// test:VerifyImageHead skip
// VerifyImageBody sha256 skip

// *ATREADY: 1

// SIM Ready

// +CEREG: 2

// lidt efter ca 10 til 20 sek.
// Network Available

// +CEREG: 1  // reg på hjemme netværk = 1 5 = Roaming

  // Run once
  
  SerialAT.println("AT+COPS?"); //(tdc= AT+COPS=1,2,"28301",9)
  delay(1000);
  // +COPS: 0,2,"23801",9
  SerialAT.println("AT+CGPADDR"); //Request the assigned IP address
  delay(5000);
  // +CGPADDR: 0,"10.9.18.110"
  // +CGPADDR: 1
  SerialAT.println("AT+CGCONTRDP"); //Auto connect !! vent på IP adr
  delay(10000); 
  SerialAT.println("AT+VIOSET=2"); //Set Module to 2.8V
  delay(1000);
  // OK
  SerialAT.println("AT+CFUN=0"); //Switch off the radio module
  delay(1000); 
  // OK
  // +CEREG: 0
  SerialAT.println("AT+QCBAND=0,20"); //Set the frequency band to 20 for TDC (think can read)
  delay(1000);
  // OK
  SerialAT.println("AT+CFUN=1,1"); //Switch on the radio again
  delay(5000); 
  // SIM Ready

  // +CEREG: 2

  // Network Available

  // +CEREG: 1 
  
  // OK
  SerialAT.println("AT+CGDCONT=1,\"IP\",\"nbiot.tdc.dk\""); //Set APN AT+CGDCONT= 0 -> 10 også prævet med "IP"
  //SerialAT.println("AT+CGDCONT=1," + SettdcAPN); //Set APN AT+CGDCONT= 0 -> 10
  delay(5000);
  SerialAT.println("AT+CGCONTRDP"); //Auto connect !! vent på IP adr
  delay(10000); 
  // +CGCONTRDP: 0,5,"internet","10.136.240.222.255.255.255.0","10.136.240.222","194.239.134.83","193.162.153.164",,,,,1500
  // OK   
  SerialAT.println("AT+CGPADDR"); //Request the assigned IP address
  // +CGPADDR: 0,"10.136.240.222"
  // +CGPADDR: 1

  // OK
  delay(1000);
  SerialAT.println("AT+COPS?"); //(tdc= AT+COPS=1,2,"28301",9)
  delay(5000);   
  // +COPS: 0,2,"23801",9

  // OK
  SerialAT.println("AT+CGCONTRDP=?"); //check IP adr
  delay(5000);
  // +CGCONTRDP: (0)

  // OK
  SerialAT.println("AT+CGDCONT?"); //check IP adr
  delay(5000);
  // +CGDCONT: 0,"IP","internet","10.136.240.222"
  // +CGDCONT: 1,"IPV6","nbiot.tdc.dk"

  // OK
}

void loop()
{

}