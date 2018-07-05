#include "stdafx.h"
#include "BaseModel.h"


//���� �ʱ�ȭ
BaseModel::BaseModel()
{
	_vertexCount = 0;
	_indexCount = 0;

	_indexBuffer = NULL;

	_isNormalize = false;
	_name = L"";

	_primitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	_rotate		=	XMFLOAT3(0.f, 0.f, 0.f);									
	_center		=	XMFLOAT3(0.f, 0.f, 0.f);
	_size		=	XMFLOAT3(1.f, 1.f, 1.f);

	
	_shader = NULL; ;
	_scaleFactor = 1.f;								
	
}

//���� �޸� ����
void BaseModel::Release()
{
	SAFE_RELEASE(_indexBuffer);
	
	SAFE_RELEASE(_vertexDataBuffer.positionBuffer);
	SAFE_RELEASE(_vertexDataBuffer.colorBuffer);
	SAFE_RELEASE(_vertexDataBuffer.texcoordBuffer);
	SAFE_RELEASE(_vertexDataBuffer.normalBuffer);
	SAFE_RELEASE(_vertexDataBuffer.tangentBuffer);
	SAFE_RELEASE(_vertexDataBuffer.bitangentBuffer);
}

bool BaseModel::CreateModel(ID3D11Device* device, Vertex& vertices, vector<unsigned long>& indices,	D3D11_PRIMITIVE_TOPOLOGY type)
{	

	//���� ���� ������ ����
	if (vertices.position.empty()) { return false; }

	_primitiveType = type;
	float maxSize = 0.f;


	//Scale Factor ���ϱ�
	//���� ��ġ �������� ���� ū ���� �����´�.
	for (auto vertex : vertices.position) {
		maxSize = XMMax(maxSize, abs(vertex.x));
		maxSize = XMMax(maxSize, abs(vertex.y));
		maxSize = XMMax(maxSize, abs(vertex.z));
	}

	_scaleFactor = 1.f / maxSize;

	//���ؽ� ���� ����
	if (!InitVertextBuffers(device, vertices)) {
		_vertexCount = 0;
		return false;
	}

	//�ε��� ������ ������ �ε��� ���� ����
	if (!indices.empty()) {
		if (!InitIndexBuffers(device, indices)) {
			_indexCount = 0;
		}
	}

	

	return true;
}

//���� ���� ����
bool BaseModel::InitVertextBuffers(ID3D11Device* device, Vertex &vertices, bool dynamicBuffer)
{
	_vertexCount = (UINT)vertices.position.size();

	//������ ��ġ ������ ������ ��ȯ
	if (vertices.position.empty()) {
		return false;
	}

	//��ġ ���� ����
	if (!CreateBuffer(device, &_vertexDataBuffer.positionBuffer, vertices.position, dynamicBuffer)) {
		_vertexCount = 0;
		return false;
	}

	//���� ���� ����
	CreateBuffer(device, &_vertexDataBuffer.colorBuffer, vertices.color, dynamicBuffer);			
	//UV ���� ����
	CreateBuffer(device, &_vertexDataBuffer.texcoordBuffer, vertices.uv, dynamicBuffer);
	//���� ���� ����
	CreateBuffer(device, &_vertexDataBuffer.normalBuffer, vertices.normal, dynamicBuffer);
	//ź��Ʈ ���� ����
	CreateBuffer(device, &_vertexDataBuffer.tangentBuffer, vertices.tangent, dynamicBuffer);
	//���� ź��Ʈ ���� ����
	CreateBuffer(device, &_vertexDataBuffer.bitangentBuffer, vertices.bitangent, dynamicBuffer);
	//�� �ε��� ���� ����
	CreateBuffer(device, &_vertexDataBuffer.boneIdBuffer, vertices.boneidx, dynamicBuffer);
	//����ġ ���� ����
	CreateBuffer(device, &_vertexDataBuffer.weightBuffer, vertices.weight, dynamicBuffer);


	return true;
}

bool BaseModel::InitIndexBuffers(ID3D11Device* device, vector<unsigned long>& indices)
{
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;
	_indexCount = (UINT)indices.size();

	//�������� ����(��� ����, ũ��, ��Ÿ)
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * _indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Set Index Data
	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &_indexBuffer);
	if (FAILED(result)) { return false; }



	return true;

}

