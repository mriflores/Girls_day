#include <RH_ASK.h>
#include <SPI.h> // not used, but important for getting fonctions for make it work

RH_ASK driver; // Config 2000bps, TX pin 12, RX  pin 11

#define Mon_ID "100"
#define RECIVER_ID "300"

void setup() {
    Serial.begin(9600);
    if (!driver.init()) {
        Serial.println("Init not working");
    }
}

void loop() {
    Sending_message();
    reading_message();
}

void Sending_message(){

 if (Serial.available() > 0) { 

        String input = Serial.readStringUntil('\n'); 
        input.trim(); 

        if (input.length() > 0) {
           
            String message_id_temp = String(RECIVER_ID)+" "+input;
            const char* msg = message_id_temp.c_str();

            driver.send((uint8_t *)msg, strlen(msg));
            driver.waitPacketSent(); 

            Serial.print("Sending: ");
            Serial.println(input.c_str());
        }
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
            Serial.print("Recive: ");
            Serial.println(message); 
        }
    }
}