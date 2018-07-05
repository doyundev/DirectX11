//====================================================================
//			## GameFont ## (Font �׸���)
//====================================================================
#pragma once
#include "singletonBase.h"
#include "..\include\tinyxml\tinyxml.h"
#include "model\SimpleTextureModel.h"


//��Ʈ ����ü
struct CharFont
{
	int x;
	int y;
	int width;
	int height;
	int xoffset;
	int yoffset;
	int xadvance;
};


class GameFont : public SingletonBase <GameFont>
{
private:
	std::map<unsigned int, CharFont>	_charators;			//���� ����
	ComPtr<ID3D11ShaderResourceView>	_fontTex;			//���� �ؽ���
	
	Vertex								_vertices;			//�׷��� ������ ���� ������
	unique_ptr<SimpleTextureModel>		_fontModel;			//������ �� ��

	unsigned int						_nowLength = 0;		//ȭ�鿡 �׷����� ��ü ���� ����
	unsigned int						_maxLength = 200;	//��ü ���� �ִ� ����

	
public:
	GameFont(void);
	~GameFont(void);
	HRESULT Init();
	
	//Text �߰�
	void Print(wchar_t * str, int x, int y, int fontSize = 25, XMFLOAT3 color = XMFLOAT3(1.f,1.f,1.f));
	//Text Render
	void Render(ID3D11DeviceContext* dc);


private:
	//��Ʈ �ؽ��� �ε�
	bool LoadTexture(std::string fileName);
	//���� �ʱ�ȭ
	bool InitBuffer(int maxLength);
};