//���� �� �ε��� ���� ����
void BaseModel::SetRenderBuffers(ID3D11DeviceContext* dc)
{
	unsigned int offset = 0;

	//���� ���� ����
	for (unsigned int i = 0; i < _vertexBuffer.size(); i++) {
		dc->IASetVertexBuffers(i, 1, _vertexBuffer[i], &_vertexStride[i], &offset);
	}

	//�ε��� ������ ������ �ε��� ���� ����
	if (_indexBuffer) {
		dc->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	//���� ������ Ÿ�� ����
	dc->IASetPrimitiveTopology(_primitiveType);
}


//�� ��� �籸��
XMMATRIX BaseModel::UpdateModelMatrix()
{
	//ũ��
	if (_isNormalize) {
		_tmModel = XMMatrixScaling(_size.x * _scaleFactor, _size.y * _scaleFactor, _size.z * _scaleFactor);
	}
	else {
		_tmModel = XMMatrixScaling(_size.x, _size.y, _size.z);
	}
	
	//ȸ��
	_tmModel = XMMatrixMultiply(_tmModel, XMMatrixRotationX(_rotate.x));
	_tmModel = XMMatrixMultiply(_tmModel, XMMatrixRotationY(_rotate.y));
	_tmModel = XMMatrixMultiply(_tmModel, XMMatrixRotationZ(_rotate.z));

	//�̵�
	_tmModel = XMMatrixMultiply(_tmModel, XMMatrixTranslation(_center.x, _center.y, _center.z));
	
	return _tmModel;
}

//���� �������� ���̴� ����
//���̴� ����� ���̴��� ���� ���̾ƿ� ������ ��������
//�𵨿��� ���� ���� ���� ������ �籸���Ѵ�.
void BaseModel::SetShader(Shader * shader, bool buildLayoutInfo)
{	
	//���̴� ����
	_shader = shader;

	if (!shader || !buildLayoutInfo) return;

	//���̴��� ���� �Է� ������ �����´�.
	auto desc = shader->GetVertexLayoutDesc();

	//���� �ʱ�ȭ
	_vertexBuffer.clear();	//�������� ���� ���ؽ� ����
	_vertexStride.clear();	//�� ���ۿ� ���� ������ ũ��
	
	//���� ���̾ƿ� ������ �������� ���� ���� �籸��
	for (auto vertexItem : desc) {
		if (_stricmp(vertexItem.SemanticName, "POSITION") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.positionBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT3));
		}
		else if (_stricmp(vertexItem.SemanticName, "COLOR") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.colorBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT4));
		}
		else if (_stricmp(vertexItem.SemanticName, "TEXCOORD") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.texcoordBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT2));
		}
		else if (_stricmp(vertexItem.SemanticName, "NORMAL") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.normalBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT3));
		}
		else if (_stricmp(vertexItem.SemanticName, "TANGENT") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.tangentBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT3));
		}
		else if (_stricmp(vertexItem.SemanticName, "BITANGENT") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.bitangentBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT3));
		}
		else if (_stricmp(vertexItem.SemanticName, "BONEID") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.boneIdBuffer);
			_vertexStride.push_back(sizeof(XMUINT4));
		}
		else if (_stricmp(vertexItem.SemanticName, "WEIGHT") == 0) {
			_vertexBuffer.push_back(&_vertexDataBuffer.weightBuffer);
			_vertexStride.push_back(sizeof(XMFLOAT4));
		}
	}
}

//���� ����
template<typename T>
bool BaseModel::CreateBuffer(ID3D11Device* device, ID3D11Buffer** buffer, vector<T>& data, bool dynamicBuffer)
{
	D3D11_BUFFER_DESC bufferDesc;
	D3D11_SUBRESOURCE_DATA bufferData;

	if (data.empty()) {
		return false;
	}

	//�������� ����(��� ����, ũ��, ��Ÿ)
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (UINT)(sizeof(T) * data.size());
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	if (dynamicBuffer) {
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}


	//Set Vertex Data
	bufferData.pSysMem = &data[0];
	bufferData.SysMemPitch = 0;
	bufferData.SysMemSlicePitch = 0;
	
	if (FAILED(device->CreateBuffer(&bufferDesc, &bufferData, buffer))) {
		return false;
	};
	

	return true;
}
