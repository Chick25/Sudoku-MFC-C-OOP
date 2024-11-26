#include "pch.h"
#include "CHcn.h"

CHcn::CHcn()
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	bcolor = 1;
}

CHcn::CHcn(int x1, int y1, int x2, int y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	bcolor = 1;
}

void CHcn::setHcn(int x1, int y1, int x2, int y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

void CHcn::draw(CPaintDC* dc)
{
	//CPen penBorder(PS_SOLID, 3, RGB(255, 0, 0));
	//CPen* oldPen = dc->SelectObject(&penBorder);
	//CBrush whiteBrush(RGB(255, 255, 255));
	CBrush blueBrush(RGB(121, 205, 205));
	CBrush redBrush(RGB(121, 121, 121));
	CBrush* pOldBrush = new CBrush();
	
	if (bcolor == 1) {
		pOldBrush = dc->SelectObject(&redBrush);

	}
	else if (bcolor == 2) {
		pOldBrush = dc->SelectObject(&blueBrush);
	}
	else if (bcolor == 3) {
		dc->SelectStockObject(NULL_BRUSH);
	}
	dc->Rectangle(x1, y1, x2, y2);
	if (bcolor == 1 || bcolor == 2 || bcolor == 3)
	{
		dc->SelectObject(pOldBrush);
	}
}

void CHcn::draw(CClientDC* dc)
{
	//CPen penBorder(PS_SOLID, 3, RGB(255, 0, 0));
	//CPen* oldPen = dc->SelectObject(&penBorder);

	CBrush redBrush(RGB(121, 121, 121));
	CBrush* pOldBrush = new CBrush();
	if (bcolor == 1) {
		pOldBrush = dc->SelectObject(&redBrush);
		dc->SelectStockObject(NULL_BRUSH);

	}
	dc->Rectangle(x1, y1, x2, y2);
	if (bcolor == 1) {
		dc->SelectObject(pOldBrush);
		dc->SelectStockObject(NULL_BRUSH);
	}
	
}

int CHcn::kttronghinh(CPoint p)
{
	if (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2)
		return 1;
	return 0;
}

/*

void CHcn::up(int d)
{
	y1 -= d;
	y2 -= d;
}

void CHcn::down(int d)
{
	y1 = y1 + d;
	y2 = y2 + d;
}

void CHcn::right(int d)
{
	x1 = x1 + d;
	x2 = x2 + d;
}

void CHcn::left(int d)
{
	x1 = x1 - d;
	x2 = x2 - d;
}
*/
