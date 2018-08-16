unsigned long time=0;
const byte PWM = 10;               // Timer 1 "B" output: OC1B
int period = 2000;
int period_1 = 1000;
int period_2 = 1000;
unsigned long time_now = 0;

  int AH =  2;
  int BH =  5;
  int CH =  6;
  int AL =  3;
  int BL =  4;
  int CL =  7;
  int sw_pin = 8;

  int Hallsensor1 =  9;
  int Hallsensor2 =  11;
  int Hallsensor3 =  12;


// 16 MHz clock divided by 10 KHz frequency desired
  const long timer1_OCR1A_Setting = 16000000L / 1000L;

void setup()
{
 Serial.begin(9600);
 pinMode(PWM, OUTPUT);
 pinMode(AH, OUTPUT);
 pinMode(BH, OUTPUT);
 pinMode(CH, OUTPUT);
 pinMode(AL, OUTPUT);
 pinMode(BL, OUTPUT);
 pinMode(CL, OUTPUT);
 pinMode(Hallsensor1, INPUT);
 pinMode(Hallsensor2, INPUT);
 pinMode(Hallsensor3, INPUT);
digitalWrite(sw_pin, HIGH);
 
// set up Timer 1 - gives us 10.000 KHz
 // Fast PWM top at OCR1A
 TCCR1A = _BV (WGM10) | _BV (WGM11) | _BV (COM1B1); // fast PWM, clear OC1B on compare
 TCCR1B = _BV (WGM12) | _BV (WGM13) | _BV (CS10);   // fast PWM, no prescaler
 OCR1A =  timer1_OCR1A_Setting - 1;                 // zero relative

 }

 void loop()
{   
   int joystick = analogRead(A5);
                   
 /* if (joystick < 520 && joystick > 440)
             {
              time = time + 1000;
              Serial.print ("timeval= ");Serial.println (time);
             }
  else 
      {
        time = 0;
        }
   if (time < 2000)
 {*/
if(joystick > 520 && joystick <= 1023)
  {
    for (int x=0; x <= 1023; x=x+1)
    {
      int joystick = analogRead(A5);
      int time=time+1;
      while (time >= 1020 && joystick >= 1020)
   {
    int joystick = analogRead(A5);
    Serial.print ("time= ");
     Serial.println (time);  
     Serial.print ("joyval= ");
     Serial.println (joystick); 
    OCR1B = (((long) 1023 * timer1_OCR1A_Setting) / 1024L) - 1;
    forward();

    if (joystick < 900)
    break;
    }
    
     OCR1B = (((long) x * timer1_OCR1A_Setting) / 1024L) - 1;
     
     Serial.print ("joyval= ");
     Serial.println (joystick);
     forward();
     int a=x;
    if (joystick < 520)
   {
    Serial.println (joystick);
     for (int z=a; z >= 0; z=z-1)
     { 
      Serial.println ("z");
      Serial.println (z);
      OCR1B = (((long) z * timer1_OCR1A_Setting) / 1024L) - 1;  
      forward();
      if (z == 0)
      {
      OCR1B= 0;
      delay(1000);
      } 
     }
break;
}}}






else if (joystick >= 0 && joystick < 500)
  { 
    for (int y=0; y <= 1023; y=y+1)
    {
     Serial.print ("joyval= ");
     Serial.println (joystick);
     OCR1B = (((long) y * timer1_OCR1A_Setting) / 1024L) - 1;
 
reverse();
 int b=y;
 int joystick = analogRead(A5);
  int time1=time1+10;
      while (time1 >= 1020 && joystick <= 10)
   {
    int joystick = analogRead(A5);
    Serial.print ("time= ");
     Serial.println (time1);  
     Serial.print ("joyval= ");
     Serial.println (joystick); 
    OCR1B = (((long) 1023 * timer1_OCR1A_Setting) / 1024L) - 1;
    reverse();

    if (joystick >10 )
    break;
    }
 if (joystick >= 500)
 {
   for (int m=b; m >= 0; m=m-1)
    {
     int joystick = analogRead(A5);
     Serial.print ("joyval2= ");
     Serial.println (joystick); 
     OCR1B = (((long) m * timer1_OCR1A_Setting) / 1024L) - 1;  
     reverse ();
     if (m == 0)
      {
      OCR1B= 0;
      delay(1000);
      } 
}
break;
}}}}
 
 
 
 
 void forward()
 {
 if (digitalRead(Hallsensor1)== 1 && digitalRead(Hallsensor2)== 0 && digitalRead(Hallsensor3)== 1) // 101
 {
  digitalWrite(AH, HIGH);    
  digitalWrite(BH, LOW);    
  digitalWrite(CH, LOW);
  digitalWrite(AL, HIGH);      
  digitalWrite(BL, LOW);     
  digitalWrite(CL, HIGH);
 }

 else if(digitalRead(Hallsensor1)==0 && digitalRead(Hallsensor2)== 0 && digitalRead(Hallsensor3)== 1) // 001
 {
   digitalWrite(AH, HIGH);     digitalWrite(BH, LOW);    digitalWrite(CH, LOW);
   digitalWrite(AL, HIGH);      digitalWrite(BL, HIGH);         digitalWrite(CL, LOW);

 }
 
 else if(digitalRead(Hallsensor1)== 0 && digitalRead(Hallsensor2)== 1 && digitalRead(Hallsensor3)== 1) // 011
 {
   digitalWrite(AH, LOW);   digitalWrite(BH, HIGH);   digitalWrite(CH, LOW);
   digitalWrite(AL, HIGH);   digitalWrite(BL, HIGH);   digitalWrite(CL, LOW);
 }
 
else if(digitalRead(Hallsensor1)==0 && digitalRead(Hallsensor2)== 1 && digitalRead(Hallsensor3)== 0) // 010
{
   digitalWrite(AH, LOW);   digitalWrite(BH, HIGH);   digitalWrite(CH, LOW);
   digitalWrite(AL, LOW);   digitalWrite(BL, HIGH);   digitalWrite(CL, HIGH);
}

else if(digitalRead(Hallsensor1)== 1 && digitalRead(Hallsensor2)== 1 && digitalRead(Hallsensor3)== 0) // 110
{
   digitalWrite(AH, LOW);      digitalWrite(BH, LOW);    digitalWrite(CH, HIGH);
   digitalWrite(AL, LOW);       digitalWrite(BL, HIGH);      digitalWrite(CL, HIGH);
}

else if(digitalRead(Hallsensor1)==1 && digitalRead(Hallsensor2)== 0 && digitalRead(Hallsensor3)== 0) // 100
{

   digitalWrite(AH, LOW);       digitalWrite(BH, LOW);       digitalWrite(CH, HIGH);
   digitalWrite(AL, HIGH);        digitalWrite(BL, LOW);     digitalWrite(CL, HIGH);
 }
 }
 
