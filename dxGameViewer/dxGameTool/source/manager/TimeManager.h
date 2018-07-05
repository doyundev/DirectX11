#pragma once
#include "SingletonBase.h"
#include <chrono>
//==================================================================
//		## timeManager ## (Ÿ�� �Ŵ���, ������. ũ�γ�� �����Ҽ��� ����.)
//==================================================================

class TimeManager : public SingletonBase <TimeManager>
{
private:
	float _timeScale;				//�ð� �����
	float _timeElapsed;				//�������Ӵ� �����
	__int64 _curTime;				//����ð�
	__int64 _lastTime;				//�������ð�
	__int64 _periodFrequency;		//�ð��ֱ� (1�ʿ� ����̳� ī��Ʈ�Ǵ���)

	unsigned long _frameRate;		//FPS
	unsigned long _FPSFrameCount;	//FPS ī��Ʈ
	float _FPSTimeElapsed;			//FPS �����
	float _worldTime;				//��ü ����ð�

public:
	HRESULT Init(void);
	void Release(void);
	void Update(float lockFPS);

	//�������Ӵ� ����ð� ��������
	float GetElapedTime(void) { return _timeElapsed; }
	//��ü ����ð� ��������
	float GetWorldTime(void) { return _worldTime; }
	int		GetFrameRate() { return _frameRate; }

	TimeManager() {}
	~TimeManager() {}
};