//=============================================================
//	## RMShader ## (�ε�� ���̴� ������ �����Ѵ�.)
//=============================================================
#pragma once
#include "ResourceManager.h"
#include "shader\Shader.h"


struct CameraBuffer
{
	XMMATRIX matView;
	XMMATRIX matProj;
};

struct TransBuffer
{
	XMMATRIX matWorld;
};

struct ColorBuffer
{
	XMFLOAT4 fColor;
};

struct BoneBuffer
{
	XMMATRIX matBones[128];
};

class RMShader : public ResourceManager<Shader*, RMShader>
{
	
public:
	RMShader() {};
	~RMShader() {};

	HRESULT Init(ID3D11Device* device);

	bool SetShaderParameters(ID3D11DeviceContext * dc, vector<XMMATRIX>& matBoneList);
	bool SetShaderParameters(ID3D11DeviceContext * dc, XMMATRIX matWorld);
	bool SetShaderParameters(ID3D11DeviceContext * dc, XMMATRIX matView, XMMATRIX matProj);
	bool SetShaderParameters(ID3D11DeviceContext * dc, XMFLOAT4 color);

protected:
	Shader* loadResource(wstring fileName, void* param=nullptr);
	void releaseResource(Shader* data);
private:
	ID3D11Buffer*			_transBuffer	= nullptr;
	ID3D11Buffer*			_cameraBuffer	= nullptr;
	ID3D11Buffer*			_colorBuffer	= nullptr;
	ID3D11Buffer*			_boneBuffer		= nullptr;
	
};
