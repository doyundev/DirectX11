//==================================================================
//		## sceneManager ## (�� �Ŵ���)
//==================================================================
#pragma once
#include "SingletonBase.h"


//���ӳ�� Ŭ���� ���漱��
class GameNode;

class SceneManager : public SingletonBase <SceneManager>
{
private:
	typedef map<string, GameNode*> mSceneList;
	typedef map<string, GameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//������ ��(ȭ��)���� ��Ƶ� ��
	GameNode* _currentScene;	//�����
public:
	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(ID3D11DeviceContext* dc);


	//���߰�
	GameNode* AddScene(string sceneName, GameNode* scene);

	//������
	HRESULT ChangeScene(string sceneName);

	SceneManager() : _currentScene(NULL) {}
	~SceneManager() {}
};