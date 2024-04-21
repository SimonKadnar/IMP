/*Autor: Šimon Kadnár xkadna00*/

#include <Arduino.h>
#include <stdio.h>
#include <WiFi.h>
#include "ESPmDNS.h"

const int output_red = 2;
const int output1 = 5;
const int output_r = 13;
const int output_g = 12;
const int output_b = 14;
const int output2 = 27;

WiFiServer server(80);
String header;    //information from client
int mod = 0;      //tipe of animation
int speed = 500;  // speed of animation
int cnt1 = 0;
int cnt2 = 0;

void get_speed()
{
  int tmp = 0;
  int i = 18;   // on position 18 start speed number from form
  while(1)
  {
    if(header[i] >= 48 && header[i] <= 57)
    {
      tmp = tmp *10 + int(header[i]) - 48;
    }
    else
    {
      break;  // if speed number from form is complete
    }
    i++;
  }
  if (tmp>0)
  speed = tmp;
}

void animation1()
{
  if(cnt1 == 0)
  {
    analogWrite(output1, 255);
    analogWrite(output_r, 0);
    analogWrite(output_g, 0);
    analogWrite(output_b, 255);
    analogWrite(output2, 0);
    
    cnt1 = 1;
  }
  else if (cnt1 == 1 )
  {
    analogWrite(output1, 0);
    analogWrite(output_r, 255);
    analogWrite(output_g, 255);
    analogWrite(output_b, 0);
    analogWrite(output2, 255);
    cnt1 = 2;
  }
  else if (cnt1 == 2)
  {
    analogWrite(output1, 255);
    analogWrite(output_r, 255);
    analogWrite(output_g, 0);
    analogWrite(output_b, 255);
    analogWrite(output2, 0);
    cnt1 = 3;
  }
  else if (cnt1 == 3)
  {
    analogWrite(output1, 0);
    analogWrite(output_r, 255);
    analogWrite(output_g, 255);
    analogWrite(output_b, 255);
    analogWrite(output2, 255);
    cnt1 = 4;
  }
  else if (cnt1 == 4)
  {
    analogWrite(output1, 255);
    analogWrite(output_r, 0);
    analogWrite(output_g, 255);
    analogWrite(output_b, 255);
    analogWrite(output2, 0);
    cnt1 = 5;
  }
  else if (cnt1 == 5)
  {
    analogWrite(output1, 0);
    analogWrite(output_r, 0);
    analogWrite(output_g, 255);
    analogWrite(output_b, 0);
    analogWrite(output2, 255);
    cnt1 = 6;
  }
  else if (cnt1 == 6)
  {
    analogWrite(output1, 255);
    analogWrite(output_r, 255);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    analogWrite(output2, 0);
    cnt1 = 0;
  }
}
void animation2(int cnt){
  if(cnt & 0x01)
  {
    analogWrite(output1, 255);
    analogWrite(output_r, 0);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    analogWrite(output2, 0);
    cnt2++;
  }
  else
  {
    analogWrite(output1, 0);
    analogWrite(output_r, 0);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    analogWrite(output2, 255);
    cnt2++;
  }

  if(cnt1 == 0 && cnt2 ==3)
  {
    analogWrite(output_r, 255);
    analogWrite(output_g, 0);
    analogWrite(output_b, 255);
    cnt1 = 1;
    cnt2 = 0;
  }
  else if (cnt1 == 1 && cnt2 ==3)
  {
    analogWrite(output_r, 255);
    analogWrite(output_g, 255);
    analogWrite(output_b, 0);
    cnt1 = 2;
    cnt2 = 0;
  }
  else if (cnt1 == 2 && cnt2 ==3)
  {
    analogWrite(output_r, 0);
    analogWrite(output_g, 0);
    analogWrite(output_b, 255);
    cnt1 = 3;
    cnt2 = 0;
  }
  else if (cnt1 == 3 && cnt2 ==3)
  {
    analogWrite(output_r, 255);
    analogWrite(output_g, 255);
    analogWrite(output_b, 255);
    cnt1 = 4;
    cnt2 = 0;
  }
  else if (cnt1 == 4 && cnt2 ==3)
  {
    analogWrite(output_r, 0);
    analogWrite(output_g, 255);
    analogWrite(output_b, 0);
    cnt1 = 5;
    cnt2 = 0;
  }
  else if (cnt1 == 5 && cnt2 ==3)
  {
    analogWrite(output_r, 0);
    analogWrite(output_g, 255);
    analogWrite(output_b, 255);
    cnt1 = 6;
    cnt2 = 0;
  }
  else if (cnt1 == 6 && cnt2 ==3)
  {
    analogWrite(output_r, 255);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    cnt1 = 0;
    cnt2 = 0;
  }
}
void animation3()
{
  analogWrite(output1, 255 - cnt1);
  analogWrite(output2, 255 - cnt1);
  if(cnt2 == 0)
  {
    cnt1+=5;
    analogWrite(output_r, cnt1);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    if(cnt1 >= 255)
    cnt2++;
  }
  else if(cnt2 == 1)
  {
    cnt1-=5;
    analogWrite(output_r, cnt1);
    analogWrite(output_g, 255 - cnt1);
    analogWrite(output_b, 0);
    if(cnt1 <= 0)
    cnt2++;
  }
  else if(cnt2 == 2)
  {
    cnt1+=5;
    analogWrite(output_r, 0);
    analogWrite(output_g, 255 - cnt1);
    analogWrite(output_b, cnt1);
    if(cnt1 >= 255)
    cnt2++;
  }
  else if(cnt2 == 3)
  {
    cnt1-=5;
    analogWrite(output_r, 255 - cnt1);
    analogWrite(output_g, 0);
    analogWrite(output_b, cnt1);
    if(cnt1 <= 0)
    cnt2++;
  }
  else if(cnt2 == 4)
  {
    cnt1+=5;
    analogWrite(output_r, 255 - cnt1);
    analogWrite(output_g, cnt1);
    analogWrite(output_b, cnt1 );
    if(cnt1 >= 255)
    {
      cnt2++;
    }
  }
  else if(cnt2 == 5)
  {
    cnt1-=5;
    analogWrite(output_r, 255 - cnt1);
    analogWrite(output_g, cnt1);
    analogWrite(output_b, cnt1 );
    if(cnt1 <= 0)
    {
      cnt2 = 1;
      cnt1 = 255;
    }
  }
}
void animation4()
{
  analogWrite(output1, 255 - cnt1*2);
  analogWrite(output2, 255 - cnt1*2);
  if(cnt2 == 0)
  {
    cnt1+=5;
    analogWrite(output_r, cnt1);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    if(cnt1 >= 122)
    cnt2++;
  }
  else if(cnt2 == 1)
  {
    cnt1-=5;
    analogWrite(output_r, cnt1);
    analogWrite(output_g, 0);
    analogWrite(output_b, 0);
    if(cnt1 <= 0)
    cnt2++;
  }
  else if(cnt2 == 2)
  {
    cnt1+=5;
    analogWrite(output_r, 0);
    analogWrite(output_g, cnt1);
    analogWrite(output_b, 0);
    if(cnt1 >= 122)
    cnt2++;
  }
  else if(cnt2 == 3)
  {
    cnt1-=5;
    analogWrite(output_r, 0);
    analogWrite(output_g, cnt1);
    analogWrite(output_b, 0);
    if(cnt1 <= 0)
    cnt2=4;
  }
  else if(cnt2 == 4)
  {
    cnt1+=5;
    analogWrite(output_r, 0);
    analogWrite(output_g, 0);
    analogWrite(output_b, cnt1);
    if(cnt1 >= 122)
    {
      cnt2 = 5;
    }
  }
  else if(cnt2 == 5)
  {
    cnt1-=5;
    analogWrite(output_r, 0);
    analogWrite(output_g, 0);
    analogWrite(output_b, cnt1);
    if(cnt1 <= 0)
    {
      cnt2 = 0;
      cnt1 = 0;
    }
  }
}

