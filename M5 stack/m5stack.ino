#include <M5Stack.h>
#include <TinyGPS++.h>
#include <Wire.h>

#define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
#define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
#define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
#define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define VL53L0X_REG_SYSRANGE_START                  0x00
#define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
#define VL53L0X_REG_RESULT_RANGE_STATUS             0x14

#define ToF_ADDR 0x29
#define NOTE_DH2 661

#include <WiFi.h>
#include <esp_wifi.h>
WiFiClient wifi_client;
#include <PubSubClient.h>
PubSubClient ps_client( wifi_client );
#include "Timer.h"


/*******************************************************************************************
 *
 * Global Variables
 *
 ******************************************************************************************/


// My windows laptop
uint8_t guestMacAddress[6] = {0xDC, 0xFB, 0x48, 0x4C, 0xF6, 0x35};

// My home Wifi settings
const char* ssid = "H660W";            
const char* password = "0952009537";   


// MQTT Settings
const char* MQTT_clientname = "pet_iot"; 
const char* MQTT_sub_topic = "pet_warn";
const char* MQTT_pub_topic = "pet_info";

// Please leave this alone - to connect to HiveMQ
const char* server = "broker.mqttdashboard.com";
const int port = 1883;

const byte DELAY_CHECK_CONST = 100;                           /* Delay to check if any data received 100 * 10 = 1 sec */
const byte MINUMUM_SAT = 4;                                   /* Minumum number of satellites before fix is accepted */

boolean UPDATE_FLAG;                 
boolean LOC_UPDATE_FLAG;
byte DELAY_CHECK = 0;
byte GPS_STATUS; 
unsigned int NO_OF_SAT; 
unsigned int CHARS_PROCESSED = 0;  
unsigned int OLD_CHARS_PROCESSED = 1;                               
float OLD_LOC_LAT;
float OLD_LOC_LNG;
byte gbuf[16];
char CONVERTED[32]; 

Timer publishing_timer(5000);
TinyGPSPlus gps;
HardwareSerial GPSRaw(2);




/*******************************************************************************************
 *
 * Setup() and Loop()
 *
 ******************************************************************************************/

// Standard, one time setup function.
void setup() {
  
    Wire.begin(); 
    M5.begin();
    M5.Power.begin();
    GPSRaw.begin(9600);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor( 10, 10 );
    M5.Lcd.setTextColor( WHITE );
    M5.Lcd.println("Reset, connecting...");

    Serial.begin(115200);
    delay(10);
    Serial.println("*** RESET ***\n");

    setupWifi();
    setupMQTT();
    UPDATE_FLAG = true;
    LOC_UPDATE_FLAG = true; 

}


// Standard, iterative loop function (main)
void loop() {

  if (!ps_client.connected()) {
    reconnect();
  }
  ps_client.loop();
  gps_loop();
  
  if( M5.Lcd.getCursorY() > M5.Lcd.height() ) {
    M5.Lcd.fillScreen( BLACK );
    M5.Lcd.setCursor( 0, 10 );
  }
}


