#include<Servo.h>
const unsigned int MAX_MESSAGE_LENGTH = 5;
int number;
int angle1, angle2, angle3, angle4, angle5;
Servo shoulder;
Servo elbow;
Servo wrist;
Servo gripper;


void setup() {
 Serial.begin(9600);
 pinMode(13,OUTPUT);

 shoulder.attach(3);
 shoulder.write(90);
 elbow.attach(5);
 elbow.write(180);
 wrist.attach(6);
 wrist.write(180);
 gripper.attach(9);
 gripper.write(10);
 
}

void loop() {

 //Check to see if anything is available in the serial receive buffer
 while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';
     digitalWrite(13,HIGH);
     
     //Or convert to integer and print
     number = atoi(message);
    // Serial.println(number);

     //Reset for the next message
     message_pos = 0;
   }
 }
 int angl = number/10;
 int serv = number%10;
 switch(serv){
  case 1:
    angle1 = angl;
    break;
  case 2:
    angle2 = angl;
    break;
  case 3:
    angle3 = angl;
    break;
  case 4:
    angle4 = angl;
    break;
  case 5:
    angle5 = angl;
  default:
    angle1=0;
 }
 Serial.print(angle1);
 Serial.print("\t");
 Serial.print(angle2);
 Serial.print("\t");
 Serial.print(angle3);
 Serial.print("\t");
 Serial.print(angle4);
 Serial.print("\t");
 Serial.println(angle5);

 shoulder.write(angle1);
 elbow.write(angle2);
 wrist.write(angle3);
 gripper.write(angle4);
}
