//Connect to Network | Send Button Data to Google Sheets.
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char * ssid = "<replace with network name>";    
const char * password = "<replace with password>";
const char * host = "script.google.com";
const int httpsPort = 443;
// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;
// SHA1 fingerprint of the certificate, don't care with your GAS service
const char* fingerprint = "67 12 5D A1 8A F5 FD EC 11 FD 73 61 69 A8 4C 3F 3A B9 C2 18";
String GAS_ID = "<replace with google apps script id>";


void setup() {
  client.setInsecure();
  Serial.begin(9600);
  while (!Serial);
  
  Serial.println();
  //connecting to internet
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


void loop() {

  if (Serial.available()) {
    String SerialResponse = Serial.readStringUntil('\r\n');
    Serial.println(SerialResponse);
    sendData(SerialResponse);
  }
  // 
  delay(10);
}


// Function for Send data into Google Spreadsheet
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
  while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r") {
    Serial.println("headers received");
    break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
  Serial.println("esp8266/Arduino CI successfull!");
  } else {
  Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}
