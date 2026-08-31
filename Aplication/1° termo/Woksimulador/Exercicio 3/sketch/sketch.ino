int led[] = {2, 3, 4, 5};   

void setup()
{
for (int i=0; i<4; i++)
{
pinMode(led[i], OUTPUT);
}
}

void loop()
{    
  for (byte num=0; num<=15; num++)
  {
  for (int n=0; n<=3; n++)
  {    
  if (bitRead(num, n) == 1)   
  {
  digitalWrite(led[n], HIGH);
  }
  else
  {
  digitalWrite(led[n], LOW);
  }
  }
  delay(2000);
  }
}
