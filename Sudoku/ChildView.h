
// ChildView.h : interface of the CChildView class
//

#define ID_NUMBER_1  33001
#define ID_NUMBER_2  33002
#define ID_NUMBER_3  33003
#define ID_NUMBER_4  33004
#define ID_NUMBER_5  33005
#define ID_NUMBER_6  33006
#define ID_NUMBER_7  33007
#define ID_NUMBER_8  33008
#define ID_NUMBER_9  33009


#pragma once
#include "CHcn.h"
#include "Banco.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	CHcn hcn;
	Banco banco;
	//
	
	// 
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