void reverse()
 {
 if (digitalRead(Hallsensor1)== 0 && digitalRead(Hallsensor2)== 1 && digitalRead(Hallsensor3)== 1) // 011
 {
  digitalWrite(AH, HIGH);    
  digitalWrite(BH, LOW);    
  digitalWrite(CH, LOW);
  digitalWrite(AL, HIGH);      
  digitalWrite(BL, LOW);     
  digitalWrite(CL, HIGH);
 }

 else if(digitalRead(Hallsensor1)==0 && digitalRead(Hallsensor2)== 1 && digitalRead(Hallsensor3)== 0) //0
 {
   digitalWrite(AH, HIGH);     digitalWrite(BH, LOW);    digitalWrite(CH, LOW);
   digitalWrite(AL, HIGH);      digitalWrite(BL, HIGH);         digitalWrite(CL, LOW);

 }
 
 else if(digitalRead(Hallsensor1)== 1 && digitalRead(Hallsensor2)== 1 && digitalRead(Hallsensor3)== 0) // 011
 {
   digitalWrite(AH, LOW);   digitalWrite(BH, HIGH);   digitalWrite(CH, LOW);
   digitalWrite(AL, HIGH);   digitalWrite(BL, HIGH);   digitalWrite(CL, LOW);
 }
 
else if(digitalRead(Hallsensor1)==1 && digitalRead(Hallsensor2)== 0 && digitalRead(Hallsensor3)== 0) // 010
{
   digitalWrite(AH, LOW);   digitalWrite(BH, HIGH);   digitalWrite(CH, LOW);
   digitalWrite(AL, LOW);   digitalWrite(BL, HIGH);   digitalWrite(CL, HIGH);
}

else if(digitalRead(Hallsensor1)== 1 && digitalRead(Hallsensor2)== 0 && digitalRead(Hallsensor3)== 1) // 110
{
   digitalWrite(AH, LOW);      digitalWrite(BH, LOW);    digitalWrite(CH, HIGH);
   digitalWrite(AL, LOW);       digitalWrite(BL, HIGH);      digitalWrite(CL, HIGH);
}

else if(digitalRead(Hallsensor1)==0 && digitalRead(Hallsensor2)== 0 && digitalRead(Hallsensor3)== 1) // 100
{

   digitalWrite(AH, LOW);       digitalWrite(BH, LOW);       digitalWrite(CH, HIGH);
   digitalWrite(AL, HIGH);        digitalWrite(BL, LOW);     digitalWrite(CL, HIGH);
 }
 }
 
