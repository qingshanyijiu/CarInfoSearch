#if !defined(AFX_LISTCTRLEXTENTION_H__CA4A6739_6A8B_4AC1_A683_E3389A52C3F1__INCLUDED_)
#define AFX_LISTCTRLEXTENTION_H__CA4A6739_6A8B_4AC1_A683_E3389A52C3F1__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlExtention.h : header file
//

#include <functional>
#include "HeaderCtrlExt.h"

typedef std::tr1::function<void()> MouseWheelCallbackFunc;

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExtention window

class CListCtrlExtention : public CListCtrl
{
// Construction
public:
	CListCtrlExtention();

	void SetMouseWheelCallFunc(MouseWheelCallbackFunc pUpCall,MouseWheelCallbackFunc pDownCall);
	void InitHead();
	int  GetListWidth();

private:
	MouseWheelCallbackFunc	m_pUpCall;
	MouseWheelCallbackFunc	m_pDownCall;

// Attributes
public:

// Operations
public:

public:
	CFont m_NewHeaderFont;
	CHeaderCtrlEx m_HeaderCtrl;
	bool  m_isInitHead;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlExtention)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CListCtrlExtention();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlExtention)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEXTENTION_H__CA4A6739_6A8B_4AC1_A683_E3389A52C3F1__INCLUDED_)
