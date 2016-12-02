void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  
  // four mode changes called to ensure that the pins used for the pairs of Red and Green lights are in the proper mode
  pinMode(0, OUTPUT); // R1
  pinMode(1, OUTPUT); // G1
  pinMode(2, OUTPUT); // R2
  pinMode(3, OUTPUT); // G2
}

void loop() {
}

double defuzzify(double dot[6]){
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
randomSeed(analogRead(0));
array[0] = random(100);
array[1] = random(100);
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
    digitalWrite(0, LOW);
    delay(100);
    digitalWrite(1, HIGH);

    // delay for the time taken as input
    delay(1000*lDelay); // delay is in ms so *1000
    
    // turn off G1 turn on R1
    digitalWrite(1, LOW);
    delay(100);
    digitalWrite(0, HIGH);
    
  }
  else if(gType == 2){
    // turn off R2 turn on G2
    digitalWrite(2, LOW);
    delay(100);
    digitalWrite(3, HIGH);
    
    // delay for the time taken as input
    delay(1000*lDelay);
    
    // turn off G2 turn on R2
    digitalWrite(3, LOW);
    delay(100);
    digitalWrite(2, HIGH);
    
  }
}

