String FrontTireShift(int fronttop, int frontbot)
{

  String ShiftType;
  if (fronttop == frontbot)
  {
    Serial.println("Normal Shift");
    ShiftType = 'Normal';
  }
  else if (fronttop < frontbot)
  {
    Serial.println("Shift to left");
    ShiftType = 'Left';
  }
  else if (fronttop > frontbot)
  {
    Serial.println("Shift to right");
    ShiftType = 'Right';
  }
  return (ShiftType);
}
