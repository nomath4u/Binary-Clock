

#define BUTTON 12

unsigned int sum_set = 0;
int val = 0; //store the state of input pin
int old_val =0;
unsigned long time_run =0;
int adjust = 43000;
void calculate(int);

void setup(){
  int j; //index variable
  //Serial.begin(9600);           // set up Serial library at 9600 bps
  //delay(1000);
  for(j=2; j<=11; j++){
    pinMode(j, OUTPUT); //pins 2-11 output
  }
  pinMode(BUTTON, INPUT); //button read
}

void loop(){
  int j; //index variable
  val = digitalRead(BUTTON);  //read input from button to val
  time_run = millis(); 
   // check if button is pressed or not
   
   if(val == HIGH && old_val == LOW){
       adjust += 60; //add one minute
       delay(10); //de-bounce
   }
   
   old_val = val; //val is now old
    sum_set= (time_run / 1000) + adjust;
   
   
   calculate(sum_set, &sum_set, &adjust);
   for(j=2; j<=11; j++)
     digitalWrite(j, LOW); //clear lights that may not need to be on
    
   //Serial.println(sum_set);
   //delay(50);  
   
}

//Determine which lights need to be on

void calculate(unsigned int sum, unsigned int* sum_set, int* adjust){
  int k; // index variable
  
  int led_calc[] = {43200,28800,14400, 7200, 3600, 1920, 960, 480, 240, 120,60};// array for
                                                     // led place
                                                     // value
  
  if(sum >= led_calc[0]){ //reset once we get to 12 hrs
    *sum_set = 0;
    *adjust = 0;
  }
  
  for(k=1; k<=10; k++){
    if( sum >= led_calc[k]){
      digitalWrite (11-(k-1), HIGH);
      sum = sum - led_calc[k];
    }
  }
}
