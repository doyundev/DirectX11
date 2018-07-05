#include "stdafx.h"
#include "GameFont.h"


GameFont::GameFont(void)
{
}


GameFont::~GameFont(void)
{
}

//��Ʈ�� �ؽ��� ������ �ε��Ѵ�. 
HRESULT GameFont::Init()
{
	
	//Set Font Info
	char fontPath[50] = "res\\fonts\\";
	char fontImagePath[50] = "res\\fonts\\";
	
	strcat_s(fontPath, "candy.fnt");

	//Font Load
	TiXmlDocument fontXml;
	if (fontXml.LoadFile(fontPath, TIXML_ENCODING_UTF8) == false)	//xml �ε� ����
	{
		MessageBox(NULL, L"Can't find font file", L"Error", MB_OK);
		return E_FAIL;
	}
	else
	{
		TiXmlNode *pNode;
		//�̹��� ������ �̸��� �޾Ƽ� �ش� �̹��� �ε�
		pNode = fontXml.FirstChild("font")->FirstChild("pages")->FirstChild("page");
		const char *fontImage = pNode->ToElement()->Attribute("file");
		strcat_s(fontImagePath, fontImage);
		
		if (!LoadTexture(fontImagePath)) {
			MessageBox(NULL, L"Can't find font texture file", L"Error", MB_OK);
			return E_FAIL;
		}

		pNode = fontXml.FirstChild("font")->FirstChild("chars");
		pNode = pNode->FirstChild("char");

		int id = 0;
		while (pNode != NULL)
		{
			CharFont charFont;
			pNode->ToElement()->Attribute("id", &id);

			pNode->ToElement()->Attribute("x", &charFont.x);
			pNode->ToElement()->Attribute("y", &charFont.y);
			pNode->ToElement()->Attribute("width", &charFont.width);
			pNode->ToElement()->Attribute("height", &charFont.height);
			pNode->ToElement()->Attribute("xoffset", &charFont.xoffset);
			pNode->ToElement()->Attribute("yoffset", &charFont.yoffset);
			pNode->ToElement()->Attribute("xadvance", &charFont.xadvance);
			
			_charators[id] = charFont;

			pNode = pNode->NextSibling();
		}
		fontXml.Clear();
	}


	InitBuffer(_maxLength);

	return S_OK;
}



//������ ���� ���� �ʱ�ȭ
bool GameFont::InitBuffer(int maxLength)
{
	int vertCnt = maxLength * 4;
	int idxCnt = maxLength * 6;

	if (maxLength <= 0) {
		return false;
	}

	
	_vertices.position.resize(vertCnt);
	_vertices.uv.resize(vertCnt);
	_vertices.color.resize(vertCnt);


	vector<unsigned long> indices;
	MYUTIL::GenerateIndexList(indices, idxCnt);

	
	ID3D11Device *device= DEVICEMANAGER.GetDevice();
	_fontModel = make_unique<SimpleTextureModel>();
	_fontModel->InitVertextBuffers(device, _vertices, true);
	_fontModel->InitIndexBuffers(device, indices);
	_fontModel->SetShader(RM_SHADER.AddResource(L"source\\shader\\font"));
	_fontModel->SetTexture(_fontTex.Get());

	return true;
}

