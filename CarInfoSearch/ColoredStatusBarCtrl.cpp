// ColoredStatusBarCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "dlgviewtest.h"
#include "ColoredStatusBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColoredStatusBarCtrl

CColoredStatusBarCtrl::CColoredStatusBarCtrl()
{
	m_statusStrVect.reserve(3);
	m_statusStrVect.push_back("");
	m_statusStrVect.push_back("");
	m_statusStrVect.push_back("");
}

CColoredStatusBarCtrl::~CColoredStatusBarCtrl()
{
}


BEGIN_MESSAGE_MAP(CColoredStatusBarCtrl, CStatusBar)
	//{{AFX_MSG_MAP(CColoredStatusBarCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColoredStatusBarCtrl message handlers

void CColoredStatusBarCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// Attach to a CDC object
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	dc.SetBkMode(TRANSPARENT);

	// Get the pane rectangle and calculate text coordinates
	CRect rect(&lpDrawItemStruct->rcItem);

	switch(lpDrawItemStruct->itemID) 
	{
		case 0:
			dc.SetTextColor(RGB(0, 255, 0));
			break;
		case 1:
			dc.SetTextColor(RGB(255, 0, 0));
			break;
		case 2:
			dc.SetTextColor(RGB(0, 0, 255));
			break;
	}

	dc.TextOut(rect.left+5,rect.top,m_statusStrVect[lpDrawItemStruct->itemID]);
	

	// Detach from the CDC object, otherwise the hDC will be
	// destroyed when the CDC object goes out of scope
	dc.Detach();
}

void CColoredStatusBarCtrl::UpdateRowString(int iRow,const char* lpStarString)
{
	m_statusStrVect[iRow] = lpStarString;
	GetStatusBarCtrl().SetText("", iRow, SBT_OWNERDRAW);
}