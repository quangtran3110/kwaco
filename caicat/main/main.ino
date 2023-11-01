/* V0-
   V1-date/time
   V2-rửa lọc
   V3-man/auto cap 1
   V4-on/off bao ve ampe
   V5-terminal
   V6-chon may bao ve
   V7-min
   V8-max
   V9-time input
   V10-on B1
   V11-Off B1
   V12-on B2
   V13-off B2
   V14-on B3
   V15-off B3
   V16-on G1
   V17-off G1
   V18-on G2
   V19-off G2
   V20-on G3
   V21-off G3
   V22-status RuaLoc
   V23-Rualoc
   V24-Hidden/visible
   V25-The tich
   V26-Con lai
   V27-Dung tich
   V28-Do sau
   V29-Ap luc
   V30-I0-B1
   V31-I1-B2
   V32-I2-B3
   V33-I3-G1
   V34-I4-G2
   V35-I5-G3
   V36-temp1
   V37-temp2
   V38-temp3
   V39-
   V40-StatusMucnuoc
   V41- Ampe NK1
   V42- Ampe NK22
   V43- btn NK1
   V44- btn NK2
   V45-
   V46-
   V47-
   V48-
   V49-
   V50-Terminal Luu luong
   V51-input luu luong
   V52-check luu luong
   V53-menu chọn giếng
   V54-Luu Luong G1
   V55-Luu Luong G2
   V56-Khoi luong Clo
   V57-Luu Luong G3

*/

#define BLYNK_TEMPLATE_ID "TMPLEpk-Eewt"
#define BLYNK_TEMPLATE_NAME "Trạm Cái Cát"
#define BLYNK_AUTH_TOKEN "OwqkFUOpl8p9-AP235SQquza0fmhwImP"
#define BLYNK_PRINT Serial
#define BLYNK_FIRMWARE_VERSION "23.11.1"
const char* ssid = "NHA MAY NUOC CAI CAT";
const char* password = "12345678";
// const char *ssid = "Wifi";
// const char *password = "Password";

#define APP_DEBUG
#include <BlynkSimpleEsp8266.h>
//-------------
#include "EmonLib.h"
EnergyMonitor emon0, emon1, emon2, emon3, emon4, emon5, emon6, emon7, emon8;
//-------------
#include "PCF8575.h"
PCF8575 pcf8575_1(0x20);
//-------------
#include <WidgetRTC.h>
#include "RTClib.h"
RTC_DS3231 rtc_module;
char daysOfTheWeek[7][12] = { "CN", "T2", "T3", "T4", "T5", "T6", "T7" };
char tz[] = "Asia/Ho_Chi_Minh";
//-------------
#include <Wire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress temp = { 0x28, 0xFF, 0x05, 0x2E, 0x32, 0x17, 0x03, 0x0E };
DeviceAddress temp2 = { 0x28, 0xA8, 0x45, 0x79, 0xA2, 0x01, 0x03, 0x7C };
DeviceAddress temp3 = { 0x28, 0x83, 0xF3, 0x79, 0xA2, 0x00, 0x03, 0x25 };
//-------------
#include <ESP8266WiFi.h>
WiFiClient client;
//-------------
#include <Eeprom24C32_64.h>
#define EEPROM_ADDRESS 0x57
static Eeprom24C32_64 eeprom(EEPROM_ADDRESS);
//-------------
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 20, 4);
//-------------
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
#define URL_fw_Bin "https://raw.githubusercontent.com/quangtran3110/work/kwaco/caicat/main/main.ino.bin"
//-------------
#include <ESP8266HTTPClient.h>
HTTPClient http;
String server_rualoc = "http://blynkkwaco.ddns.net:8080/";
String rualoc = "p1Aq8WlkeB78YRnL9JBfZmrTdaOruolY";
String server_Main = "http://sgp1.blynk.cloud/external/api/";
String Main = "OwqkFUOpl8p9-AP235SQquza0fmhwImP";
//-------------
const int S0 = 14;
const int S1 = 12;
const int S2 = 13;
const int S3 = 15;
const word address = 0;
const int pin_on_G1 = P7;
const int pin_off_G1 = P6;
const int pin_on_G2 = P5;
const int pin_off_G2 = P4;
const int pin_on_G3 = P3;
const int pin_off_G3 = P2;
const int pin_NK1 = P1;
const int pin_NK2 = P0;
const int pin_on_Bom1 = P8;
const int pin_off_Bom1 = P9;
const int pin_on_Bom2 = P10;
const int pin_off_Bom2 = P11;
const int pin_on_Bom3 = P12;
const int pin_off_Bom3 = P13;
const int pin_on_Bom4 = P14;
const int pin_off_Bom4 = P15;

byte menu_gieng_luuluong;
unsigned long ll_g1_cache = 0, ll_g2_cache = 0, ll_g3_cache = 0;
float clo_cache = 0;
uint32_t timestamp;

int timer_rtc, timer_I, timer_pre;
int z;
long t;
int xSetAmpe = 0, xSetAmpe1 = 0, xSetAmpe2 = 0, xSetAmpe3 = 0, xSetAmpe4 = 0, xSetAmpe5 = 0, xSetAmpe6 = 0, xSetAmpe7 = 0, xSetAmpe8 = 0;
unsigned long int yIrms0 = 0, yIrms1 = 0, yIrms2 = 0, yIrms3 = 0, yIrms4 = 0, yIrms5 = 0, yIrms6 = 0, yIrms7 = 0, yIrms8 = 0;
float Irms0, Irms1, Irms2, Irms3, Irms4, Irms5, Irms6, Irms7, Irms8;
float temp_1, temp_2, temp_3;
bool trip0 = false, trip1 = false, trip2 = false, trip3 = false, trip4 = false, trip5 = false, trip6 = false, trip7 = false, trip8 = false;
float Result1, value1, conlai, thetich, dungtich;
const int dai = 2400;
const int rong = 1230;
const int cao = 330;
bool key = false, keySet = false;
bool blynk_first_connect = false;

unsigned long screen1 = 5000, screen2 = 0;

