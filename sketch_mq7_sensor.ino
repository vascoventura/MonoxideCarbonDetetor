/*  
 MQ-7 cheater  
 Uses PWM and an N-Channel MosFET to trick an ICSTATION MQ-7 CO detector  
 into measuring CO according to the datasheet of the manufaturer.  
 */

 //Variáveis Sensor
 int sensorPin = A4;  // select the input pin for the CO sensor  
 int sensorValue = 0; // variable to store the value coming from the sensor  

 //Variáveis LED
  int rSensor = A0;
  int gSensor = A1;
  int bSensor = A2;
 
 // Initial setup
 void setup() {  
  // initialize digital pin LED_BUILTIN as an output  
  pinMode(LED_BUILTIN, OUTPUT);

  //initialize LED pins
  pinMode(rSensor, OUTPUT);
  pinMode(gSensor, OUTPUT);
  pinMode(bSensor, OUTPUT);
  
  // initialize the serial port  
  Serial.begin(9600);  
 }  
 // the loop function runs over and over again forever  
 void loop() {  
  analogWrite(LED_BUILTIN, 255);  // turn the heater fully on  
  delay(15000);            // heat for 60 second  
 // now reduce the heating power  
  analogWrite(LED_BUILTIN, 72);  // turn the heater to approx 1,4V  
  delay(90000);            // wait for 90 seconds  
 // we n1eed to read the sensor at 5V, but must not let it heat up. So hurry!  
  digitalWrite(LED_BUILTIN, HIGH);  
  delay (5000); //don't know how long to wait without heating up too much. Getting an analog read apparently takes 100uSec  
   // read the value from the sensor:  
  sensorValue = analogRead(sensorPin);  
  Serial.println(sensorValue);

  if(sensorValue > 0 && sensorValue <= 255){
    verde();
  } else if(sensorValue > 255 && sensorValue <=716){
    amarelo();
  }else{
    vermelho();
  }
 }

 void vermelho(){
  analogWrite(rSensor, 1023);
  analogWrite(gSensor, 0);
  analogWrite(bSensor, 0);
 }
 void amarelo(){
  analogWrite(rSensor, 0);
  analogWrite(gSensor, 0);
  analogWrite(bSensor, 1023);
  
 }
 void verde(){
  analogWrite(rSensor, 0);
  analogWrite(gSensor, 1023);
  analogWrite(bSensor, 0);  
 }