void animation_mod(void *pvParameter)
{
  int cnt = 0;
  while(1)
  {
    if(mod == 1)
    {
      animation1();
    }
    else if(mod == 2)
    {
      animation2(cnt);
    }
    else if(mod == 3)
    {
      animation3();
    }
    else if(mod == 4)
    {
      animation4();
    }
    delay(speed);
    digitalWrite(output_red, LOW);
    cnt++;
    if (cnt == 255)
    {
      cnt = 0;
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(output_red, OUTPUT);
  pinMode(output1, OUTPUT);
  pinMode(output_r, OUTPUT);
  pinMode(output_g, OUTPUT);
  pinMode(output_b, OUTPUT);
  pinMode(output2, OUTPUT);

  // crate process animation_mod()
  xTaskCreate(&animation_mod, "animation_mod", 2048, NULL, 5, NULL);

  digitalWrite(output_red, LOW);
  digitalWrite(output1, LOW);
  digitalWrite(output_r, LOW);
  digitalWrite(output_g, LOW);
  digitalWrite(output_b, LOW);
  digitalWrite(output2, LOW);
  
  /*
  const char* ssid = "TP-LINK_EB28";
  const char* password ="82819958";

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());*/

  WiFi.softAP("rgb_esp32", NULL);
  Serial.println("");
  Serial.println("wifi: rgb_esp32");
  Serial.println("http://esp32");
  Serial.println(WiFi.softAPIP());

  server.begin();

  if(!MDNS.begin("esp32")) 
  {
    Serial.println("Error starting mDNS");
    return;
  }
}
/*CODE FOR CATCHING HAEDER TAKEN FROM https://randomnerdtutorials.com/esp32-web-server-arduino-ide/*/
void loop(){
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) 
  {                                       
    String currentLine = "";                
    while (client.connected()) 
    {  // loop while the client's connected
      if (client.available()) 
      {             
        char c = client.read();                              
        header += c;
        if (c == '\n') {

          if (currentLine.length() == 0) 
          {
            if (header.indexOf("GET /MOD1/on") >= 0) //choosing tipe of animation by button
            {
              Serial.println("MOD1");
              digitalWrite(output_red, HIGH); //showing the request was catched
              mod = 1;
              cnt1 = 0;
              cnt2 = 0;
            } 
            else if (header.indexOf("GET /MOD2/on") >= 0) 
            {
              Serial.println("MOD2");
              digitalWrite(output_red, HIGH);
              mod = 2;
              cnt1 = 0;
              cnt2 = 0;
            } 
            else if (header.indexOf("GET /MOD3/on") >= 0) 
            {
              Serial.println("MOD3");
              digitalWrite(output_red, HIGH);
              mod = 3;
              cnt1 = 0;
              cnt2 = 0;
            } 
            else if (header.indexOf("GET /MOD4/on") >= 0) 
            {
              Serial.println("MOD4");
              digitalWrite(output_red, HIGH);
              mod = 4;
              cnt1 = 0;
              cnt2 = 0;
            } 
            else if (header.indexOf("GET /off") >= 0) 
            {
              Serial.println("MOD4");
              digitalWrite(output_red, HIGH);
              mod = 0;
              cnt1 = 0;
              cnt2 = 0;
              analogWrite(output1, 0);
              analogWrite(output_r, 0);
              analogWrite(output_g, 0);
              analogWrite(output_b, 0);
              analogWrite(output2, 0);
            }
            else if (header.indexOf("GET /on") >= 0) 
            {
              Serial.println("MOD4");
              digitalWrite(output_red, HIGH);
              mod = 5;
              cnt1 = 0;
              cnt2 = 0;
            }
            else if (header.indexOf("GET /get?inputInt=") >= 0) 
            {
              digitalWrite(output_red, HIGH);
              get_speed();
              Serial.printf("SPEED: %i",speed);
            }
            
            client.println("<!DOCTYPE html><html>");
              client.println("<head> ");
                client.println("<meta name=\"viewport\" content=\"width=device-width, charset=\"utf-8\"");

                client.println("<link rel=\"icon\" href=\"data:,\">");
                client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                client.println(".button { background-color: green; border: none; color: white; padding: 16px 40px;");
                client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
                client.println(".button2 {background-color: red;}");
                client.println("input {background-color: #0CAFFF; color:white; font-size: 20px; font-family: Helvetica; padding: 16px; border: none;}");
                client.println("</style>");
              client.println("</head>");
            
              client.println("<body>");
              client.println("<h1>RGB CONTROLL PAGE</h1>");
              if (mod == 0)
              {
                client.println("<p><a href=\"/on\"><button class=\"button button2\">OFF</button></a></p>");
              } 
              else
              {   
                if (mod == 1) {
                  client.println("<p><a href=\"/MOD1/now\"><button class=\"button\">MOD1</button></a></p>");
                } else {
                  client.println("<p><a href=\"/MOD1/on\"><button class=\"button button2\">MOD1</button></a></p>");
                } 
                        
                if (mod == 2) {
                  client.println("<p><a href=\"/MOD2/now\"><button class=\"button\">MOD2</button></a></p>");
                } else {
                  client.println("<p><a href=\"/MOD2/on\"><button class=\"button button2\">MOD2</button></a></p>");
                }

                if (mod == 3) {
                  client.println("<p><a href=\"/MOD3/now\"><button class=\"button\">MOD3</button></a></p>");
                } else {
                  client.println("<p><a href=\"/MOD3/on\"><button class=\"button button2\">MOD3</button></a></p>");
                }

                if (mod == 4) {
                  client.println("<p><a href=\"/MOD4/now\"><button class=\"button\">MOD4</button></a></p>");
                } else {
                  client.println("<p><a href=\"/MOD4/on\"><button class=\"button button2\">MOD4</button></a></p>");
                }
                client.println("<p>SPEED:");
                client.println(speed);
                client.println("</p>");
                client.println("<form action=\"/get\" target=\"hidden-form\">");
                client.println("<input type=\"number \" name=\"inputInt\">");
                client.println("<input type=\"submit\" value=\"OK\" onclick=\"submitMessage()\">");
                client.println("</form>");

                client.println("<p><a href=\"/off\"><button class=\"button button\">ON</button></a></p>");
              }
              client.println("</body>");
            client.println("</html>");
            
            client.println();
            break;
          } 
          else 
          {
            currentLine = "";
          }
        } 
        else if (c != '\r') 
        {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    header = "";
    // close the connection
    client.stop();
    Serial.println("");
  }
}