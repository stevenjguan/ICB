// Steven Guan, 8/6/13. Calculator.

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>


using namespace std;
int calc(float array[], int cap);

int main () {
  int a = 0, overshoot = 0, pr = 0, zz = 0;
  //bool skip = false;
  int histo[10000];
  int c1, c2, c3, c4, c5;
   for(int i=0;i<10001;i++)
    histo[i] = 0;
  float r1[5000];
  float r2[5000];
  float r3[5000];
  float r4[5000];
  float r5[5000];
  for(int i= 0;i<5001;i++){
    r1[i] = 0;
    r2[i] = 0;
    r3[i] = 0;
    r4[i] = 0;
    r5[i] = 0;
  }
  int val;
  string line, fileName, t;
  char temp[4], temp2[10];
  ifstream myfile;
  double t1, t2, t3, lowest, highest, p_high, p_low, average, t4, t5, t6, t7;
  double f1, p1, i1, f2, p2, i2;
  t1 = 0.0;
  t2 = 0.0;
  t5 = 0.0;
  t6 = 0.0;
  t7 = 0.0;
  p_high = 0.0;
  p_low = 100.0;
  lowest = 100.0;
  highest = 0.0;
  average = 0.0;
  int b = 0;
  int yy = 0;
  //int refractory;
  //cout << "Enter refractory period value : " << endl;
  //cin >> t;
  //refractory = atoi(t.c_str());
  cout << "Enter log file name : " << endl;
  cin >> fileName;
  cout << "Opening " << fileName << "..." << endl;
  myfile.open(fileName.c_str());
  while ( myfile.good() == true ){
    getline (myfile,line);
    //initial data analysis
    if(line[0] == 's'){
      size_t n = line.copy(temp2,(line.size() - 15), 15);
      temp2[n] = '\0';
      //cout << temp2 << endl;
      t3 = atof(temp2);
      if(t1 == 0)
	t1 = t3;
      else if (t5 == 0)
	t5 = t3;
      else if (t6 == 0)
	t6 = t3;
      else if (t7 == 0)
      t7 = t3;
      else{
	t2 = t3;
	c1 = int(t1);
	c2 = int(t2);
	c3 = int(t5);
	c4 = int(t6);
	c5 = int(t7);
	if(c1 != c2 || c2 != c3 || c3 != c4 || c4 != c5){
	  //printf("skipping: %i %i %i %i %i\n", c1,c3,c4,c5, c2);
	  if(c1 == c3 && c3 == c4 && c4 == c5){
	    //printf("%f %f %f %f\n", t1,t5,t6,t7);
	    if((t7 - t1) > 0){
	      if((t7 - t1) > 0.01){
		printf("%f %f %f %f\n", t1,t5,t6,t7);
		t1 = t5;
		t5 = t6;
		t6 = t7;
		t7 = t2;
		continue;
	      }
	      r1[yy] = t7 - t1;
	      yy++;
	    }
	  }
	}
	else{
	  if((t7 - t6) < 0 || (t6 - t5) < 0 || (t5 - t1) < 0 || (t2 - t7) < 0){
	    //printf("skipping: %f %f %f %f %f\n", t1,t5,t6,t7,t2);
	    continue;
	  }
	  //r1[zz] = t5 - t1;
	  //r2[zz] = t6 - t5;
	  //r3[zz] = t7 - t6;
	  //r4[zz] = t2 - t7;
	  if((t2 -t1) > 0.01){
	    b++;
	    t1 = t5;
	    t5 = t6;
	    t6 = t7;
	    t7 = t2;
	    continue;
	  }
	  r5[zz] = t2 - t1;
	  //cout << r2[zz] << endl;
	  zz++;
	  // if((t2 - t1) > 0.008)
	  //   printf("%2.6f\n",t2);
	  //printf(" t1 %2.6f, t2 %2.6f, t5 %2.6f\n", t1, t2, t5);
	}
	t1 = t5;
	t5 = t6;
	t6 = t7;
	t7 = t2;
      }
    }
  }   
  
  //printf("zz: %i\n", zz);
  myfile.close();
  cout << "For 4 entries\n";
  calc(r1, yy);
  // cout << "C - D\n";
  // calc(r2, zz);
  // cout << "B - C\n";
  // calc(r3, zz);
  // cout << "A - C\n";
  // calc(r4, zz);
  cout << "For 5 entries\n";
  calc(r5, zz);
  return 0;
}
int calc(float array[], int cap){
    float histo2[31];
    for(int i=0;i<31;i++)
      histo2[i] = 0;
    double stdev = 0.0, variance = 0.0;
    double t1 = 0.0, t4 = 0.0;
    double average = 0.0;
    int b = 0;
    for(int i=0;i<=cap;i++){
      if(array[i] < 0)
	cout << "o?\n";
      else if(array[i] != 0){
	average +=array[i];
      }
    }
    int a = cap;
    //cout << average << " " << cap << endl;
    average = average / cap;
    for(int i=0;i<=cap;i++){
      t4 = array[i];
      if(t4 > 1){
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
	else if(t4 < .0025)
	  histo2[20]++;
	else if(t4 < .00275)
	  histo2[21]++;
	else if(t4 < .003)
	  histo2[22]++;
  	else if(t4 < .00325)
	  histo2[23]++;
	else if(t4 < .0035)
	  histo2[24]++;
	else if(t4 < .00375)
	  histo2[25]++;
	else if(t4 > .00375)
	  histo2[26]++;
	
      }
      if(array[i] > average)
	variance += (array[i] - average) * (array[i] - average);
      else
	variance += (average - array[i]) * (average - array[i]);
      //printf("variance: %1.12f\n", variance);
    }
    
    variance = variance / cap;
    stdev = sqrt(variance);
    printf("Variance over %i comparisons: %1.9f\n", cap, variance);
    printf("Standard deviation: %1.9f\n", stdev);
    printf("Average period: %1.9f seconds\n", (average));
    cout << "Period histogram" << endl;
    for(int i=0;i<27;i++){
      if(histo2[i] != 0){
	switch(i){
	case 26: printf("T < 3.75ms: %2.2f%%\n", (histo2[26]/a * 100)); break;
	case 25: printf("T = 3.75ms to 3.55ms: %2.2f%%\n", (histo2[25]/a * 100)); break;
	case 24: printf("T = 3.5ms to 3.25ms: %2.2f%%\n", (histo2[24]/a * 100)); break;
	case 23: printf("T = 3.25ms to 3.0ms: %2.2f%%\n", (histo2[23]/a * 100)); break;
	case 22: printf("T = 3.0ms to 2.75ms: %2.2f%%\n", (histo2[22]/a * 100)); break;
	case 21: printf("T = 2.75ms to 2.5ms: %2.2f%%\n", (histo2[21]/a * 100)); break;
	case 20: printf("T = 2.5ms to 2.25ms: %2.2f%%\n", (histo2[20]/a * 100)); break;
	case 19: printf("T = 2.25ms to 2.0ms: %2.2f%%\n", (histo2[19]/a*100)); break;
	case 18: printf("T = 2.0ms to 1.75ms: %2.2f%%\n", (histo2[18]/a*100)); break;
	case 17: printf("T = 1.75ms to 1.5ms: %2.2f%%\n", (histo2[17]/a*100)); break;
	case 16: printf("T = 1.5ms to 1.25ms: %2.2f%%\n", (histo2[16]/a*100)); break;
	case 15: printf("T = 1.25ms to 1.0ms: %2.2f%%\n", (histo2[15]/a*100)); break;
	case 14: printf("T = 1.0ms to 0.75ms: %2.2f%%\n", (histo2[14]/a*100)); break;
	case 13: printf("T = 0.75ms to 0.5ms: %2.2f%%\n", (histo2[13]/a*100)); break;
	case 12: printf("T = 0.5ms to 0.25ms: %2.2f%%\n", (histo2[12]/a*100)); break;
	case 11: printf("T = 0.25ms to 0.0ms: %2.2f%%\n", (histo2[11]/a*100)); break;
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
    /*printf("Largest periodic difference under one second: %1.9f seconds\n", highest);
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
      printf("Total percentage of packets received in refractory period (%i): %2.2f%%\n", refractory,r);*/
    return 0;
  }
