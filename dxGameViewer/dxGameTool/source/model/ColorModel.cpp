#include "stdafx.h"
#include "ColorModel.h"

ColorModel::ColorModel()
{
	SetShader(RM_SHADER.AddResource(L"source\\shader\\color"));
}


void ColorModel::Render(ID3D11DeviceContext * dc)
{
	//�޽� ������ ������ ����

	RM_SHADER.SetShaderParameters(dc, _worldMat);

	if (_useColor) {
		RM_SHADER.SetShaderParameters(dc, _color);
	}

	//�������� ���� ���ۼ���
	SetRenderBuffers(dc);

	if (_indexCount != 0)
		GetShader()->IndexRender(dc, _indexCount, 0);
	else
		GetShader()->VertexRender(dc, _vertexCount, 0);
}

void ColorModel::SetColor(XMFLOAT4 color)
{
	_color = color;
}

void ColorModel::TurnOnColor()
{
	_useColor = true;
}

void ColorModel::TurnOffColor()
{
	_useColor = false;
}