//�ؽ�Ʈ �߰�
void GameFont::Print(wchar_t * str, int x, int y, int fontSize, XMFLOAT3 color)
{
	//�ִ� ǥ�� ���ڼ��� ������ �� �̻� ���ڸ� �������� �ʴ´�.
	unsigned int fontLength =lstrlen(str) + _nowLength;

	if (_maxLength <= fontLength) {
		return;
	}

	float left = (float)((WINSIZEX / 2) * -1) + (float)x;
	float top = (float)(WINSIZEY / 2) - (float)y;
	
	XMFLOAT3 position = XMFLOAT3(left, top, 0.f);
	XMFLOAT4 colorData = XMFLOAT4(color.x, color.y, color.z, 1.f);

	//���������� ����
	while (*str != NULL) {
		int charNum = *str;	//�����ڵ尪�� ����
		
		//��ĭ ���� ��� �׸��� ���� 11�ȼ���ŭ �ڷ� �Űܼ� �׸��� ��
		if (charNum == 32) {
			position.x += 11;
			str++;
			continue;
		}
		
		auto charData = _charators.find(charNum)->second;
		
		int fontWidth = charData.width * (fontSize / 10);
		int fontHeight = charData.height * (fontSize / 10);
		int beforeXOffset = charData.xoffset;
		
		float mulNum = 1.f / 1024.f;
		float tu = (float)charData.x, tv = (float)charData.y;

		if (tu > 0) {		tu *=  mulNum;	}
		if (tv > 0) {		tv *= mulNum;	}

		float maxTu = (charData.x + charData.width) * mulNum;
		float maxTv = (charData.y + charData.height) * mulNum;


		int indexCnt = _nowLength * 4;

		//�»��
		_vertices.position[indexCnt] = (XMFLOAT3(position.x, position.y + fontHeight, 0.f));
		_vertices.color[indexCnt] = (colorData);
		_vertices.uv[indexCnt] = (XMFLOAT2(tu, tv));

		//����
		indexCnt++;
		_vertices.position[indexCnt] = (XMFLOAT3(position.x + fontWidth, position.y + fontHeight, 0.f));
		_vertices.color[indexCnt] = (colorData);
		_vertices.uv[indexCnt] = (XMFLOAT2(maxTu, tv));

		//���ϴ�
		indexCnt++;
		_vertices.position[indexCnt] = (XMFLOAT3(position.x, position.y, 0.f));
		_vertices.color[indexCnt] = (colorData);
		_vertices.uv[indexCnt] = (XMFLOAT2(tu, maxTv));

		//���ϴ�
		indexCnt++;
		_vertices.position[indexCnt] = (XMFLOAT3(position.x + fontWidth, position.y, 0.f));
		_vertices.color[indexCnt] = (colorData);
		_vertices.uv[indexCnt] = (XMFLOAT2(maxTu, maxTv));


		position.x += fontWidth + beforeXOffset;	//�۾��� ������ �ڷ� �������� ��
		str++;
		_nowLength++;
	}
			
}


//�ؽ�Ʈ �׸���
void GameFont::Render(ID3D11DeviceContext * dc)
{
	unsigned int vertCnt = _nowLength*4;

	if (vertCnt <= 0) { 
		return;
	}

	//���� ���� ������Ʈ
	unsigned int idxCnt = (_nowLength) * 6;
	VertexDataBuffer* vertexBuffer = _fontModel->GetVertexBuffer();
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	
	ID3D11Buffer* buffer = vertexBuffer->positionBuffer;
	if (FAILED(dc->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return;
	}
	auto posPtr = (XMFLOAT3*)mappedResource.pData;
	memcpy(posPtr, (void*)&_vertices.position[0], (sizeof(XMFLOAT3) * vertCnt));
	dc->Unmap(buffer, 0);


	buffer = vertexBuffer->colorBuffer;
	if (FAILED(dc->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return;
	}
	auto colorPtr = (XMFLOAT4*)mappedResource.pData;
	memcpy(colorPtr, (void*)&_vertices.color[0], (sizeof(XMFLOAT4) * vertCnt));
	dc->Unmap(buffer, 0);

	buffer = vertexBuffer->texcoordBuffer;
	if (FAILED(dc->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource))) {
		return;
	}
	auto uvPtr = (XMFLOAT2*)mappedResource.pData;
	memcpy(uvPtr, (void*)&_vertices.uv[0], (sizeof(XMFLOAT2) * vertCnt));
	dc->Unmap(buffer, 0);


	////���⼭ ��������
	_fontModel->SetIndexCnt(idxCnt);

	DEVICEMANAGER.TurnZBufferOff();
	DEVICEMANAGER.TurnOnAlphaBlending();
	
	_fontModel->Render(dc);

	DEVICEMANAGER.TurnOffAlphaBlending();
	DEVICEMANAGER.TurnZBufferOn();
	_nowLength = 0;
}


//�ؽ��� �ε�
bool GameFont::LoadTexture(std::string fileName)
{
	//��Ʈ �ؽ��� �ε�
	wstring filePath = CA2CT(fileName.c_str());

	_fontTex = RM_TEXTURE.LoadTexture(filePath);
	
	if (!_fontTex) {
		return false;
	}

	return true;
}


