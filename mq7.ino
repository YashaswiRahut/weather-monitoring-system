void setup() 
{
  Serial.begin(9600);
}
 
void loop() 
{
  double sensorValue;
  sensorValue = analogRead(A0);
  double sensor_volt = sensorValue/1024*5.0;
  double RS_gas = (5.0-sensor_volt)/sensor_volt;
  double R0 = RS_gas/(26+(1/3));
  Serial.print("CO :");
  Serial.print(R0);
  Serial.println("*10^(-4) moles ");
  delay(1000);
}

