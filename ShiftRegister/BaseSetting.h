#pragma once
#include "digitalWriteFast.h"

#define ALLSPEED 18UL
const  int latchPinA = 32;
const  int clockPinA = 30;
const  int dataPinA = 34;
const  int latchPinB = 44;
const  int clockPinB = 42;
const  int dataPinB = 46;

const  int COLUMN = 15;
const  int LAYER = 5;
const  int COLOR_BITS = 4;

// global array that keeps track of the LEDs brightnesses
int bgrColorMask[LAYER][COLUMN] = { 0 }; //0~15
int cash[LAYER][COLUMN] = { 0 };
bool brightnessMask[COLOR_BITS][LAYER][COLUMN] = { 0 };//it's //only one layer// for BAM
bool btTable[LAYER][COLUMN / 3] = { false };//5=column/3
int Color_m[2] = { 0,10 }; // =0(B) =10(G) =20(R) 30(C=B+G !=2) 40(M=R+B !=1) 50(Y=R+G !=0) [0]set [1]reset
int m_b[2] = { 1,1 }, m_g[2] = { 0 }, m_r[2] = { 0 };
int Pallete[LAYER][COLUMN] = { 0 };
//alpha[layer= 0, column = 1][alpha + blank][Maximum pool num]
int alpha[2][27][11] = 
{ {	{0,},	//blank
	{2,0,-1,-1,0,1,1,0,},	//a
	{1,0,-1,-2,0,0,-1,-2,},	//b
	{1,1,0,-1,-1,0,},			//c
	{2,1,0,-1,0,-1,-2,-2,},//d
	{0,1,1,0,-1,-1,0,},		//e
	{2,2,1,0,-1,-2,-1,1,},
	{2,1,0,0,2,1,0,-1,-2,-2,},
	{1,0,-1,-2,0,0,-1,},		//h
	{2,0,-1,-2,},
	{2,0,-1,-2,-2,-1,},
	{1,0,-1,-2,0,1,2,0,-1,}, //k
	{1,2,1,0,-1,-2,-1,},
	{-2,-1,0,1,0,-1,1,0,-1,},//m
	{-2,-1,0,1,1,0,-1,},
	{-1,0,1,1,0,-1,},
	{1,0,-1,-2,2,2,1,0,}, //p
	{2,2,1,0,0,1,-1,-2,-1,},
	{0,-1,-2,0,1,},
	{2,2,1,0,0,0,-1,-2,-2,},
	{1,0,-1,-2,-1,-1,1,},
	{0,-1,-1,1,0,0,},
	{0,-1,-2,-2,-1,0,1,},//v
	{0,-1,-2,-2,-1,0,-1,0,1,},
	{1,0,0,0,-1,2,1,-1,-2,},
	{1,0,2,1,0,-1,-2,},
	{0,1,2,1,0,-1,-2,-1,0,-1,1}},//z
  { {0,}, //blank
	{2,1,0,-1,-1,0,1,2,},
	{-1,-1,-1,-1,0,1,1,0,},
	{1,0,-1,-1,0,1,},
	{1,1,1,1,0,-1,-1,0},
	{0,1,0,-1,-1,0,1,},//e
	{1,0,0,0,0,0,-1,1,},
	{0,-1,-1,0,1,1,1,1,0,-1,},
	{-1,-1,-1,-1,0,1,1,},
	{0,0,0,0,},
	{0,0,0,0,-1,-1,},
	{-1,-1,-1,-1,0,1,2,1,1,},//k
	{-1,0,0,0,0,0,1,},
	{-1,-1,-1,0,0,0,1,1,1,},
	{-1,-1,-1,0,1,1,1,},
	{-1,-1,0,1,1,0,},
	{-1,-1,-1,-1,0,1,1,0,},
	{1,0,-1,-1,0,1,0,0,1,},//q
	{-1,-1,-1,0,1,},
	{1,0,-1,-1,0,1,1,0,-1,},
	{0,0,0,0,1,-1,1,},
	{-1,-1,0,1,1,2,},//u
	{-1,-1,-1,0,1,1,1,},
	{-1,-1,-1,0,0,0,1,1,1,},
	{-1,-1,0,1,1,1,1,-1,-1,},
	{-1,-1,1,1,0,0,0,},
	{-2,-1,0,0,0,0,0,1,2,-1,1}} };



