//====================================================================================
//		## SimpleTextureModel ## (���� �ؽ��ĸ� �������ϴ� Square Model)
//====================================================================================
#pragma once
#include "BasicModel.h"

class SimpleTextureModel : public BasicModel
{
public:
	SimpleTextureModel();
	~SimpleTextureModel() {};

	virtual void Render(ID3D11DeviceContext* dc);
	
	void SetTexture(ID3D11ShaderResourceView* texture);
	ID3D11ShaderResourceView* GetTexture();

protected:
	ID3D11ShaderResourceView* _tex = NULL;
};
