#define  R1 2
#define  G1 3
#define  R2 4
#define  G2 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  // four mode changes called to ensure that the pins used for the pairs of Red and Green lights are in the proper model
  pinMode(R1, OUTPUT); // R1
  pinMode(G1, OUTPUT); // G1
  pinMode(R2, OUTPUT); // R2
  pinMode(G2, OUTPUT); // G2
  digitalWrite(R1, HIGH);
  digitalWrite(G1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(G2, LOW);
}

void loop() {
  //Serial.print("Hello\n");
  //delay(1000);

  int *array;
  double *DoT;
  double crispTime;
  //randNumber(array);
  array[1] = random(100);
  array[2] = random(100);
  Serial.print("Random Backup and ThruTraffic integers\n");
  Serial.print(array[1]);
  Serial.print(' ');
  //Serial.println();
  Serial.print(array[2]);
  Serial.print("\n\n");
  DoT = getDoT(array[1], array[2]);
  //Serial.print("Degrees of Truth:\n");
  //Serial.print(DoT[0]);
  //Serial.println();
  //Serial.print(DoT[1]);
  //Serial.println();
  //Serial.print(DoT[2]);
  //Serial.println();
  //Serial.print(DoT[3]);
  //Serial.println();
  //Serial.print(DoT[4]);
  //Serial.println();
  //Serial.print(DoT[5]);
  //Serial.println();
  crispTime = defuzzify(DoT);
  Serial.print("Time to set L1 on: ");
  Serial.print(crispTime);
  Serial.print('s');
  Serial.println("\n\n");
  lightChange(crispTime, 1);
  //randNumber(array);
  array[1] = random(100);
  array[2] = random(100);
  DoT = getDoT(array[1], array[2]);
  Serial.print(array[1]);
  Serial.print("\n");
  Serial.print(array[2]);
  crispTime = defuzzify(DoT);
   Serial.print("Time to set L2 on: ");
  Serial.print(crispTime);
  Serial.print('s');
  Serial.println("\n\n");
  lightChange(crispTime, 2);
}

double defuzzify(double *dot){
  int i,k,z=0;
  double statetable[9];
  double crisptime;
  double finalweights[4];

  for(i=0;i<3;i++){
    for(k=0;k<3;k++){
       statetable[z] = min(dot[k],dot[3+i]);
       z++;
    }
  }
  finalweights[0] = maxval(statetable[3], statetable[6], 0.0, 0.0);
  finalweights[1] = maxval(statetable[0],statetable[4],statetable[7],statetable[8]);
  finalweights[2] = maxval(statetable[1],statetable[5],0.0,0.0);
  finalweights[3] = statetable[2];
  crisptime = (5.0 * finalweights[0]) + (7.0 * finalweights[1]) + (12.0 * finalweights[2]) + (15.0 * finalweights[3]);
  crisptime = crisptime / (finalweights[0] + finalweights[1] + finalweights[2] + finalweights[3]);
  return crisptime;
}

double minval(double x, double y){
  if(x < y) return x;
  else return y;
}

double maxval(double raphael, double michaelangelo, double leonardo, double donatello){
  if((raphael > michaelangelo) && (raphael > leonardo) && (raphael > donatello)) return raphael;
  if((michaelangelo > raphael) && (michaelangelo > leonardo) && (michaelangelo > donatello)) return michaelangelo;
  if((leonardo > raphael) && (leonardo > michaelangelo) && (leonardo > donatello)) return leonardo;
  if((donatello > raphael) && (donatello > michaelangelo) && (donatello > leonardo)) return donatello;
  return 0.0;
}

int randNumber(int *array){
//randomSeed(analogRead(0));
array[1] = random(100);
array[2] = random(100);
//return array;
return 1;
}

void lightChange(double lDelay, int gType) {
  // function called to take defuzzified time as the first input and a hard 1 or 2 as second input
  // turns on and off the traffic lights at the determined inputs
  // gType is 1 for the first set of lights and 2 for the second set
  // lDelay is the output of the defuzzification
  // 1/10th of a second delay is added between digitial writes for safety and smoothness, remove or alter if needed.
  
  if(gType == 1){
    // turn off R1 turn on G1
    delay(1000);
    digitalWrite(R1, LOW);
    delay(100);
    digitalWrite(G1, HIGH);

    // delay for the time taken as input
    delay(1000*lDelay); // delay is in ms so *1000
    
    // turn off G1 turn on R1
    digitalWrite(G1, LOW);
    delay(100);
    digitalWrite(R1, HIGH);
    
  }
  else if(gType == 2){
    // turn off R2 turn on G2
    delay(1000);
    digitalWrite(R2, LOW);
    delay(100);
    digitalWrite(G2, HIGH);
    
    // delay for the time taken as input
    delay(1000*lDelay);
    
    // turn off G2 turn on R2
    digitalWrite(G2, LOW);
    delay(100);
    digitalWrite(R2, HIGH);
    
  }
}

double* getDoT(int waiting, int through)
{
  /*Holds degree of truth in following order
  Few Waiting, Some Waiting, Lots Waiting,
  Not Busy, Kind of Busy, Very Busy */
  static double DoT[6];   
  
  /*Gets degrees of truth for cars stopped
    at red light */
  if(waiting <= 20) 
  {
    DoT[0] = 1;
    DoT[1] = 0;
    DoT[2] = 0;
  }
  else if(waiting > 20 && waiting <= 40)
  {
    DoT[0] = (40 - waiting) * .05;
    DoT[1] = (waiting - 20) * .05;
    DoT[2] = 0;
  }
  else if(waiting > 40 && waiting <= 60)
  {
    DoT[0] = 0;
    DoT[1] = 1;
    DoT[2] = 0;
  }
  else if(waiting > 60 && waiting <= 80)
  {
    DoT[0] = 0;
    DoT[1] = (80 - waiting) * .05;
    DoT[2] = (waiting - 60) * .05;
  }
  else if(waiting > 80)
  {
    DoT[0] = 0;
    DoT[1] = 0;
    DoT[2] = 1;
  }

  /*Gets degrees of truth for cars going through
    gree light */
  if(through <= 20)
  {
    DoT[3] = 1; 
    DoT[4] = 0;
    DoT[5] = 0;
  }
  if(through > 20 && through <= 40)
  {
    DoT[3] = (40 - through) * .05;
    DoT[4] = (through - 20) * .05;
    DoT[5] = 0;
  }
  if(through > 40 && through <= 60)
  {
    DoT[3] = 0;
    DoT[4] = 1;
    DoT[5] = 0;
  }
  if(through > 60 && through <= 80)
  {
    DoT[3] = 0;
    DoT[4] = (80 - through) * .05;
    DoT[5] = (through - 60) * .05;    
  }
  if(through > 80)
  {
    DoT[3] = 0;
    DoT[4] = 0;
    DoT[5] = 1;
  }

  return DoT;
}