int pool[2][5][24] = { { { 0 }, //x[column = 0, layer = 1][District][Maximum pool num]
{ 0,3,3,0,-3,-3 },
{ 0,3,6,6,6,3,0,-3,-6,-6,-6,-3 },
{ 0,3,6,9,9,9,9,6,3,0,-3,-6,-9,-9,-9,-9,-6,-3 },
{ 0,3,9,6,12,12,12,12,12,9,6,3,0,-3,-6,-9,-12,-12,-12,-12,-12,-9,-6,-3 } },
{ { 0 },
{ 1,1,0,-1,-1,0 },
{ 2,2,2,1,0,-1,-2,-2,-2,-1,0,1 },
{ 3,3,3,3,2,1,0,-1,-2,-3,-3,-3,-3,-2,-1,0,1,2 },
{ 4,4,4,4,4,3,2,1,0,-1,-2,-3,-4,-4,-4,-4,-4,-3,-2,-1,0,1,2,3 } } };

int colorTable[LAYER][COLUMN/3][3] = { 0 }; // for mode_2

unsigned long mil = 0; //prev Millis
bool isSet = true;
int clock_m = 0;
int clock_rT = 0;
int m_for_bam = 0;
bool isRandT = false;
int ModeNum = 0;
bool isMode_Random = false;
bool isNeedColorChange = false;

void BAM(int mode=0) {//Bit Angle Modulation
	int brightness = 0;
	for (int layer = 0; layer<LAYER; layer++) {
		for (int col = 0; col<COLUMN; col++) {
			if (mode == 4) {
				brightness = Pallete[layer][col];
				brightness = constrain(brightness, 0, 15);
				Pallete[layer][col] = brightness;
			}
			else {
				brightness = bgrColorMask[layer][col];
				// ensure 4-bit limited brightness
				brightness = constrain(brightness, 0, 15); //2^COLOR_BITS-1
				bgrColorMask[layer][col] = brightness;
				// turn 4-bit brightness into brightness mask
			}
			for (int i = COLOR_BITS - 1; i >= 0; i--) {
				if (brightness - (1 << i) >= 0) {
					brightness -= (1 << i);
					brightnessMask[i][layer][col] = 1;
				}
				else {
					brightnessMask[i][layer][col] = 0;
				}
			}
		}
	}
}
void allOff() {
	digitalWriteFast(latchPinA, LOW);
	shiftOut(dataPinA, clockPinA, LSBFIRST, B00000000);
	shiftOut(dataPinA, clockPinA, LSBFIRST, B00000000);
	digitalWriteFast(latchPinA, HIGH);
}
void allOn(int br = 15, int b=1, int g=1, int r=1) {
	for (int i = 0; i < LAYER; i++)
		for (int j = 0; j < COLUMN / 3; j++) {
			bgrColorMask[i][j*3] = br*b;
			bgrColorMask[i][j*3+1] = br*g;
			bgrColorMask[i][j*3+2] = br*r;
		}
}
void CP_display() {
	for (int layer = 0; layer<LAYER; layer++) {
		//layer setting start
		digitalWriteFast(latchPinB, LOW);
		digitalWriteFast(clockPinB, LOW);
		digitalWrite(dataPinB, (layer == 0) ? 1 : 0);
		digitalWriteFast(clockPinB, HIGH);
		digitalWriteFast(latchPinB, HIGH);
		//layer setting end
		for (int clk = 0; clk<16; clk++) { //2^(COLOR_BITS)
			digitalWrite(latchPinA, LOW);
			int b = 0;
      bool n=false;
			if (clk == 0) b = 0;
			else if (clk == 1 || clk == 2) b = 1;
			else if (clk >= 3 && clk <= 6) b = 2;
			else if (clk >= 7 && clk <= 15) b = 3;
			for (int c = 14; c >= 0; c--) {
				digitalWriteFast(clockPinA, LOW);
				digitalWrite(dataPinA,brightnessMask[b][layer][c]);
				digitalWriteFast(clockPinA, HIGH);
			}
			digitalWriteFast(latchPinA, HIGH);
		}
		allOff();
	}
}
int setbgrCM(int i, int j, bool isSet = true, int clk = 0) {
	if (clk % 4 != 0) return 0;  //color set speed
	if (i<0 || i>4 || j<0 || j>14) return 0;
 if (isSet) {
		bgrColorMask[i][j + 2] += m_r[0];
		bgrColorMask[i][j + 1] += m_g[0];
		bgrColorMask[i][j] += m_b[0];
	}
	else {
		bgrColorMask[i][j + 2] -= m_r[1];
		bgrColorMask[i][j + 1] -= m_g[1];
		bgrColorMask[i][j] -= m_b[1];
	}
}
int setbgrCM2(int i, int j, int ii, int jj) {
	if (i < 0 || i>4 || j < 0 || j>14) return 0;
		//int colorTable[LAYER][COLUMN/3][2][3] = { 0 }; // for mode_2
	int sum = bgrColorMask[i][j + 2] + bgrColorMask[i][j + 1] + bgrColorMask[i][j];
	if (sum>= 39) {
		bgrColorMask[i][j + 2] = 15*colorTable[ii][jj][2];
		bgrColorMask[i][j + 1] = 15*colorTable[ii][jj][1];
		bgrColorMask[i][j] = 15*colorTable[ii][jj][0];
	}
	else if(sum < 39 && sum >= 33){
		bgrColorMask[i][j + 2] = (bgrColorMask[i][j + 2])/10 + 15*colorTable[ii][jj][2];
		bgrColorMask[i][j + 1] = (bgrColorMask[i][j + 1]) /10 + 15*colorTable[ii][jj][1];
		bgrColorMask[i][j] = (bgrColorMask[i][j]) / 10 + 15*colorTable[ii][jj][0];
	}
	else if (sum < 33 && sum >= 27) {
		bgrColorMask[i][j + 2] = (bgrColorMask[i][j + 2] ) / 5 + 15*colorTable[ii][jj][2];
		bgrColorMask[i][j + 1] = (bgrColorMask[i][j + 1] ) / 5 + 15*colorTable[ii][jj][1];
		bgrColorMask[i][j] = (bgrColorMask[i][j] ) / 5 + 15*colorTable[ii][jj][0];
	}
	else if (sum < 27 && sum >= 21) {
		bgrColorMask[i][j + 2] = (bgrColorMask[i][j + 2]*3) / 7 + 15*colorTable[ii][jj][2];
		bgrColorMask[i][j + 1] = (bgrColorMask[i][j + 1]*3) / 7 + 15*colorTable[ii][jj][1];
		bgrColorMask[i][j] = (bgrColorMask[i][j]*3) / 7 + 15*colorTable[ii][jj][0];
	}
	else if (sum < 21) {
		bgrColorMask[i][j + 2] = (bgrColorMask[i][j + 2])/  2 + 15*colorTable[ii][jj][2];
		bgrColorMask[i][j + 1] = (bgrColorMask[i][j + 1]) / 2 + 15*colorTable[ii][jj][1];
		bgrColorMask[i][j] = (bgrColorMask[i][j]) / 2+ 15*colorTable[ii][jj][0];
	}
}
int setbgrCM3(int i, int j, int index) {//index 0~10;
	if (i<0 || i>4 || j<0 || j>14) return 0;
	bgrColorMask[i][j + 2] = (15-index)*m_r[0]+(3*index/2)*m_r[1];
	bgrColorMask[i][j + 1] = (15 - index)*m_g[0]+(3*index/2)*m_g[1];
	bgrColorMask[i][j] = (15 - index)*m_b[0]+(3*index/2)*m_b[1];
}

