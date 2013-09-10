// Steven Guan, 8/6/13. Calculator.

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>


using namespace std;

int main () {
  int a = 0, overshoot = 0, pr = 0;
  int histo[10000];
  float histo2[30];
  int c1, c2;
  for(int i=0;i<31;i++)
    histo2[i] = 0;
  for(int i=0;i<10001;i++)
    histo[i] = 0;
  int val;
  string line, fileName, t;
  char temp[4], temp2[10];
  ifstream myfile;
  double t1, t2, t3, lowest, highest, p_high, p_low, average, t4;
  double f1, p1, i1, f2, p2, i2;
  t1 = 0.0;
  t2 = 0.0;
  p_high = 0.0;
  p_low = 100.0;
  lowest = 100.0;
  highest = 0.0;
  average = 0.0;
  int refractory;
  cout << "Enter refractory period value : " << endl;
  cin >> t;
  refractory = atoi(t.c_str());
  cout << "Enter log file name : " << endl;
  cin >> fileName;
  cout << "Opening " << fileName << "..." << endl;
  myfile.open(fileName.c_str());
  while ( myfile.good() == true ){
    getline (myfile,line);
    //initial data analysis
    if(line[0] == 'c'){
      size_t l = line.copy(temp,(line.size() - 9), 9);
      temp[l] = '\0';
      val = atoi(temp);
      histo[val]++;
      pr++;
    }
    if(line[0] == 's'){
      size_t n = line.copy(temp2,(line.size() - 15), 15);
      temp2[n] = '\0';
      //cout << temp2 << endl;
      t3 = atof(temp2);
      if(t1 == 0)
	t1 = t3;
      else{
	t2 = t3;
	//printf("t1 %2.6f, t2 %2.6f\n", t1, t2);
	c1 = int(t1);
	c2 = int(t2);
	if(c1 != c2)
	  ;
	else{
	t4 = t2 - t1;
	//printf("t4 %2.6f\n", t4);
	if(t4 < 0){
	  //cout << temp2 << endl;
	  //printf(" t1 %2.6f, t2 %2.6f\n", t1, t2);
	  t1 = t2;
	  continue;
	}
	if(t4 > 0.010){
	  cout << t4 << endl;
	  printf(" t1 %2.6f, t2 %2.6f\n", t1, t2);
	}
	average += t4;
	a++;
	if(t4 > 1){
	  //t4 = t4 - 1;
	  if(t4 < .00025){
	    histo2[1]++;
	    // cout << line << endl;
	  }
	  else if(t4 < .0005)
	    histo2[2]++;
	  else if(t4 < .00075)
	    histo2[3]++;
	  else if(t4 < .001)
	    histo2[4]++;
	  else if(t4 < .00125)
	    histo2[5]++;
	  else if(t4 < .0015)
	    histo2[6]++;
	  else if(t4 < .00175)
	    histo2[7]++;
	  else if(t4 < .002)
	    histo2[8]++;
	  else if(t4 < .00225)
	    histo2[9]++;
	  else if(t4 > .00225)
	    histo2[10]++;
	}
	else{
	  //t4 = 1 - t4;
	  //printf("t4: %f2.6\n", t4);
	  if(t4 == 0){
	    //cout << line << endl;
	    histo2[0]++;
	  }
	  else if(t4 < .00025)
	    histo2[11]++;
	  else if(t4 < .0005)
	    histo2[12]++;
	  else if(t4 < .00075)
	    histo2[13]++;
	  else if(t4 < .001)
	    histo2[14]++;
	  else if(t4 < .00125)
	    histo2[15]++;
	  else if(t4 < .0015)
	    histo2[16]++;
	  else if(t4 < .00175)
	    histo2[17]++;
	  else if(t4 < .002)
	    histo2[18]++;
	  else if(t4 < .00225)
	    histo2[19]++;
	  else if(t4 > .00225)
	    histo2[20]++;
	}
	}
	t1 = t2;
	
      }
    }
  } 
  //cout << "closing" << endl;
  myfile.close();
  average = average/a;
  //getting the variance and standard deviation
  double stdev = 0.0, variance = 0.0;
  t1 = 0.0;
  myfile.open(fileName.c_str());
  while ( myfile.good() == true ){
    getline (myfile,line);
    if(line[0] == 's'){
      size_t n = line.copy(temp2,(line.size() - 15), 15);
      temp2[n] = '\0';
      t3 = atof(temp2);
      if(t1 == 0)
	t1 = t3;
      else{
	t2 = t3;
	c1 = int(t1);
	c2 = int(t2);
	if(c1 != c2)
	  ;
	else{
	t4 = t2 - t1;
	if(t4 < 0){
	  t1 = t2;
	  continue;
	}
	if(t4 > average)
	  variance += (t4 - average) * (t4 - average);
	else
	  variance += (average - t4) * (average - t4);
	//printf("variance: %1.12f\n", variance);
	}
	t1 = t2;
      
	
      }
    }
  }
  variance = variance / a;
  stdev = sqrt(variance);
  printf("Variance over %i comparisons: %1.9f\n", a, variance);
  printf("Standard deviation: %1.9f\n", stdev);
  printf("Average period: %1.9f seconds\n", (average));
  cout << "Period histogram" << endl;
  for(int i=0;i<21;i++){
    if(histo2[i] != 0){
      switch(i){
      case 20: printf("T < -2.25ms: %2.2f%%\n", (histo2[20]/a * 100)); break;
      case 19: printf("T = -2.25ms to -2.0ms: %2.2f%%\n", (histo2[19]/a*100)); break;
      case 18: printf("T = -2.0ms to -1.75ms: %2.2f%%\n", (histo2[18]/a*100)); break;
      case 17: printf("T = -1.75ms to -1.5ms: %2.2f%%\n", (histo2[17]/a*100)); break;
      case 16: printf("T = -1.5ms to -1.25ms: %2.2f%%\n", (histo2[16]/a*100)); break;
      case 15: printf("T = -1.25ms to -1.0ms: %2.2f%%\n", (histo2[15]/a*100)); break;
      case 14: printf("T = -1.0ms to -0.75ms: %2.2f%%\n", (histo2[14]/a*100)); break;
      case 13: printf("T = -0.75ms to -0.5ms: %2.2f%%\n", (histo2[13]/a*100)); break;
      case 12: printf("T = -0.5ms to -0.25ms: %2.2f%%\n", (histo2[12]/a*100)); break;
      case 11: printf("T = -0.25ms to -0.0ms: %2.2f%%\n", (histo2[11]/a*10)); break;
	/*case 0: printf("T = 1 second: %i\n", histo2[0]); break;
      case 10: printf("T > 2.25ms: %i\n", histo2[10]); break;
      case 9: printf("T = 2.0ms to 2.25ms: %i\n", histo2[9]); break;
      case 8: printf("T = 1.75ms to 2.0ms: %i\n", histo2[8]); break;
      case 7: printf("T = 1.5ms to 1.75ms: %i\n", histo2[7]); break;
      case 6: printf("T = 1.25ms to 1.5ms: %i\n", histo2[6]); break;
      case 5: printf("T = 1.0ms to 1.25ms: %i\n", histo2[5]); break;
      case 4: printf("T = 0.75ms to 1.0ms: %i\n", histo2[4]); break;
      case 3: printf("T = 0.5ms to 0.75ms: %i\n", histo2[3]); break;
      case 2: printf("T = 0.25ms to 0.5ms: %i\n", histo2[2]); break;
      case 1: printf("T = 0ms to 0.25ms: %i\n", histo2[1]); break;*/
      }
    }
  }
  printf("Largest periodic difference under one second: %1.9f seconds\n", highest);
  printf("Smallest periodic difference under one second: %1.9f seconds\n", lowest);
  if(overshoot == 0)
    printf("Period never went over 1 second.\n");
  else{
    printf("Largest periodic difference over one second: %1.9f seconds\n", p_high);
    printf("Smallest periodic difference over one second: %1.9f seconds\n", p_low);
    }
  float r = 0;
  cout << "Counter histogram: ";
  float rec = pr - histo[0];
  float percent = 0.0;
  for(int i=0;i<10001;i++){
    if(histo[i] != 0){
      if(i == 0)
	printf(" Total packets sent / received: %i / %4.0f\n", histo[0], rec);
      else{
	if(i < refractory)
	  r += histo[i];
	percent = histo[i]/rec;
	percent = percent * 100;
	printf("At counter value %i: %i (%2.2f%%)\n", i, histo[i], percent);
      }
    }
  }
  if(rec != 0){
  r = r/rec;
  r = r * 100;
  }
  else
    r = 0;
  printf("Total percentage of packets received in refractory period (%i): %2.2f%%\n", refractory,r);
  return 0;
}
