//=============================================================
//	## Texture Manager ## (�ε�� �ؽ��� ������ �����Ѵ�.)
//=============================================================
#pragma once
#include "ResourceManager.h"

//Texture Info
struct Texture {
	wstring name					= L"";
	ID3D11ShaderResourceView* data	= NULL;

	~Texture() {
		SAFE_RELEASE(data);
	}
};

class RMTexture : public ResourceManager<Texture*, RMTexture>
{
public:
	RMTexture() {};
	~RMTexture() {};

	//Load Texture
	ID3D11ShaderResourceView* LoadTexture(wstring fileName);

protected:
	//Override
	Texture * loadResource(wstring fileName, void* param=NULL);
	void releaseResource(Texture* data);
};
