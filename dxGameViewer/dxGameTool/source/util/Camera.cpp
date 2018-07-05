
#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	_position = XMFLOAT3(0.f, 0.f, 0.f);
	_rotation = XMFLOAT3(0.f, 0.f, 0.f);

	_speed = 10.f;
	_mouseSpeed = 10.f;
}


Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}

//��ġ �� ����
void Camera::SetPosition(float x, float y, float z)
{
	
	_position.x = x;
	_position.y = y;
	_position.z = z;
	return;
}

//ȸ�� �� ����
void Camera::SetRotation(float x, float y, float z)
{
	_rotation.x = x;
	_rotation.y = y;
	_rotation.z = z;
	return;
}

//��ġ ��� ��ȯ
XMVECTOR Camera::GetPosition()
{
	return XMLoadFloat3(&_position);
}


//ȸ�� ��� ��ȯ
XMVECTOR Camera::GetRotation()
{
	return XMLoadFloat3(&_rotation);
}

//�� ��� ������Ʈ
XMMATRIX Camera::Update(float duration)
{
	float yaw, pitch, roll;
	XMFLOAT3 up,  lookAt;
	XMMATRIX rotationMatrix;


	up = XMFLOAT3(0.f, 1.f, 0.f);
	lookAt = XMFLOAT3(0.f, 0.f, 1.f);

	pitch = _rotation.x * 0.0174532925f;
	yaw   = _rotation.y * 0.0174532925f;
	roll  = _rotation.z * 0.0174532925f;

	//ȸ�� ������ ī�޶� ȸ�� ��� ����
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//ī�޶� up ����, LookAtVector ���� ȸ��
	XMVECTOR upVec = XMVector3TransformCoord(XMLoadFloat3(&up), rotationMatrix);
	XMVECTOR lookAtVec = XMVector3TransformCoord(XMLoadFloat3(&lookAt), rotationMatrix);
	_lookAtVec = lookAtVec;

	//LookAtVector�� �̵����Ϳ� ���� �� ����
	lookAtVec = XMLoadFloat3(&_position) + lookAtVec;

	//�� ��� �����
	_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&_position), lookAtVec, upVec);

	return _viewMatrix;
}


//���� ���� ���
Ray Camera::ComputeRay(XMFLOAT2 screenPos, D3D11_VIEWPORT viewPort, XMMATRIX matProj)
{
	//��ũ���� ��ġ ������ ���
	float factorX = screenPos.x / viewPort.Width;
	float factorY = (1.0f - (screenPos.y / viewPort.Height));

	//0 ~ 1 => -1 ~ 1
	factorX = factorX * 2.0f - 1.0f;
	factorY = factorY * 2.0f - 1.0f;


	//[1][][][]
	//[][1][][]
	//[][][1][]
	//[0][0][0][]
	//ȭ�� �����Ϸ��� ������


	XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, matProj);
	XMVECTOR rayDirection = XMLoadFloat4(&XMFLOAT4(factorX / proj._11, factorY / proj._22, 1.0f, 0.0f));

	//ī�޶� ���� ���
	XMMATRIX invView = XMMatrixInverse(nullptr, _viewMatrix);

	//������ ������ ī�޶� ����������� ����Ѵ�
	rayDirection = XMVector4Transform(rayDirection, invView);

	//���⺤�� ����ȭ
	rayDirection = XMVector4Normalize(rayDirection);

	//Ray�� ����
	XMFLOAT3 direction;
	XMStoreFloat3(&direction, rayDirection);

	return Ray{_position, direction};
}



//�Է� �̺�Ʈ
void Camera::DeviceInput(float duration)
{
	MouseInput(duration);
	KeyboardInput(duration);
}


//���콺 �̵�, ���� ����
void Camera::MouseInput(float duration)
{
	POINT screenCenter{	(LONG)(WINSIZEX * 0.5f), (LONG)(WINSIZEY * 0.5f) };

	if (KEYMANAGER.IsOnceKeyDown(VK_RBUTTON)) {
		MYUTIL::setMousePos(screenCenter.x, screenCenter.y);
	}
	else if(KEYMANAGER.IsStayKeyDown(VK_RBUTTON)) {
		POINT mousePos = MYUTIL::getMousePos();

		float Hori = (float)(mousePos.x - screenCenter.x);
		float Vert = (float)(mousePos.y - screenCenter.y);
		
		_rotation.x += Vert * duration * _mouseSpeed;
		_rotation.y += Hori * duration * _mouseSpeed;

		MYUTIL::setMousePos(screenCenter.x, screenCenter.y);
	}
}


//Ű���带 �̿��� ī�޶� ��ġ ����
void Camera::KeyboardInput(float duration)
{
	//��ġ����, ī�޶� ���⺤��, �� ����
	XMVECTOR posVec = XMLoadFloat3(&_position);
	XMVECTOR moveVec = XMVector3Normalize(_lookAtVec);
	XMVECTOR upVec = XMVectorSet(0.f, 1.f, 0.f, 0.f);



	if (KEYMANAGER.IsStayKeyDown('W')) {
		posVec += (moveVec * duration * _speed);
	} 
	else if (KEYMANAGER.IsStayKeyDown('S')) {
		posVec -= (moveVec * duration * _speed);
	}

	if (KEYMANAGER.IsStayKeyDown('A')) {
		posVec -= XMVector3Cross(upVec, moveVec) * duration *  _speed;
	}
	else if (KEYMANAGER.IsStayKeyDown('D')) {
		posVec += XMVector3Cross(upVec, moveVec) * duration * _speed;
	}

	if (KEYMANAGER.IsStayKeyDown('Q')) {
		posVec -= (upVec * duration * _speed);
	}
	else if (KEYMANAGER.IsStayKeyDown('E')) {
		posVec += (upVec * duration * _speed);
	}

	//�̵��� ���� ��ġ ����
	XMStoreFloat3(&_position, posVec);

}
