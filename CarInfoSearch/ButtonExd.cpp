#include "StdAfx.h"
#include "ButtonExd.h"
CButtonExd::CButtonExd(void)
{
	m_bShow = false;
	m_bExpand = false;
	m_parent = NULL;
	m_pBtn =NULL;
	m_leftpad = 0;
	m_toppad = 0;
	m_index = 0;
	m_rc.SetRect(0,0,0,0);
	m_Name = _T("");
	m_bUseAbsolutePos = false;
	m_all = NULL;
	m_ID = 0;
	m_BeforeLBClickDealFunc = 0;
	m_AfterLBClickDealFunc = 0;
}
CButtonExd::CButtonExd(CWnd* pWnd,CButton* pBtn,LPTSTR Name,long nID ,int leftpad,int toppad)
{
	m_bShow = false;
	m_bExpand = true;
	m_pWnd = pWnd;
	m_parent = NULL;
	m_pBtn =pBtn;
	m_leftpad = leftpad;
	m_toppad = toppad;
	m_index = 0;
	m_rc.SetRect(0,0,0,0);
	m_Name.Format(_T("%s"),Name);
	m_bUseAbsolutePos = false;
	m_all = NULL;
	m_ID = nID;
	m_BeforeLBClickDealFunc = 0;
	m_AfterLBClickDealFunc = 0;
}
CButtonExd::~CButtonExd(void)
{
	for (int i=0;i<m_Childs.size();++i)
	{
		delete m_Childs[i];
	}
	m_Childs.clear();
	if(IsRoot()&& m_all!=NULL)
		delete m_all;
}
void CButtonExd::Move(int leftpad,int toppad)
{
	CRect rc;
	m_pBtn->GetWindowRect(&rc);
	m_pWnd->ScreenToClient(&rc);
	rc.left+=leftpad;
	rc.bottom+=toppad;
	rc.right+=leftpad;
	rc.top+=toppad;
	m_pBtn->MoveWindow(rc);
	m_rc.OffsetRect(leftpad,toppad);
	for (int i=0;i<m_Childs.size();++i)
	{
		m_Childs[i]->Move(leftpad,toppad);
	}
}
void CButtonExd::Revise(int leftpad,int toppad)
{
	if(m_parent == NULL ||(leftpad==0 && toppad==0))
		return;
	if(toppad<0)
	{
		for (int i=m_index+1;i<m_parent->m_Childs.size();++i)
		{
			if(!m_parent->m_Childs[i]->m_bUseAbsolutePos)
				m_parent->m_Childs[i]->Move(leftpad,toppad);
		}
	}
	else
	{
		for (int i=m_parent->m_Childs.size()-1;i>m_index;--i)
		{
			if(!m_parent->m_Childs[i]->m_bUseAbsolutePos)
				m_parent->m_Childs[i]->Move(leftpad,toppad);
		}
	}
	m_parent->Revise(leftpad,toppad);
}
CRect CButtonExd::Show(bool NeedRevise,int leftpad,int toppad,bool bdelay ,CArray<CButton*>* pButtons )
{
	if(m_bShow ||(m_parent!=NULL&&m_parent->m_bShow == false))
		return m_rc;
	m_bShow = true;
	CRect beforeCuurentRC = m_rc;
	CButtonExd* pCompareButton = NULL;
	if(m_index >0 && m_parent!=NULL)
		pCompareButton =m_parent->m_Childs[m_index-1];
	else
		pCompareButton = m_parent;
	if(pCompareButton != NULL)
	{
		if(!pCompareButton->IsRoot()&&!m_bUseAbsolutePos)
		{
			CRect rc_c;
			pCompareButton->m_pBtn->GetWindowRect(&rc_c);
			m_pWnd->ScreenToClient(&rc_c);
			m_pBtn->GetWindowRect(&m_rc);
			int width = m_rc.Width();
			int height = m_rc.Height();
			m_rc.left = rc_c.left+m_leftpad+leftpad;
			m_rc.right = rc_c.left+m_leftpad+leftpad+width;
			m_rc.top = rc_c.bottom+m_toppad+toppad;
			m_rc.bottom = rc_c.bottom+m_toppad+toppad+height;
			m_pBtn->MoveWindow(m_rc.left,m_rc.top,m_rc.Width(),m_rc.Height());
		}
		else
		{
			m_pBtn->GetWindowRect(m_rc);
			m_pWnd->ScreenToClient(&m_rc);
		}
		if(bdelay && pButtons!=NULL)
			pButtons->Add(m_pBtn);
		else
			m_pBtn->ShowWindow(SW_SHOW);
	}	
	if(m_bExpand)
	{
		CRect RetRect,UnionRC;
		int childtoppad = 0;
		for (int i=0;i<m_Childs.size();++i)
		{
			CRect beforeRC = m_Childs[i]->m_rc;
			RetRect = m_Childs[i]->Show();
			childtoppad =toppad + RetRect.bottom-beforeRC.bottom;
			UnionRC.UnionRect(m_rc,RetRect);
			m_rc = UnionRC;
		}
	}	
	if(NeedRevise)
		Revise(0,m_rc.bottom-beforeCuurentRC.bottom);
	return m_rc;
}
CRect CButtonExd::Hide(bool NeedRevise)
{
	if(!m_bShow ||(m_parent!=NULL&&m_parent->m_bShow == false))
		return m_rc;
	m_bShow = false;
	m_pBtn->ShowWindow(SW_HIDE);
	if(m_bExpand)
	{
		CRect RetRect;
		for (int i=0;i<m_Childs.size();++i)
			RetRect = m_Childs[i]->Hide();
	}	
	if(NeedRevise)
		Revise(0,m_rc.top-m_rc.bottom);
	CRect retRect = m_rc;
	m_rc.SetRectEmpty();
	return retRect;
}
void CButtonExd::AddChild(CButtonExd* pChild)
{
	m_Childs.push_back(pChild);
	pChild->m_parent = this;
	pChild->m_index = m_Childs.size()-1;
	pChild->m_bShow = false;
	pChild->m_pBtn->ShowWindow(SW_HIDE);
	pChild->RemoveFromBtnMap(pChild->m_ID);
	AddToBtnMap(pChild->m_ID,pChild);
	pChild->m_all = m_all;
}
CRect CButtonExd::Expand()
{
	if(m_bExpand)
		return m_rc;
	m_bExpand = true;
	CRect RetRect,UnionRC;
	int childtoppad = 0;
	CRect beforeCuurentRC = m_rc;
	CArray<CButton*>* pButtons = new CArray<CButton*>();
	for (int i=0;i<m_Childs.size();++i)
	{
		CRect beforeRC = m_Childs[i]->m_rc;
		RetRect = m_Childs[i]->Show(false,0,0,true,pButtons);
		childtoppad =RetRect.bottom-beforeRC.bottom;
		UnionRC.UnionRect(m_rc,RetRect);
		m_rc = UnionRC;
	}
	Revise(0,m_rc.bottom-beforeCuurentRC.bottom);
	for (int i=0;i<pButtons->GetCount();++i)
	{
		pButtons->GetAt(i)->ShowWindow(SW_SHOW);
	}
	return m_rc;
}
CRect CButtonExd::Folded()
{
	if(!m_bExpand)
		return m_rc;
	m_bExpand = false;
	for (int i=0;i<m_Childs.size();++i)
		m_Childs[i]->Hide();
	CRect rc;
	m_pBtn->GetWindowRect(&m_rc);
	m_pWnd->ScreenToClient(&m_rc);
	m_pBtn->GetWindowRect(&rc);
	if(m_index<m_parent->m_Childs.size()-1)
		Revise(0,-(m_parent->m_Childs[m_index+1]->m_rc.top-m_rc.bottom-m_parent->m_Childs[m_index+1]->m_toppad));
	
	return m_rc;
}
bool CButtonExd::OnLBClick()
{
	if(m_BeforeLBClickDealFunc)
		m_BeforeLBClickDealFunc(this);
	if(m_bExpand)
		Folded();
	else
		Expand();
	if(m_AfterLBClickDealFunc)
		m_AfterLBClickDealFunc(this);
	return true;
}
bool CButtonExd::OnCommond(CButtonExd* pRootBtn,WPARAM wParam,LPARAM lParam)
{
	long ID = LOWORD(wParam);
	BtnMapType::iterator iter = pRootBtn->m_all->find(ID);
	if(iter == pRootBtn->m_all->end())
		return false;
	int iEvent = HIWORD(wParam);
	switch(iEvent)
	{
	case BN_CLICKED:
		iter->second->OnLBClick();
		break;
	default:
		return false;
	}
	return true;
}
void CButtonExd::InitBtnMap()
{
	if(m_parent != NULL)
		return;
	if (m_all == NULL)
	{
		m_all = new BtnMapType();
		m_all->insert(std::make_pair(m_ID,this));
	}
}
bool CButtonExd::AddToBtnMap(long ID,CButtonExd* pBtn)
{
	if(m_all == NULL)
		return false;
	m_all->insert(std::make_pair(ID,pBtn));
	return true;
}
bool CButtonExd::RemoveFromBtnMap(long ID)
{
	if(m_all == NULL)
		return false;
	BtnMapType::iterator iter = m_all->find(ID);
	if(iter == m_all->end())
		return false;
	m_all->erase(iter);
	return true;
}
