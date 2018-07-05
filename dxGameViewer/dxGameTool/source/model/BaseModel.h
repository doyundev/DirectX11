//====================================================================================
//		## BaseModel ## (���� �⺻������ ��Ƶ� Ŭ����)
//		## ���� ������ �ε��� ���۴� row ptr�� ����ϹǷ� ������ �� �����ؾ� �Ѵ�.
//====================================================================================
#pragma once
#include "..\shader\Shader.h"
#include "ModelStructure.h"


class BaseModel
{
public:
	BaseModel();
	virtual ~BaseModel() {};

	virtual void				Release();
	virtual void				Render(ID3D11DeviceContext* dc)	PURE;
		

	bool						CreateModel(ID3D11Device* device, Vertex& vertices, vector<unsigned long>& indices, 
										D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	template <typename T>
	bool						CreateBuffer(ID3D11Device* device, ID3D11Buffer** buffer, vector<T>& data, bool dynamicBuffer = false);

	bool						InitVertextBuffers(ID3D11Device*, Vertex&, bool dynamicBuffer = false);
	bool						InitIndexBuffers(ID3D11Device*, vector<unsigned long>&);
	
	XMMATRIX					UpdateModelMatrix();
	
	
	//Set Function
	void						SetShader(Shader* shader, bool buildLayoutInfo = true);
	void						SetRenderBuffers(ID3D11DeviceContext* dc);

	void						SetCenter(XMFLOAT3 center) {_center = center;}
	void						SetRotate(XMFLOAT3 rotate) { _rotate = rotate; }
	void						SetSize(XMFLOAT3 size) { _size = size; }
	
	void						SetNormalize(bool isNormalize)						{	_isNormalize = isNormalize;		}	
	void						SetPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY type)		{	_primitiveType = type;			}
	void						SetName(wstring name)								{	_name = name;					}
	void						SetScaleFactor(float scaleFactor)					{	_scaleFactor =scaleFactor;		}
	void						SetIndexCnt(int idxCnt)								{	_indexCount = idxCnt;			}

	//Get Function
	Shader*						GetShader()											{	return	_shader;				}
	bool						IsNormalize()										{	return	_isNormalize;			}
	float						GetScaleFactor()									{	return	_scaleFactor;			}
	wstring						GetName()											{	return	_name;					}
	XMFLOAT3					GetSize()											{	return	_size;					}
	XMFLOAT3					GetRotate()											{	return	_rotate;				}
	XMFLOAT3					GetCenter()											{	return	_center;				}
	VertexDataBuffer*			GetVertexBuffer()									{	return	&_vertexDataBuffer;		}
	
//==================================== ��� ���� =======================================//

protected:
	//���� ������ ����� ������ ����
	VertexDataBuffer			_vertexDataBuffer;

	//vertexDataBuffer���� ���� ���۸� �����Ѵ�.
	vector<ID3D11Buffer**>		_vertexBuffer;							//���ؽ�����
	vector<unsigned int>		_vertexStride;							//���ؽ� ���� ���� ũ��

	ID3D11Buffer*				_indexBuffer;							//�ε��� ����
	wstring						_name;


	XMFLOAT3					_rotate;								//ȸ����
	XMFLOAT3					_center;								//��ġ
	XMFLOAT3					_size;									//ũ��
	XMMATRIX					_tmModel;								//Model TM


	bool						_isNormalize;							//�� ũ�� ����ȭ
	float						_scaleFactor;							//����ȭ�� ���� ũ�� ��
	UINT						_vertexCount, _indexCount;				//���� ���� �� �ε��� ��

	D3D11_PRIMITIVE_TOPOLOGY	_primitiveType;							//������Ƽ��
	Shader*						_shader;								//����� ���̴�
	
};
