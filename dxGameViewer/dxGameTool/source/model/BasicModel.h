//====================================================================================
//		## BasicModel ## (������ ��ġ������ ���� ���� ������ ������)
//====================================================================================
#pragma once
#include "BaseModel.h"

class BasicModel : public BaseModel
{
public:
	BasicModel();
	~BasicModel() {};

	virtual void Render(ID3D11DeviceContext* dc);
};
