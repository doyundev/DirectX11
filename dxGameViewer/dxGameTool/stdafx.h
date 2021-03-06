
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"
#include "resource.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#define _XM_NO_INTRINSICS_

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.



#include <iostream>
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// STL 컨테이너 헤더파일
#include <string>
#include <vector>
#include <list>
#include <map>

#include <memory>
using namespace std;

// DIRECT3D 헤더 및 라이브러리 추가
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#include <DirectXMath.h>
using namespace DirectX;



//====================================================================
//			## 사용자 메시지 ##
//====================================================================
#define WM_INSERT_MODEL		WM_USER + 1
#define WM_DELETE_MODEL		WM_USER + 2
#define WM_VISIBLE_DLG		WM_USER + 3

#define WM_UPDATE_COMMAND	WM_USER + 4

//====================================================================
//			## 메크로함수 ## (클래스 동적할당된 부분 해제)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = NULL;}}

//====================================================================
//			## 매크로 변수 ##
//====================================================================
#define WINSIZEX	1680
#define WINSIZEY	1050

//====================================================================
//			## 내가 만든 헤더파일을 이곳에 추가한다 ##
//====================================================================
#include "manager\DeviceManager.h"
#include "manager\KeyManager.h"
#include "manager\TimeManager.h"
#include "manager\SceneManager.h"


#include "manager\RMTexture.h"
#include "manager\GameFont.h"
#include "manager\RMShader.h"
#include "manager\RMModel.h"


#include "util\MYUTIL.h"
#include "util\Camera.h"

//====================================================================
//			## 전역 변수 ##
//====================================================================
extern HWND		_hWnd;
extern Camera	_mainCam;


//====================================================================
//			## 싱글톤으로 사용되는 매니저 ##
//====================================================================
#define DEVICEMANAGER DeviceManager::GetSingleton()
#define KEYMANAGER KeyManager::GetSingleton()
#define TIMEMANAGER TimeManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()

#define RM_SHADER RMShader::GetSingleton()
#define RM_TEXTURE RMTexture::GetSingleton()
#define FONTMANAGER GameFont::GetSingleton()
#define RM_MODEL RMModel::GetSingleton()




#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
#include <afxwin.h>



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


