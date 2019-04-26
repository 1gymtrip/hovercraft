int ultrasonic() {
  /* 
  Through transmition of ultrasonic waves calculates the distance to the nearest object.
  Distance = Δt * c / 2
  Δt: Time between Transmition and Reception 
  c : Speed of Sound in dry air at 20°C
  We divide by 2 because the Δt represents the time for the wave to go hit the object and then come back again.
  By dividing by 2 we can find the distance the wave traversed to reach the object, thus finding the distance between object and vehicle
  */
  int distance;
  int duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);//Transmition
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);//Δt
  distance = duration * 343 / 2;//Distance = Δt * c / 2
  return (distance);
}
