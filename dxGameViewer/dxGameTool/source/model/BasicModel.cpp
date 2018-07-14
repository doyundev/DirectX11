#include "stdafx.h"
#include "BasicModel.h"


BasicModel::BasicModel()
{
	SetShader(RM_SHADER.AddResource(L"source\\shader\\basic"));
}


void BasicModel::Render(ID3D11DeviceContext * dc)
{
	//���� ������ ������ ����
	if (_vertexCount<=0) 	return;

	//model tm
	RM_SHADER.SetShaderParameters(dc, UpdateModelMatrix());

	//�������� ���� ���ۼ���
	SetRenderBuffers(dc);

	if (_indexCount != 0)
		GetShader()->IndexRender(dc, _indexCount, 0);
	else
		GetShader()->VertexRender(dc, _vertexCount, 0);
	
}
