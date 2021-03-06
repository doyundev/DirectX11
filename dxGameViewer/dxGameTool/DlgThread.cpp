// DlgThread.cpp: 구현 파일
//

#include "stdafx.h"
#include "dxGameTool.h"
#include "DlgThread.h"


// DlgThread

IMPLEMENT_DYNCREATE(DlgThread, CWinThread)

BEGIN_MESSAGE_MAP(DlgThread, CWinThread)
	ON_THREAD_MESSAGE(WM_VISIBLE_DLG, TurnDlgState)
END_MESSAGE_MAP()

DlgThread::DlgThread()
{
}

DlgThread::~DlgThread()
{
}

void DlgThread::TurnDlgState(WPARAM wParam, LPARAM lParam)
{
	for (auto& dlg : _dlgList) {
		if (_dlgVisible)
			dlg->ShowWindow(SW_HIDE);
		else
			dlg->ShowWindow(SW_SHOW);
	}
	
	_dlgVisible = !_dlgVisible;

}



BOOL DlgThread::InitInstance()
{
	_dlgList.emplace_back(make_unique<ModelDlg>());
	_dlgList.emplace_back(make_unique<RenderStateDlg>());
	_dlgList.emplace_back(make_unique<TextureDlg>());
	

	for (auto& dlg : _dlgList) {
		dlg->ShowWindow(SW_SHOW);
	}
	return TRUE;
}

int DlgThread::ExitInstance()
{

	return CWinThread::ExitInstance();
}

BOOL DlgThread::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_INSERT_MODEL || pMsg->message == WM_DELETE_MODEL) {
		for (auto& dlg : _dlgList) {
			dlg->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		}
	}

	return CWinThread::PreTranslateMessage(pMsg);
}
