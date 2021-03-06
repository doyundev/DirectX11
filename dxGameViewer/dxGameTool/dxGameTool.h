#pragma once

#include "resource.h"       // 주 기호입니다.
#include "MainFrm.h"


class CdxGameToolApp : public CWinAppEx
{
public:
	CdxGameToolApp();
	~CdxGameToolApp();

	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual int Run();

protected:
	CMainFrame*	_pFrame;
};

extern CdxGameToolApp		theApp;
