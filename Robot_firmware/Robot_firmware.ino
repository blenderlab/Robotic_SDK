#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define LED 13
bool state = LOW; //The initial state of the function is defined as a low level
char getstr;      //Defines a function that receives the Bluetooth character


//Control LED sub function
void stateChange() {
  state = !state;
  digitalWrite(LED, state);
}

/*
  Stop motor control：Turn off the motor drive
*/
void motorstop(bool debug = false)
{
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  if (debug)
    Serial.println("Stop!");
}
void setup() {
  // put your setup code here, to run once:

  pinMode(IN1, OUTPUT); //Motor-driven port configuration
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("I'm ready !!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    //The Bluetooth serial port to receive the data in the function
    getstr = Serial.read();
    //Serial.print(getstr);
    if (getstr == 'a') {
      stateChange();
    }
    if (getstr == 'f') {
      forward(true, 255);
    }
    if (getstr == 'b') {
      back(true, 255);
    }
    if (getstr == 'X') {
      motorstop(true);
    }
  }
}
/*
  Control motor：Car movement forward
*/
void forward(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed);
  analogWrite(ENB, in_carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  if (debug)
    Serial.println("Go forward!");
}
/*
  Control motor：Car moving backwards
*/
void back(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed);
  analogWrite(ENB, in_carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  if (debug)
    Serial.println("Go back!");
}
/*
  Control motor：The car turns left and moves forward
*/
void left(bool debug, int16_t in_carSpeed)
{

  analogWrite(ENA, in_carSpeed);
  analogWrite(ENB, in_carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  if (debug)
    Serial.println("Go left!");
}
/*
  Control motor：The car turns right and moves forward
*/
void right(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed);
  analogWrite(ENB, in_carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  if (debug)
    Serial.println("Go right!");
}

void forward_left(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed / 2);
  analogWrite(ENB, in_carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  if (debug)
    Serial.println("Go right!");
}

void forward_right(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed);
  analogWrite(ENB, in_carSpeed / 2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  if (debug)
    Serial.println("Go right!");
}

void back_left(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed / 2);
  analogWrite(ENB, in_carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  if (debug)
    Serial.println("Go right!");
}

void back_right(bool debug, int16_t in_carSpeed)
{
  analogWrite(ENA, in_carSpeed);
  analogWrite(ENB, in_carSpeed / 2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  if (debug)
    Serial.println("Go right!");
}
