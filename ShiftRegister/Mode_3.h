#pragma once
#include "BaseSetting.h"

int printAlpha[3][2][30] = { 0 }; //string num = 3

char string[3][30] = { "hello`world``",
								"abcdefghijklmnopqrstuvwxyz``",
								"pen`pineapple`apple`pen``"
								 };
int stringLen[3] = { 0 };
int setAlpha(int i,char *str) {
	int n = 0;
	while (str[n] != '\0') {
		printAlpha[i][0][n] = (int)str[n] - 96;
		n++;
	}
	int r = n;
	for (n--; n >= 0; n--) {
		printAlpha[i][1][n] = -1;
	}
	printAlpha[i][1][0] = 4;
	return r;
}
int nn = 0;	
int moveSpeed = 25;
int clock_m3 = 0;
int idx = 0;
void Mode_3(int b_n) {
	if (b_n == 11) nn = (nn + 1) % 3;
	for (int i = 0; i < 2; i++) {
		if (b_n == i + 2) {
			Color_m[i] = (Color_m[i] + 1) % 60; //[0] set [1] reset
			if (Color_m[i] >= 0 && Color_m[i] < 10&&i==0) { m_b[i] = 0; m_g[i] = 0; m_r[i] = 1; }
			else if (Color_m[i] >= 10 && Color_m[i] < 20&&i==1) { m_b[i] = 0; m_g[i] = 1; m_r[i] = 1; }
			else if (Color_m[i] >= 20 && Color_m[i] < 30&&i==0) { m_b[i] = 0; m_g[i] = 1; m_r[i] = 0; }
			else if (Color_m[i] >= 30 && Color_m[i] < 40&i==1) { m_b[i] = 1; m_g[i] = 1; m_r[i] = 0; }
			else if (Color_m[i] >= 40 && Color_m[i] < 50&&i==0) { m_b[i] = 1; m_g[i] = 0; m_r[i] = 0; }
			else if (Color_m[i] >= 50 && Color_m[i] < 60&&i==1) { m_b[i] = 1; m_g[i] = 0; m_r[i] = 1; }
			bgrColorMask[1 - i][12 - 3 * i] = 15 * m_b[i];
			bgrColorMask[1 - i][13 - 3 * i] = 15 * m_g[i];
			bgrColorMask[1 - i][14 - 3 * i] = 15 * m_r[i];
		}
	}

	if (printAlpha[nn][1][idx] == 0) printAlpha[nn][1][(idx + 1) % stringLen[nn]] = 4;
	allOn(0);
	for (int w = 0; w < 2; w++) {
		int L = (idx + w) % stringLen[nn];
		if (printAlpha[nn][1][L] != -1) {
			int k = printAlpha[nn][0][L];
			int kky = kkk(k);
			for (int kk = 0; kk < kky; kk++) {
				int i = printAlpha[nn][1][L] + alpha[0][k][kk];
				int j = printAlpha[nn][1][L] + alpha[1][k][kk];
				setbgrCM3(i, j * 3, kk);
			}
			if ((clock_m3%moveSpeed) == (moveSpeed - 1)) {
				printAlpha[nn][1][L] -= 1;
			}
		}
	}
	if (printAlpha[nn][1][idx] == -1) { idx = ((idx + 1) % stringLen[nn]);}
	clock_m3++;
if(b_n==12) {
  for (int i = 0; i<2; i++) {//set reset coloring
      bgrColorMask[1 - i][12 - 3 * i] = 0;
      bgrColorMask[1 - i][13 - 3 * i] = 0;
      bgrColorMask[1 - i][14 - 3 * i] = 0;
  }}
  else{
	for (int i = 0; i<2; i++) {//set reset coloring
			bgrColorMask[1 - i][12 - 3 * i] = 15 * m_b[i];
			bgrColorMask[1 - i][13 - 3 * i] = 15 * m_g[i];
			bgrColorMask[1 - i][14 - 3 * i] = 15 * m_r[i];
	}}
}
