#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"
#include "MotorController.h"
#include "SAMDTimerInterrupt.h"
#include "SAMD_ISR_Timer.h"

#define M1_DIR1 A2
#define M1_DIR2 5
#define M2_DIR1 A3
#define M2_DIR2 6 

#define IR_LEFT 9
#define IR_RIGHT 10

#define trigPin 12                                    
#define echoPin A1

SAMDTimer ITimer0(TIMER_TC3);
MotorController motor;

int currentSpeed = 255;

volatile long echo_start = 0;                          
volatile long echo_end = 0;                           
volatile long echo_duration = 0;
volatile long previous_duration = 0;

volatile bool previousObstacleCheck = LOW;
volatile bool stop_trigger;
volatile bool pulseSwitch = LOW;
bool darkMode = HIGH; // HIGH = black track, LOW = white track


///////please enter your sensitive data in the Secret tab/arduino_secrets.h
/////// Wifi Settings ///////
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

String message;
char dir;
int input;
long timerino;
long timerinoo;

char serverAddress[] = "192.168.50.170";  // server address
int port = 8080;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;
int count = 0;

void setup() {

  // put your setup code here, to run once:
  pinMode(M1_DIR1, OUTPUT);
  pinMode(M1_DIR2, OUTPUT);
  pinMode(M2_DIR1, OUTPUT);
  pinMode(M2_DIR2, OUTPUT);
  
  motor = MotorController(M1_DIR1, M1_DIR2, M2_DIR1, M2_DIR2);

  
  Serial.begin(9600);
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  Serial.println("starting WebSocket client");
  client.begin();

  while (client.connected()) {

    int messageSize = client.parseMessage();

    if (messageSize > 0) {
      
      Serial.println("Received a message:");
      message = client.readString();
      dir = message[0];
      Serial.println(message);

      timerino = micros();

    }

    if(micros()- timerino >100000 || timerino == 0){
      dir = '0';  
      timerino = 0;
    }

    
    if(dir == 'w'){
      input = 1;
    }else if(dir == 's'){
      input = 2;
    }else if(dir == 'a'){
      input = 4;
    }else if(dir =='d'){
      input = 3;
    }else{
      input = 0;  
    }

    switch(input){
      case 1:
        Serial.println(1);
        motor.moveTo(1, currentSpeed);
        break;
      case 4:
        Serial.println(4);
        motor.moveTo(4, currentSpeed);
        break;
      case 3:
        Serial.println(3);
        motor.moveTo(3, currentSpeed);
        break;
      case 2:
        Serial.println(2);
        motor.moveTo(2, currentSpeed);
        break;  
      default:
        motor.moveTo(0, 0);
    }
 
  }

  Serial.println("disconnected");
}

