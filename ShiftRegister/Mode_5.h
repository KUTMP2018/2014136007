#pragma once
#include "BaseSetting.h"

int m_5_mode = 0;
bool isNext = false;
bool isSleep = false;
int br = 0;
int Mode_5(int b_n) {
	if (b_n == 10) { isMode_Random ^= 1; }
	//if (isMode_Random && (!clock_m)) { Color_m[0] = (Color_m[0] + 10+ random(40)) % 60; }
	if (b_n == 2) {
		Color_m[0] = (Color_m[0] + 1) % 60;
		if (Color_m[0] >= 0 && Color_m[0] < 10) { m_b[0] = 0; m_g[0] = 0; m_r[0] = 1; }
		else if (Color_m[0] >= 10 && Color_m[0] < 20) { m_b[0] = 0; m_g[0] = 1; m_r[0] = 1; }
		else if (Color_m[0] >= 20 && Color_m[0] < 30) { m_b[0] = 0; m_g[0] = 1; m_r[0] = 0; }
		else if (Color_m[0] >= 30 && Color_m[0] < 40) { m_b[0] = 1; m_g[0] = 1; m_r[0] = 0; }
		else if (Color_m[0] >= 40 && Color_m[0] < 50) { m_b[0] = 1; m_g[0] = 0; m_r[0] = 0; }
		else if (Color_m[0] >= 50 && Color_m[0] < 60) { m_b[0] = 1; m_g[0] = 0; m_r[0] = 1; }
		m_b[1] =m_g[1] =m_r[1] = 1;
		bgrColorMask[1][12] = 15 * m_b[0];
		bgrColorMask[1][13] = 15 * m_g[0];
		bgrColorMask[1][14] = 15 * m_r[0];
	}
	else if (b_n == 3) {
		Color_m[1] = (Color_m[1] + 1) % 60;
		m_5_mode = Color_m[1] / 10; //// 0~5
	}
	int speed = 90;

	switch (m_5_mode) {
	case 0: {
		int dis = (clock_m%speed) / (speed / 15); //int dis = clock_m %20;//dis 0~14
		if (clock_m%speed == 0) isNext ^= 1;
		for (int h = dis / 5; h >= 0; h--) { //h 0~2
			int n = (h == 2) ? 12 : (h == 1) ? 6 : 1;
			for (int k = 0; k < n; k++) {  //pool[column = 0, layer = 1][District][Maximum pool num]
				setbgrCM(2 + pool[1][h][k], 2 * 3 + pool[0][h][k], isNext, clock_m % 2);
			}
			if (dis > 1)
				for (int k = 0; k < 12; k++) {  //pool[column = 0, layer = 1][District][Maximum pool num]
					setbgrCM(2 + pool[1][h + 1][k], 2 * 3 + pool[0][h + 1][k], isNext, clock_m % 2);
				}
		}
		break; }
	case 1: {
		if ((clock_m % 5) == 0) {
			if (br <= 3) isNext = true;
			else if (br >= 15) isNext = false;
			if (isNext) { br++; }
			else { br--; }
			allOn(br, m_b[0], m_g[0], m_r[0]);
		}
		break; }
	case 2: {allOn(15, m_b[0], m_g[0], m_r[0]); break;}
	case 3: {allOn(9, m_b[0], m_g[0], m_r[0]); break; }
	case 4: {allOn(5, m_b[0], m_g[0], m_r[0]); break; }
	case 5: {allOn(2, m_b[0], m_g[0], m_r[0]); break; }
		break;
	}
	///spread end
	if (b_n == 12) isSleep = true;
	else isSleep = false;
	if (isSleep) {
		bgrColorMask[1][12] = bgrColorMask[0][9] = bgrColorMask[0][12] = bgrColorMask[0][6];
		bgrColorMask[1][13] = bgrColorMask[0][10] = bgrColorMask[0][13] = bgrColorMask[0][7];
		bgrColorMask[1][14] = bgrColorMask[0][11] = bgrColorMask[0][14] = bgrColorMask[0][8];
	}
	else {
		bgrColorMask[1][12] = 15 * m_b[0];
		bgrColorMask[1][13] = 15 * m_g[0];
		bgrColorMask[1][14] = 15 * m_r[0];

		bgrColorMask[0][9] = 5 + 2 * m_5_mode * m_b[0];
		bgrColorMask[0][10] = 5 + 2 * m_5_mode * m_g[0];
		bgrColorMask[0][11] = 5 + 2 * m_5_mode * m_r[0];

		bgrColorMask[0][12] = bgrColorMask[0][9];
		bgrColorMask[0][13] = bgrColorMask[0][10];
		bgrColorMask[0][14] = bgrColorMask[0][11];
	}
	clock_m++;
	return 0;
}
//////////////////////////////////////////Mode_1 end
