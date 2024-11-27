#pragma once
#include "Oso.h"
class Banco
{
public:
	Oso mang[9][9];
	Banco();
	int control;
	void draw(CClientDC* dc);
	void draw(CPaintDC* dc);
	bool isDatSo(int mi, int mj, int num);
	void ngauNhien();
	//void keyPress(CPoint p, CPaintDC* dc);
	void showPopup(CPoint p, CWnd* pWnd, int mi, int mj);
	int hoveredRow;
	int hoveredCol;
	void chonSo(int num);
	
	int selectedRow = -1; // Bi?n l?u hàng c?a ô ???c ch?n (kh?i t?o là -1)
	int selectedCol = -1; // Bi?n l?u c?t c?a ô ???c ch?n (kh?i t?o là -1)
	//bool isLocked;
};

