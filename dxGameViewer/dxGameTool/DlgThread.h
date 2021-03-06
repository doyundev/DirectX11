#pragma once

#include "dlg\ModelDlg.h"
#include "dlg\RenderStateDlg.h"
#include "dlg\TextureDlg.h"

// DlgThread

class DlgThread : public CWinThread
{
	DECLARE_DYNCREATE(DlgThread)

protected:
	afx_msg void TurnDlgState(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DlgThread();    
	virtual ~DlgThread();

private:
	bool	_dlgVisible = TRUE;
	vector<unique_ptr<CDialog>>		_dlgList;
	
};