void gps_loop{
 while (GPSRaw.available() > 0)                             
  {
    gps.encode(GPSRaw.read());                               
  }

  CHARS_PROCESSED = gps.charsProcessed();               

  /* No chars processed or no more data received --> Checked every 10ms ? */
  if ((CHARS_PROCESSED  < 10)|| (CHARS_PROCESSED == OLD_CHARS_PROCESSED))                                   
  {
    if (DELAY_CHECK < 230)                              
    {
      DELAY_CHECK = DELAY_CHECK + 10;            
    }
  }
  else                                                
  {
    DELAY_CHECK = 0;                                         
  }

  /* Case 1: Timeout */
  if (DELAY_CHECK > DELAY_CHECK_CONST)                     
  {
    if (GPS_STATUS > 0)                                  
    {
      UPDATE_FLAG = true;                                    
    }
    if (UPDATE_FLAG == true)                               
    {
      SUB_DISPLAY_NO_REC();                             
      UPDATE_FLAG = false;                                   
    } 
    GPS_STATUS = 0;                                         
  }
  else                                                        
  {
    if (GPS_STATUS == 0)                                     
    {
      GPS_STATUS = 1;                                         
      UPDATE_FLAG = true;                                    
    }
  }

  /* Case 2: Receiver found and data are received but no GPS signal --> Status 1 */
  if (GPS_STATUS == 1)                                        
  {
    
    if (gps.satellites.isValid() == true)                    
    {
      NO_OF_SAT = gps.satellites.value();                       
    }
    else                                                      
    {
      NO_OF_SAT = 0;                                       
    }
    /* Decide on number of satellites received */
    if (NO_OF_SAT < MINUMUM_SAT)                           
    {
      if (UPDATE_FLAG == true)                              
      {
        SUB_DISPLAY_NO_GPS();                              
        UPDATE_FLAG = false;                                 
      } 
    }
    else                                                
    {
      GPS_STATUS = 2;                                                                      
      UPDATE_FLAG = true;                                    
      LOC_UPDATE_FLAG = true;                                
    } 
  }

   /* Case 2: Enough satellites received ? --> Valid fix*/
  if (GPS_STATUS == 2)                                 
  {
    if (gps.satellites.isValid() == true)                   
    {
      NO_OF_SAT = gps.satellites.value();                    
    }
    else                                                   
    {
      NO_OF_SAT = 0;                                       
    }
    if (NO_OF_SAT < MINUMUM_SAT)                            
    {   
      GPS_STATUS = 1;                                     
      UPDATE_FLAG = true;                                     
    } 
    else                                                  
    {
      if (UPDATE_FLAG == true)                              
      {
        SUB_DISPLAY_MAIN(); 
        UPDATE_FLAG = false;                                  
      }       
           
      SUB_DISPLAY_LOCATION();
      measure_distance();                                
    }
  } 

  OLD_CHARS_PROCESSED = CHARS_PROCESSED;
}


/*******************************************************************************************
 *
 * Helper functions after this...
 *
 ******************************************************************************************/


void publishMessage( String message) {

  if( ps_client.connected() ) {

    if( message.length() > 0 ) {
      char msg[ message.length() ];
      message.toCharArray( msg, message.length() );
      M5.Lcd.println( message );
      ps_client.publish( MQTT_pub_topic, msg );
    }

  } else {
    Serial.println("Can't publish message: Not connected to MQTT :( ");

  }


}

