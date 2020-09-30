/*********
ESP32 remote relay controller program Ver 2.0
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
boolean outputState[16];  // false = off, true = on

// value to GPIO-pin table   0  1  2  3  4  5  6  7  8  9  A  B C  D  E F
const char num2gpio_data[] = {32,33,25,26,27,14,13,23,22,21,19,18,5,17,16,4};
  
// Auto mode data
const char auto_data[] = {0,2,0,0,    // Start address : 0200
                        0,            // Write
                        10,2,1,8,
                        6,1,2,0,
                        6,2,0,8,
                        6,3,0,4,
                        6,4,0,6,
                        13,1,2,8,
                        14,3,10,1,
                        7,1,15,15,
                        14,4,10,1,
                        7,1,0,1,
                        0,0,14,0,
                        1,2,0,10,
                        15,15,8,1,
                        8,1,8,1,
                        8,1,8,1,
                        8,1,15,15};   // End address : 021F

// Demo mode data
const char demo_data[] = {0,15,0,0,    // Start address : 0F00
                        0,             // Write
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // End address : 0FAF

// Key on
void key_on(char key) {
    Serial.print(key,HEX);
    Serial.println(" on");
    outputState[key] = true;
    digitalWrite(num2gpio_data[key], LOW);
}

// Key off
void key_off(char key) {
    Serial.print(key,HEX);
    Serial.println(" off");
    outputState[key] = false;
    digitalWrite(num2gpio_data[key], HIGH);
}

// Auto mode start
void auto_run() {
  for (int i = 0 ; i < sizeof(auto_data); i++){
    key_on(auto_data[i]);
    delay(100);
    key_off(auto_data[i]);
    delay(100);
  }
}

// Demo mode start
void demo_run() {
  for (int i = 0 ; i < sizeof(demo_data); i++){
    key_on(demo_data[i]);
    delay(100);
    key_off(demo_data[i]);
    delay(100);
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize the state flags as false
  for (int i = 0 ; i < sizeof(outputState); i++) {
    outputState[i] = false;
  }

  // Initialize the output variables as outputs
  for (int i = 0 ; i < sizeof(num2gpio_data); i++) {
    // Set outputs to HIGH
    pinMode(num2gpio_data[i], OUTPUT);
    digitalWrite(num2gpio_data[i], HIGH);
  }

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
              key_on(0);
            } else if (header.indexOf("GET /0/off") >= 0) {
              key_off(0);
            // 1 IO33
            } else if (header.indexOf("GET /1/on") >= 0) {
              key_on(1);
            } else if (header.indexOf("GET /1/off") >= 0) {
              key_off(1);
            // 2 IO25
            } else if (header.indexOf("GET /2/on") >= 0) {
              key_on(2);
            } else if (header.indexOf("GET /2/off") >= 0) {
              key_off(2);
            // 3 IO 26
            } else if (header.indexOf("GET /3/on") >= 0) {
              key_on(3);
            } else if (header.indexOf("GET /3/off") >= 0) {
              key_off(3);
            // 4 IO 27
            } else if (header.indexOf("GET /4/on") >= 0) {
              key_on(4);
            } else if (header.indexOf("GET /4/off") >= 0) {
              key_off(4);
            // 5 IO 14
            } else if (header.indexOf("GET /5/on") >= 0) {
              key_on(5);
            } else if (header.indexOf("GET /5/off") >= 0) {
              key_off(5);
            // 6 IO 13  
            } else if (header.indexOf("GET /6/on") >= 0) {
              key_on(6);
            } else if (header.indexOf("GET /6/off") >= 0) {
              key_off(6);
            // 7 IO 23
            } else if (header.indexOf("GET /7/on") >= 0) {
              key_on(7);
            } else if (header.indexOf("GET /7/off") >= 0) {
              key_off(7);
            // 8 IO 22
            } else if (header.indexOf("GET /8/on") >= 0) {
              key_on(8);
            } else if (header.indexOf("GET /8/off") >= 0) {
              key_off(8);
            // 9 IO21
            } else if (header.indexOf("GET /9/on") >= 0) {
              key_on(9);
            } else if (header.indexOf("GET /9/off") >= 0) {
              key_off(9);
            // A IO19
            } else if (header.indexOf("GET /A/on") >= 0) {
              key_on(10);
            } else if (header.indexOf("GET /A/off") >= 0) {
              key_off(10);
            // B IO18
            } else if (header.indexOf("GET /B/on") >= 0) {
              key_on(11);
            } else if (header.indexOf("GET /B/off") >= 0) {
              key_off(11);
            // C IO5
            } else if (header.indexOf("GET /C/on") >= 0) {
              key_on(12);
            } else if (header.indexOf("GET /C/off") >= 0) {
              key_off(12);
            // D IO17
            } else if (header.indexOf("GET /D/on") >= 0) {
              key_on(13);
            } else if (header.indexOf("GET /D/off") >= 0) {
              key_off(13);
            // E IO16
            } else if (header.indexOf("GET /E/on") >= 0) {
              key_on(14);
            } else if (header.indexOf("GET /E/off") >= 0) {
              key_off(14);
            // F IO4
            } else if (header.indexOf("GET /F/on") >= 0) {
              key_on(15);
            } else if (header.indexOf("GET /F/off") >= 0) {
              key_off(15);
            // AUTO
            } else if (header.indexOf("GET /AUTO") >= 0) {
              Serial.println("START AUTO MODE");
              auto_run();
              Serial.println("END AUTO MODE");
            // DEMO
            } else if (header.indexOf("GET /DEMO") >= 0) {
              Serial.println("START DEMO MODE");
              demo_run();
              Serial.println("END DEMO MODE ");
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
            client.println(".center {margin-left: auto;margin-right: auto;}</style></head>");

            // Javascript
            client.println("<script type=\"text/javascript\">");
            client.println("function restapi($param){var request = new XMLHttpRequest();request.open('GET', $param, true);request.responseType = 'json';");
            client.println("request.onload = function () {var data = this.response;console.log(data);};request.send();console.log($param);}</script>");
           
            // Web Page Heading
            client.println("<body><h1>COSMAC VIP OS</h1>");

            // 1 2 3 C
            client.println("<table class=\"center\"><tr>");
            client.println("<td><button ontouchstart=\"restapi('/1/on')\"; ontouchend=\"restapi('/1/off')\"; class=\"button\">1</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/2/on')\"; ontouchend=\"restapi('/2/off')\"; class=\"button\">2</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/3/on')\"; ontouchend=\"restapi('/3/off')\"; class=\"button\">3</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/C/on')\"; ontouchend=\"restapi('/C/off')\"; class=\"button\">C</button></td>");
            client.println("</tr>");
                           
            // 4 5 6 D
            client.println("<tr>");
            client.println("<td><button ontouchstart=\"restapi('/4/on')\"; ontouchend=\"restapi('/4/off')\"; class=\"button\">4</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/5/on')\"; ontouchend=\"restapi('/5/off')\"; class=\"button\">5</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/6/on')\"; ontouchend=\"restapi('/6/off')\"; class=\"button\">6</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/D/on')\"; ontouchend=\"restapi('/D/off')\"; class=\"button\">D</button></td>");
            client.println("</tr>");
                        
            // 7 8 9 E
            client.println("<tr>");
            client.println("<td><button ontouchstart=\"restapi('/7/on')\"; ontouchend=\"restapi('/7/off')\"; class=\"button\">7</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/8/on')\"; ontouchend=\"restapi('/8/off')\"; class=\"button\">8</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/9/on')\"; ontouchend=\"restapi('/9/off')\"; class=\"button\">9</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/E/on')\"; ontouchend=\"restapi('/E/off')\"; class=\"button\">E</button></td>");
            client.println("</tr>");

            // A 0 B F
            client.println("<tr>");
            client.println("<td><button ontouchstart=\"restapi('/A/on')\"; ontouchend=\"restapi('/A/off')\"; class=\"button\">A</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/0/on')\"; ontouchend=\"restapi('/0/off')\"; class=\"button\">0</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/B/on')\"; ontouchend=\"restapi('/B/off')\"; class=\"button\">B</button></td>");
            client.println("<td><button ontouchstart=\"restapi('/F/on')\"; ontouchend=\"restapi('/F/off')\"; class=\"button\">F</button></td>");
            client.println("</tr>");

            // function
            client.println("<tr>");
            client.println("<td>MR</td>");
            client.println("<td>MW</td>");
            client.println("<td>TR</td>");
            client.println("<td>TW</td>");
            client.println("</tr>");

            client.println("</table>");
            client.println("<p><button ontouchstart=\"restapi('/AUTO')\"; class=\"button\">AUTO</button>  ");
            client.println("<button ontouchstart=\"restapi('/DEMO')\"; class=\"button\">DEMO</button></p>");
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
