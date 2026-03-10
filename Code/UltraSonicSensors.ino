/*
 * Information about Ultrasonic_Sensor Function
*/
int Ultrasonic_Sensor(const int trigPin, const int echoPin)
{
  //pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  //pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.0343 / 2;
  const int numVal = 10;
  int avgVal = 0;
  int totalVal = 0;
  for (int i = 0; i < numVal; i++)
  {
    totalVal = totalVal + distance;
      Serial.println(totalVal);
    delay(100);        // delay in between reads for stability
  }
  avgVal = totalVal / numVal;

  // Prints the distance on the Serial Monitor
  return avgVal;
  delay(1950);
}
