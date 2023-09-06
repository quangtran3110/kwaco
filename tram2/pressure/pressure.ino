#define BLYNK_TEMPLATE_ID "TMPL6PNR4qqpm"
#define BLYNK_TEMPLATE_NAME "Multi"
#define BLYNK_AUTH_TOKEN "LtMwtUXWi8mAX47_K17_z5rr8C3HNDjk"
#define BLYNK_FIRMWARE_VERSION "T2.PRE.060923"

#define BLYNK_PRINT Serial
#define APP_DEBUG
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
WiFiClient client;
HTTPClient http;
String server_name = "http://sgp1.blynk.cloud/external/api/";
String Main = "ESzia3fpA-29cs8gt85pGnrPq_rICcqf";
#define URL_fw_Bin "https://raw.githubusercontent.com/quangtran3110/work/kwaco/tram2/pressure/pressure.ino.bin"

const char* ssid = "Nha May Nuoc So 2";
const char* password = "02723841572";

//----------------------------------
float timerun, value = 0, value_s = 0, Result1, Result1_s;
int i = 0, j = 0;
bool keyPRE2 = true, keyPRE4 = true;

WidgetTerminal terminal(V0);
BlynkTimer timer;
BLYNK_CONNECTED() {
}
//-------------------------------------------------------------------
void send_update(String token, int virtual_pin, String value_to_send) {
  String server_path = server_name + "update?token=" + token + "&V" + String(virtual_pin) + "=" + value_to_send;
  Serial.println(server_path);
  http.begin(client, server_path.c_str());
  int httpResponseCode = http.GET();
  http.end();
}
BLYNK_WRITE(V0) {
  if (param.asInt() >= 1) {
    terminal.clear();
    send_update(BLYNK_AUTH_TOKEN, 1, param.asStr());
  }
}
BLYNK_WRITE(V1) {
  if (param.asInt() == 3) {
    send_update(BLYNK_AUTH_TOKEN, 0, "UPDATE T2-PRE");
    update_fw();
  }
}
//-------------------------------------------------------------------
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
//-------------------------------------------------------------------
void updata() {
  String server_path = server_name + "batch/update?token=" + Main
                       + "&V10=" + Result1
                       + "&V38=" + 1;
  http.begin(client, server_path.c_str());
  int httpResponseCode = http.GET();
  http.end();
}

void readPressure() {
  float sensorValue = analogRead(A0);
  float Result, Result_s;
  Result = (((sensorValue - 197) * 10) / (914.6 - 197)); //
  if (Result > 0)
  {
    value += Result;
    Result1 = value / 32.0;
    value -= Result1;
  }
  /*
  Result_s = sensorValue;
  if (Result_s > 0)
  {
    value_s += Result_s;
    Result1_s = value_s / 32.0;
    value_s -= Result1_s;
  }
  Serial.println(Result1_s);
  */
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Blynk.config(BLYNK_AUTH_TOKEN);
  delay(5000);

  timer.setInterval(1603L, updata);
  timer.setInterval(175L, readPressure);
}
void loop() {
  Blynk.run();
  timer.run();
}