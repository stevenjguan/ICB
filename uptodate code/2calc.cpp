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
  int histo2[30];
  for(int i=0;i<31;i++)
    histo2[i] = 0;
  for(int i=0;i<10001;i++)
    histo[i] = 0;
  int val;
  string line, fileName, t;
  char temp[4], temp2[10];
  ifstream myfile;
  double t1, t2, t3, lowest, highest, p_high, p_low, average, t4;
  t1 = 0.0;
  t2 = 0.0;
  p_high = 0.0;
  p_low = 100.0;
  lowest = 100.0;
  highest = 0.0;
  average = 0.0;
  int over = 0;
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
      if(val == 1000)
	cout << temp << endl;
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
	if(t2 < 1 && t1 > 1)
	  t2 = t2 + 60;
	if(t1 > (t2 - 1)){
	  t4 = t2 - t1;

	  if((1 - t4) > highest)
	    highest = (1 - t4);
	  if((1 - t4) < lowest)
	    lowest = (1 - t4);
	}
	else{
	  overshoot++;
	  t4 = t2 - t1;
	  if(t4 > p_high)
	    p_high = t4;
	  if(t4 < p_low)
	    p_low = t4;
	}
	 if(t4 > 1.01 || t4 < 0.99){
	   over++;
	   t1 = t2;
	   continue;
	 }
	average += t4;
	if(t4 > 1){
	  t4 = t4 - 1;
	  if(t4 < .0005){
	    histo2[1]++;
	    // cout << line << endl;
	  }
	  else if(t4 < .001)
	    histo2[2]++;
	  else if(t4 < .0015)
	    histo2[3]++;
	  else if(t4 < .002)
	    histo2[4]++;
	  else if(t4 < .0025)
	    histo2[5]++;
	  else if(t4 < .003)
	    histo2[6]++;
	  else if(t4 < .0035)
	    histo2[7]++;
	  else if(t4 < .004)
	    histo2[8]++;
	  else if(t4 < .0045)
	    histo2[9]++;
	  else if(t4 < .005)
	    histo2[10]++;
	  else if(t4 < .0055)
	    histo2[21]++;
	  else if(t4 < .006)
	    histo2[22]++;
	  else if(t4 < .0065)
	    histo2[23]++;
	  else if(t4 < .007)
	    histo2[24]++;
	  else if(t4 < .0075)
	    histo2[25]++;
	  else if(t4 > .0075)
	    histo2[26]++;
	}
	else{
	  t4 = 1 - t4;
	  //printf("t4: %f\n", t4);
	  if(t4 == 0){
	    //cout << line << endl;
	    histo2[0]++;
	  }
	  else if(t4 < .0005)
	    histo2[11]++;
	  else if(t4 < .001)
	    histo2[12]++;
	  else if(t4 < .0015)
	    histo2[13]++;
	  else if(t4 < .002)
	    histo2[14]++;
	  else if(t4 < .0025)
	    histo2[15]++;
	  else if(t4 < .003)
	    histo2[16]++;
	  else if(t4 < .0035)
	    histo2[17]++;
	  else if(t4 < .004)
	    histo2[18]++;
	  else if(t4 < .0045)
	    histo2[19]++;
	  else if(t4 > .0045)
	    histo2[20]++;

	}
	a++;
	if(t1 < 1 && t2 < 1)
	  t1 = t2;
	else{
	  t1 = t2;
	  if(t3 < 1)
	    t1 = t1 - 60;
	}
      }
    }		
  }

  //cout << "closing" << endl;
  myfile.close();
  cout << "over: " << over << endl;
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
	if(t2 < 1 && t1 > 1)
	  t2 = t2 + 60;
	t4 = t2 - t1;
	 if(t4 > 1.01 || t4 < 0.99){
	   //cout << temp2 << endl;
	   t1 = t2;
	   continue;
	 }
	if(t4 > average)
	  variance += (t4 - average) * (t4 - average);
	else
	  variance += (average - t4) * (average - t4);
	//printf("variance: %1.12f\n", variance);
	t1 = t2;
	if(t1 < 1 && t2 < 1)
	  t1 = t2;
	else{
	  t1 = t2;
	  if(t3 < 1)
	    t1 = t1 - 60;
	}
      }
    }
  }
  variance = variance / a;
  stdev = sqrt(variance);
  printf("Variance over %i packets sent: %1.9f\n", histo[0], variance);
  printf("Standard deviation: %1.9f\n", stdev);
  printf("Average period: %1.9f seconds\n", (average));
  cout << "Period histogram" << endl;
  for(int i=0;i<27;i++){
    if(histo2[i] != 0){
      switch(i){
     case 26: printf("T < 7.5ms: %i\n", (histo2[26])); break;
      case 25: printf("T = 7.0ms to 7.5ms: %i\n", (histo2[25])); break;
      case 24: printf("T = 6.5ms to 7.0ms: %i\n", (histo2[24])); break;
      case 23: printf("T = 6.0ms to 6.5ms: %i\n", (histo2[23])); break;
      case 22: printf("T = 5.5ms to 6.0ms: %i\n", (histo2[22])); break;
      case 21: printf("T = 5.0ms to 5.5ms: %i\n", (histo2[21])); break;
      case 20: printf("T < -4.5ms: %i\n", (histo2[20])); break;
      case 19: printf("T = -4.5ms to -4.0ms: %i\n", histo2[19]); break;
      case 18: printf("T = -4.0ms to -3.5ms: %i\n", histo2[18]); break;
      case 17: printf("T = -3.5ms to -3.0ms: %i\n", histo2[17]); break;
      case 16: printf("T = -3.0ms to -2.5ms: %i\n", histo2[16]); break;
      case 15: printf("T = -2.5ms to -2.0ms: %i\n", histo2[15]); break;
      case 14: printf("T = -2.0ms to -1.5ms: %i\n", histo2[14]); break;
      case 13: printf("T = -1.5ms to -1.0ms: %i\n", histo2[13]); break;
      case 12: printf("T = -1.0ms to -0.5ms: %i\n", histo2[12]); break;
      case 11: printf("T = -0.5ms to -0.0ms: %i\n", histo2[11]); break;
      case 0: printf("T = 1 second: %i\n", histo2[0]); break;
      case 10: printf("T = 4.5ms to 5.0ms: %i\n", histo2[10]); break;
      case 9: printf("T = 4.0ms to 4.5ms: %i\n", histo2[9]); break;
      case 8: printf("T = 3.5ms to 4.0ms: %i\n", histo2[8]); break;
      case 7: printf("T = 3.0ms to 3.5ms: %i\n", histo2[7]); break;
      case 6: printf("T = 2.5ms to 3.0ms: %i\n", histo2[6]); break;
      case 5: printf("T = 2.0ms to 2.5ms: %i\n", histo2[5]); break;
      case 4: printf("T = 1.5ms to 2.0ms: %i\n", histo2[4]); break;
      case 3: printf("T = 1ms to 1.5ms: %i\n", histo2[3]); break;
      case 2: printf("T = 0.5ms to 1ms: %i\n", histo2[2]); break;
      case 1: printf("T = 0ms to 0.5ms: %i\n", histo2[1]); break;
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
  float rec = pr - (histo[0] + histo[1]);
  float percent = 0.0;
   int start = 0, end = 0;
  float total = 0.0;
  for(int i=1;i<10001;i++){
    if(histo[i] != 0){
      if(i == 1)
	printf(" Total packets sent / received: %i / %4.0f\n", histo[0] + histo[1], rec);
      else{
	if(i < refractory)
	  r += histo[i];
	if(total == 0.0){
	  start = i;
	  end = i;
	  total = histo[i];
	}
	else if(total/rec < 0.01){
	  total += histo[i];
	  end = i;
	}
	if(total/rec > 0.01){
	  if(start == end)
	    printf("At counter value %i: %4.0f (%2.2f%%)\n", start, total, (total/rec * 100));
	  else
	    printf("Between counter value %i - %i: %4.0f (%2.2f%%)\n", start, end, total, (total/rec*100));
	  total = 0.0;
	}
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
