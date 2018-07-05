#include "stdafx.h"
#include "SimpleTextureModel.h"
#include "GeoEntity.h"

SimpleTextureModel::SimpleTextureModel()
{
	_tex = NULL;
	//�⺻ ���̴�
	SetShader(RM_SHADER.AddResource(L"source\\shader\\texture"));

	//�� ����
	GeoEntity::CreateSquare(DEVICEMANAGER.GetDevice(), this);
}

void SimpleTextureModel::Render(ID3D11DeviceContext *dc)
{
	if (_tex)
		dc->PSSetShaderResources(0, 1, &_tex);

	BasicModel::Render(dc);

}

void SimpleTextureModel::SetTexture(ID3D11ShaderResourceView * texture)
{
	_tex = texture;
}

ID3D11ShaderResourceView * SimpleTextureModel::GetTexture()
{
	return _tex;
}
