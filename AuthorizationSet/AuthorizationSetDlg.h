
// AuthorizationSetDlg.h : ͷ�ļ�
//

#pragma once


// CAuthorizationSetDlg �Ի���
class CAuthorizationSetDlg : public CDialogEx
{
// ����
public:
	CAuthorizationSetDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTHORIZATIONSET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonGetLocalMac();
	afx_msg void OnBnClickedButtonCreateCode();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};
