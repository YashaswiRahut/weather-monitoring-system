int AnalogPin = 0; 
int LEDpin = 11;      
int Reading;      
void setup(void) 
{
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
  pinMode(LEDpin, OUTPUT);
}
 
void loop(void) {
  Reading = analogRead(AnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(Reading);
if(Reading<200)
Serial.print("needs water"), //connect your motor pins and turn on the motor
delay(50000);
else
Serial.print("the plants is watered");
delay(100);
}
