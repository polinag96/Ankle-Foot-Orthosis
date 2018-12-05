// globals
const int FSR1 = A0; // heel 
const int FSR2 = A1; // toe 
const int EMG1 = A2; // soleus
const int EMG2 = A3; // calf muscle

const int motor1 = 11; 
const int motor2 = 12; 
const int motor3 = 13; 

int emg1VT;
int emg2VT;

int prevFSR1 = 0;
int prevFSR2 = 0;
unsigned long time;

// DATA
int force1[57]={0,0,0,0,10,30,25,20,15,13,10,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,30,25,20,15,0,0,0};
int force2[57]={0,0,0,0,0,0,0,5,10,15,20,25,30,35,37,37,35,30,25,20,15,10,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,15,20,25,37,35};
int electro1[57]={882,881,887,892,920,956,967,965,978,986,1028,1035,1038,1024,1025,1025,1013,997,966,935,926,919,914,913,902,902,903,900,901,896,901,901,893,889,888,885,886,886,886,884,875,871,878,876,873,868,864,869,866,912,964,967,1010,1032,1006,968,901};
int electro2[57]={932,931,937,942,970,1006,1017,1015,1028,1037,1078,1085,1088,1074,1075,1075,1063,1047,1016,985,976,969,964,963,952,952,953,950,951,946,951,951,943,939,938,935,936,936,936,934,925,921,928,926,923,918,914,919,916,962,1014,1017,1060,1082,1056,1018,951};

void setup() { // calibration
  
  Serial.begin(9600);
  // current calibration values
  int emg1Cal = 0;
  int emg2Cal = 0;
  // threshold voltage
  emg1VT = 0;
  emg2VT = 0; 
  
  //while (millis() < 10000){ // 10 second calibration
    // read data from sensors
    //emg1Cal = analogRead(EMG1);
    //emg2Cal = analogRead(EMG2);
    
    /*  FOR TESTING ONLY */
    for (int i = 0; i < 57; i++){
      emg1Cal=electro1[i];
      emg2Cal=electro2[i];
      // compare current V with previous Vt
      if (emg1Cal > emg1VT){
        emg1VT = emg1Cal;
      }
      if (emg2Cal > emg2VT){
        emg2VT = emg2Cal;
      }
    }
    
  // scale threshold so motor starts before step off
  emg1VT=.96*emg1VT;
  emg2VT=.96*emg2VT;
  
  //prints time since program started, varify 10 sec cal
  //Serial.print("Time: ");
  //time = millis();
  //Serial.println(time);  
}

void loop() {
  // current input values
  int fsr1 = 0;
  int fsr2 = 0;
  int emg1 = 0;
  int emg2 = 0;
   
  // read data from sensors
  //fsr1 = analogRead(FSR1);
  //fsr2 = analogRead(FSR2);
  //emg1 = analogRead(EMG1);
  //emg2 = analogRead(EMG2);
  int i;
  for (i = 0; i <= 56; i++){
    Serial.print("COUNT: ");
    Serial.println(i);
    fsr1=force1[i];
    fsr2=force2[i];
    emg1=electro1[i];
    emg2=electro2[i];
    Serial.print("FORCE IN HEEL: ");
    Serial.println(fsr1);
    Serial.print("FORCE IN TOE: ");
    Serial.println(fsr2);
    Serial.print("EMG 1 IN LEG: ");
    Serial.println(emg1);
    Serial.print("EMG 2 IN LEG: ");
    Serial.println(emg2);
      if (emg1 >= emg1VT && emg2 >= emg2VT && prevFSR1 >= fsr1 && prevFSR2 <= fsr2){
        Serial.println("MOTOR ON\n");  
        //analogWrite(HIGH); 
    }
      else {
        Serial.println("MOTOR OFF\n"); 
        //analogWrite(LOW);  
      }
    prevFSR1 = fsr1;
    prevFSR2 = fsr2;
  }
  // STATE 1: no signal, step down, flat
  // STATE 2: partial high, mid step
  // STATE 3: initial high, step off
}
