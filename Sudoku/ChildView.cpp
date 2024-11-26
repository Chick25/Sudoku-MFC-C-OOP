
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Sudoku.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	//hcn.setHcn(50, 50, 200, 200);
	//hcn.draw(&dc);
	
	banco.draw(&dc);
	//banco.ngauNhien();
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    static int lastHoveredRow = -1, lastHoveredCol = -1;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // T�nh to�n t?a ?? h�nh ch? nh?t c?a � hi?n t?i
            int left = 50 + j * 40;          // T?a ?? x b�n tr�i
            int top = 50 + i * 40;           // T?a ?? y b�n tr�n
            int right = left + 40;           // T?a ?? x b�n ph?i
            int bottom = top + 40;           // T?a ?? y b�n d??i

            // Ki?m tra n?u con tr? n?m trong � v� l� � tr?ng
            if (point.x >= left && point.x <= right &&
                point.y >= top && point.y <= bottom &&
                banco.mang[i][j].dong == 1) {

                if (lastHoveredRow == i && lastHoveredCol == j) {
                    // Tr�nh l?p l?i n?u hover v?n tr�n c�ng m?t �
                    return;
                }

                lastHoveredRow = i;
                lastHoveredCol = j;

                // T�nh to�n ?i?m hi?n th? menu
                CPoint popupPoint(left + 20, top + 20); // ??t menu g?n g�c tr�i tr�n c?a �
                banco.showPopup(popupPoint, this, i, j); // Hi?n th? menu
                return;
            }
        }
    }

    // N?u kh�ng hover v�o � n�o, reset tr?ng th�i
    lastHoveredRow = -1;
    lastHoveredCol = -1;

	CWnd::OnMouseMove(nFlags, point);
}

BOOL CChildView::OnCommand(WPARAM wParam, LPARAM lParam)
{
   
        int id = LOWORD(wParam);

        if (id >= 1001 && id <= 1009) {
            int number = id - 1000;
            banco.chonSo(number);

            // Y�u c?u v? l?i
            Invalidate();
            UpdateWindow();
            return TRUE;
        }
     
    /*
    int id = LOWORD(wParam);

    // Ki?m tra n?u ID l� c?a menu s?
    if (id >= 1001 && id <= 1009) {
        int number = id - 1000; // Chuy?n ??i ID menu th�nh s? (1-9)

        if (banco.selectedRow != -1 && banco.selectedCol != -1) {
            // ?i?n s? v�o � ???c ch?n
            banco.mang[banco.selectedRow][banco.selectedCol].so = number;
            banco.mang[banco.selectedRow][banco.selectedCol].dong = 0; // ?�nh d?u � kh�ng c�n tr?ng

            // Reset v? tr� � ???c ch?n
            banco.selectedRow = -1;
            banco.selectedCol = -1;

            // C?p nh?t giao di?n
            Invalidate();
            UpdateWindow();
        }
        return TRUE; // Command ?� x? l�
    }
    */
    return CWnd::OnCommand(wParam, lParam);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{

    // TODO: Add your message handler code here and/or call default
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // X�c ??nh t?a ?? c?a �
            int left = 50 + j * 40;
            int top = 50 + i * 40;
            int right = left + 40;
            int bottom = top + 40;

            // N?u nh?n v�o � v� � ?� tr?ng
            if (point.x >= left && point.x <= right &&
                point.y >= top && point.y <= bottom &&
                banco.mang[i][j].dong == 1) {

                // L?u l?i � ???c ch?n
                banco.selectedRow = i;
                banco.selectedCol = j;

                // Hi?n popup menu cho ph�p ch?n s?
                CPoint popupPoint(left + 20, top + 20);
                banco.showPopup(popupPoint, this, i, j);

                return;
            }
        }
    }

    CWnd::OnLButtonDown(nFlags, point);
}
