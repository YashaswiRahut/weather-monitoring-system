void setup(){
 Serial.begin(9600);
 pinMode(A0, OUTPUT);
}
void loop(){
 if(analogRead(A0)<300&&analogRead(A0)>0) Serial.println("heavy rain");
 else if(analogRead(A0)<500&&analogRead(A0)>300) Serial.println("Moderate Rain");
 else Serial.println("No Rain");


delay(1000);}
