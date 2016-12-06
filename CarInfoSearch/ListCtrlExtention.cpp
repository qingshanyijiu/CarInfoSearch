// ListCtrlExtention.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderCtrlExt.h"
#include "ListCtrlExtention.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExtention

CListCtrlExtention::CListCtrlExtention()
{
	m_pUpCall = NULL;
	m_pDownCall = NULL;
	m_isInitHead = false;
}

CListCtrlExtention::~CListCtrlExtention()
{
}


BEGIN_MESSAGE_MAP(CListCtrlExtention, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlExtention)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExtention message handlers

int CListCtrlExtention::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	m_NewHeaderFont.CreatePointFont(190,"MS Serif");

	CHeaderCtrl* pHeader = NULL;
	pHeader=GetHeaderCtrl();

	if(pHeader==NULL)
		return -1;
	
	VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));	

	m_HeaderCtrl.SetFont(&m_NewHeaderFont);
	HDITEM hdItem;

	hdItem.mask = HDI_FORMAT;

	for(int i=0; i<m_HeaderCtrl.GetItemCount(); i++)
	{
		m_HeaderCtrl.GetItem(i,&hdItem);

		hdItem.fmt|= HDF_OWNERDRAW;
		
		m_HeaderCtrl.SetItem(i,&hdItem);
	}
	return 0;


}


void CListCtrlExtention::InitHead()
{
	if (!m_isInitHead)
	{
		m_isInitHead = true;
		m_NewHeaderFont.CreatePointFont(165,"MS Serif");
	}

	CHeaderCtrl* pHeader = NULL;
	pHeader=GetHeaderCtrl();

	if(pHeader==NULL)
		return ;

	VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));	

	m_HeaderCtrl.SetFont(&m_NewHeaderFont);
	HDITEM hdItem;

	hdItem.mask = HDI_FORMAT;

	for(int i=0; i<m_HeaderCtrl.GetItemCount(); i++)
	{
		m_HeaderCtrl.GetItem(i,&hdItem);

		hdItem.fmt|= HDF_OWNERDRAW;

		m_HeaderCtrl.SetItem(i,&hdItem);
	}
}

int  CListCtrlExtention::GetListWidth()
{
	CRect rect;
	GetWindowRect(&rect);

	return rect.Width()-20;
}

void CListCtrlExtention::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// ´Ë¹¦ÄÜÒªÇó Windows Vista »ò¸ü¸ß°æ±¾¡£
	// _WIN32_WINNT ·ûºÅ±ØÐë >= 0x0600¡£
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ


}


BOOL CListCtrlExtention::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ

	if (zDelta>20)
	{
		if (m_pUpCall)
		{
			m_pUpCall();
			return TRUE;
		}
		
	}
	else if (zDelta<-20)
	{
		if (m_pDownCall)
		{
			m_pDownCall();
			return TRUE;
		}
	}

	CListCtrl::OnMouseHWheel(nFlags, zDelta, pt);

	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}


void CListCtrlExtention::SetMouseWheelCallFunc(MouseWheelCallbackFunc pUpCall,MouseWheelCallbackFunc pDownCall)
{
	m_pUpCall = pUpCall;
	m_pDownCall = pDownCall;
}