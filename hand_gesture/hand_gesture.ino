const int trigger1 = 2; //Trigger pin of 1st Sensor -Left
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; // 2nd Sesnor -right
const int echo2 = 5;//
const int trigger3 = 6;// 3 -3rd sensor  
const int echo3 = 7; // 
const int ir = 8; // ir sensor pin  
const int ldr = 9; // light sensor 

long time_taken;
int dist,distL,distR,dist3;
int ir_flag=0;
int bright_flag=0;


 

void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
pinMode(trigger3, OUTPUT); 
pinMode(echo3, INPUT); 
pinMode(ir, INPUT);
pinMode(ldr,INPUT);

}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
/*if(dist>50)
  dist=50;*/
/*
if (dsit <10)
  dist=10;*/
}

void loop() { //infinite loop
//Serial.println(ir_flag);
//Serial.println(digitalRead(ldr));
if(Serial.print(digitalRead(ldr)==0))
{Serial.println("lightup");
 bright_flag=1;}
if(digitalRead(ldr)==1 && bright_flag==1)
{bright_flag=0;
Serial.println("lightdown");}
if(digitalRead(ir)==1)
  {ir_flag=ir_flag+1;
   if(ir_flag%2==1)
   Serial.println("start");
   else
   Serial.println("stop");
   } // switch on /off gestures depending on ir_flag value

if(ir_flag%2==1){
calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);
distR =dist; //get distance of right sensor

calculate_distance(trigger3,echo3);
dist3 =dist; //get distance of 3rd sensor

Serial.print("L=");
Serial.println(distL);

Serial.print("THREE=");
Serial.println(dist3);

Serial.print("R=");
Serial.println(distR);
  
//exit  
if(distL<10 && distR<10)
{
  delay(200);
  calculate_distance(trigger1,echo1);
  distL =dist;
  calculate_distance(trigger2,echo2);
  distR =dist;
  if(distL<10 && distR<10)
  {
    delay(100);
    if(distL <10 && distR <10)
    {Serial.println("Exit"); delay(300);}
  }
}

//Pause Mode -Hold
else if (distL <= 10) //Detect left hand
{
  delay(100);
  calculate_distance(trigger1,echo1);
  distL =dist;
  if(distL <=10)  
  {Serial.println("Play/Pause"); delay (500);}
}
 

//Control Modes
//Lock Left - Control Mode
else if (distL>=13 && distL<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  if (distL>=13 && distL<=17)
  {
    int distL2=0;
    Serial.println("Left Locked");
    while(distL2<=40)
    {
      delay(200);
      calculate_distance(trigger1,echo1);
      distL2 =dist;
      if (distL2>distL) //Hand pulled out
      {Serial.println ("Vup"); delay (500);}
      if (distL2<distL) //Hand pushed in 
      {Serial.println ("Vdown"); delay (500);}
      
    }
  }
}

//Lock Right - Control Mode
else if (distR>=13 && distR<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=13 && distR<=17)
  {
    int distR2=0;
    Serial.println("Right Locked");
    while(distR2<=40)
    {
      delay(200);
      calculate_distance(trigger2,echo2);
      distR2 =dist;
      if (distR2<distR) //Right hand pushed in
      {Serial.println ("Rewind"); delay (300);}
      if (distR2>distR) //Right hand pulled out
      {Serial.println ("Forward"); delay (300);}
  }
}
}

else if(dist3 <=40)
{
  delay(100);
  calculate_distance(trigger3,echo3);
  dist3 =dist;
  if(dist3<=40)
  { 
    
    Serial.println("tab");
    while(dist3<=40){
    calculate_distance(trigger3,echo3);
    dist3 =dist; //get distance of 3rd sensor

    calculate_distance(trigger1,echo1);
    distL =dist; //get distance of left sensor

    calculate_distance(trigger2,echo2);
    distR =dist; //get distance of right sensor

    if(distL<40)
    {Serial.println("lefttab"); delay(1000);}
    else if(distR<40)
    {Serial.println("righttab"); delay(1000);}
    }
    delay(100);
  }
  Serial.println("release");
}

else if(distR <=10)
{ delay(100);
  calculate_distance(trigger2,echo2);
  distR =dist;
  if(distR <=10)  
  {Serial.println("fullscreen"); delay (500);}
}
}
delay(500);
}

 
