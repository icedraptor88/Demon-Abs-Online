int getUserInput(){
  int s = Serial.read();
  while(s < 1)
    s = Serial.read();
  return s;
}

bool success;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  int sittingUp = 0;
  int sensorStatus = 0;
  int numSitUps = 0;
  int timeSec = 0;

  int maxSitup = 0;

  Serial.println("How many Sit-Ups do you want? (In Incremants of 10, from 1-9)");
  maxSitup = (getUserInput() - 48) * 10;
    
  Serial.print("Sit-ups: ");
  
  
  Serial.println(maxSitup);
  
  int previousRead = 0;
  
  while(timeSec < 30)
  {
    sensorStatus = digitalRead(6);
    if(timeSec < 16)
    {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    }
    if(timeSec > 15)
    {
      digitalWrite(3, HIGH);
      delay(100);
      digitalWrite(3, LOW);
    }
    if(sensorStatus == 0)
    {
      previousRead = 0;
      sittingUp = 0;
      timeSec += 1;
    }
    else if(sensorStatus == 1)
    {
      if(previousRead == 0){
        sittingUp = 1;
        timeSec = 0;
        numSitUps = numSitUps + 1;
        Serial.print("Sit Up: ");
        Serial.println(numSitUps);
        sensorStatus = 0;
        previousRead = 1;
      }
    }
    //Serial.println(sittingUp);
    delay(1000);
  }
  Serial.print("You did ");
  Serial.print(numSitUps);
  Serial.println(" sit-ups!");  


  
  if(numSitUps < maxSitup)
  {
    success = false;
  }
  else
  {
    success = true;
    Serial.println("Success!");
  }
    
}

void loop() {
  if(!success){
    digitalWrite(3, HIGH);
    delay(100);
    digitalWrite(3, LOW);
    Serial.println("You Failed!");
  }
  else{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    //   Serial.println("Success!");
  }
}
