#include "pch.h"
#include "Oso.h"

void Oso::draw(CClientDC* dc)
{
	//
	if (so > 0) {
		CString numStr;
		numStr.Format(_T("%d"), so); // Convert number to CString

		// Center the text in the rectangle
		int centerX = (x1 + x2) / 2;
		int centerY = (y1 + y2) / 2;
		/*
		CFont font;
		font.CreatePointFont(120, _T("Arial")); // Create a font
		CFont* oldFont = dc->SelectObject(&font);

		dc->SetTextAlign(TA_CENTER);
		*/
		dc->SetTextColor(RGB(0, 0, 0));
		dc->SetBkMode(TRANSPARENT);
		dc->TextOutW(centerX, centerY - 8, numStr); // Draw the number

		//dc->SelectObject(oldFont); // Restore the old font
	}
	//
	/*
	CHcn::draw(dc);
	if (dong == 0)
	{
		int xmoi = (x1 + x2) / 2 - 5;
		int ymoi = (y1 + y2) / 2 - 8;
		CString str;
		str.Format(_T("%d"), gtri);
		dc->MoveTo(xmoi, ymoi);
		if (so == 1)
		{
			dc->TextOutW(xmoi, ymoi, CString("X"));
			dc->SetTextColor(RGB(121, 121, 121));
		}
		else
		{
			if (gtri > 0)
			dc->TextOutW(xmoi, ymoi, CString("0"));
			dc->SetTextColor(RGB(121, 121, 121));
		}

	}
	*/
}

void Oso::draw(CPaintDC* dc)
{
	CHcn::draw(dc);
	
	//
	if (so > 0) {
		CString numStr;
		numStr.Format(_T("%d"), so); // Convert number to CString

		// Center the text in the rectangle
		int centerX = (x1 + x2) / 2-5;
		int centerY = (y1 + y2) / 2-5;
		/*
		CFont font;
		font.CreatePointFont(120, _T("Arial")); // Create a font
		CFont* oldFont = dc->SelectObject(&font);

		dc->SetTextAlign(TA_CENTER);
		*/
		dc->SetTextColor(RGB(0, 0, 0));
		dc->SetBkMode(TRANSPARENT);
		dc->TextOutW(centerX, centerY - 8, numStr); // Draw the number
	
		//dc->SelectObject(oldFont); // Restore the old font
	}
		
	//
	/*
	if (dong == 0)
	{
		int xmoi = (x1 + x2) / 2 - 5;
		int ymoi = (y1 + y2) / 2 - 8;
		CString str;
		str.Format(_T("%d"), gtri);
		dc->MoveTo(xmoi, ymoi);
		if (so == 1)
		{
			dc->TextOutW(xmoi, ymoi, CString("X"));
			dc->SetTextColor(RGB(121, 121, 121));
		}
		else
		{
			if (gtri > 0)
				dc->TextOutW(xmoi, ymoi, CString("0"));
				dc->SetTextColor(RGB(121, 121, 121));
		}

	}
	*/
}
/*
int Oso::setNum(CPaintDC* dc, CPoint p, int num)
{
	if (kttronghinh(p) == 1) {
		if (dong == 1) {
			so = num;
			draw(dc);
			return 1;
		}
		else {
			return -1;
		}
	}
		return 0;
}
*/
