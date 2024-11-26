
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
            // Tính toán t?a ?? hình ch? nh?t c?a ô hi?n t?i
            int left = 50 + j * 40;          // T?a ?? x bên trái
            int top = 50 + i * 40;           // T?a ?? y bên trên
            int right = left + 40;           // T?a ?? x bên ph?i
            int bottom = top + 40;           // T?a ?? y bên d??i

            // Ki?m tra n?u con tr? n?m trong ô và là ô tr?ng
            if (point.x >= left && point.x <= right &&
                point.y >= top && point.y <= bottom &&
                banco.mang[i][j].dong == 1) {

                if (lastHoveredRow == i && lastHoveredCol == j) {
                    // Tránh l?p l?i n?u hover v?n trên cùng m?t ô
                    return;
                }

                lastHoveredRow = i;
                lastHoveredCol = j;

                // Tính toán ?i?m hi?n th? menu
                CPoint popupPoint(left + 20, top + 20); // ??t menu g?n góc trái trên c?a ô
                banco.showPopup(popupPoint, this, i, j); // Hi?n th? menu
                return;
            }
        }
    }

    // N?u không hover vào ô nào, reset tr?ng thái
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

            // Yêu c?u v? l?i
            Invalidate();
            UpdateWindow();
            return TRUE;
        }
     
    /*
    int id = LOWORD(wParam);

    // Ki?m tra n?u ID là c?a menu s?
    if (id >= 1001 && id <= 1009) {
        int number = id - 1000; // Chuy?n ??i ID menu thành s? (1-9)

        if (banco.selectedRow != -1 && banco.selectedCol != -1) {
            // ?i?n s? vào ô ???c ch?n
            banco.mang[banco.selectedRow][banco.selectedCol].so = number;
            banco.mang[banco.selectedRow][banco.selectedCol].dong = 0; // ?ánh d?u ô không còn tr?ng

            // Reset v? trí ô ???c ch?n
            banco.selectedRow = -1;
            banco.selectedCol = -1;

            // C?p nh?t giao di?n
            Invalidate();
            UpdateWindow();
        }
        return TRUE; // Command ?ã x? lý
    }
    */
    return CWnd::OnCommand(wParam, lParam);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{

    // TODO: Add your message handler code here and/or call default
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // Xác ??nh t?a ?? c?a ô
            int left = 50 + j * 40;
            int top = 50 + i * 40;
            int right = left + 40;
            int bottom = top + 40;

            // N?u nh?n vào ô và ô ?ó tr?ng
            if (point.x >= left && point.x <= right &&
                point.y >= top && point.y <= bottom &&
                banco.mang[i][j].dong == 1) {

                // L?u l?i ô ???c ch?n
                banco.selectedRow = i;
                banco.selectedCol = j;

                // Hi?n popup menu cho phép ch?n s?
                CPoint popupPoint(left + 20, top + 20);
                banco.showPopup(popupPoint, this, i, j);

                return;
            }
        }
    }

    CWnd::OnLButtonDown(nFlags, point);
}
