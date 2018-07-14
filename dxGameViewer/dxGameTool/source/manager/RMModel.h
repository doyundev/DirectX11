//=============================================================
//	## RMModel ## (�ε�� �𵨸� ���� ������ �����Ѵ�.)
//=============================================================
#pragma once

#include "ResourceManager.h"
#include "model/SkinModel.h"
#include "util/loader/ModelLoader.h"

class RMModel : public ResourceManager<SkinModel*, RMModel>
{
public:
	RMModel() {};
	~RMModel() {};

	//�� �ε�
	SkinModel* loadResource(wstring fileName, void* param= nullptr);

	//�� ����
	void releaseResource(SkinModel* data);
};
