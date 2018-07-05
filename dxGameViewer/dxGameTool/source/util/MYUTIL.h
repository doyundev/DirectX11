// MYUTIL.h 
// 2017.12.20
#pragma once

#define EPSILON 0.0001f
#define ONE_RADIAN	 0.0174532925f

// float ������ ���� �� ���Ƿ� ������ ������ ���� 
// a = 10.00001f
// b = 10.00008f
// abs(a-b) < c => a = b �� ����. 

#define FLOATEQUAL(a, b)	(abs((a) - (b)) < EPSILON)		// a �� b �� ������?
#define FLOATZERO(a)		(abs(a) < EPSILON)				// a �� ���� 0�� ������?
#define VECTORZERO(v)		(FLOATZERO((v).x) && FLOATZERO((v).y) && FLOATZERO((v).z))



//���� ����ü
typedef struct tagRay
{
	XMFLOAT3 origin;		//������ ������ġ
	XMFLOAT3	direction;	//������ ����(����ȭ �Ǿ� �־�� ��)
}Ray, *LPRay;

namespace MYUTIL
{
	//=============================================================
	//	## ���콺 ##
	//=============================================================
	POINT getMousePos();						// ���콺 ��ġ ���
	void setMousePos(int x, int y);				// ���콺 ��ġ ����

	CString getFileName(CString path);
	CString GetDirectoryPath(CString path);

	//=============================================================
	//	## ���� �Լ� ##
	//=============================================================
	// ���� �õ� ����
	void initForRandomSeed();
	// min ~ max ������ ���� ���� ����
	int randomIntRange(int min, int max);
	// min ~ max ������ ���� �Ǽ� ����
	float randomFloatRange(float min, float max);
	wstring ConvertToWString(CString& str);

	float InverseFloat(float num);
	
	void GenerateIndexList(std::vector<unsigned long> &indices, int idxCnt);
}

