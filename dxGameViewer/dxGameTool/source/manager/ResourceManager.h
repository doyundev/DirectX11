#pragma once
#include "SingletonBase.h"
//=============================================================
//	## resourceManager ## (���ҽ� �Ŵ���)
//=============================================================
template<typename T, typename A>
class ResourceManager : public SingletonBase <A>
{
protected:
	typedef map<wstring, T> mapResource;
	mapResource _resourceList;	// �ʾȿ� ��� ���ҽ� ��ϵ�

public:
	// ���ҽ� �߰�
	T AddResource(wstring fileName, void* param = nullptr);
	// ���ҽ� ����
	void RemoveResource(wstring fileName);
	void RemoveResource(T);

	// ��� ���ҽ� ����
	void ClearResource(void);

	//���ҽ� ����Ʈ ��ȯ
	mapResource GetResource() {
		return _resourceList;
	}

	//�ε����� �ش��ϴ� ���ҽ� ������ ��ȯ
	T GetResourceData(int i) {
		mapResource::iterator it = _resourceList.begin();
		std::advance(it, i);
		return it->second;
	}

	//�ε����� �ش��ϴ� Ű ��ȯ
	const wstring* GetResourceKey(int i) {
		mapResource::iterator it = _resourceList.begin();
		std::advance(it, i);
		return &it->first;
	}

	//=============================================================
	//	## ���ҽ� �ε� �������� ���������Լ� ##
	//=============================================================
	virtual T loadResource(wstring fileName, void* param = nullptr) PURE;
	virtual void releaseResource(T data) PURE;

	ResourceManager() {}
	~ResourceManager() {}
};



// ���ҽ� �߰�
template<typename T, typename A>
inline T ResourceManager<T, A>::AddResource(wstring fileName, void * param)
{
	mapResource::iterator find;
	// �̹� ���ҽ��� �߰��� �Ǿ����� Ȯ��
	find = _resourceList.find(fileName);

	// �ش� ���ҽ��� �ʿ� �߰��Ǿ� ���� �ʴٸ� ���� ���� �߰���Ű��
	if (find == _resourceList.end())
	{
		// �ε帮�ҽ� �Լ��� ���ο� ���ҽ� �߰�
		T newResource = this->loadResource(fileName, param);
		// ���ҽ� �߰��� �����ߴٸ� 0����
		if (newResource == NULL) return NULL;
		// ���ҽ���Ͽ� �߰��ϱ�
		_resourceList.insert(make_pair(fileName, newResource));

		return newResource;
	}

	return find->second;
}

// ���ҽ� ����
template<typename T, typename A>
inline void ResourceManager<T, A>::RemoveResource(wstring fileName)
{
	mapResource::iterator find;
	// �̹� ���ҽ��� �߰��� �Ǿ����� Ȯ��
	find = _resourceList.find(fileName);

	// ���ҽ��� �ִٸ� �����
	if (find != _resourceList.end())
	{
		// ã�� ���ҽ� ����
		this->releaseResource(find->second);
		// �ش��ϴ� ���� ����
		_resourceList.erase(find);
	}
}

template<typename T, typename A>
inline void ResourceManager<T, A>::RemoveResource(T data)
{
	mapResource::iterator iter;
	for (iter = _resourceList.begin(); iter != _resourceList.end(); ++iter)
	{
		if (iter->second == data) {
			this->releaseResource(iter->second);
			_resourceList.erase(iter);
			break;
		}
	}
}

// ��� ���ҽ� ����
template<typename T, typename A>
inline void ResourceManager<T, A>::ClearResource(void)
{
	mapResource::iterator iter;
	for (iter = _resourceList.begin(); iter != _resourceList.end(); ++iter)
	{
		this->releaseResource(iter->second);
	}
	// ��ü����
	_resourceList.clear();
}