int kkk(int k) {
	switch (k) {
	case 0: return 0;
	case 1: return 8;
	case 2: return 8;
	case 3: return 6;
	case 4: return 8;
	case 5: return 7;
	case 6: return 8;
	case 7: return 10;
	case 8: return 7;
	case 9: return 4;
	case 10: return 6;
	case 11: return 9;
	case 12: return 7;
	case 13: return 9;
	case 14: return 7;
	case 15: return 6;
	case 16: return 8;
	case 17: return 9;
	case 18: return 5;
	case 19: return 9;
	case 20: return 7;
	case 21: return 6;
	case 22: return 7;
	case 23: return 9;
	case 24: return 9;
	case 25: return 7;
	case 26: return 11;
	}
}

bool s_Rs = false;
inline int isBtPushed(int a_n) {
	if (a_n>150) return 3;
	else if (a_n <= 150 && a_n>70) return 2;
	else if (a_n <= 40 && a_n>28) return 1;
	else return 0;
}
int randTouch(int ar9, int ar10) {
	int s = isBtPushed(ar9);
	int m = isBtPushed(ar10);
	int bt = 0;
	if (s*m==4) { clock_rT = 0; isRandT = false; return 0; }
	clock_rT++;
	isMode_Random = true;
	int term = 100;
	if (clock_rT % term == 0) return 0;
	if (clock_rT % term == 1) {
		bt = random(1, 20);//btTable[LAYER][COLUMN/3]
		for (int i = 0; i < 5; i++)//layer
			for (int j = 0; j < 5; j++) {//column
				if ((i*j == 0 && (i + j == 3 || i + j == 4)) || (i*j == 4 && i + j == 5)) continue;
				bt--;
				if (bt == 0) btTable[i][j] = 1;
				else btTable[i][j] = 0;
			}
		s_Rs ^= 1;
	}
	if (clock_rT % term ==term-1) {
		if (s_Rs) return 2; 
		else return 3;
	}
	return 1;
}
//2(set)//3(reset)//4(mode)//5(set+mode=auto mode)//6(reset+set)//0(nothing)
int buttonRefresh(int ar, int ar1, int ar2, int ar3, int ar4, int ar5, int ar6, int ar7, int ar8, int ar9, int ar10) {
	int is_1 = isBtPushed(ar); int is_2 = isBtPushed(ar1); int is_3 = isBtPushed(ar2);
	int is_4 = isBtPushed(ar3); int is_5 = isBtPushed(ar4); int is_6 = isBtPushed(ar5);
	int is_7 = isBtPushed(ar6); int is_8 = isBtPushed(ar7); int is_9 = isBtPushed(ar8);
	int is_10 = isBtPushed(ar9); int is_11 = isBtPushed(ar10);
	int r = 0;
	switch (is_1) {
	case 3: btTable[4][2] = btTable[4][3] = true; break;
	case 2: btTable[4][3] = true; break;
	case 1: btTable[4][2] = true; break;
	case 0: btTable[4][2] = btTable[4][3] = false; break;
	}
	switch (is_2) {
	case 3: btTable[3][1] = btTable[3][2] = true; break;
	case 2: btTable[3][2] = true; break;
	case 1: btTable[3][1] = true; break;
	case 0: btTable[3][1] = btTable[3][2] = false; break;
	}
	switch (is_3) {
	case 3: btTable[2][0] = btTable[2][1] = true; break;
	case 2: btTable[2][1] = true; break;
	case 1: btTable[2][0] = true; break;
	case 0: btTable[2][0] = btTable[2][1] = false; break;
	}
	switch (is_4) {
	case 3: btTable[1][0] = btTable[1][1] = true; break;
	case 2: btTable[1][1] = true; break;
	case 1: btTable[1][0] = true; break;
	case 0: btTable[1][0] = btTable[1][1] = false; break;
	}
	switch (is_5) {
	case 3: btTable[0][0] = btTable[0][1] = true; break;
	case 2: btTable[0][1] = true; break;
	case 1: btTable[0][0] = true; break;
	case 0: btTable[0][0] = btTable[0][1] = false; break;
	}
	switch (is_6) {
	case 3: btTable[2][2] = btTable[3][3] = true; break;
	case 2: btTable[3][3] = true; break;
	case 1: btTable[2][2] = true; break;
	case 0: btTable[2][2] = btTable[3][3] = false; break;
	}
	switch (is_7) {
	case 3: btTable[1][2] = btTable[2][3] = true; break;
	case 2: btTable[2][3] = true; break;
	case 1: btTable[1][2] = true; break;
	case 0: btTable[1][2] = btTable[2][3] = false; break;
	}
	switch (is_8) {
	case 3: btTable[0][2] = btTable[1][3] = true; break;
	case 2: btTable[1][3] = true; break;
	case 1: btTable[0][2] = true; break;
	case 0: btTable[0][2] = btTable[1][3] = false; break;
	}
	switch (is_9) {
	case 3: btTable[4][4] = btTable[3][4] = true; break;
	case 2: btTable[3][4] = true; break;
	case 1: btTable[4][4] = true; break;
	case 0: btTable[4][4] = btTable[3][4] = false; break;
	}
	switch (is_10) {
	case 3: btTable[2][4] = btTable[1][4] = true; break;
	case 2: btTable[1][4] = true; r = 2; break; //set button
	case 1: btTable[2][4] = true; break;
	case 0: btTable[2][4] = btTable[1][4] = false; break;
	}
	switch (is_11) {
	case 3: btTable[0][3] = btTable[0][4] = true; break;
	case 2: btTable[0][4] = true; if (r == 2) r = 5; else r = 4; break; //Mode button=4, set+mode=5
	case 1: btTable[0][3] = true; if (r == 2) r = 6; else r = 3; break; //reset button
	case 0: btTable[0][3] = btTable[0][4] = false; break;
	}
	if (is_1 || is_2 || is_3 || is_4 || is_5 || is_6 || is_7 || is_8 || is_9 || (is_10 == 1 || is_10 == 3)) return 1;
	else return r; //2(set)//3(reset)//4(mode)//5(set+mode=auto mode)//6(reset+set)//0(nothing)

}
//buttonRefresh() end
