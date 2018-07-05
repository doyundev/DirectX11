//====================================================================
//			## CCustomTreeCtrl ## (MFC TreeCtrl ��� Ȯ��)
//====================================================================

#pragma once
class CCustomTreeCtrl : public CTreeCtrl
{
public:
//********************************************* ��� �Լ� *******************************************//
	CCustomTreeCtrl();
	~CCustomTreeCtrl();

	//��� �߰�
	HTREEITEM		CreateItem(HTREEITEM hItem, CString name = L"none", DWORD_PTR data = NULL);	
	
	//��� Ȯ��
	void			NodeExpand(HTREEITEM hitem);							
	
	//GetFunction
	int				GetNodeIndex(HTREEITEM hitem);							//��带 ã�´�, ��Ʈ ���� Ž��
	int				GetNodeIndex(HTREEITEM findNode, HTREEITEM findTree);	//��带 ã�´�. �Էµ� ��ġ���� Ž��
	HTREEITEM		GetRootNode(HTREEITEM hitem);							//�ش� ����� ��Ʈ ��ȯ

	//Ʈ�� ��Ʈ�� ��Ʈ �̺�Ʈ
	HTREEITEM		HitEvent();												
	
	HTREEITEM		CheckBoxHitEvent();										//üũ �ڽ� Ŭ�� �̺�Ʈ
	void			CheckParent(HTREEITEM hItem);							//�θ� ��� üũ
	void			CheckChild(HTREEITEM hItem, BOOL check);				//�ڽ� ��� ���� üũ


//*********************************************** ��� ���� *****************************************************//
private:
	//Select Item
	HTREEITEM		m_treeSelectItem;															
};
