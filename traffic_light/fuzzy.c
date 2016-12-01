#include <stdio.h>
#include <stdlib.h>

double defuzzify(double degreeoftruth[6]);
double min(double x, double y);
double max(double raphael, double michaelangelo, double leonardo, double donatello);
double* getDoT(int waiting, int through);

int main(void){
  int i;
  double degree[6];
  double* DoT;
  double result;
  degree[0] = .33;
  degree[1] = .67;
  degree[2] = 0;
  degree[3] = .33;
  degree[4] = .67;
  degree[5] = 0;
  DoT = getDoT(0, 81);
  for (i = 0; i < 6; i++)
  {
	printf( "Degree of truth %d: %lf\n", i, *(DoT + i));
  }
  result = defuzzify(degree);
  printf("Crisp time is %lf\n", result);
  return 0;
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
  if((michaelangelo > raphael) && (michaelangelo > leonardo) && (michaelangelo > donatello)) return michaelangelo;
  if((leonardo > raphael) && (leonardo > michaelangelo) && (leonardo > donatello)) return leonardo;
  if((donatello > raphael) && (donatello > michaelangelo) && (donatello > leonardo)) return donatello;
  return 0.0;
}

double* getDoT(int waiting, int through)
{
	/*Holds degree of truth in following order
	Few Waiting, Some Waiting, Lots Waiting,
	Not Busy, Kind of Busy, Very Busy */
	static double DoT[6];		
	
	/*Gets degrees of truth for cars stopped
	  at red light */
	if(waiting < 20) 
	{
		DoT[0] = 1;
		DoT[1] = 0;
		DoT[2] = 0;
	}
	else if(waiting > 20 && waiting < 40)
	{
		DoT[0] = (40 - waiting) * .05;
		DoT[1] = (waiting - 20) * .05;
		DoT[2] = 0;
	}
	else if(waiting > 40 && waiting < 60)
	{
		DoT[0] = 0;
		DoT[1] = 1;
		DoT[2] = 0;
	}
	else if(waiting > 60 && waiting < 80)
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
	if(through < 20)
	{
		DoT[3] = 1; 
		DoT[4] = 0;
		DoT[5] = 0;
	}
	if(through > 20 && through < 40)
	{
		DoT[3] = (40 - through) * .05;
		DoT[4] = (through - 20) * .05;
		DoT[5] = 0;
	}
	if(through > 40 && through < 60)
	{
		DoT[3] = 0;
		DoT[4] = 1;
		DoT[5] = 0;
	}
	if(through > 60 && through < 80)
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
