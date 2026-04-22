
#include <RH_ASK.h>
#include <SPI.h> // not used, but important for getting fonctions for make it work
#include <ServoTimer2.h>

#define rollPin  2
int pos = 0; 
RH_ASK driver; // Config 2000bps, TX pin 12, RX  pin 11
ServoTimer2 miServo; 


#define Mon_ID "100"
#define RECIVER_ID "300"

void setup() {
    miServo.attach(rollPin);     
    Serial.begin(9600);

    if (!driver.init()) {
        Serial.println("Init not working");
    }
}

void loop() {
    //incPulse();
    Sending_message();
    reading_message();
}

void Sending_message(){
    if (Serial.available() == 0){
        return;
    }

    String input = Serial.readStringUntil('\n'); 
    if (input != NULL){
        String message_id_temp = String(RECIVER_ID)+" "+input;
        const char* msg = message_id_temp.c_str();

        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();

        Serial.print("Sending: ");
        Serial.println(input.c_str());
    }
}

void reading_message(){
    uint8_t buf[50]; 
    uint8_t buflen = sizeof(buf);
    char * id_read;
    char * message;
    if (driver.recv(buf, &buflen)) { 
        
        buf[buflen]='\0'; //End of message
        id_read = strtok((char*)buf, " ");
        message =strtok(NULL,"\0");
        
        if(id_read != NULL && strcmp(id_read, Mon_ID) == 0){
            Serial.print("Receive: ");
            Serial.println(message); 
            strupr(message);
            if(strcmp(message, "OPEN") == 0){
                Serial.println("Opening doors");
                int angle = 90;
                int anchoPulso = map(angle, 0, 180, 750, 2800);
                miServo.write(anchoPulso);

            }else if(strcmp(message, "CLOSE") == 0){
                
                Serial.println("Closing doors");
                int angle = 0;
                int anchoPulso = map(angle, 0, 180, 750, 2800);
                miServo.write(anchoPulso);

            }
        }
    }
}

int incPulse(){
   if (Serial.available() > 0) {
    
    int angle = Serial.parseInt();
    
    while(Serial.available() > 0) {
      Serial.read();
    }
    
    
    if (angle >= 0 && angle <= 180) {
      Serial.print("Moving servo: ");
      Serial.print(angle);
      Serial.println(" degrees.");
      
    
      int anchoPulso = map(angle, 0, 180, 750, 2800);
      
      miServo.write(anchoPulso);
      
    } else {
      Serial.println("Error: anglee out of range");
    }
  } 
}
