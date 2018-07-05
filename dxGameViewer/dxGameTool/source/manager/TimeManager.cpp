#include "stdafx.h"
#include "TimeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime�Լ��� ����ϱ� ���ؼ�
//�����찡 ���۵ǰ� �� �� �ð��� ���Ͻ����ش�
//GetTickCount���� ������ �ɿ���~ �� ����

HRESULT TimeManager::Init(void)
{
	//���� Ÿ�̸� �������� üũ
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);
	//�ʴ� �ð� ���(1�� ��� ī���� �ϳ�)
	_timeScale = 1.0f / _periodFrequency;
	//�ʱ�ȭ ������ �ð��� ������ �ð�����
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);


	//������ �ʱ�ȭ
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0;

	return S_OK;
}

void TimeManager::Release(void)
{
}

void TimeManager::Update(float lockFPS)
{

	//����ð� ���
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	//�������� ������ �� ��� (���� �ð����� ������ ���)
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//������ ��Ű��
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			//����ð� ���
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			
			//�������� ������ �� ���
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//���� �ð� ����
	_lastTime = _curTime;
	//������ �� ����
	_FPSTimeElapsed += _timeElapsed;
	//������ �ð� ����
	_worldTime += _timeElapsed;

	//������ �ʱ�ȭ�� 1�ʸ��� �����ϱ�
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}

	_FPSFrameCount++;
}
