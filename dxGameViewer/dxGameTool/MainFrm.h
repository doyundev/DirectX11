//====================================================================
//			## MainFrm.h ## (CMainFrame 클래스)
//====================================================================

#pragma once
#include "scene\mainGame.h"

#include "DlgThread.h"


class CMainFrame : public CFrameWnd
{
	//msg event
	DECLARE_DYNAMIC(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
	
public:
	//Default Func
	CMainFrame();
	virtual ~CMainFrame();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	//Msg Process 
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);


public:
	//System Init
	HRESULT Init();

	//System Main Event
	void MainLoop();

	//System Release
	void Release();

private:
	//Camera Update
	void UpdateMainCamera();
	void UpdateSystemKeyEvent();


	//Init Singltone Class
	HRESULT	InitManager();

private:
	//MainGame 클래스			
	unique_ptr<MainGame>			_mg = nullptr;

	//DC
	ID3D11DeviceContext*			_mainDC = nullptr;

	//DLG UI Thread
	CWinThread*						_dlgUIThread;
	HANDLE							_hUIThread;

	//mouse Flag
	BOOL							_mouseEvent;

};


