// ZoneServerDlg.h : 头文件
//

#pragma once

#include "Trace.h"
#include <vector>
#include "afxwin.h"
#include "TraceRichEdit2.h"
#include "afxcmn.h"

using namespace std;
using namespace rkt;

// CZoneServerDlg 对话框
class CZoneServerDlg : public CDialog
{
// 构造
public:
	CZoneServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
private:
	enum { IDD = IDD_ZONESERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:



private:
	afx_msg void	OnBnClickedStart(void);
	afx_msg void	OnBnClickedClose(void);
	afx_msg void	OnBnClickedPerson(void);
	afx_msg void	OnBnClickedCheckEntityTile(void);
	afx_msg void	OnBnClickedRemovePerson(void);
	afx_msg void	OnBnClickedCheckInitTile(void);
	afx_msg void	OnBnClickedTestZoneClone(void);
	afx_msg void	OnBnClickedTestZoneDestory(void);
	afx_msg void	OnBnClickedTestZoneRestore(void);

	afx_msg void OnBnClickedButtonScheme();
	afx_msg void OnBnClickedButtonLua();
	afx_msg void OnBnClickedButtonScanlua();
	afx_msg void OnCbnSetfocusComboScheme();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedCheckInfo();
	afx_msg void OnBnClickedCheckTrace();
	afx_msg void OnBnClickedCheckWarning();
	afx_msg void OnBnClickedCheckError();
	afx_msg void OnEnChangeEditZoneID();
	afx_msg void OnEnChangeEditZoneName();
	afx_msg void OnEnChangeEditCenterIP();
	afx_msg void OnEnChangeEditCenterPort();
	void		InitUIConfig(void);
	void		OnEnChangeEdit(void);
	void		SetViewLevel();

private:
	// TRACE窗口
	TraceRichEdit2	m_MyTraceListener;

	CComboBox m_ComboScheme;
	CEdit m_EditLuaFile;
	CString m_stringLuaFile;
	long m_ZoneServerID;
	CString m_ZoneServerName;
	CString m_CenterServerIP;
	long m_CenterServerPort;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
private:
	UINT m_loginServerPort;
	DWORD m_loginServerIP;
public:
	afx_msg void OnEnChangeLoginServerPort();
	afx_msg void OnIpnFieldchangedLoginServerIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
private:
	UINT m_portForClient;
	UINT m_portForGM;
public:
	afx_msg void OnEnChangeEditZonePort();
	afx_msg void OnEnChangeEditGMPort();
	afx_msg void OnBnClickedLogicErrorLocate();
};

extern CZoneServerDlg * g_pZoneServerDlg;
