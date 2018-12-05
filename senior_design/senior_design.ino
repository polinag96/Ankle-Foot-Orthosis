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

void setup() { // calibration
  
  Serial.begin(9600);
  // current calibration values
  int emg1Cal = 0;
  int emg2Cal = 0;
  // threshold voltage
  emg1VT = 0;
  emg2VT = 0; 
  
  while (millis() < 10000){ // 10 second calibration
    // read data from sensors
    emg1Cal = analogRead(EMG1);
    emg2Cal = analogRead(EMG2);
    
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
  fsr1 = analogRead(FSR1);
  fsr2 = analogRead(FSR2);
  emg1 = analogRead(EMG1);
  emg2 = analogRead(EMG2);
 
    Serial.print("COUNT: ");
    Serial.println(i);
    Serial.print("FORCE IN HEEL: ");
    Serial.println(fsr1);
    Serial.print("FORCE IN TOE: ");
    Serial.println(fsr2);
    Serial.print("EMG 1 IN LEG: ");
    Serial.println(emg1);
    Serial.print("EMG 2 IN LEG: ");
    Serial.println(emg2);
    
    if (emg1 >= emg1VT && emg2 >= emg2VT && prevFSR1 >= fsr1 && prevFSR2 <= fsr2){
        analogWrite(HIGH); 
    }
    else {
        analogWrite(LOW);  
    }
    prevFSR1 = fsr1;
    prevFSR2 = fsr2;
  }
}
