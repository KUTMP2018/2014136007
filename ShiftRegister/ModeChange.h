#pragma once
#include "BaseSetting.h"
int prtMode[2][5][9] = { { { 1,2,2,2,2,2 }, //x[column = 0, layer = 1][Mode][Maximum pool num]
{ 1,2,3,3,2,1,1,2,3 },
{ 1,2,3,3,2,3,3,2,1 },
{ 1,1,2,3,3,3,3 },
{ 3,2,1,1,2,3,3,2,1 } },
{ { 3,4,3,2,1,0 },
{ 3,4,4,3,2,1,0,0,1 },
{ 3,4,4,3,2,2,1,0,0 },
{ 3,2,2,3,4,2,1 },
{ 4,4,3,2,2,2,1,0,0 } } };

inline int maskReset() {
	for (int i = 0; i<LAYER; i++)
		for (int j = 0; j<COLUMN; j++) {
			bgrColorMask[i][j] = 0;
		}
}
////////////////////slct Mode start  
void slctMode() {
	for (int i = 0; i<LAYER; i++) {
		for (int j = 0; j<COLUMN; j++) {
			cash[i][j] = bgrColorMask[i][j];
			bgrColorMask[i][j] = 0;
		}
	}
	allOff();
	int h = ModeNum;
	while (true) {
		h = h % 5;
		int n = (h == 0) ? 6 : ((h == 1) ? 9 : ((h == 2) ? 9 : ((h == 3) ? 7 : 9)));
		maskReset();
		for (int k = 0; k<n; k++) {
			int i = prtMode[1][h][k];   //layer = i
			int j = 3 * prtMode[0][h][k]; //column = j
			bgrColorMask[i][j + 2] = 15 * m_r[0]; //red
			bgrColorMask[i][j + 1] = 15 * m_g[0]; //green
			bgrColorMask[i][j] = 15 * m_b[0]; //blue
		}
		BAM();
		CP_display();
		unsigned long Mmil = millis();
		if (Mmil - mil >= 200UL) {
			int rs_m = analogRead(A10);
			int set = analogRead(A9);
			mil = Mmil;
			if (isBtPushed(rs_m) == 2) h++;
			else if (isBtPushed(set) == 2) {
				if (h != ModeNum) {
					maskReset();
					ModeNum = h;
					if (ModeNum == 3||ModeNum==1) allOn(); break;
				}
				else {
					for (int i = 0; i<LAYER; i++)
						for (int j = 0; j<COLUMN; j++) {
							bgrColorMask[i][j] = cash[i][j];
						}
					break;
				}
			}
		}
	}
	isMode_Random = false;
	m_for_bam = 0;
}
