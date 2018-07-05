#include "stdafx.h"
#include "SceneManager.h"
#include "scene\gameNode.h"

HRESULT SceneManager::Init(void)
{
	return S_OK;
}

void SceneManager::Release(void)
{
	//�������� ���
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();
}

void SceneManager::Update(void)
{
	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ
	if (_currentScene) _currentScene->Update();
}

void SceneManager::Render(ID3D11DeviceContext* dc)
{
	//������� �����ϸ� �ش��ϴ� ������� ������Ʈ
	if (_currentScene) _currentScene->Render(dc);
}

GameNode * SceneManager::AddScene(string sceneName, GameNode * scene)
{
	//���� ������ �ΰ� ����
	if (!scene) return NULL;

	//���� ������ �ʿ� ����
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã�Ҵٸ�
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������� ����?
	if (find->second == _currentScene) return E_FAIL;

	//������� ������ ���� ������ �� �ʱ�ȭ �ϰ� �������ش�
	if (SUCCEEDED(find->second->Init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

