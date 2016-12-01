#include <stdio.h>
#include <stdlib.h>

double defuzzify(double degreeoftruth[6]);
double min(double x, double y);
double max(double raphael, double michaelangelo, double leonardo, double donatello);

int main(void){
  
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
  finalweights[0] = max(statetable[3], statetable[6], 0.0, 0.0);
  finalweights[1] = max(statetable[0],statetable[4],statetable[7],statetable[8]);
  finalweights[2] = max(statetable[1],statetable[5],0.0,0.0);
  finalweights[3] = statetable[2];
  crisptime = (5.0 * finalweights[0]) + (7.0 * finalweights[1]) + (12.0 * finalweights[2]) + (15.0 * finalweights[3]);
  crisptime = crisptime / (finalweights[0] + finalweights[1] + finalweights[2] + finalweights[3]);
  return crisptime;
}

double min(double x, double y){
  if(x < y) return x;
  else return y;
}

double max(double raphael, double michaelangelo, double leonardo, double donatello){
  if((raphael > michaelangelo) && (raphael > leonardo) && (raphael > donatello)) return raphael;
  if((michaelango > raphael) && (michaelangelo > leonardo) && (michaelangelo > donatello)) return michaelangelo;
  if((leonardo > raphael) && (leonardo > michaelangelo) && (leonardo > donatello)) return leonardo;
  if((donatello > raphael) && (donatello > michaelangelo) && (donatello > leonardo)) return donatello;
  return 0.0;
}
