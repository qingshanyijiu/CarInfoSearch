#pragma once
#include <vector>
#include <map>
#include <functional>
class CButtonExd;
typedef std::tr1::function<void(CButtonExd*)> LBClickCallbackFunc;
typedef LBClickCallbackFunc BeforeLBClickDealFunc;
typedef LBClickCallbackFunc AfterLBClickDealFunc;
class CButtonExd
{
public:
	typedef std::map<long, CButtonExd*> BtnMapType;
	std::vector<CButtonExd*> m_Childs;
private:
	long m_ID;
	CString m_Name;
	CButton* m_pBtn;
	CWnd* m_pWnd;//父窗体，也是当前整个树结构上的父窗体，主要用到坐标转换
	CButtonExd* m_parent;
	bool m_bShow;
	bool m_bExpand;
	bool m_bUseAbsolutePos;
	int m_leftpad;//相对前一个节点的偏移（1.当前Index=0,则前一个节点是parent 2.其他情况，则是兄弟节点index-1）
	int m_toppad;
	int m_index;
	CRect m_rc;
	BtnMapType* m_all;
	BeforeLBClickDealFunc  m_BeforeLBClickDealFunc;
	AfterLBClickDealFunc  m_AfterLBClickDealFunc;
public:
	static bool OnCommond(CButtonExd* pRootBtn,WPARAM wParam,LPARAM lParam);
	CRect Show(bool NeedRevise = false,int leftpad = 0,int toppad = 0,bool bdelay =false,CArray<CButton*>* pButtons = NULL);
	CRect Hide(bool NeedRevise = false);
	CRect Expand();
	CRect Folded();
	void AddChild(CButtonExd* pChild);
	void Move(int leftpad,int toppad);
	void Revise(int leftpad,int toppad);
	void InitBtnMap();
	void SetBeforeLBClickDealFunc(BeforeLBClickDealFunc func)
	{
		m_BeforeLBClickDealFunc = func;
	}
	void SetAfterLBClickDealFunc(AfterLBClickDealFunc func)
	{
		m_AfterLBClickDealFunc = func;
	}
	bool IsRoot()
	{
		return m_parent == NULL;
	}
	void SetAbsolutePos(bool abspos)
	{
		m_bUseAbsolutePos = abspos;
	}
	bool IsAbsolutePos()
	{
		return m_bUseAbsolutePos;
	}
	bool IsExpand()
	{
		return m_bExpand;
	}
	CString GetName()
	{
		return m_Name;
	}
	bool IsShow()
	{
		return m_bShow;
	}
	CRect GetRect()
	{
		return m_rc;
	}
	int GetIndex()
	{
		return m_index;
	}

private:
	bool AddToBtnMap(long ID,CButtonExd* pBtn);
	bool RemoveFromBtnMap(long ID);
	bool OnLBClick();
	
public:
	CButtonExd(void);
	~CButtonExd(void);
	CButtonExd(CWnd* pWnd,CButton* pBtn,LPTSTR Name,long nID,int leftpad=0,int toppad=0);
private:
	CButtonExd(CButtonExd&);
};
