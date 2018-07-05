#include "stdafx.h"
#include "CustomTreeCtrl.h"


CCustomTreeCtrl::CCustomTreeCtrl()
{
}

CCustomTreeCtrl::~CCustomTreeCtrl()
{
}

//��� �߰�
HTREEITEM CCustomTreeCtrl::CreateItem(HTREEITEM hItem, CString name, DWORD_PTR data)
{
	HTREEITEM subItem = this->InsertItem(name, hItem, TVI_LAST);

	if(data)
		this->SetItemData(subItem, data);

	return subItem;
}


//��� ����
void CCustomTreeCtrl::NodeExpand(HTREEITEM hitem)
{
	//��� Ȯ��
	while (hitem)
	{
		this->Expand(hitem, TVE_EXPAND);

		if (this->ItemHasChildren(hitem))
			NodeExpand(this->GetChildItem(hitem));

		hitem = this->GetNextItem(hitem, TVGN_NEXT);
	}

}

//��� Ž�� �� �ε��� ��ȯ
int CCustomTreeCtrl::GetNodeIndex(HTREEITEM hitem)
{
	int idx = 0;
	//�θ��带 ���Ѵ�.
	HTREEITEM finditem = this->GetParentItem(hitem);
	
	//NULL�� �ֻ��� ��� �� ���� ù��° ��带 ����
	//NULL �ƴϸ�, �ڽĳ�� �� ���� ù��° ��带 ����
	if (finditem == NULL)
		finditem = this->GetRootItem();
	else
		finditem = this->GetChildItem(finditem);

	//��� Ž��.
	while (finditem) {
		if (finditem == hitem)
			return idx;

		finditem = this->GetNextSiblingItem(finditem);
		idx++;
	}
	return -1;
}

//��� Ž�� �� �ε��� ��ȯ
int CCustomTreeCtrl::GetNodeIndex(HTREEITEM findNode, HTREEITEM findTree)
{
	int Cnt = 0;
	while (findTree) {
		if (findNode == findTree)
			return Cnt;
		
		findTree = this->GetNextItem(findTree, TVGN_NEXT);
		Cnt++;
	}

	return -1;
}

//��Ʈ��� Ž��
HTREEITEM CCustomTreeCtrl::GetRootNode(HTREEITEM hitem) {

	HTREEITEM find = hitem;

	while (this->GetParentItem(find)) {
		find = this->GetParentItem(find);
	}

	return find;
}


//��Ʈ�� Ŭ�� �̺�Ʈ
HTREEITEM CCustomTreeCtrl::HitEvent()
{
	CPoint pt;
	// ȭ��󿡼� ���콺�� ��ġ�� ��´�.
	GetCursorPos(&pt);
	

	// ���� ���콺 ��ǥ�� ��ġ�� �׸� ������ ��´�.
	::ScreenToClient(this->m_hWnd, &pt);
	HTREEITEM hitem = HitTest(pt);
	
	return hitem;
}

//üũ�ڽ� ���� Ŭ�� �̺�Ʈ
HTREEITEM CCustomTreeCtrl::CheckBoxHitEvent()
{

	CPoint	point;
	UINT	nFlags = 0;

	GetCursorPos(&point);
	::ScreenToClient(this->m_hWnd, &point);

	HTREEITEM	hItem = HitTest(point, &nFlags);

	// �������� �����ϰ� üũ�ڽ��� �̺�Ʈ�� �߻��ߴٸ�
	if (hItem != NULL && (nFlags & TVHT_ONITEMSTATEICON) != 0) {
		return hItem;
	}
	return NULL;
}


//�ڽĳ�� üũ�� �θ��� ��ü üũ
void CCustomTreeCtrl::CheckParent(HTREEITEM hItem)
{
	//��������� Ȱ��ȭ ����
	HTREEITEM hParent = this->GetParentItem(hItem);
	while (hParent) {
		this->SetCheck(hParent, TRUE);
		hParent = this->GetParentItem(hParent);
	}
}

//�γ�� üũ�� �ڽĳ�� ��ü üũ
void CCustomTreeCtrl::CheckChild(HTREEITEM hItem, BOOL check)
{
	//��������� Ȱ��ȭ ����
	HTREEITEM hChild = this->GetChildItem(hItem);
	while (hChild) {
		this->SetCheck(hChild, check);
		hChild = this->GetNextItem(hChild, TVGN_NEXT);
	}
}

