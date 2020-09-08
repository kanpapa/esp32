/*********
ESP32 remote relay controller program
 Kazuhiro Ouchi  @kanpapa

 Controller: ESP32DEV-C
 Sainsmart 16 Relay Module

Original Source:
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
  How to Set an ESP32 Access Point (AP) for Web Server
  https://randomnerdtutorials.com/esp32-access-point-ap-web-server/

License:
  Creative Commons Attribution-Non Commercial-Share Alike v3.0 license
  https://creativecommons.org/licenses/by-nc-sa/3.0/  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "esp32relay";
const char* password = "password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output0State = "off";
String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";
String output5State = "off";
String output6State = "off";
String output7State = "off";
String output8State = "off";
String output9State = "off";
String outputAState = "off";
String outputBState = "off";
String outputCState = "off";
String outputDState = "off";
String outputEState = "off";
String outputFState = "off";

// Assign output variables to GPIO pins
const int output13 = 13;
const int output14 = 14;
const int output27 = 27;
const int output26 = 26;
const int output25 = 25;
const int output33 = 33;
const int output32 = 32;
const int output23 = 23;
const int output22 = 22;
const int output21 = 21;
const int output19 = 19;
const int output18 = 18;
const int output17 = 17;
const int output16 = 16;
const int output4 = 4;
const int output5 = 5;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output32, OUTPUT);  // GPIO32   0
  pinMode(output33, OUTPUT);  // GPIO33   1
  pinMode(output25, OUTPUT);  // GPIO25   2
  pinMode(output26, OUTPUT);  // GPIO26   3
  pinMode(output27, OUTPUT);  // GPIO27   4
  pinMode(output14, OUTPUT);  // GPIO14   5
  pinMode(output13, OUTPUT);  // GPIO13   6
  pinMode(output23, OUTPUT);  // GPIO23   7
  pinMode(output22, OUTPUT);  // GPIO22   8
  pinMode(output21, OUTPUT);  // GPIO21   9
  pinMode(output19, OUTPUT);  // GPIO19   A
  pinMode(output18, OUTPUT);  // GPIO18   B
  pinMode(output5, OUTPUT);   // GPIO5(internal pullup)  C
  pinMode(output17, OUTPUT);  // GPIO17   D
  pinMode(output16, OUTPUT);  // GPIO16   E
  pinMode(output4, OUTPUT);   // GPIO4    F
    
  // Set outputs to HIGH
  digitalWrite(output13, HIGH);
  digitalWrite(output14, HIGH);
  digitalWrite(output27, HIGH);
  digitalWrite(output26, HIGH);
  digitalWrite(output25, HIGH);
  digitalWrite(output33, HIGH);
  digitalWrite(output32, HIGH);
  digitalWrite(output23, HIGH);
  digitalWrite(output22, HIGH);
  digitalWrite(output21, HIGH);
  digitalWrite(output19, HIGH);
  digitalWrite(output18, HIGH);
  digitalWrite(output17, HIGH);
  digitalWrite(output16, HIGH);
  digitalWrite(output4, HIGH);
  digitalWrite(output5, HIGH);

  // Connect to Wi-Fi network with SSID and password
  Serial.println("Setting AP (Access Point)");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            // 0 IO32
            if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("GPIO 32 on");
              output0State = "on";
              digitalWrite(output32, LOW);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("GPIO 32 off");
              output0State = "off";
              digitalWrite(output32, HIGH);
            // 1 IO33
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("GPIO 33 on");
              output1State = "on";
              digitalWrite(output33, LOW);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("GPIO 33 off");
              output1State = "off";
              digitalWrite(output33, HIGH);
            // 2 IO25
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 25 on");
              output2State = "on";
              digitalWrite(output25, LOW);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 25 off");
              output2State = "off";
              digitalWrite(output25, HIGH);
            // 3 IO 26
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("GPIO 26 on");
              output3State = "on";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("GPIO 26 off");
              output3State = "off";
              digitalWrite(output26, HIGH);
            // 4 IO 27
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 27 on");
              output4State = "on";
              digitalWrite(output27, LOW);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 27 off");
              output4State = "off";
              digitalWrite(output27, HIGH);
            // 5 IO 14
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 14 on");
              output5State = "on";
              digitalWrite(output14, LOW);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 14 off");
              output5State = "off";
              digitalWrite(output14, HIGH);
            // 6 IO 13  
            } else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 13 on");
              output6State = "on";
              digitalWrite(output13, LOW);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 13 off");
              output6State = "off";
              digitalWrite(output13, HIGH);
            // 7 IO 23
            } else if (header.indexOf("GET /7/on") >= 0) {
              Serial.println("GPIO 23 on");
              output7State = "on";
              digitalWrite(output23, LOW);
            } else if (header.indexOf("GET /7/off") >= 0) {
              Serial.println("GPIO 23 off");
              output7State = "off";
              digitalWrite(output23, HIGH);
            // 8 IO 22
            } else if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("GPIO 22 on");
              output8State = "on";
              digitalWrite(output22, LOW);
            } else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("GPIO 22 off");
              output8State = "off";
              digitalWrite(output22, HIGH);
            // 9 IO21
            } else if (header.indexOf("GET /9/on") >= 0) {
              Serial.println("GPIO 21 on");
              output9State = "on";
              digitalWrite(output21, LOW);
            } else if (header.indexOf("GET /9/off") >= 0) {
              Serial.println("GPIO 21 off");
              output9State = "off";
              digitalWrite(output21, HIGH);
            // A IO19
            } else if (header.indexOf("GET /A/on") >= 0) {
              Serial.println("GPIO 19 on");
              outputAState = "on";
              digitalWrite(output19, LOW);
            } else if (header.indexOf("GET /A/off") >= 0) {
              Serial.println("GPIO 19 off");
              outputAState = "off";
              digitalWrite(output19, HIGH);
            // B IO18
            } else if (header.indexOf("GET /B/on") >= 0) {
              Serial.println("GPIO 18 on");
              outputBState = "on";
              digitalWrite(output18, LOW);
            } else if (header.indexOf("GET /B/off") >= 0) {
              Serial.println("GPIO 18 off");
              outputBState = "off";
              digitalWrite(output18, HIGH);
            // C IO5
            } else if (header.indexOf("GET /C/on") >= 0) {
              Serial.println("GPIO 5 on");
              outputCState = "on";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /C/off") >= 0) {
              Serial.println("GPIO 5 off");
              outputCState = "off";
              digitalWrite(output5, HIGH);
            // D IO17
            } else if (header.indexOf("GET /D/on") >= 0) {
              Serial.println("GPIO 17 on");
              outputDState = "on";
              digitalWrite(output17, LOW);
            } else if (header.indexOf("GET /D/off") >= 0) {
              Serial.println("GPIO 17 off");
              outputDState = "off";
              digitalWrite(output17, HIGH);
            // E IO16
            } else if (header.indexOf("GET /E/on") >= 0) {
              Serial.println("GPIO 16 on");
              outputEState = "on";
              digitalWrite(output16, LOW);
            } else if (header.indexOf("GET /E/off") >= 0) {
              Serial.println("GPIO 16 off");
              outputEState = "off";
              digitalWrite(output16, HIGH);
            // F IO4
            } else if (header.indexOf("GET /F/on") >= 0) {
              Serial.println("GPIO 4 on");
              outputFState = "on";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /F/off") >= 0) {
              Serial.println("GPIO 4 off");
              outputFState = "off";
              digitalWrite(output4, HIGH);
            }
            else
            {
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button {background-color: #4CAF50; border: none; color: white; padding: 16px 32px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;border-bottom: solid 4px #627295;border-radius:3px;}");
            client.println(".button:active { -webkit-transform: translateY(4px);transform: translateY(4px);border-bottom: none;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Javascript
            client.println("<script type=\"text/javascript\">");
            client.println("function restapi($param){var request = new XMLHttpRequest();request.open('GET', $param, true);request.responseType = 'json';");
            client.println("request.onload = function () {var data = this.response;console.log(data);};request.send();console.log($param);}</script>");
           
            // Web Page Heading
            client.println("<body><h1>COSMAC VIP OS</h1>");
            
            // 1 2 3 C
            client.print("<p>");
            client.println("<button ontouchstart=\"restapi('/1/on')\"; ontouchend=\"restapi('/1/off')\"; class=\"button\">1</button>");
            client.println("<button ontouchstart=\"restapi('/2/on')\"; ontouchend=\"restapi('/2/off')\"; class=\"button\">2</button>");
            client.println("<button ontouchstart=\"restapi('/3/on')\"; ontouchend=\"restapi('/3/off')\"; class=\"button\">3</button>");
            client.println("<button ontouchstart=\"restapi('/C/on')\"; ontouchend=\"restapi('/C/off')\"; class=\"button\">C</button>");
            client.println("<p>");
                           
            // 4 5 6 D
            client.print("<p>");
            client.println("<button ontouchstart=\"restapi('/4/on')\"; ontouchend=\"restapi('/4/off')\"; class=\"button\">4</button>");
            client.println("<button ontouchstart=\"restapi('/5/on')\"; ontouchend=\"restapi('/5/off')\"; class=\"button\">5</button>");
            client.println("<button ontouchstart=\"restapi('/6/on')\"; ontouchend=\"restapi('/6/off')\"; class=\"button\">6</button>");
            client.println("<button ontouchstart=\"restapi('/D/on')\"; ontouchend=\"restapi('/D/off')\"; class=\"button\">D</button>");
            client.println("<p>");
                        
            // 7 8 9 E
            client.print("<p>");
            client.println("<button ontouchstart=\"restapi('/7/on')\"; ontouchend=\"restapi('/7/off')\"; class=\"button\">7</button>");
            client.println("<button ontouchstart=\"restapi('/8/on')\"; ontouchend=\"restapi('/8/off')\"; class=\"button\">8</button>");
            client.println("<button ontouchstart=\"restapi('/9/on')\"; ontouchend=\"restapi('/9/off')\"; class=\"button\">9</button>");
            client.println("<button ontouchstart=\"restapi('/E/on')\"; ontouchend=\"restapi('/E/off')\"; class=\"button\">E</button>");
            client.println("<p>");

            // A 0 B F
            client.print("<p>");
            client.println("<button ontouchstart=\"restapi('/A/on')\"; ontouchend=\"restapi('/A/off')\"; class=\"button\">A</button>");
            client.println("<button ontouchstart=\"restapi('/0/on')\"; ontouchend=\"restapi('/0/off')\"; class=\"button\">0</button>");
            client.println("<button ontouchstart=\"restapi('/B/on')\"; ontouchend=\"restapi('/B/off')\"; class=\"button\">B</button>");
            client.println("<button ontouchstart=\"restapi('/F/on')\"; ontouchend=\"restapi('/F/off')\"; class=\"button\">F</button>");
            client.println("<p>");
            
            client.println("</body></html>");

            }
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
