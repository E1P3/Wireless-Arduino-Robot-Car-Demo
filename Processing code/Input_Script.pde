import websockets.*;

WebsocketServer ws;
int now;
String keyInput;

void setup(){
  size(200,200);
  ws= new WebsocketServer(this,8080,"");
  now=millis();
}

void draw(){

}

void webSocketServerEvent(String msg){
 println("moved " + msg);
}

void keyPressed(){
  keyInput = str(key);
  ws.sendMessage(keyInput);
  println(keyInput);
}
