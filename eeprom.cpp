#include <Stepper.h>
#include <EEPROM.h>
const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int data;
float data_disp,tot = 0;
int address = 0;
int count=0;
boolean zero = true;
void setup() {
//  /*
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
//  */
  // Set the speed to 5 rpm:
  myStepper.setSpeed(15);
  Serial.begin(9600);
  EEPROM.get(address, data_disp);
  Serial.println(data_disp,4);
  tot=data_disp;
  Serial.println("Masukan nilai step (1 rotasi = 2048) lalu tekan enter");
  Serial.println("+ untuk CW (Buka) dan - untuk CCW (tutup)");
  Serial.println("Tekan tombol reset pada arduino untuk mereset total step");
//          while(tot!=0){
//          }
  delay(500);
}
void loop() {
        if (zero == false){
          float total = abs(tot*1000);
           for(count=0;count<total;count++){
            Serial.print("\t");
            Serial.print("StepA = ");
            Serial.println(total);
            if (total > 0){
              myStepper.step(1);
              tot=tot-0.001;
            }
            
            else if(total == 0){
              myStepper.step(0);
              zero = false;
            }
            
            else if (total < 0){
              myStepper.step(-1);
              tot=tot+0.001;
            }

            data_disp=tot;
            Serial.println(data_disp,3);
            EEPROM.put(address, data_disp);
            }

      }
  Serial.print("Total Step = ");
  Serial.print(tot,3);
    if (Serial.available() > 0) {
      data = Serial.parseInt();
      if (Serial.read() == '\n') {
          for(count=0;count<abs(data);count++){
            Serial.print("\t");
            Serial.print("Step = ");
            Serial.println(count);
            if (data > 0){
              myStepper.step(-1);
              tot=tot+0.001;
            }
            else{
              myStepper.step(1);
              tot=tot-0.001;
            }
            data_disp=tot;
            Serial.println(data_disp,3);
            EEPROM.put(address, data_disp);
          }
      }
    }
    else{
      Serial.println("");
      myStepper.step(0);
    }
}
