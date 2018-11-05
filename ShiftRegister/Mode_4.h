#pragma once
#include "BaseSetting.h"

//x[layer][COLUMN/3][0=0, 1=1]
int ColorPallete[LAYER][COLUMN / 3][2] = 
	{ { {0,0},{0,6},{0,9},{0,0},{0,0} },
		{ {0,4},{0,9},{0,12},{0,15},{0,15} },
		{ {1,5},{3,6},{3,9},{3,12},{3,15} },
		{ {0,0},{4,8},{6,9},{6,12},{6,15} },
		{ {0,0},{0,0},{7,11},{9,12},{9,15} } };


void prtPallete(int b, int g, int r) {
	int color[3] = { b,g,r };
	for (int i = 0; i < LAYER; i++) {
		for (int j = 0; j < COLUMN; j++) {
			Pallete[i][j] = ColorPallete[i][j / 3][color[j % 3]];
		}
	}
}

bool isErase = false;
int Mode_4(int b_n) {
  unsigned long Mmil_4 = millis();
	if (b_n == 0|| b_n==12) { return 0; }
  if (b_n == 6&&clock_m%20==0) {
    int temp[3]={0};
    for(int i=0;i<3;i++){
      temp[i]=bgrColorMask[1][12+i];
      bgrColorMask[1][12+i] = bgrColorMask[0][12+i];
      bgrColorMask[0][12+i] = temp[i];
    }
    m_for_bam = 0;
  }
  if (b_n == 11) { allOn(); return 0; }
 
	if (!isSet) { m_b[1] = 1; m_g[1] = 1; m_r[1] = 1; }
	else { m_b[1] = 0; m_g[1] = 0; m_r[1] = 0; }
  
	if (b_n ==2) {
		isSet = true;
		Color_m[0] = (Color_m[0] + 1) % 60;
		if (Color_m[0] >= 0 && Color_m[0]<10) { m_b[0] = 0; m_g[0] = 0; m_r[0] = 1; }
		else if (Color_m[0] >= 10 && Color_m[0]<20) { m_b[0] = 0; m_g[0] = 1; m_r[0] = 1; }
		else if (Color_m[0] >= 20 && Color_m[0]<30) { m_b[0] = 0; m_g[0] = 1; m_r[0] = 0; }
		else if (Color_m[0] >= 30 && Color_m[0]<40) { m_b[0] = 1; m_g[0] = 1; m_r[0] = 0; }
		else if (Color_m[0] >= 40 && Color_m[0]<50) { m_b[0] = 1; m_g[0] = 0; m_r[0] = 0; }
		else if (Color_m[0] >= 50 && Color_m[0]<60) { m_b[0] = 1; m_g[0] = 0; m_r[0] = 1; }
		prtPallete(m_b[0],m_g[0],m_r[0]);
		m_for_bam = 4;  //BAM Pallete,  not bgrColorM-
	}
	else if (b_n == 3) {
		if (isSet) return 0;
		Color_m[1] = (Color_m[1] + 1) % 20;
		if (Color_m[1] >= 0 && Color_m[1]<10) { 
			m_b[1] = 1; m_g[1] = 1; m_r[1] = 1; isErase = true;}
		else if (Color_m[1] >= 10 && Color_m[1] < 20) {
			m_b[1] = 0; m_g[1] = 0; m_r[1] = 0; isErase = false;}
		bgrColorMask[0][11] = 15 * m_b[1];
		bgrColorMask[0][10] = 15 * m_g[1];
		bgrColorMask[0][9] = 15 * m_r[1];
	}
	else if (b_n == 1) {
		if (isSet) {
			clock_m = 0;
			for (int i = 0; i<5; i++) //layer
				for (int j = 0; j < 5; j++) { //column
					if (btTable[i][j]) {
						bgrColorMask[1][12] = Pallete[i][j*3];			//input color to set button
						bgrColorMask[1][13] = Pallete[i][j*3+1];
						bgrColorMask[1][14] = Pallete[i][j*3+2];
						i = 5; break;
					}
				}

			isSet = false;
			m_for_bam = 0;
		}
		else if (isErase) {
			for (int i = 0; i < 5; i++) //layer
				for (int j = 0; j < 5; j++) {//column
					if (btTable[i][j]) {
						bgrColorMask[i][j*3 + 2] = bgrColorMask[0][11];
						bgrColorMask[i][j*3 + 1] = bgrColorMask[0][10];
						bgrColorMask[i][j*3] = bgrColorMask[0][9];
					}
				}
		}
		else if(clock_m>20) {
			for (int i = 0; i < 5; i++) //layer
				for (int j = 0; j < 5; j++) { //column
					if ((i*j == 0 && (i + j == 3 || i + j == 4)) || (i*j == 4 && i + j == 5)) continue;
					if (btTable[i][j]) {
						bgrColorMask[i][j*3 + 2] = bgrColorMask[1][14];
						bgrColorMask[i][j*3 + 1] = bgrColorMask[1][13];
						bgrColorMask[i][j*3] = bgrColorMask[1][12];
					}
				}
		}
	}
	clock_m++;
	return 0;
}
//////////////////////////////////////////Mode_4 end
