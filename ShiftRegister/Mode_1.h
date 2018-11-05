#pragma once
#include "BaseSetting.h"

int Mode_1(int b_n) {
	if (b_n == 0|| b_n == 12) { clock_m = 0; return 0; }
	if (b_n == 10) { isMode_Random ^= 1; }
	if (b_n == 11) { maskReset(); return 0; }

	/////(re)set_button color setting
	for (int i = 0; i<2; i++) {
		if (isMode_Random && (!clock_m) && (b_n == 1)) { Color_m[i] = (Color_m[i] + 10+ random(40)) % 60; }
		else if (b_n == i + 2) {
			Color_m[i] = (Color_m[i] + 1) % 60; //[0] set [1] reset
			isSet = 1 - i;
		}
		if (Color_m[i] >= 0 && Color_m[i]<10) { m_b[i] = 0; m_g[i] = 0; m_r[i] = 1; }
		else if (Color_m[i] >= 10 && Color_m[i]<20) { m_b[i] = 0; m_g[i] = 1; m_r[i] = 1; }
		else if (Color_m[i] >= 20 && Color_m[i]<30) { m_b[i] = 0; m_g[i] = 1; m_r[i] = 0; }
		else if (Color_m[i] >= 30 && Color_m[i]<40) { m_b[i] = 1; m_g[i] = 1; m_r[i] = 0; }
		else if (Color_m[i] >= 40 && Color_m[i]<50) { m_b[i] = 1; m_g[i] = 0; m_r[i] = 0; }
		else if (Color_m[i] >= 50 && Color_m[i]<60) { m_b[i] = 1; m_g[i] = 0; m_r[i] = 1; }

		if ((i == 0 && isSet) || (i == 1 && !isSet)) {
			bgrColorMask[1 - i][12 - 3 * i] = 15 * m_b[i];
			bgrColorMask[1 - i][13 - 3 * i] = 15 * m_g[i];
			bgrColorMask[1 - i][14 - 3 * i] = 15 * m_r[i];
		}
	}
	/////(re)set_button color setting end isMode_Random

	///spread start  

	if (b_n == 1) {
		for (int i = 0; i<5; i++) //layer
			for (int j = 0; j<5; j++) { //column
										/////start
				if ((i*j == 0 && (i + j == 3 || i + j == 4)) || (i*j == 4 && i + j == 5)) continue;
				if (btTable[i][j]) {
					int dis = clock_m/4;
					if (dis>20) dis = 20; //district <= 20
					for (int h = dis / 5; h >= 0; h--) {
						int n = (h == 4) ? 24 : (h == 3) ? 18 : (h == 2) ? 12 : (h == 1) ? 6 : 1;
						for (int k = 0; k<n; k++) {  //pool[column = 0, layer = 1][District][Maximum pool num]
							setbgrCM(i + pool[1][h][k], j * 3 + pool[0][h][k], isSet, clock_m);
						}
					}
				}
			}
		clock_m++;
	}
	///spread end

	for (int i = 0; i<2; i++) {//set reset coloring
		if ((i == 0 && isSet) || (i == 1 && !isSet)) {
			bgrColorMask[1 - i][12 - 3 * i] = 15 * m_b[i];
			bgrColorMask[1 - i][13 - 3 * i] = 15 * m_g[i];
			bgrColorMask[1 - i][14 - 3 * i] = 15 * m_r[i];
		}
		else {
			bgrColorMask[1 - i][12 - 3 * i] = 0;
			bgrColorMask[1 - i][13 - 3 * i] = 0;
			bgrColorMask[1 - i][14 - 3 * i] = 0;
		}
	}
	if (isMode_Random) {
		if (isSet) {
			bgrColorMask[0][12] = 15 * m_b[0];
			bgrColorMask[0][13] = 15 * m_g[0];
			bgrColorMask[0][14] = 15 * m_r[0];
		}
		else {
			bgrColorMask[0][12] = 15 * m_b[1];
			bgrColorMask[0][13] = 15 * m_g[1];
			bgrColorMask[0][14] = 15 * m_r[1];
		}
	}
	else {
		bgrColorMask[0][14] = 0; //Mode decoloring
		bgrColorMask[0][13] = 0;
		bgrColorMask[0][12] = 0;
	}
	return 0;
}
//////////////////////////////////////////Mode_1 end