void callback(char* topic, byte* payload, unsigned int length) {

  String in_str = "";

  // Copy chars to a String for convenience.
  // Also prints to USB serial for debugging
  for (int i=0;i<length;i++) {
    in_str += (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  M5.Speaker.tone(NOTE_DH2, 200); 
  M5.Lcd.println( in_str );


}

void measure_distance() {
  write_byte_data_at(VL53L0X_REG_SYSRANGE_START, 0x01);

  read_block_data_at(VL53L0X_REG_RESULT_RANGE_STATUS, 12);//read 12 bytes once

  uint16_t dist = makeuint16(gbuf[11], gbuf[10]);//split distance data to "dist"
  byte DeviceRangeStatusInternal = ((gbuf[0] & 0x78) >> 3);

  M5.Lcd.fillRect(123, 170, 110, 44, 0x1E9F);   
  M5.Lcd.setCursor(125, 175);
  M5.Lcd.print(dist);
  M5.Lcd.print("mm");
  publishMessage(MQTT_pub_topic,String(dist));
}


void SUB_DISPLAY_LOCATION ()
{
  boolean LOC_FAIL_UPDATE;                                   
  float ACT_LOC_LAT;                                          
  float ACT_LOC_LNG;                                         
  float ROUNDED_VAL;                                        
  uint16_t CONVERT_DATA;                                   

  LOC_FAIL_UPDATE = false;                               
  
  if (gps.location.isValid() == true)                         /* Valid GPS location received ? */
  {
    LOC_FAIL_UPDATE = true;                                  
    M5.Lcd.setTextSize(3);                                  
    ACT_LOC_LAT = gps.location.lat();                     
    ACT_LOC_LNG = gps.location.lng();                        

    /* Display lattitude value */
    ROUNDED_VAL = SUB_ROUND_FLOAT_VALUE (ACT_LOC_LAT, 5);     /* Call subroutine to round float to 5 digits */
    if ((OLD_LOC_LAT != ROUNDED_VAL) || (LOC_UPDATE_FLAG == true))                          
    {
      OLD_LOC_LAT = ROUNDED_VAL;                             
      M5.Lcd.fillRect(114, 40, 169, 44, 0x1E9F);             
      M5.Lcd.setCursor(115, 50);                               
      M5.Lcd.print(ACT_LOC_LAT, 6);                     
    }
    
    /* Display longitude value */
    ROUNDED_VAL = SUB_ROUND_FLOAT_VALUE (ACT_LOC_LNG, 5);     /* Call subroutine to round float to 5 digits */
    if ((OLD_LOC_LNG != ROUNDED_VAL) || (LOC_UPDATE_FLAG == true))
    {
      OLD_LOC_LNG = ROUNDED_VAL;                         
      M5.Lcd.fillRect(114, 94, 169, 44, 0x1E9F);            
      M5.Lcd.setCursor(115, 104);                         
      M5.Lcd.print(ACT_LOC_LNG, 6);                    
 
    }
    String stringtopub =  String(String(ACT_LOC_LAT) + ","+String(ACT_LOC_LNG));
    publishMessage(MQTT_pub_topic,stringtopub);
    LOC_UPDATE_FLAG = false;                             
  }
  else                                                        /* Not valid GPS location received ? */    
  {
    if (LOC_FAIL_UPDATE == true)                           
    { 
      M5.Lcd.setTextSize(3);
      M5.Lcd.fillRect(114, 40, 169, 44, 0x1E9F);            
      M5.Lcd.fillRect(114, 94, 169, 44, 0x1E9F);              
      M5.Lcd.setCursor(115, 50);                           
      M5.Lcd.print("--.------");
      M5.Lcd.setCursor(115, 104);
      M5.Lcd.print("--.------");   
    }
    String stringtopub =  String(String("--.------" + ","+"--.------");
    publishMessage(MQTT_pub_topic,stringtopub);
    LOC_FAIL_UPDATE = false;                                
  }
}

 /* Display mainpage */
void SUB_DISPLAY_MAIN (void)
{    
  M5.Lcd.fillRect(0, 0, 320, 30, 0x439);                     
  M5.Lcd.fillRect(0, 31, 320, 178, 0x1E9F);                   
  M5.Lcd.fillRect(0, 210, 320, 30, 0x439);                  
  M5.Lcd.fillRect(0, 30, 320, 4, 0xffff);                    
  M5.Lcd.fillRect(0, 208, 320, 4, 0xffff);                    
  M5.Lcd.fillRect(0, 84, 320, 4, 0xffff);                   
  M5.Lcd.fillRect(0, 140, 320, 4, 0xffff);                   
  M5.Lcd.setTextSize(2);                                     
  M5.Lcd.setTextColor(WHITE);                                
  M5.Lcd.setCursor(10, 7);                                  
  M5.Lcd.print("Pet information");

    M5.Lcd.setCursor(5, 40);                                 
    M5.Lcd.print("Degree");
    M5.Lcd.setCursor(5, 65);  
    M5.Lcd.print("of Lat.");
    M5.Lcd.setCursor(5, 94);                                
    M5.Lcd.print("Degree");
    M5.Lcd.setCursor(5, 119);  
    M5.Lcd.print("of Long.");
    M5.Lcd.setCursor(5, 175);                               
    M5.Lcd.print("Distance");
}


/*******************************************************************************************
 *
 *
 * You shouldn't need to change any code below this point!
 *
 *
 *
 ******************************************************************************************/


void setupMQTT() {
    ps_client.setServer(server, port);
    ps_client.setCallback(callback);
}

void setupWifi() {

    byte mac[6];
    Serial.println("Original MAC address: " + String(WiFi.macAddress()));
    esp_base_mac_addr_set(guestMacAddress);
    Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    Serial.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid );
    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("IP address allocated: " + String(WiFi.localIP()));
}

void setupWifiWithPassword( ) {

    byte mac[6];
    Serial.println("Original MAC address: " + String(WiFi.macAddress()));
    esp_base_mac_addr_set(guestMacAddress);
    Serial.println("Borrowed MAC address: " + String(WiFi.macAddress()));

    Serial.println("Connecting to network: " + String(ssid));
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) delay(500);
    Serial.println("IP address allocated: " + String(WiFi.localIP()));

}



void reconnect() {

  // Loop until we're reconnected
  while (!ps_client.connected()) {

    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    // Sometimes a connection with HiveMQ is refused
    // because an old Client ID is not erased.  So to
    // get around this, we just generate new ID's
    // every time we need to reconnect.
    String new_id = generateID();

    Serial.print("connecting with ID ");
    Serial.println( new_id );

    char id_array[ (int)new_id.length() ];
    new_id.toCharArray(id_array, sizeof( id_array ) );

    if (ps_client.connect( id_array ) ) {
      Serial.println("connected");

      // Once connected, publish an announcement...
      ps_client.publish( MQTT_pub_topic, "reconnected");
      // ... and resubscribe
      ps_client.subscribe( MQTT_sub_topic );
    } else {
      M5.Lcd.println(" - Coudn't connect to HiveMQ :(");
      M5.Lcd.println("   Trying again.");
      Serial.print("failed, rc=");
      Serial.print(ps_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  M5.Lcd.println(" - Success!  Connected to HiveMQ\n\n");
}

String generateID() {

  String id_str = MQTT_clientname;
  id_str += random(0,9999);

  return id_str;
}

uint16_t bswap(byte b[]) {
  // Big Endian unsigned short to little endian unsigned short
  uint16_t val = ((b[0] << 8) & b[1]);
  return val;
}

uint16_t makeuint16(int lsb, int msb) {
    return ((msb & 0xFF) << 8) | (lsb & 0xFF);
}

uint16_t VL53L0X_decode_vcsel_period(short vcsel_period_reg) {
  // Converts the encoded VCSEL period register value into the real
  // period in PLL clocks
  uint16_t vcsel_period_pclks = (vcsel_period_reg + 1) << 1;
  return vcsel_period_pclks;
}

/*
 * IIC Functions
 */
/* function description: write one byte data */
void write_byte_data(byte data) {
  Wire.beginTransmission(ToF_ADDR);
  Wire.write(data);
  Wire.endTransmission();
}

/* function description: write one byte data to specifical register */
void write_byte_data_at(byte reg, byte data) {
  Wire.beginTransmission(ToF_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

/* function description: read multiple bytes data from specifical register */
void read_block_data_at(byte reg, int sz) {
  int i = 0;
  write_byte_data(reg);
  Wire.requestFrom(ToF_ADDR, sz);
  for (i=0; i<sz; i++) {
    while (Wire.available() < 1) delay(1);
    gbuf[i] = Wire.read();
  }
}

void SUB_DISPLAY_NO_GPS (void)
{  
    M5.Lcd.fillRect(0, 0, 320, 30, 0x439);                 
    M5.Lcd.fillRect(0, 31, 320, 178, 0x1E9F);                  
    M5.Lcd.fillRect(0, 210, 320, 30, 0x439);                  
    M5.Lcd.setTextSize(3);                                    
    M5.Lcd.setTextColor(WHITE);    
    M5.Lcd.setCursor(70, 80);                             
    M5.Lcd.print(F("No valid"));
    M5.Lcd.setCursor(50, 120);
    M5.Lcd.print(F("GPS signal!"));     
}

/* Input to this subroutine is float value amd number of digits after decimal point*/
float SUB_ROUND_FLOAT_VALUE (float FLOAT_IN, byte DIGITS) 
{
  float SHIFTS = 1;                                        
  while (DIGITS--)                                          
  {
    SHIFTS *= 10;                                             
  }
  return floor(FLOAT_IN * SHIFTS + .5) / SHIFTS;             
}
