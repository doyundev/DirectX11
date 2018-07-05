#pragma once

//Vertex Info, ���߿� normal ���� �߰�
struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT4 color;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
	
	XMFLOAT4 tangent;
	XMFLOAT3 bitangent;
};

struct Material
{
	wstring name;
	
	Texture* diffuseMap;
	Texture* alphaMap;
	Texture* normalMap;
	Texture* sepcularMap;
	Texture* lightMap;

	Material() {
		diffuseMap	= NULL;
		alphaMap	= NULL;
		normalMap	= NULL;
		sepcularMap = NULL;
		lightMap	= NULL;
	}
};

struct Mesh {
	wstring	name;	//Object Name Info
	
	int start;		//Object Start Idx or Vert Info
	int count;		//Object Idx or Vert Count Info
	
	bool isDraw;

	Material* mat;

	Mesh() {
		name = L"";
		isDraw = true;
		start	= -1;
		count	= -1;
		
		mat = NULL;
	}

	Mesh(wstring strName, int iStart, int iCount) {
		Mesh();
		name = strName;
		start = iStart;
		count = iCount;

		mat = NULL;
	}
	
};

struct Node {
	Node* parrentNode;
	vector<Node*> childNode;
	Mesh* nodeData;

	Node(Mesh* meshData = NULL) {
		parrentNode = NULL;
		nodeData = meshData;
	}

	~Node() {
		SAFE_DELETE(nodeData);
		
		vector<Node*>::iterator iter = childNode.begin();
		for (iter; iter != childNode.end(); iter++) {
			SAFE_DELETE(*iter);
		}

		vector<Node*>().swap(childNode);
	}
};

class Model
{
public:
	Model();
	virtual ~Model();

	//�Լ� �̸��� �� ����...
	bool CreateModel(ID3D11Device*, vector<Vertex>, vector<unsigned long>);
	void InsertNode(Node* node);
	void InsertMaterial(Material* mat);
	void Release();

	virtual void Render(ID3D11DeviceContext*, PWindowRender pWR);
	

	void SetPrimitiveType(D3D11_PRIMITIVE_TOPOLOGY type);
	void SetCenter(XMFLOAT3 center);
	void SetRotate(XMFLOAT3 rotate);
	void SetSize(XMFLOAT3 size);
	void SetRotVelocity(XMFLOAT3 rot);		
	void SetShader(wstring path);
	void SetName(wstring name);
	void SetScaleFactor(float scaleFactor);

	void		SetNormalize(bool isNormalize);
	bool		IsNormalize();


	int			GetIndexCount();
	int			GetVertexCount();
	float		GetScaleFactor();
	wstring		GetName();

	XMFLOAT3	GetSize();
	XMFLOAT3	GetRotate();
	XMFLOAT3	GetCenter();
	XMFLOAT3	GetRotVelocity();
	
	vector<Node*>&	GetNodeList();
	vector<Material*>&	GetMaterialList();

protected:
	bool InitVertextBuffers(ID3D11Device*, vector<Vertex>);
	bool InitIndexBuffers(ID3D11Device*, vector<unsigned long>);
	void RenderBuffers(ID3D11DeviceContext*);
	void RenderNode(ID3D11DeviceContext* deviceContext, PWindowRender pWR, Node* node);

protected:
	wstring	_name;										//�� ��
	bool	_isNormalize;								//�� ũ�� ����ȭ
	int		_vertexCount, _indexCount;					//���� ���� �� �ε��� ��
	float	_scaleFactor;								//����ȭ�� ���� ũ�� ��

	ID3D11Buffer *_vertexBuffer, *_indexBuffer;			//����
	D3D11_PRIMITIVE_TOPOLOGY	_primitiveType;			//������Ƽ��

	XMFLOAT3					_rotate;				//ȸ����
	XMFLOAT3					_center;				//��ġ
	XMFLOAT3					_size;					//ũ��
	XMFLOAT3					_rotVelocity;			//�� ȸ�� �ӵ�
	XMVECTOR					_accVel;				//ȸ���ӵ��� ���� ���ӵ�
	
	vector<Material*>			_matList;
	vector<Node*>				_nodeList;				//Obj List, ���� ���� ������Ʈ�� ������

	Shader*						_shader;				//����� ���̴�
};