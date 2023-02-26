/*
   Developed for GM Capstone Project
   The relays should not change state rapidly as this will reduce the lifetime of the relay
   Each relay should have a 2 seconds(2000 ms) delay between switching between states
   Actuators move at a rate of +/- 5mm/s.
   All measurements are in cm or ms.
   Do I want to use an encoder?
*/

const int RequiredDistance = 10; //This measured in cm.
//Variables for the sensors
int readings[10];
int index = 0;
int total = 0;
int average = 0;


//Variables for the actuators
//Top Front Actuator
const int TF_Extend = 9;
const int TF_Retract = 8;
//Top Bot Actuator
const int TB_Extend = 11;
const int TB_Retract = 10;

const int CadillacTireAlingment = 4;
const int ImpalaTireAlignment = 3;


int duty;
bool MoveState;
//Define LEDs
int GreenLED;//This for met distance requirement
int RedLED;//Error
int YellowLED;//Operation in Process

int timer = 0;
const int ActuatorLength = 17.5;
//const int BallSliderLength = 4;
//Ultrasonic Sensor Pin Location Definement
const int TFUSSEcho = 26;
const int TFUSSTrig = 27;


const int TBUSSEcho = 22;
const int TBUSSTrig = 23;


//Ultrasonic Sensor Distance Variables

int FrontTop_Distance = 0;
int FrontBack_Distance = 0;

//Timers
int intervalTFE = 4000;
int intervalTFR = 3000;
int intervalTBE = 4000;
int intervalTBR = 3000;

unsigned long currentMillis;

String CarType;
String AlignmentType;




void setup()
{
  Serial.begin(115200); // Starts the serial communication

  pinMode(TFUSSTrig, OUTPUT);
  pinMode(TFUSSEcho, INPUT);

  pinMode(TBUSSTrig, OUTPUT);
  pinMode(TBUSSEcho, INPUT);

  pinMode(TF_Extend, OUTPUT);
  pinMode(TF_Retract, OUTPUT);

  pinMode(TB_Extend, OUTPUT);
  pinMode(TB_Retract, OUTPUT);
ResetPosition(TF_Extend, TF_Retract);
  ResetPosition(TB_Extend,TB_Retract);
  delay(5000);
  

}

void loop()
{
  
  FrontTop_Distance = constrain(Ultrasonic_Sensor(TFUSSTrig, TFUSSEcho), 0, 20);
  FrontBack_Distance = constrain(Ultrasonic_Sensor(TBUSSTrig, TBUSSEcho), 0, 20);
  AlignmentType = FrontTireShift(FrontTop_Distance, FrontBack_Distance);
  Serial.print("Tire Alignment: ");
  Serial.println(AlignmentType);

  Serial.print("Front Top Distance: ");
  Serial.print(FrontTop_Distance);
  Serial.println(" cm.");

  Serial.print("Front Bot Distance: ");
  Serial.print(FrontBack_Distance);
  Serial.println(" cm.");

  //Determine shift distance
  currentMillis = millis();
  unsigned long prevMillisTF;
  unsigned long prevMillisTB;
  
  if (FrontBack_Distance >9 && FrontBack_Distance <11)
  {
    Stop(TB_Extend, TB_Retract);
    delay(3000);
  }
  else if (FrontBack_Distance < 9)
  {
    prevMillisTB = Extend(TB_Extend, TB_Retract, currentMillis, prevMillisTB, intervalTBE);
  }
  else if (FrontBack_Distance > 11)
  {
    prevMillisTB = Retract(TB_Extend, TB_Retract, currentMillis, prevMillisTB, intervalTFR);
  }
  if (FrontTop_Distance >10 && FrontTop_Distance<12)
  {
    Stop(TF_Extend, TF_Retract);
    delay(3000);
  }
  else if (FrontTop_Distance < 10)
  {
    prevMillisTF = Extend(TF_Extend, TF_Retract, currentMillis, prevMillisTF, intervalTFE);
  }
  else if (FrontTop_Distance > 12)
  {
    prevMillisTF = Retract(TF_Extend, TF_Retract, currentMillis, prevMillisTF, intervalTFR);
  }
  
}
