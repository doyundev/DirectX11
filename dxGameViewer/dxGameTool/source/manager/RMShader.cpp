#include "stdafx.h"
#include "RMShader.h"


HRESULT RMShader::Init(ID3D11Device * device)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;


	matrixBufferDesc.ByteWidth = sizeof(CameraBuffer);
	if (FAILED(device->CreateBuffer(&matrixBufferDesc, NULL, &_cameraBuffer))) {
		AfxMessageBox(L"Shader Manager Error");
		return E_FAIL;
	}

	matrixBufferDesc.ByteWidth = sizeof(TransBuffer);
	if (FAILED(device->CreateBuffer(&matrixBufferDesc, NULL, &_transBuffer))) {
		AfxMessageBox(L"Shader Manager Error");

		return E_FAIL;
	}

	matrixBufferDesc.ByteWidth = sizeof(ColorBuffer);
	if (FAILED(device->CreateBuffer(&matrixBufferDesc, NULL, &_colorBuffer))) {
		AfxMessageBox(L"Shader Manager Error");

		return E_FAIL;
	}

	matrixBufferDesc.ByteWidth = sizeof(BoneBuffer);
	if (FAILED(device->CreateBuffer(&matrixBufferDesc, NULL, &_boneBuffer))) {
		AfxMessageBox(L"Shader Manager Error");

		return E_FAIL;
	}

	return S_OK;
}

bool RMShader::SetShaderParameters(ID3D11DeviceContext * dc, vector<XMMATRIX>& matBoneList)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;

	//���̴��� ����� ��Ʈ���� ���� �ּҸ� �����´�.
	auto matBuff = _boneBuffer;

	//���� ������ �����Ѵ�.
	if (FAILED(dc->Map(matBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return false;
	}

	//������ ��� ������ ��ġ�� �����´�.
	BoneBuffer* dataPtr = (BoneBuffer*)mappedResource.pData;

	//��� ���� �ѱ��
	for(UINT i = 0; i< matBoneList.size(); i++)
		dataPtr->matBones[i] = matBoneList[i];

	dc->Unmap(matBuff, 0);

	//bufferSturct.h �� ������ ��ġ�ؾ� �Ѵ�.
	bufferNumber = 3;

	dc->VSSetConstantBuffers(bufferNumber, 1, &matBuff);



	return true;
}

bool RMShader::SetShaderParameters(ID3D11DeviceContext * dc, XMMATRIX matWorld)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;

	//���̴��� ����� ��Ʈ���� ���� �ּҸ� �����´�.
	auto matBuff = _transBuffer;

	//���� ������ �����Ѵ�.
	if (FAILED(dc->Map(matBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return false;
	}

	//������ ��� ������ ��ġ�� �����´�.
	TransBuffer* dataPtr = (TransBuffer*)mappedResource.pData;

	//��� ���� �ѱ��
	dataPtr->matWorld = XMMatrixTranspose(matWorld);
	
	dc->Unmap(matBuff, 0);
	
	//bufferSturct.h �� ������ ��ġ�ؾ� �Ѵ�.
	bufferNumber = 1;

	dc->VSSetConstantBuffers(bufferNumber, 1, &matBuff);

	

	return true;
}

bool RMShader::SetShaderParameters(ID3D11DeviceContext * dc, XMMATRIX matView, XMMATRIX matProj)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber =0;

	//���̴��� ����� ��Ʈ���� ���� �ּҸ� �����´�.
	auto matBuff = _cameraBuffer;

	//���� ������ �����Ѵ�.
	if (FAILED(dc->Map(matBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return false;
	}

	//������ ��� ������ ��ġ�� �����´�.
	CameraBuffer* dataPtr = (CameraBuffer*)mappedResource.pData;

	//��� ���� �ѱ��
	dataPtr->matView = XMMatrixTranspose(matView);
	dataPtr->matProj = XMMatrixTranspose(matProj);

	dc->Unmap(matBuff, 0);

	dc->VSSetConstantBuffers(bufferNumber, 1, &matBuff);

	return false;
}

bool RMShader::SetShaderParameters(ID3D11DeviceContext * dc, XMFLOAT4 color)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;

	//���̴��� ����� ��Ʈ���� ���� �ּҸ� �����´�.
	auto buff = _colorBuffer;

	//���� ������ �����Ѵ�.
	if (FAILED(dc->Map(buff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return false;
	}

	//������ ��� ������ ��ġ�� �����´�.
	ColorBuffer* dataPtr = (ColorBuffer*)mappedResource.pData;

	//��� ���� �ѱ��
	dataPtr->fColor = color;
	dc->Unmap(buff, 0);

	bufferNumber = 2;

	dc->VSSetConstantBuffers(bufferNumber, 1, &buff);

	return true;
}


Shader* RMShader::loadResource(wstring fileName, void * param)
{
	//���̴� �߰�.
	
	wstring vsFilename = fileName + L".vs";
	wstring psFilename = fileName + L".ps";


	//���� ���
	Shader* shader = new Shader;
	if (!shader->InsertShader(DEVICEMANAGER.GetDevice(), _hWnd, (WCHAR*)vsFilename.c_str(), (WCHAR*)psFilename.c_str())) {
		SAFE_DELETE(shader);
	}
	
	return shader;
}


void RMShader::releaseResource(Shader* data)
{
	SAFE_DELETE(data);
}

