#include "stdafx.h"
#include "Shader.h"

//�������� �ʱ�ȭ
vector<LAYOUT_INFO> Shader::_layoutList = {};

Shader::Shader()
{
}

Shader::~Shader()
{

}


//������ �̿��� �׸���.
void Shader::VertexRender(ID3D11DeviceContext *deviceContext, int vertexCount, int startVertex)
{
	RenderShader(deviceContext);
	deviceContext->Draw(vertexCount, startVertex);
}

//�ε����� �̿��� �׸���.
void Shader::IndexRender(ID3D11DeviceContext *deviceContext, int indexCount, int startIndex)
{
	RenderShader(deviceContext);
	deviceContext->DrawIndexed(indexCount, startIndex, 0);
}


//���̴��� �߰��Ѵ�.
bool Shader::InsertShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	//���̴� ������ �� �ʱ�ȭ
	if (!InitializeShader(device, hwnd, vsFilename, psFilename)) {
		return false;
	}

	return true;
}

//���̴��� �о� ������ �� ����
bool Shader::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	ComPtr<ID3D10Blob> errorMessage;
	ComPtr<ID3D10Blob> vertexShaderBuffer;
	ComPtr<ID3D10Blob> pixelShaderBuffer;
	

    // Compile the vertex shader code.
	if(FAILED(D3DX11CompileFromFile(vsFilename, NULL, NULL, "vsMain", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL))) {
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage) {
			OutputShaderErrorMessage(errorMessage.Get(), hwnd, vsFilename);
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else {
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

    // Compile the pixel shader code.
	if(FAILED(D3DX11CompileFromFile(psFilename, NULL, NULL, "psMain", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL))) {
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage) {
			OutputShaderErrorMessage(errorMessage.Get(), hwnd, psFilename);
		}
		// If there was nothing in the error message then it simply could not find the file itself.
		else {
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

    // Create the vertex shader from the buffer.
	if (FAILED(device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), 
											vertexShaderBuffer->GetBufferSize(), NULL, &_vertexShader))) {
		return false;
	}
	

    // Create the pixel shader from the buffer.
	if (FAILED(device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), 
											pixelShaderBuffer->GetBufferSize(), NULL, &_pixelShader))) {
		return false;
	}
	
	//���̾ƿ� ���� ����
	vector<D3D11_INPUT_ELEMENT_DESC> layoutDescInfo;

	//�����ϵ� ���̴��� ���� ������ �������� �����Է������� �����Ѵ�.
	BuildLayoutDesc(CT2CA(vsFilename), layoutDescInfo);

	//���� ������ ������ ��ȯ, Vertex Shader�� ������� �ʴ� ��츦 ��� ���� �ʾҴ�.
	if (layoutDescInfo.empty()) 
		return false;

	//������ ���̾ƿ� ����Ʈ���� ������ ������ ������ ������ �����´�.
	//���� ��� �߰��Ѵ�.
	if ((_layoutIdx = FindLayout(layoutDescInfo)) == -1) {
		ComPtr<ID3D11InputLayout> layout;
		//���̾ƿ� ����
		if (FAILED(device->CreateInputLayout(&layoutDescInfo[0], (UINT)layoutDescInfo.size(), vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(), &layout))) {
			return false;
		}

		//���� ���̴����� ����� ���̾ƿ� ���� �ε���
		_layoutIdx = (int)_layoutList.size();

		//������ ���̾ƿ� ���������� �߰��Ͽ� ����
		_layoutList.emplace_back(LAYOUT_INFO{ layout, layoutDescInfo });
	}


	return true;
}


//���̴� ���� ���
void Shader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	auto bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(auto i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

//���� �Է� ���̾ƿ� ���� ����
void Shader::BuildLayoutDesc(char * vsPath, vector<D3D11_INPUT_ELEMENT_DESC>& layoutDesc)
{
	//���ؽ� ���̴� ������ ����.
	FILE* vsShader;
	if (fopen_s(&vsShader, vsPath, "r") != 0)
		return;
	

	//�Ľ� ����
	char line[512];
	while (NULL != fgets(line, sizeof(line), vsShader)) {
		char word[256] = { 0, };
		sscanf_s(line, "%s", word, 256);

		//struct Ű���� Ž��
		if (_stricmp(word, "struct") == 0) {
			char type[128] = { 0, };
			sscanf_s(line, "%s%s", word, 256, word, 256);

			//���ؽ� Ÿ�� Ű���� ���� Ȯ��
			if (_stricmp(word, "VertexInputType") == 0) {
				while (NULL != fgets(line, sizeof(line), vsShader)) {
					if (_stricmp(line, "};\n") == 0) {
						break;
					}
					//�ø�ƽ ��������
					char* context = NULL;
					char* tok = strtok_s(line, " ", &context);
					
					while (tok) {
						UINT semanticIdx = (UINT)layoutDesc.size();

						if (_stricmp(tok, "POSITION;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, semanticIdx, 0, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "COLOR;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "TEXCOORD;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "NORMAL;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "TANGENT;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "BITANGENT;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "BITANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "BONEID;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "BONEID", 0, DXGI_FORMAT_R32G32B32A32_UINT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						else if (_stricmp(tok, "WEIGHT;\n") == 0) {
							layoutDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, semanticIdx, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,	0 });
						}
						tok = strtok_s(NULL, " ", &context);
					}
				}
				break;
			}
		}
	}

	fclose(vsShader);
}


//����� ���̾ƿ�, ����, �ȼ� ���̴��� ����Ѵ�.
void Shader::RenderShader(ID3D11DeviceContext* deviceContext)
{
	// Set the vertex input layout.
	deviceContext->IASetInputLayout(_layoutList[_layoutIdx].first.Get());
	
	// Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(_vertexShader.Get(), NULL, 0);
	deviceContext->PSSetShader(_pixelShader.Get(), NULL, 0);
	
	return;
}

//���̾ƿ� Ž��
int Shader::FindLayout(vector<D3D11_INPUT_ELEMENT_DESC>& refLayoutDesc)
{

	//layoutList�� ������ ���� ���̾ƿ��� �ִ��� ã�´�.
	for (int i = 0; i < _layoutList.size(); i++) {
		auto desc = _layoutList[i].second;

		//1. ���̾ƿ� ������ ���� ��ġ�ϴ��� üũ
		if (desc.size() != refLayoutDesc.size()) 
			continue;

		//��� ������ ��ġ�ϴ��� üũ
		unsigned int cnt = 0;
		for (cnt = 0; cnt < desc.size(); cnt++) {
			if (desc[cnt].SemanticName != refLayoutDesc[cnt].SemanticName) {
				break;
			}
		}

		//��� ������ ��ġ�ϸ� ��ġ ���� ��ȯ
		if (cnt >= desc.size()) {
			return i;
		}
	}
	return -1;
}
