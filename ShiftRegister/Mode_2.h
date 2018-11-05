#pragma once
#include "BaseSetting.h"

int disTable[LAYER][COLUMN] = { 0 };

int speedM_2 = 50; //0 ~ 60;
bool isSpread = false;
bool touch = false;

int Mode_2(int b_n) {
	if (clock_m%8==1) {//auto color increasing
		for (int i = 0; i < LAYER; i++)
			for (int j = 0; j < COLUMN; j++) {
				if ((i*(j/3) == 0 && (i + (j/3) == 3 || i + (j/3) == 4)) || (i*(j/3) == 4 && i + (j/3) == 5)) continue;
				bgrColorMask[i][j]++;
			}
		CP_display();
	}
	else if (b_n == 10) { isMode_Random ^= 1; }
	else if (b_n == 11) { allOn(); return 0; }
	else if (b_n == 3) { speedM_2 = (speedM_2 + 1) % 60; }

	/////(re)set_button color setting
	if (b_n == 1 || b_n == 2 || b_n == 0) {

		
			if (isMode_Random && (b_n == 0) && touch) {
				Color_m[0] = (Color_m[0] +10+ random(20)) % 60;
				touch = false;
			}
			else if (b_n == 2 && clock_m % 2 == 0) {
				Color_m[0] = (Color_m[0] + 1) % 60; //[0] set [1] reset
			}

			if (Color_m[0] >= 0 && Color_m[0] < 10) { m_b[0] = 0; m_g[0] = 0; m_r[0] = 1; }
			else if (Color_m[0] >= 10 && Color_m[0] < 20) { m_b[0] = 0; m_g[0] = 1; m_r[0] = 1; }
			else if (Color_m[0] >= 20 && Color_m[0] < 30) { m_b[0] = 0; m_g[0] = 1; m_r[0] = 0; }
			else if (Color_m[0] >= 30 && Color_m[0] < 40) { m_b[0] = 1; m_g[0] = 1; m_r[0] = 0; }
			else if (Color_m[0] >= 40 && Color_m[0] < 50) { m_b[0] = 1; m_g[0] = 0; m_r[0] = 0; }
			else if (Color_m[0] >= 50 && Color_m[0] < 60) { m_b[0] = 1; m_g[0] = 0; m_r[0] = 1; }

		for (int i = 0; i < 2; i++) {
			int n = (i == 0) ? 15 : (speedM_2 / 4);
			bgrColorMask[1 - i][12 - 3 * i] = n * m_b[0];
			bgrColorMask[1 - i][13 - 3 * i] = n * m_g[0];
			bgrColorMask[1 - i][14 - 3 * i] = n * m_r[0];
		}
		/////(re)set_button color setting end
		//spread start  
		if (b_n == 1) {
			if (isMode_Random) touch = true;
			isSpread = true;
			for (int i = 0; i < 5; i++) //layer
				for (int j = 0; j < 5; j++) { //column
					if ((i*j == 0 && (i + j == 3 || i + j == 4)) || (i*j == 4 && i + j == 5)) continue;
					if (btTable[i][j] && disTable[i][j] == 0) {
						disTable[i][j] = 1;
						colorTable[i][j][0] = m_b[0];
						colorTable[i][j][1] = m_g[0];
						colorTable[i][j][2] = m_r[0];
					}
				}
		}
	}
	if (clock_m % (30-(speedM_2/15)*7) == 0) {
		bool res = false;
		for (int i = 0; i < 5; i++) //layer
			for (int j = 0; j < 5; j++) { //column
				if ((i*j == 0 && (i + j == 3 || i + j == 4)) || (i*j == 4 && i + j == 5)) continue;
				if (disTable[i][j] == 0) { continue; }
				else res = true;

				int h = disTable[i][j] - 1;
				if (h == 5)	 disTable[i][j] = 0;
				else {
					int n = (h == 4) ? 24 : (h == 3) ? 18 : (h == 2) ? 12 : (h == 1) ? 6 : 1;
					for (int k = 0; k < n; k++) {  //pool[column = 0, layer = 1][District0~4][Maximum pool num]
						setbgrCM2(i + pool[1][h][k], j * 3 + pool[0][h][k], i,j);
					}
					disTable[i][j]++;
				}
			}
		isSpread = res;
		
	}
	CP_display();
	//spread end
	for (int i = 0; i<2; i++) {//set reset coloring
		int n = (i == 0) ? 15 : (speedM_2 / 4);
		bgrColorMask[1 - i][12 - 3 * i] = n * m_b[0];
		bgrColorMask[1 - i][13 - 3 * i] = n * m_g[0];
		bgrColorMask[1 - i][14 - 3 * i] = n * m_r[0];
	}
	if (isMode_Random) {
			bgrColorMask[0][12] = 15 * m_b[0]; //mode == set
			bgrColorMask[0][13] = 15 * m_g[0];
			bgrColorMask[0][14] = 15 * m_r[0];
	}
	else {
		bgrColorMask[0][14] = 0; //Mode decoloring
		bgrColorMask[0][13] = 0;
		bgrColorMask[0][12] = 0;
	}
	clock_m++;
	if (clock_m == 100000) clock_m = 0;
	return 0;
}
//////////////////////////////////////////Mode_2 end
