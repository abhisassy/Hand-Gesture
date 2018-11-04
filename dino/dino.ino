const int trigger1 = 2; //Trigger pin of 1st Sesnor
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor

long time_taken;
int dist,distL,distR;

 

void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
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

}

void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);
distR =dist; //get distance of right sensor

//Uncomment for debudding
Serial.print("L=");
Serial.println(distL);
Serial.print("R=");
Serial.println(distR);


//Pause Modes -Hold
if (distL <50) 
{Serial.println("Jump"); delay (500);}
/*
if(distR <50) 
{Serial.println("Duck"); delay(500);}
*/
if((distR <50))
{
  delay(200);
  calculate_distance(trigger2,echo2);
  distR =dist;
  if(distR <50)
  
  {Serial.println("Exit"); delay(500);}
}
delay(50);
}

 
