#include "stdafx.h"
#include "MainGame.h"


PWindowRender GameNode::_sceneInfo = NULL;

//==================================================================
//		## �ʱ�ȭ ## Init(void)
//==================================================================
HRESULT MainGame::Init(void)
{
	_sceneInfo = DEVICEMANAGER.InitRenderScreen(_hWnd, WINSIZEX, WINSIZEY, 0.1f, 1000.f);
	InitScene();

	return S_OK;
}


//==================================================================
//		## Scene ���� ## InitScene(void)
//==================================================================
HRESULT MainGame::InitScene()
{
	//�� �߰� �� ����
	SCENEMANAGER.AddScene("test", new TestScene);
	SCENEMANAGER.ChangeScene("test");

	return S_OK;
}




//==================================================================
//		## ������Ʈ ## Update(void)
//==================================================================
void MainGame::Update(void)
{
	TIMEMANAGER.Update(0.0f);
	
	
	TCHAR buff[255];
	wsprintf(buff, L"������ ���� : %d", TIMEMANAGER.GetFrameRate());
	FONTMANAGER.Print(buff, 30, 80, 20, XMFLOAT3(1,1,0));


	if (DEVICEMANAGER.IsVSync()) {
		FONTMANAGER.Print(L"��������ȭ(F3) : On", 30, 180);
	}
	else {
		FONTMANAGER.Print(L"��������ȭ(F3) : Off", 30, 180);
	}

	SCENEMANAGER.Update();
	_sceneInfo->viewMatrix = _mainCam.Update(TIMEMANAGER.GetElapedTime());
}


//==================================================================
//		## ���� ## render(void)
//==================================================================
void MainGame::Render(ID3D11DeviceContext* dc)
{	
	DEVICEMANAGER.BeginScene(_sceneInfo, 0, 0, 0, 1);
	
	//���� �� �� ��� ����
	RM_SHADER.SetShaderParameters(dc, _sceneInfo->viewMatrix, _sceneInfo->projectionMatrix);
	SCENEMANAGER.Render(dc);

	//������� : ������ķ� ����
	RM_SHADER.SetShaderParameters(dc, XMMatrixTranslation(0, 0, 1), _sceneInfo->orthoMatrix);
	FONTMANAGER.Render(dc);
	
	DEVICEMANAGER.EndScene(_sceneInfo);
}

