//==================================================================
//		## Camera ## (Camera)
//==================================================================
#pragma once

class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	//Set Function
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	//Get Function
	XMVECTOR GetPosition();
	XMVECTOR GetRotation();

	//Camera Update
	XMMATRIX Update(float duration);

	//ȭ�鿡�� ī�޶� ���� ���̰��
	Ray ComputeRay(XMFLOAT2 screenPos, D3D11_VIEWPORT viewPort, XMMATRIX matProj);

	//Interrupt Event
	void DeviceInput(float duration);
	void MouseInput(float duration);
	void KeyboardInput(float duration);

private:
	//�̵�, ȸ�� �ӵ�
	float _speed, _mouseSpeed;

	//��ġ, ȸ�� ��
	XMFLOAT3	_position, _rotation;


	XMVECTOR _lookAtVec;		//direction
	XMMATRIX _viewMatrix;		//viewMat
};
