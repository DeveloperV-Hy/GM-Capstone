unsigned long Extend(int forward, int reverse, unsigned long currentMillis, unsigned long prevMillis, int Interval) //extending action
{
  if ((currentMillis - prevMillis) >= Interval)
    digitalWrite(forward, LOW);
  digitalWrite(reverse, HIGH);
  prevMillis = currentMillis;
  return prevMillis;
}

unsigned long Retract(int forward, int reverse, unsigned long currentMillis, unsigned long prevMillis, int Interval) //retracting action
{
  if ((currentMillis - prevMillis) >= Interval)
    digitalWrite(forward, HIGH);
  digitalWrite(reverse, LOW);
  prevMillis = currentMillis;
  return prevMillis;
}


void Stop(int forward, int reverse) //braking
{
  digitalWrite(forward, HIGH);
  digitalWrite(reverse, HIGH);
}

void ResetPosition(int forward, int reverse)
{
  digitalWrite(reverse,LOW);
  digitalWrite(forward,HIGH);
  
}
