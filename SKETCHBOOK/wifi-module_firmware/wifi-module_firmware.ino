//Connect to Network | Send Button Data to Google Sheets.
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

const char * host = "script.google.com";
const int httpsPort = 443;
// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;
// SHA1 fingerprint of the certificate
const char* fingerprint = "67 12 5D A1 8A F5 FD EC 11 FD 73 61 69 A8 4C 3F 3A B9 C2 18";
String GAS_ID = "<Place Google App Script ID here>";
String wifiStatus;

void setup() {
  // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  // put your setup code here, to run once:
  client.setInsecure();
  Serial.begin(115200);
  while (!Serial);

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  wm.resetSettings();
  wm.setClass("invert"); // dark theme

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  res = wm.autoConnect("<Place Name of IOT device here>"); // anonymous ap
  // res = wm.autoConnect("<Place Name of IOT device here>","password"); // password protected ap

  if(!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else {
    //if you get here you have connected to the WiFi
    Serial.println("Connected");
    wifiStatus = "Y";
    Serial.println(wifiStatus);
  }
}

void loop() {
  if(Ping.ping(host)) {
    wifiStatus = "Y";
    Serial.println(wifiStatus);
  } else {
    wifiStatus = ".";
    Serial.println(wifiStatus);
  }

  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String SerialResponse = Serial.readStringUntil('\r\n');
    Serial.println(SerialResponse);
    sendData(SerialResponse);
  }

  delay(10);
}


// Function to send data into GoogleSheet
void sendData(String btn){
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String string_button = btn;
  String url = "/macros/s/" + GAS_ID + "/exec?button=" + string_button;

  Serial.print("requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");
  Serial.println("request sent");
}
