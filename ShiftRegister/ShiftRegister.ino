#include "ModeChange.h"
#include "Mode_1.h"
#include "Mode_2.h"
#include "Mode_3.h"
#include "Mode_4.h"
#include "Mode_5.h"
int btClk = 0;
int slpClk = 0;
void setup() {
  pinModeFast(latchPinA, OUTPUT);
  pinMode(dataPinA, OUTPUT);  
  pinModeFast(clockPinA, OUTPUT);  
  pinModeFast(latchPinB, OUTPUT);
  pinMode(dataPinB, OUTPUT);  
  pinModeFast(clockPinB, OUTPUT);
  for(int i=0;i<3;i++) {
    stringLen[i] = setAlpha(i,string[i]);}
  allOff();
  randomSeed(analogRead(A15));
  slctMode();
}

int b_n=0;
void loop() {
  int ar = analogRead(A0);
  int ar1 = analogRead(A1);
  int ar2 = analogRead(A2);
  int ar3 = analogRead(A3);
  int ar4 = analogRead(A4);
  int ar5 = analogRead(A5);
  int ar6 = analogRead(A6);
  int ar7 = analogRead(A7);
  int ar8 = analogRead(A8);
  int ar9 = analogRead(A9);
  int ar10 = analogRead(A10);
  unsigned long cmil = millis(); 
  if(cmil - mil>=ALLSPEED){ ///All function speed 
    mil = cmil;
    if((ModeNum==0||ModeNum==1 )&& isRandT) {b_n=randTouch(ar9,ar10);}
    else {
      b_n = buttonRefresh(ar,ar1,ar2,ar3,ar4,ar5,ar6,ar7,ar8,ar9,ar10);
      switch(b_n) {
        case 0:{
          btClk =0; 
          if(ModeNum==4||ModeNum==2){
          slpClk++;
          if(slpClk >= 5000/ALLSPEED){
            b_n = 12;}}
          break;}
        case 1: {
          slpClk = 0;
          break;}
        case 2:{
          slpClk = 0;
          btClk ++;
          if( btClk==90) b_n=10; break; }
        case 3:{
          slpClk = 0;
         btClk ++;
          if( btClk==90) b_n=11; break;}
        case 4:{
          slpClk = 0;
          slctMode(); break;}
        case 5:{
          slpClk = 0;
          isRandT =true;
          mil+=200UL;}
      }
    }
    CP_display();
    switch(ModeNum) {
      case 0: {Mode_1(b_n); break;}
      case 1: {Mode_2(b_n); BAM();break;}
      case 2: {Mode_3(b_n); BAM(); break;}
      case 3: {Mode_4(b_n); break;}
      case 4: {Mode_5(b_n); BAM();break;}
    }
    if(b_n != 0)  BAM(m_for_bam);
  }
  CP_display();
}
