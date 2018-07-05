#include "stdafx.h"
#include "MYUTIL.h"

namespace MYUTIL
{
	//=============================================================
	//	## ���콺 ## 
	//=============================================================
	POINT getMousePos()
	{
		POINT mousePos;

		// ��ũ������ ���콺 ��ǥ�� �޾ƿ�.
		GetCursorPos(&mousePos);

		// ��ũ������ ��ġ�� Ŭ����Ʈ ������ ������ �ٲ�
		ScreenToClient(_hWnd, &mousePos);

		return mousePos;
	}

	void setMousePos(int x, int y)
	{
		POINT mousePos;

		mousePos.x = x;
		mousePos.y = y;

		// Ŭ���̾�Ʈ ���� ��ġ�� ��ũ�� �������� �ٲ�
		ClientToScreen(_hWnd, &mousePos);
		
		// ��ũ������ ��ġ�� ����
		SetCursorPos(mousePos.x, mousePos.y);
	}


	CString getFileName(CString path) {
		int index = path.ReverseFind('\\') + 1;

		if (index == 0) {
			index = path.ReverseFind('/') + 1;
		}

		CString name = path.Right(path.GetLength() - index);

		return name;
	}

	CString GetDirectoryPath(CString path)
	{
		int index = path.ReverseFind('\\') + 1;

		if (index == 0) {
			index = path.ReverseFind('/') + 1;
		}

		CString dirPath = path.Left(index);
		
		return dirPath;
	}

	
	//=============================================================
	//	## ���� �Լ� ## 
	//=============================================================
	// ���� �õ� ����
	void initForRandomSeed()
	{
		srand(GetTickCount());
	}

	// min ~ max ������ ���� ���� ����
	int randomIntRange(int min, int max)
	{
		int delta = max - min;
		return (rand() % delta + 1) + min;
		
	}

	// min ~ max ������ ���� �Ǽ� ����
	float randomFloatRange(float min, float max)
	{
		float delta = max - min;
		float factor = (rand() % 1001) * 0.001f;

		return (delta * factor) + min;
		
	}

	//CString -> wstring
	wstring ConvertToWString(CString & str)
	{
		return (wstring)str;
	}

	float InverseFloat(float num)
	{
		if (num == 0.f) {
			return 0.f;
		}

		return 1.f / num;
	}

	void GenerateIndexList(std::vector<unsigned long> &indices, int idxCnt)
	{
		indices.resize(idxCnt, 0);

		int range = 0;
		for (int i = 0; i < idxCnt; i += 6) {
			indices[i] = 0 + range;
			indices[i + 1] = 1 + range;
			indices[i + 2] = 2 + range;

			indices[i + 3] = 1 + range;
			indices[i + 4] = 3 + range;
			indices[i + 5] = 2 + range;

			range += 4;
		}
	}
	
}