struct Data {
  byte SetAmpemax, SetAmpemin;
  byte SetAmpe1max, SetAmpe1min;
  byte SetAmpe2max, SetAmpe2min;
  byte SetAmpe3max, SetAmpe3min;
  byte SetAmpe4max, SetAmpe4min;
  byte SetAmpe5max, SetAmpe5min;
  byte SetAmpe6max, SetAmpe6min;
  byte SetAmpe7max, SetAmpe7min;
  byte SetAmpe8max, SetAmpe8min;
  byte man;
  int save_num;
  byte reboot_num;
  int start, stop;
  byte keyp, rl;
  unsigned long ll_g1, ll_g2, ll_g3;
  float clo;
  int time_clo;
} data, dataCheck;
const struct Data dataDefault = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

WidgetTerminal keyterminal(V5);
WidgetTerminal terminal_luuluong(V50);
WidgetRTC rtc_widget;
BlynkTimer timer, timer1;
BLYNK_CONNECTED() {
  rtc_widget.begin();
  blynk_first_connect = true;
}
//---------------------------------------------------------------------------
void savedata() {
  if (memcmp(&data, &dataCheck, sizeof(dataDefault)) == 0) {
    // Serial.println("structures same no need to write to EEPROM");
  } else {
    // Serial.println("\nWrite bytes to EEPROM memory...");
    data.save_num = data.save_num + 1;
    eeprom.writeBytes(address, sizeof(dataDefault), (byte*)&data);
  }
}
void send_rualoc(String token, int virtual_pin, float(value_to_send)) {
  String server_path = server_rualoc + token + "/update/V" + String(virtual_pin) + "?value=" + value_to_send;
  http.begin(client, server_path.c_str());
  int httpResponseCode = http.GET();
  http.end();
}
void hidden() {
  Blynk.setProperty(V6, "isHidden", true);
  Blynk.setProperty(V7, "isHidden", true);
  Blynk.setProperty(V8, "isHidden", true);
  Blynk.setProperty(V9, "isHidden", true);
  Blynk.setProperty(V3, "isHidden", true);
  Blynk.setProperty(V4, "isHidden", true);
}
void visible() {
  Blynk.setProperty(V6, "isHidden", false);
  Blynk.setProperty(V7, "isHidden", false);
  Blynk.setProperty(V8, "isHidden", false);
  Blynk.setProperty(V9, "isHidden", false);
  Blynk.setProperty(V3, "isHidden", false);
  Blynk.setProperty(V4, "isHidden", false);
}
//------------
void onG1() {
  pcf8575_1.digitalWrite(pin_on_G1, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_G1, HIGH);
}
void offG1() {
  pcf8575_1.digitalWrite(pin_off_G1, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_G1, HIGH);
}
void onG2() {
  pcf8575_1.digitalWrite(pin_on_G2, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_G2, HIGH);
}
void offG2() {
  pcf8575_1.digitalWrite(pin_off_G2, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_G2, HIGH);
}
void onG3() {
  pcf8575_1.digitalWrite(pin_on_G3, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_G3, HIGH);
}
void offG3() {
  pcf8575_1.digitalWrite(pin_off_G3, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_G3, HIGH);
}
//------------
void on_Bom1() {
  pcf8575_1.digitalWrite(pin_on_Bom1, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_Bom1, HIGH);
}
void off_Bom1() {
  pcf8575_1.digitalWrite(pin_off_Bom1, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_Bom1, HIGH);
}
void on_Bom2() {
  pcf8575_1.digitalWrite(pin_on_Bom2, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_Bom2, HIGH);
}
void off_Bom2() {
  pcf8575_1.digitalWrite(pin_off_Bom2, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_Bom2, HIGH);
}
void on_Bom3() {
  pcf8575_1.digitalWrite(pin_on_Bom3, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_Bom3, HIGH);
}
void off_Bom3() {
  pcf8575_1.digitalWrite(pin_off_Bom3, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_Bom3, HIGH);
}
void on_Bom4() {
  pcf8575_1.digitalWrite(pin_on_Bom4, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_on_Bom4, HIGH);
}
void off_Bom4() {
  pcf8575_1.digitalWrite(pin_off_Bom4, LOW);
  delay(300);
  pcf8575_1.digitalWrite(pin_off_Bom4, HIGH);
}
//------------Rua Loc-------------------
void reset_RL() {
  send_rualoc(rualoc, 1, 1);
}
void on_nk1_RL() {
  send_rualoc(rualoc, 1, 2);
}
void off_nk1_RL() {
  send_rualoc(rualoc, 1, 3);
}
void on_nk2_RL() {
  send_rualoc(rualoc, 1, 4);
}
void off_nk2_RL() {
  send_rualoc(rualoc, 1, 5);
}
void reset_btn_RL() {
  send_rualoc(rualoc, 1, 6);
}
//-------------------------------------
void readcurrent()  // C0 - Bơm 1
{
  Blynk.run();
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  float rms0 = emon0.calcIrms(740);
  if (rms0 < 3) {
    Irms0 = 0;
    yIrms0 = 0;
  } else if (rms0 > 3) {
    Irms0 = rms0;
    yIrms0 = yIrms0 + 1;
    if ((yIrms0 > 3) && ((Irms0 > data.SetAmpemax) || (Irms0 < data.SetAmpemin))) {
      xSetAmpe = xSetAmpe + 1;
      if ((xSetAmpe >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Bơm 1 lỗi: ") + Irms0 + String(" A"));
        pcf8575_1.digitalWrite(pin_off_Bom1, LOW);
        trip0 = true;
        xSetAmpe = 0;
        timer1.setTimeout(600000L, []() {
          pcf8575_1.digitalWrite(pin_off_Bom1, HIGH);
        });
      }
    } else {
      xSetAmpe = 0;
    }
  }
  //Blynk.virtualWrite(V30, Irms0);
}
void readcurrent1()  // C1 - Bơm 2
{
  Blynk.run();
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  float rms1 = emon1.calcIrms(740);
  if (rms1 < 3) {
    Irms1 = 0;
    yIrms1 = 0;
  } else if (rms1 > 3) {
    Irms1 = rms1;
    yIrms1 = yIrms1 + 1;
    if ((yIrms1 > 3) && ((Irms1 > data.SetAmpe1max) || (Irms1 < data.SetAmpe1min))) {
      xSetAmpe1 = xSetAmpe1 + 1;
      if ((xSetAmpe1 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Bơm 2 lỗi: ") + Irms1 + String(" A"));
        trip1 = true;
        xSetAmpe1 = 0;
        pcf8575_1.digitalWrite(pin_off_Bom2, LOW);
        timer.setTimeout(600000L, []() {
          pcf8575_1.digitalWrite(pin_off_Bom2, HIGH);
        });
      }
    } else {
      xSetAmpe1 = 0;
    }
  }
  //Blynk.virtualWrite(V31, Irms1);
}
void readcurrent2()  // C2 - Bơm 3
{
  Blynk.run();
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  float rms2 = emon2.calcIrms(740);
  if (rms2 < 3) {
    Irms2 = 0;
    yIrms2 = 0;
  } else if (rms2 > 3) {
    Irms2 = rms2;
    yIrms2 = yIrms2 + 1;
    if ((yIrms2 > 3) && ((Irms2 > data.SetAmpe2max) || (Irms2 < data.SetAmpe2min))) {
      xSetAmpe2 = xSetAmpe2 + 1;
      if ((xSetAmpe2 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Bơm 3 lỗi: ") + Irms2 + String(" A"));
        trip2 = true;
        xSetAmpe2 = 0;
        pcf8575_1.digitalWrite(pin_off_Bom3, LOW);
        timer.setTimeout(600000L, []() {
          pcf8575_1.digitalWrite(pin_off_Bom3, HIGH);
        });
      }
    } else {
      xSetAmpe2 = 0;
    }
  }
  //Blynk.virtualWrite(V32, Irms2);
}
void readcurrent3()  // C3 - Gieng 1
{
  Blynk.run();
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  float rms3 = emon3.calcIrms(740);
  if (rms3 < 3) {
    Irms3 = 0;
    yIrms3 = 0;
  } else if (rms3 > 3) {
    Irms3 = rms3;
    yIrms3 = yIrms3 + 1;
    if ((yIrms3 > 3) && ((Irms3 > data.SetAmpe3max) || (Irms3 < data.SetAmpe3min))) {
      xSetAmpe3 = xSetAmpe3 + 1;
      if ((xSetAmpe3 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Giếng I lỗi: ") + Irms3 + String(" A"));
        trip3 = true;
        xSetAmpe3 = 0;
        pcf8575_1.digitalWrite(pin_off_G1, LOW);
        timer.setTimeout(600000L, []() {
          pcf8575_1.digitalWrite(pin_off_G1, HIGH);
        });
      }
    } else {
      xSetAmpe3 = 0;
    }
  }
  //Blynk.virtualWrite(V33, Irms3);
}
void readcurrent4()  // C4 - Giếng 2
{
  Blynk.run();
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  float rms4 = emon4.calcIrms(740);
  if (rms4 < 3) {
    Irms4 = 0;
    yIrms4 = 0;
  } else if (rms4 > 3) {
    Irms4 = rms4;
    yIrms4 = yIrms4 + 1;
    if ((yIrms4 > 3) && ((Irms4 > data.SetAmpe4max) || (Irms4 < data.SetAmpe4min))) {
      xSetAmpe4 = xSetAmpe4 + 1;
      if ((xSetAmpe4 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Giếng 2 lỗi: ") + Irms4 + String(" A"));
        trip4 = true;
        xSetAmpe4 = 0;
        pcf8575_1.digitalWrite(pin_off_G2, LOW);
        timer.setTimeout(300000L, []() {
          pcf8575_1.digitalWrite(pin_off_G2, HIGH);
        });
      }
    } else {
      xSetAmpe4 = 0;
    }
  }
  //Blynk.virtualWrite(V34, Irms4);
}
void readcurrent5()  // C5 - Gieng 3
{
  Blynk.run();
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  float rms5 = emon5.calcIrms(740);
  if (rms5 < 3) {
    Irms5 = 0;
    yIrms5 = 0;
  } else if (rms5 >= 3) {
    Irms5 = rms5;
    yIrms5 = yIrms5 + 1;
    if ((yIrms5 > 3) && ((Irms5 > data.SetAmpe5max) || (Irms5 < data.SetAmpe5min))) {
      xSetAmpe5 = xSetAmpe5 + 1;
      if ((xSetAmpe5 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Giếng 3 lỗi: ") + Irms5 + String(" A"));
        trip5 = true;
        xSetAmpe5 = 0;
        pcf8575_1.digitalWrite(pin_off_G3, LOW);
        timer.setTimeout(300000L, []() {
          pcf8575_1.digitalWrite(pin_off_G3, HIGH);
        });
      }
    } else {
      xSetAmpe5 = 0;
    }
  }
  //Blynk.virtualWrite(V35, Irms5);
}
/*
void readcurrent6()  // C6 -
{
  Blynk.run();
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  float rms6 = emon6.calcIrms(740);
  if (rms6 < 3) {
    Irms6 = 0;
    yIrms6 = 0;
  } else if (rms6 >= 3) {
    Irms6 = rms6;
    yIrms6 = yIrms6 + 1;
    if ((yIrms6 > 3) && ((Irms6 >= data.SetAmpe6max) || (Irms6 < data.SetAmpe6min))) {
      xSetAmpe6 = xSetAmpe6 + 1;
      if ((xSetAmpe6 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Máy 30KW lỗi: ") + Irms6 + String(" A"));
        trip6 = true;
        xSetAmpe6 = 0;
        pcf8575_1.digitalWrite(pin_off_Bom2, LOW);
        timer.setTimeout(300000L, []() {
          pcf8575_1.digitalWrite(pin_off_Bom2, HIGH);
        });
      }
    } else {
      xSetAmpe6 = 0;
    }
  }
  //Blynk.virtualWrite(V46, Irms6);  // Irms6 - 30kw
}
void readcurrent7()  // C7 -
{
  Blynk.run();
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  float rms7 = emon7.calcIrms(740);
  if (rms7 < 3) {
    Irms7 = 0;
    yIrms7 = 0;
  } else if (rms7 >= 3) {
    Irms7 = rms7;
    yIrms7 = yIrms7 + 1;
    if ((yIrms7 > 3) && ((Irms7 >= data.SetAmpe7max) || (Irms7 < data.SetAmpe7min))) {
      xSetAmpe7 = xSetAmpe7 + 1;
      if ((xSetAmpe7 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Máy NÉN KHÍ 1 lỗi: ") + Irms7 + String(" A"));
        trip7 = true;
        xSetAmpe7 = 0;
        pcf8575_1.digitalWrite(pin_NK1, HIGH);
      }
    } else {
      xSetAmpe7 = 0;
    }
  }
  //Blynk.virtualWrite(V32, Irms7);  // Irms7 - NK1
}
void readcurrent8()  // C8 -
{
  Blynk.run();
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  float rms8 = emon8.calcIrms(740);
  if (rms8 < 3) {
    Irms8 = 0;
    yIrms8 = 0;
  } else if (rms8 >= 3) {
    Irms8 = rms8;
    yIrms8 = yIrms8 + 1;
    if ((yIrms8 > 3) && ((Irms8 >= data.SetAmpe8max) || (Irms8 < data.SetAmpe8min))) {
      xSetAmpe8 = xSetAmpe8 + 1;
      if ((xSetAmpe8 >= 3) && (data.keyp)) {
        Blynk.logEvent("error", String("Máy NÉN KHÍ 2 lỗi: ") + Irms8 + String(" A"));
        trip8 = true;
        xSetAmpe8 = 0;
        pcf8575_1.digitalWrite(pin_NK2, HIGH);
      }
    } else {
      xSetAmpe8 = 0;
    }
  }
  Blynk.virtualWrite(V36, Irms8);  // Irms6 - 30kw
}
*/
//------------
void readPressure()  // C14
{
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  float sensorValue = analogRead(A0);
  float Result;
  Result = (((sensorValue - 205) * 6) / (870 - 205));

  if (Result > 0) {
    value1 += Result;
    Result1 = value1 / 16;
    value1 -= Result1;
  }
  // Serial.println(Result);
  // Serial.println(Result1);
}
//------------
void temperature() {
  sensors.requestTemperatures();
  // Serial.println(temp_1);
  if (sensors.getTempC(temp) > 0) {
    temp_1 = sensors.getTempC(temp);
  } else temp_1 = 0;
  if (sensors.getTempC(temp2) > 0) {
    temp_2 = sensors.getTempC(temp2);
  } else temp_2 = 0;
  if (sensors.getTempC(temp3) > 0) {
    temp_3 = sensors.getTempC(temp3);
  } else temp_3 = 0;
}
//------------
void rtctime() {
  if (data.rl != 0) {
    send_rualoc(rualoc, 2, data.rl);
  }
  DateTime now = rtc_module.now();
  if (blynk_first_connect == true) {
    if ((now.day() != day()) || (now.hour() != hour()) || ((now.minute() - minute() > 2) || (minute() - now.minute() > 2))) {
      rtc_module.adjust(DateTime(year(), month(), day(), hour(), minute(), second()));
      DateTime now = rtc_module.now();
    }
  }
  timestamp = now.unixtime();
  Blynk.virtualWrite(V1, daysOfTheWeek[now.dayOfTheWeek()], ", ", now.day(), "/", now.month(), "/", now.year(), " - ", now.hour(), ":", now.minute(), ":", now.second());
  int nowtime = (now.hour() * 3600 + now.minute() * 60);

  if (data.man == 1) {
    if (data.start < data.stop) {
      if (nowtime > data.start && nowtime < data.stop) {
        if (!trip3) {
          pcf8575_1.digitalWrite(pin_on_G1, LOW);
        }
        if (!trip4) {
          pcf8575_1.digitalWrite(pin_on_G2, LOW);
        }
        if (!trip5) {
          pcf8575_1.digitalWrite(pin_on_G3, LOW);
        }
      } else {
        pcf8575_1.digitalWrite(pin_on_G1, HIGH);
        pcf8575_1.digitalWrite(pin_on_G2, HIGH);
        pcf8575_1.digitalWrite(pin_on_G3, HIGH);
      }
    } else if (data.start > data.stop) {
      if ((nowtime > data.start) || (nowtime < data.stop)) {
        if (!trip3) {
          pcf8575_1.digitalWrite(pin_on_G1, LOW);
        }
        if (!trip4) {
          pcf8575_1.digitalWrite(pin_on_G2, LOW);
        }
        if (!trip5) {
          pcf8575_1.digitalWrite(pin_on_G3, LOW);
        }
      } else {
        pcf8575_1.digitalWrite(pin_on_G1, HIGH);
        pcf8575_1.digitalWrite(pin_on_G2, HIGH);
        pcf8575_1.digitalWrite(pin_on_G3, HIGH);
      }
    }
  }
}
//------------
/*
void lcdscreen1() {
  if (screen1 != 0) {
    lcd.setCursor(6, 0);
    lcd.print("Be  Chua");

    lcd.setCursor(1, 1);
    lcd.print("The tich: ");
    lcd.setCursor(12, 1);
    lcd.print(thetich, 0);
    lcd.print(" m3  ");

    lcd.setCursor(1, 2);
    lcd.print("Dung tich: ");
    lcd.setCursor(12, 2);
    lcd.print(dungtich, 0);
    lcd.print(" m3  ");

    lcd.setCursor(1, 3);
    lcd.print("Con lai: ");
    lcd.setCursor(12, 3);
    lcd.print(conlai, 0);
    lcd.print(" cm  ");
  }
}
void lcdscreen2() {
  if (screen2 != 0) {
    lcd.setCursor(1, 0);
    lcd.print("Cap I");

    lcd.setCursor(0, 1);
    lcd.print("1:");
    lcd.setCursor(2, 1);
    lcd.print("    ");
    lcd.setCursor(2, 1);
    lcd.print(Irms3, 1);
    lcd.print("A ");

    lcd.setCursor(0, 2);
    lcd.print("2:");
    lcd.setCursor(2, 2);
    lcd.print("    ");
    lcd.setCursor(2, 2);
    lcd.print(Irms4, 1);
    lcd.print("A ");

    lcd.setCursor(0, 3);
    lcd.print("3:");
    lcd.setCursor(2, 3);
    lcd.print("    ");
    lcd.setCursor(2, 3);
    lcd.print(Irms5, 1);
    lcd.print("A ");
    //----------------------
    lcd.setCursor(13, 0);
    lcd.print("Cap II");

    lcd.setCursor(12, 1);
    lcd.print("1:");
    lcd.setCursor(14, 1);
    lcd.print("    ");
    lcd.setCursor(14, 1);
    lcd.print(Irms0, 1);
    lcd.print("A ");

    lcd.setCursor(12, 2);
    lcd.print("2:");
    lcd.setCursor(14, 2);
    lcd.print("    ");
    lcd.setCursor(14, 2);
    lcd.print(Irms1, 1);
    lcd.print("A ");

    lcd.setCursor(12, 3);
    lcd.print("3:");
    lcd.setCursor(14, 3);
    lcd.print("    ");
    lcd.setCursor(14, 3);
    lcd.print(Irms2, 1);
    lcd.print("A ");
    //----------------------
    lcd.setCursor(9, 0);
    lcd.print("|");
    lcd.setCursor(9, 1);
    lcd.print("|");
    lcd.setCursor(9, 2);
    lcd.print("|");
    lcd.setCursor(9, 3);
    lcd.print("|");
  }
}
void lcdscreen() {
  if ((screen1 != 0) && ((millis() - screen1) > 5000)) {
    screen2 = millis();
    screen1 = 0;
    // lcd.init();
    lcd.clear();
  }

  else if ((screen2 != 0) && ((millis() - screen2) > 5000)) {
    screen1 = millis();
    screen2 = 0;
    // lcd.init();
    lcd.clear();
  }
}
*/
//---------------------------------------------------------------------------
BLYNK_WRITE(V2)  // Rửa lọc
{
  if (key) {
    switch (param.asInt()) {
      case 0:
        {  // Tắt
          data.rl = 0;
          break;
        }
      case 1:
        {  // RL 1
          data.rl = 1;
          break;
        }
      case 2:
        {  // RL 2
          data.rl = 2;
          break;
        }
      case 3:
        {  // RL 1+2
          data.rl = 3;
          break;
        }
    }
    savedata();
    send_rualoc(rualoc, 2, data.rl);
  } else {
    Blynk.virtualWrite(V2, data.rl);
  }
}
BLYNK_WRITE(V3)  // auto/man cap 1
{
  if (keySet) {
    if (param.asInt() == HIGH) {
      data.man = 1;
    } else {
      data.man = 0;
    }
  } else
    Blynk.virtualWrite(V3, data.man);
}
BLYNK_WRITE(V4)  // On/off chuc nang bao ve
{
  if (keySet) {
    if (param.asInt() == LOW) {
      data.keyp = 0;
    } else {
      data.keyp = 1;
    }
  } else {
    Blynk.virtualWrite(V4, data.keyp);
  }
}
BLYNK_WRITE(V5)  // data string
{
  String dataS = param.asStr();
  if (dataS == "cc" || dataS == "CC") {
    keyterminal.clear();
    Blynk.virtualWrite(V5, "Người vận hành: 'NM Cái Cát'\nMain kích hoạt trong 10s");
    key = true;
    timer.setTimeout(10000, []() {
      key = false;
      keyterminal.clear();
    });
  } else if (dataS == "active") {
    keyterminal.clear();
    Blynk.virtualWrite(V5, "Kích hoạt chế độ sửa lỗi!");
    key = true;
    keySet = true;
  } else if (dataS == "deactive") {
    keyterminal.clear();
    key = false;
    keySet = false;
    Blynk.virtualWrite(V5, "Đã hủy!\n");
  } else if (dataS == "save") {
    keyterminal.clear();
    savedata();
    Blynk.virtualWrite(V5, "Đã lưu!\n");
  } else if (dataS == "reset") {
    keyterminal.clear();
    Blynk.virtualWrite(V5, "Đã reset!");
    trip0 = false;
    trip1 = false;
    trip2 = false;
    trip3 = false;
    trip4 = false;
    trip5 = false;
    trip6 = false;
    pcf8575_1.digitalWrite(pin_off_G3, HIGH);    // G3
    pcf8575_1.digitalWrite(pin_off_G2, HIGH);    // G2
    pcf8575_1.digitalWrite(pin_off_G1, HIGH);    // G1
    pcf8575_1.digitalWrite(pin_off_Bom4, HIGH);  // 11kw
    pcf8575_1.digitalWrite(pin_off_Bom3, HIGH);  // 7.5kw
    pcf8575_1.digitalWrite(pin_off_Bom1, HIGH);  // 18.5kw
    pcf8575_1.digitalWrite(pin_off_Bom2, HIGH);  // 30kw
    pcf8575_1.digitalWrite(pin_NK1, HIGH);       // NK1
    pcf8575_1.digitalWrite(pin_NK2, HIGH);       // NK2
    reset_RL();
  } else if (dataS == "save_num") {
    keyterminal.clear();
    Blynk.virtualWrite(V5, "Số lần ghi EEPROM: ", data.save_num);
  } else if (dataS == "rst") {
    keyterminal.clear();
    Blynk.virtualWrite(V5, "ESP Khởi động lại sau 3s");
    delay(3000);
    ESP.restart();
  } else if (dataS == "update") {
    keyterminal.clear();
    Blynk.virtualWrite(V5, "UPDATE FIRMWARE...");
    update_fw();
  } else {
    Blynk.virtualWrite(V5, "Mã không hợp lệ!\nVui lòng nhập lại.\n");
  }
}
BLYNK_WRITE(V6)  // Chon máy cài đặt bảo vệ
{
  switch (param.asInt()) {
    case 0:
      {
        z = 0;
        Blynk.virtualWrite(V7, 0);
        Blynk.virtualWrite(V8, 0);
        break;
      }
    case 1:
      {  // Bom 1
        z = 1;
        Blynk.virtualWrite(V7, data.SetAmpemin);
        Blynk.virtualWrite(V8, data.SetAmpemax);
        break;
      }
    case 2:
      {  // Bom 2
        z = 2;
        Blynk.virtualWrite(V7, data.SetAmpe1min);
        Blynk.virtualWrite(V8, data.SetAmpe1max);
        break;
      }
    case 3:
      {  // Bom 3
        z = 3;
        Blynk.virtualWrite(V7, data.SetAmpe2min);
        Blynk.virtualWrite(V8, data.SetAmpe2max);
        break;
      }
    case 4:
      {  // G1
        z = 4;
        Blynk.virtualWrite(V7, data.SetAmpe3min);
        Blynk.virtualWrite(V8, data.SetAmpe3max);
        break;
      }
    case 5:
      {  // G2
        z = 5;
        Blynk.virtualWrite(V7, data.SetAmpe4min);
        Blynk.virtualWrite(V8, data.SetAmpe4max);
        break;
      }
    case 6:
      {  // G3
        z = 6;
        Blynk.virtualWrite(V7, data.SetAmpe5min);
        Blynk.virtualWrite(V8, data.SetAmpe5max);
        break;
      }
  }
}
BLYNK_WRITE(V7)  // min
{
  if (keySet) {
    if (z == 1) {
      data.SetAmpemin = param.asInt();
    } else if (z == 2) {
      data.SetAmpe1min = param.asInt();
    } else if (z == 3) {
      data.SetAmpe2min = param.asInt();
    } else if (z == 4) {
      data.SetAmpe3min = param.asInt();
    } else if (z == 5) {
      data.SetAmpe4min = param.asInt();
    } else if (z == 6) {
      data.SetAmpe5min = param.asInt();
    }
  } else {
    Blynk.virtualWrite(V7, 0);
  }
}
BLYNK_WRITE(V8)  // max
{
  if (keySet) {
    if (z == 1) {
      data.SetAmpemax = param.asInt();
    } else if (z == 2) {
      data.SetAmpe1max = param.asInt();
    } else if (z == 3) {
      data.SetAmpe2max = param.asInt();
    } else if (z == 4) {
      data.SetAmpe3max = param.asInt();
    } else if (z == 5) {
      data.SetAmpe4max = param.asInt();
    } else if (z == 6) {
      data.SetAmpe5max = param.asInt();
    }
  } else {
    Blynk.virtualWrite(V8, 0);
  }
}
BLYNK_WRITE(V9)  // time input
{
  if (keySet) {
    TimeInputParam t(param);
    if (t.hasStartTime()) {
      data.start = t.getStartHour() * 3600 + t.getStartMinute() * 60;
    }
    if (t.hasStopTime()) {
      data.stop = t.getStopHour() * 3600 + t.getStopMinute() * 60;
    }
  } else {
    Blynk.virtualWrite(V9, data.start, data.stop, tz);
  }
}
BLYNK_WRITE(V10)  // On Bơm 1
{
  if (key) {
    if (param.asInt() == HIGH) {
      on_Bom1();
    }
  }
}
BLYNK_WRITE(V11)  // Off Bơm 1
{
  if (key) {
    if (param.asInt() == HIGH) {
      off_Bom1();
    }
  }
}
BLYNK_WRITE(V12)  // On Bơm 2
{
  if (key) {
    if (param.asInt() == HIGH) {
      on_Bom2();
    }
  }
}
BLYNK_WRITE(V13)  // Off Bơm 2
{
  if (key) {
    if (param.asInt() == HIGH) {
      off_Bom2();
    }
  }
}
BLYNK_WRITE(V14)  // On Bơm 3
{
  if (key) {
    if (param.asInt() == HIGH) {
      on_Bom3();
    }
  }
}
BLYNK_WRITE(V15)  // Off Bơm 3
{
  if (key) {
    if (param.asInt() == HIGH) {
      off_Bom3();
    }
  }
}
BLYNK_WRITE(V16)  // On Gieng 1
{
  if (key) {
    if (param.asInt() == HIGH) {
      onG1();
    }
  }
}
BLYNK_WRITE(V17)  // Off Gieng 1
{
  if (key) {
    if (param.asInt() == HIGH) {
      offG1();
    }
  }
}
BLYNK_WRITE(V18)  // On Gieng 2
{
  if (key) {
    if (param.asInt() == HIGH) {
      onG2();
    }
  }
}
BLYNK_WRITE(V19)  // Off Gieng 2
{
  if (key) {
    if (param.asInt() == HIGH) {
      offG2();
    }
  }
}
BLYNK_WRITE(V20)  // On Gieng 3
{
  if (key) {
    if (param.asInt() == HIGH) {
      onG3();
    }
  }
}
BLYNK_WRITE(V21)  // Off Gieng 3
{
  if (key) {
    if (param.asInt() == HIGH) {
      offG3();
    }
  }
}
BLYNK_WRITE(V24)  // hidden/visible
{
  if (param.asInt() == HIGH) {
    visible();
  } else
    hidden();
}
BLYNK_WRITE(V26)  //The tich
{
  if (param.asFloat() >= 0) {
    conlai = param.asFloat();
    thetich = (dai * conlai * rong) / 1000000;
  }
}
BLYNK_WRITE(V40)  // Nén Khí
{
  if (param.asInt() == 1) {
    pcf8575_1.digitalWrite(pin_NK1, LOW);
  }
}
BLYNK_WRITE(V43)  // BTN NK1
{
  if (key) {
    if (param.asInt() == HIGH) {
      on_nk1_RL();
    } else off_nk1_RL();
  } else reset_btn_RL();
}
BLYNK_WRITE(V44)  // BTN NK2
{
  if (key) {
    if (param.asInt() == HIGH) {
      on_nk2_RL();
    } else off_nk2_RL();
  } else reset_btn_RL();
}
//----------------------------------------------------
BLYNK_WRITE(V50) {
  String dataS = param.asStr();
  if ((dataS == "ok") || (dataS == "Ok") || (dataS == "OK") || (dataS == "oK")) {
    if ((ll_g1_cache != 0) && (ll_g1_cache > data.ll_g1)) {
      Blynk.virtualWrite(V54, ll_g1_cache - data.ll_g1);  //Luu luong G1
      data.ll_g1 = ll_g1_cache;
      ll_g1_cache = 0;
      savedata();
      terminal_luuluong.clear();
      Blynk.virtualWrite(V50, "Đã lưu - G1:", data.ll_g1, "m3");
    }
    if ((ll_g2_cache != 0) && (ll_g2_cache > data.ll_g2)) {
      Blynk.virtualWrite(V55, ll_g2_cache - data.ll_g2);  //Luu Luong G2
      data.ll_g2 = ll_g2_cache;
      ll_g2_cache = 0;
      savedata();
      terminal_luuluong.clear();
      Blynk.virtualWrite(V50, "Đã lưu - G2:", data.ll_g2, "m3");
    }
    if ((ll_g3_cache != 0) && (ll_g3_cache > data.ll_g3)) {
      Blynk.virtualWrite(V57, ll_g3_cache - data.ll_g3);  //Luu Luong G3
      data.ll_g3 = ll_g3_cache;
      ll_g3_cache = 0;
      savedata();
      terminal_luuluong.clear();
      Blynk.virtualWrite(V50, "Đã lưu - G3:", data.ll_g3, "m3");
    }
    if (clo_cache > 0) {
      data.clo = clo_cache;
      clo_cache = 0;
      data.time_clo = timestamp;
      Blynk.virtualWrite(V56, data.clo);
      savedata();
      terminal_luuluong.clear();
      Blynk.virtualWrite(V50, "Đã lưu - CLO:", data.clo, "kg");
    }
  } else if (dataS == "reset_g1") {
    data.ll_g1 = 0;
    savedata();
    terminal_luuluong.clear();
    Blynk.virtualWrite(V50, "Đã reset Giếng 1: 0");
  } else if (dataS == "reset_g2") {
    data.ll_g2 = 0;
    savedata();
    terminal_luuluong.clear();
    Blynk.virtualWrite(V50, "Đã reset Giếng 2: 0");
  } else if (dataS == "reset_g3") {
    data.ll_g3 = 0;
    savedata();
    terminal_luuluong.clear();
    Blynk.virtualWrite(V50, "Đã reset Giếng 3: 0");
  }
}
BLYNK_WRITE(V51) {
  if (param.asFloat() > 0) {
    if (menu_gieng_luuluong == 1) {
      if (param.asInt() >= data.ll_g1) {
        ll_g1_cache = param.asInt();
        terminal_luuluong.clear();
        Blynk.virtualWrite(V50, "Giếng 1:\n Số hôm nay:", ll_g1_cache, "m3\n Lưu lượng:", ll_g1_cache - data.ll_g1, "m3\n Vui lòng kiểm tra kỹ, nếu đúng hãy nhập 'OK' để lưu");
      } else {
        terminal_luuluong.clear();
        Blynk.virtualWrite(V50, "KHÔNG HỢP LỆ ! ! !\nSố hôm nay:", param.asInt(), "m3 NHỎ HƠN Số hôm qua:", data.ll_g1, "m3");
      }
    } else if (menu_gieng_luuluong == 2) {
      if (param.asInt() >= data.ll_g2) {
        ll_g2_cache = param.asInt();
        terminal_luuluong.clear();
        Blynk.virtualWrite(V50, "Giếng 2:\n Số hôm nay:", ll_g2_cache, "m3\n Lưu lượng:", ll_g2_cache - data.ll_g2, "m3\n Vui lòng kiểm tra kỹ, nếu đúng hãy nhập 'OK' để lưu");
      } else {
        terminal_luuluong.clear();
        Blynk.virtualWrite(V50, "KHÔNG HỢP LỆ ! ! !\nSố hôm nay:", param.asInt(), "m3 NHỎ HƠN Số hôm qua:", data.ll_g2, "m3");
      }
    } else if (menu_gieng_luuluong == 3) {
      if (param.asInt() >= data.ll_g3) {
        ll_g3_cache = param.asInt();
        terminal_luuluong.clear();
        Blynk.virtualWrite(V50, "Giếng 3:\n Số hôm nay:", ll_g3_cache, "m3\n Lưu lượng:", ll_g3_cache - data.ll_g3, "m3\n Vui lòng kiểm tra kỹ, nếu đúng hãy nhập 'OK' để lưu");
      } else {
        terminal_luuluong.clear();
        Blynk.virtualWrite(V50, "KHÔNG HỢP LỆ ! ! !\nSố hôm nay:", param.asInt(), "m3 NHỎ HƠN Số hôm qua:", data.ll_g3, "m3");
      }
    } else if (menu_gieng_luuluong == 4) {
      terminal_luuluong.clear();
      clo_cache = param.asFloat();
      Blynk.virtualWrite(V50, " Lượng CLO châm hôm nay:", clo_cache, "kg\n Vui lòng kiểm tra kỹ, nếu đúng hãy nhập 'OK' để lưu");
    }
  }
}
BLYNK_WRITE(V52) {
  if (param.asInt() == 1) {
    DateTime dt(data.time_clo);
    terminal_luuluong.clear();
    Blynk.virtualWrite(V50, "Số mới nhất:\n G1:", data.ll_g1, "m3\n G2:", data.ll_g2, "m3\n G3:", data.ll_g3, "m3\n Châm CLO:", data.clo, "kg vào lúc", dt.hour(), ":", dt.minute(), "-", dt.day(), "/", dt.month(), "/", dt.year());
  }
}
BLYNK_WRITE(V53) {
  switch (param.asInt()) {
    case 0:
      {  //.....
        menu_gieng_luuluong = 0;
        terminal_luuluong.clear();
        break;
      }
    case 1:
      {  //Gieng 1
        menu_gieng_luuluong = 1;
        break;
      }
    case 2:
      {  //Gieng 2
        menu_gieng_luuluong = 2;
        break;
      }
    case 3:
      {  //Gieng 3
        menu_gieng_luuluong = 3;
        break;
      }
    case 4:
      {  //Clo
        menu_gieng_luuluong = 4;
        break;
      }
  }
  ll_g1_cache = 0;
  ll_g2_cache = 0;
  ll_g3_cache = 0;
  clo_cache = 0;
  Blynk.virtualWrite(V51, 0);
}
//----------------------------------------------------
void updata() {
  String server_path = server_Main + "batch/update?token=" + Main
                       + "&V29=" + Result1
                       + "&V30=" + Irms0
                       + "&V31=" + Irms1
                       + "&V32=" + Irms2
                       + "&V33=" + Irms3
                       + "&V34=" + Irms4
                       + "&V35=" + Irms5
                       + "&V36=" + temp_1
                       + "&V37=" + temp_2
                       + "&V38=" + temp_3;
  http.begin(client, server_path.c_str());
  int httpResponseCode = http.GET();
  http.end();
}
//-------------------------
void update_started() {
  Serial.println("CALLBACK:  HTTP update process started");
}
void update_finished() {
  Serial.println("CALLBACK:  HTTP update process finished");
}
void update_progress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
}
void update_error(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
}
void update_fw() {
  WiFiClientSecure client_;
  client_.setInsecure();
  Serial.print("Wait...");
  ESPhttpUpdate.onStart(update_started);
  ESPhttpUpdate.onEnd(update_finished);
  ESPhttpUpdate.onProgress(update_progress);
  ESPhttpUpdate.onError(update_error);
  t_httpUpdate_return ret = ESPhttpUpdate.update(client_, URL_fw_Bin);
  switch (ret) {
    case HTTP_UPDATE_FAILED: Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str()); break;
    case HTTP_UPDATE_NO_UPDATES: Serial.println("HTTP_UPDATE_NO_UPDATES"); break;
    case HTTP_UPDATE_OK: Serial.println("HTTP_UPDATE_OK"); break;
  }
}
//-------------------------
void connectionstatus() {
  if ((WiFi.status() != WL_CONNECTED)) {
    // Serial.println("Khong ket noi WIFI");
  }
  if ((WiFi.status() == WL_CONNECTED) && (!Blynk.connected())) {
    data.reboot_num = data.reboot_num + 1;
    savedata();
    if ((data.reboot_num == 1) || (data.reboot_num == 2)) {
      delay(1000);
      ESP.restart();
    }
    if (data.reboot_num % 5 == 0) {
      delay(1000);
      ESP.restart();
    }
  }
  if (Blynk.connected()) {
    if (data.reboot_num != 0) {
      data.reboot_num = 0;
      savedata();
    }
  }
}
//---------------------------------------------------------------------------
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Blynk.config(BLYNK_AUTH_TOKEN);
  delay(7000);

  emon0.current(A0, 106);
  emon1.current(A0, 106);
  emon2.current(A0, 106);
  emon3.current(A0, 106);
  emon4.current(A0, 106);
  emon5.current(A0, 106);
  emon6.current(A0, 106);
  emon7.current(A0, 106);

  pcf8575_1.pinMode(pin_on_G1, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_G1, HIGH);
  pcf8575_1.pinMode(pin_off_G1, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_G1, HIGH);
  pcf8575_1.pinMode(pin_on_G2, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_G2, HIGH);
  pcf8575_1.pinMode(pin_off_G2, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_G2, HIGH);
  pcf8575_1.pinMode(pin_on_G3, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_G3, HIGH);
  pcf8575_1.pinMode(pin_off_G3, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_G3, HIGH);

  pcf8575_1.pinMode(pin_on_Bom1, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_Bom1, HIGH);
  pcf8575_1.pinMode(pin_off_Bom1, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_Bom1, HIGH);
  pcf8575_1.pinMode(pin_on_Bom2, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_Bom2, HIGH);
  pcf8575_1.pinMode(pin_off_Bom2, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_Bom2, HIGH);
  pcf8575_1.pinMode(pin_on_Bom3, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_Bom3, HIGH);
  pcf8575_1.pinMode(pin_off_Bom3, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_Bom3, HIGH);
  pcf8575_1.pinMode(pin_on_Bom4, OUTPUT);
  pcf8575_1.digitalWrite(pin_on_Bom4, HIGH);
  pcf8575_1.pinMode(pin_off_Bom4, OUTPUT);
  pcf8575_1.digitalWrite(pin_off_Bom4, HIGH);

  pcf8575_1.pinMode(pin_NK1, OUTPUT);
  pcf8575_1.digitalWrite(pin_NK1, HIGH);
  pcf8575_1.pinMode(pin_NK2, OUTPUT);
  pcf8575_1.digitalWrite(pin_NK2, HIGH);

  sensors.begin();
  rtc_module.begin();
  //lcd.init();
  //lcd.backlight();

  eeprom.initialize();
  eeprom.readBytes(address, sizeof(dataDefault), (byte*)&data);

  timer.setTimeout(5000L, []() {
    timer_pre = timer.setInterval(303, []() {
      readPressure();
      // lcdscreen();
      //lcdscreen1();
      //lcdscreen2();
      timer.restartTimer(timer_pre);
    });
    timer_rtc = timer.setInterval(15000L, []() {
      rtctime();
      timer.restartTimer(timer_I);
      timer.restartTimer(timer_pre);
    });
    timer_I = timer.setInterval(1089, []() {
      readcurrent();
      readcurrent1();
      readcurrent2();
      readcurrent3();
      readcurrent4();
      readcurrent5();
      temperature();
      updata();
      timer.restartTimer(timer_I);
      timer.restartTimer(timer_pre);
    });
    timer.setInterval(900005L, []() {
      connectionstatus();
      timer.restartTimer(timer_I);
      timer.restartTimer(timer_pre);
    });
  });
  keyterminal.clear();
  //dungtich = (dai * rong * cao) / 1000000;
}

void loop() {
  Blynk.run();
  timer.run();
}