// C:\Users\Administrator\Desktop\dxGameTool\dxGameTool\dlg\ModelDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "dxGameTool.h"
#include "ModelDlg.h"
#include "LoadModelStateDlg.h"


// ModelDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ModelDlg, CDialogEx)

ModelDlg::ModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MODEL, pParent)
{

}

ModelDlg::~ModelDlg()
{
}

//��Ʈ�� ����
void ModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODELDLG_MODEL_LISTCTRL, _lstModelList);
	DDX_Control(pDX, IDC_MODELDLG_POSX_EDIT, _editModelPositionX);
	DDX_Control(pDX, IDC_MODELDLG_POSY_EDIT, _editModelPositionY);
	DDX_Control(pDX, IDC_MODELDLG_POSZ_EDIT, _editModelPositionZ);
	DDX_Control(pDX, IDC_MODELDLG_ROTX_EDIT, _editModelRotationX);
	DDX_Control(pDX, IDC_MODELDLG_ROTY_EDIT, _editModelRotationY);
	DDX_Control(pDX, IDC_MODELDLG_ROTZ_EDIT, _editModelRotationZ);
	DDX_Control(pDX, IDC_MODELDLG_SIZEX_EDIT, _editModelSizeX);
	DDX_Control(pDX, IDC_MODELDLG_SIZEY_EDIT, _editModelSizeY);
	DDX_Control(pDX, IDC_MODELDLG_SIZEZ_EDIT, _editModelSizeZ);
	DDX_Control(pDX, IDC_MODELDLG_OBJECT_TREE, _treeObjList);
	DDX_Control(pDX, IDC_MODELDLG_MODEL_NORMALIZE_CHECK, _checkModelNormalize);
	DDX_Control(pDX, IDC_MODELDLG_ANI_LISTCTRL, _lstAniList);
	DDX_Control(pDX, IDC_MODELDLG_MODEL_ANIREPEAT_CHECK, _checkAniRepeat);
}


//�̺�Ʈ �޽��� ��
BEGIN_MESSAGE_MAP(ModelDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_MODELDLG_MODEL_LISTCTRL, &ModelDlg::OnNMRClickModeldlgModelListctrl)

	ON_COMMAND(ID_DELETE_MODEL, &ModelDlg::OnDeleteModel)
	ON_COMMAND(ID_LOAD_MODEL, &ModelDlg::OnLoadModel)

	ON_NOTIFY(NM_CLICK, IDC_MODELDLG_MODEL_LISTCTRL, &ModelDlg::OnNMClickModelDlgModelListCtrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_POSX_SPIN, &ModelDlg::OnDeltaposModeldlgPosxSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_POSY_SPIN, &ModelDlg::OnDeltaposModeldlgPosySpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_POSZ_SPIN, &ModelDlg::OnDeltaposModeldlgPoszSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_ROTX_SPIN, &ModelDlg::OnDeltaposModeldlgRotxSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_ROTY_SPIN, &ModelDlg::OnDeltaposModeldlgRotySpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_ROTZ_SPIN, &ModelDlg::OnDeltaposModeldlgRotzSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_SIZEX_SPIN, &ModelDlg::OnDeltaposModeldlgSizexSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_SIZEY_SPIN, &ModelDlg::OnDeltaposModeldlgSizeySpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MODELDLG_SIZEZ_SPIN, &ModelDlg::OnDeltaposModeldlgSizezSpin)

	ON_NOTIFY(NM_CLICK, IDC_MODELDLG_OBJECT_TREE, &ModelDlg::OnNMClickModeldlgObjectTree)
	ON_BN_CLICKED(IDC_BUTTON1, &ModelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_MODELDLG_MODEL_NORMALIZE_CHECK, &ModelDlg::OnBnClickedModeldlgModelNormalizeCheck)
	ON_BN_CLICKED(IDC_MODELDLG_ANIPLAY_BTN, &ModelDlg::OnBnClickedModeldlgAniplayBtn)
	ON_BN_CLICKED(IDC_MODELDLG_ANIPAUSE_BTN, &ModelDlg::OnBnClickedModeldlgAnipauseBtn)
	ON_BN_CLICKED(IDC_MODELDLG_ANISTOP_BTN, &ModelDlg::OnBnClickedModeldlgAnistopBtn)
	ON_NOTIFY(NM_CLICK, IDC_MODELDLG_ANI_LISTCTRL, &ModelDlg::OnNMClickModeldlgAniListctrl)
	ON_BN_CLICKED(IDC_MODELDLG_MODEL_ANIREPEAT_CHECK, &ModelDlg::OnBnClickedModeldlgModelAnirepeatCheck)
	ON_NOTIFY(NM_RCLICK, IDC_MODELDLG_ANI_LISTCTRL, &ModelDlg::OnNMRClickModeldlgAniListctrl)
	ON_COMMAND(ID_LOAD_ANIMATION, &ModelDlg::OnLoadAnimation)
END_MESSAGE_MAP()

//���̾�α� �ʱ�ȭ
BOOL ModelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	_lstModelList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	_lstModelList.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	_lstModelList.InsertColumn(1, L"Path", LVCFMT_LEFT, 240);

	_lstAniList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	_lstAniList.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);

	_currentModel = NULL;
	UpdateControl();

	return TRUE;
}


//Model �� �߰��Ѵ�.
void ModelDlg::InsertModel(CString name, CString path, SkinModel* model)
{
	if (!model)	return;

	int index = _lstModelList.GetItemCount();
	_lstModelList.InsertItem(index, name);
	_lstModelList.SetItem(index, 1, LVIF_TEXT, path, 0, 0, 0, NULL);

	_lstModelList.SetItemData(index, (DWORD_PTR)model);

	//�� �߰� �޽���, �ٸ� ���̾�α� ���� ���� �޽���
	::SendMessageW(_hWnd, WM_INSERT_MODEL, NULL, NULL);
}

//���̾�α� ��Ʈ�� ������Ʈ
void ModelDlg::UpdateControl()
{
	//���� ���� ���� ��� �ʱ�ȭ, ��Ȱ��ȭ
	if (!_currentModel) {
		_editModelPositionX.SetWindowTextW(L"");
		_editModelPositionY.SetWindowTextW(L"");
		_editModelPositionZ.SetWindowTextW(L"");
		_editModelRotationX.SetWindowTextW(L"");
		_editModelRotationY.SetWindowTextW(L"");
		_editModelRotationZ.SetWindowTextW(L"");
		_editModelSizeX.SetWindowTextW(L"");
		_editModelSizeY.SetWindowTextW(L"");
		_editModelSizeZ.SetWindowTextW(L"");

		_checkModelNormalize.EnableWindow(false);
		_checkModelNormalize.SetCheck(false);
	}
	//���� ���� �ִ� ��� �� ������Ʈ
	else {
		CString strTmp;
		strTmp.Format(L"%.3f", _currentModel->GetCenter().x);
		_editModelPositionX.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetCenter().y);
		_editModelPositionY.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetCenter().z);
		_editModelPositionZ.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetRotate().x);
		_editModelRotationX.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetRotate().y);
		_editModelRotationY.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetRotate().z);
		_editModelRotationZ.SetWindowTextW(strTmp);


		strTmp.Format(L"%.3f", _currentModel->GetSize().x);
		_editModelSizeX.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetSize().y);
		_editModelSizeY.SetWindowTextW(strTmp);

		strTmp.Format(L"%.3f", _currentModel->GetSize().z);
		_editModelSizeZ.SetWindowTextW(strTmp);

		_checkModelNormalize.EnableWindow(true);
		_checkModelNormalize.SetCheck(_currentModel->IsNormalize());
	}


	UpdateTreeControl();		//������Ʈ Ʈ�� ��Ʈ�� ������Ʈ
	UpdateAnimationListCtrl();	//�ִϸ��̼� ��Ʈ�� ������Ʈ
}

//������Ʈ ������ ǥ���ϴ� Ʈ�� ������Ʈ
void ModelDlg::UpdateTreeControl()
{
	_treeObjList.DeleteAllItems();
	
	if (!_currentModel)
		return;

	//���õ� �� �̸��� ��Ʈ ���� ���
	HTREEITEM  hitem = _treeObjList.InsertItem(_currentModel->GetName().c_str(), TVI_ROOT, TVI_LAST);
	_treeObjList.SetCheck(hitem, true);


	for (auto& mesh : _currentModel->GetMeshList()) {
		HTREEITEM subItem = _treeObjList.CreateItem(hitem, mesh->name.c_str(), (DWORD_PTR)mesh);
		_treeObjList.SetCheck(subItem, mesh->isDraw);
	}

}


//������Ʈ Ʈ���� üũ�ڽ� �̺�Ʈ
//üũ ������ ���� ������Ʈ ������ ���°� �����ȴ�.
void ModelDlg::UpdateTreeControlCheckEvent(HTREEITEM hItem)
{
	while (hItem)
	{
		if (_treeObjList.ItemHasChildren(hItem)) {
			UpdateTreeControlCheckEvent(_treeObjList.GetChildItem(hItem));
		}
		else {
			if (BaseMesh* mesh = (BaseMesh *)_treeObjList.GetItemData(hItem)) {
				mesh->isDraw = _treeObjList.GetCheck(hItem);
			}
		}
		
		hItem = _treeObjList.GetNextItem(hItem, TVGN_NEXT);
	}
}

//�ִϸ��̼� ����Ʈ ������Ʈ
void ModelDlg::UpdateAnimationListCtrl()
{
	_lstAniList.DeleteAllItems();

	if (!_currentModel)
		return;

	auto& aniList = _currentModel->GetAnimationList();

	for (auto aniInfo : aniList) {
		int index = _lstAniList.GetItemCount();

		CString name = aniInfo.GetName().c_str();
		_lstAniList.InsertItem(index, name);

	}
}


//���õ� ���� �����Ѵ�.
void ModelDlg::OnDeleteModel()
{
	_currentModel = NULL;

	int selectIndex = _lstModelList.GetNextItem(-1, LVNI_SELECTED);
	SkinModel* model = (SkinModel*)_lstModelList.GetItemData(selectIndex);
	RM_MODEL.RemoveResource(model);

	_lstModelList.DeleteItem(selectIndex);
	
	UpdateControl();
}

//�� ����Ʈ Ŭ�� �̺�Ʈ, ���õ� �𵨿� �°� ���̾�α� ���� ����
void ModelDlg::OnNMClickModelDlgModelListCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;

	if (index >= 0) {
		_currentModel = (SkinModel*)_lstModelList.GetItemData(index);
		UpdateControl();

		auto aniList = _currentModel->GetAnimationList();
		
	}
	
	*pResult = 0;
}

//�� ����Ʈ ��Ʈ�� ��Ŭ�� �̺�Ʈ, �˾� �޴��� �����ش�.
void ModelDlg::OnNMRClickModeldlgModelListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;

	CPoint pt;
	GetCursorPos(&pt);

	CMenu menu, *pmenu;
	menu.LoadMenu(IDR_MODELDLG_MODELLIST_POPUP);

	pmenu = menu.GetSubMenu(0);
	if (index < 0) 
		pmenu->EnableMenuItem(ID_DELETE_MODEL, MF_DISABLED | MF_GRAYED);
	else
		pmenu->EnableMenuItem(ID_DELETE_MODEL, MF_ENABLED);

	pmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

}

//Change Current Model PosX 
void ModelDlg::OnDeltaposModeldlgPosxSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (!_currentModel) { return; }
	
	XMFLOAT3 pos = _currentModel->GetCenter();
	
	if (pNMUpDown->iDelta < 0) {
		pos.x += 0.1f;
	} else {
		pos.x -= 0.1f;
	}

	_currentModel->SetCenter(pos);
	UpdateControl();

	*pResult = 0;
}

//Change Current Model PosY 
void ModelDlg::OnDeltaposModeldlgPosySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 pos = _currentModel->GetCenter();

	if (pNMUpDown->iDelta < 0) {
		pos.y += 0.1f;
	}
	else {
		pos.y -= 0.1f;
	}

	_currentModel->SetCenter(pos);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model PosZ
void ModelDlg::OnDeltaposModeldlgPoszSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 pos = _currentModel->GetCenter();

	if (pNMUpDown->iDelta < 0) {
		pos.z += 0.1f;
	}
	else {
		pos.z -= 0.1f;
	}

	_currentModel->SetCenter(pos);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model RotX 
void ModelDlg::OnDeltaposModeldlgRotxSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 rot = _currentModel->GetRotate();

	if (pNMUpDown->iDelta < 0) {
		rot.x += 0.1f;
	}
	else {
		rot.x -= 0.1f;
	}

	_currentModel->SetRotate(rot);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model RotY
void ModelDlg::OnDeltaposModeldlgRotySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 rot = _currentModel->GetRotate();

	if (pNMUpDown->iDelta < 0) {
		rot.y += 0.1f;
	}
	else {
		rot.y -= 0.1f;
	}

	_currentModel->SetRotate(rot);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model RotZ
void ModelDlg::OnDeltaposModeldlgRotzSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 rot = _currentModel->GetRotate();

	if (pNMUpDown->iDelta < 0) {
		rot.z += 0.1f;
	}
	else {
		rot.z -= 0.1f;
	}

	_currentModel->SetRotate(rot);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model SizeX 
void ModelDlg::OnDeltaposModeldlgSizexSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 size = _currentModel->GetSize();

	if (pNMUpDown->iDelta < 0) {
		size.x += 0.1f;
	}
	else {
		size.x -= 0.1f;
	}

	_currentModel->SetSize(size);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model SizeY
void ModelDlg::OnDeltaposModeldlgSizeySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 size = _currentModel->GetSize();

	if (pNMUpDown->iDelta < 0) {
		size.y += 0.1f;
	}
	else {
		size.y -= 0.1f;
	}

	_currentModel->SetSize(size);
	UpdateControl();
	*pResult = 0;
}

//Change Current Model SizeZ
void ModelDlg::OnDeltaposModeldlgSizezSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	if (!_currentModel) { return; }

	XMFLOAT3 size = _currentModel->GetSize();

	if (pNMUpDown->iDelta < 0) {
		size.z += 0.1f;
	}
	else {
		size.z -= 0.1f;
	}

	_currentModel->SetSize(size);
	UpdateControl();
	*pResult = 0;
}


//assimp�� ���� ������ �ε��Ѵ�.
void ModelDlg::OnLoadModel()
{
	CFileDialog fileDlg(TRUE); // ���Ͽ���

	if (fileDlg.DoModal() != IDOK) {
		return;
	}

	wstring path = fileDlg.GetPathName();
	LoadModelStateDlg stateDlg;

	if (stateDlg.DoModal() != IDOK) {
		return;
	}

	auto flag = stateDlg.GetAiState();
	InsertModel(fileDlg.GetFileName(), fileDlg.GetPathName(), RM_MODEL.AddResource(path, &flag));
}


//������Ʈ Ʈ�� ��Ʈ�� Ŭ�� �̺�Ʈ
void ModelDlg::OnNMClickModeldlgObjectTree(NMHDR *pNMHDR, LRESULT *pResult)
{


	if (HTREEITEM hItem = _treeObjList.CheckBoxHitEvent()) {
		bool isDraw = false;
		BaseMesh* mesh = (BaseMesh*)_treeObjList.GetItemData(hItem);

		if (_treeObjList.GetCheck(hItem)) {
			isDraw = false;
			_treeObjList.CheckChild(hItem, isDraw);
		} else {
			isDraw = true;
			_treeObjList.CheckParent(hItem);
			_treeObjList.CheckChild(hItem, isDraw);
		}

		//������Ʈ�� ������ ���
		if (mesh) {
			mesh->isDraw = isDraw;
		}
		//üũ �ڽ��� üũ or üũ���� �� ���, ���� ������Ʈ���� ����
		else {
			UpdateTreeControlCheckEvent(hItem);
		}
	}

}

//tm ���� �ʱ�ȭ ��ư �̺�Ʈ
void ModelDlg::OnBnClickedButton1()
{
	if (_currentModel) {
		_currentModel->SetCenter(XMFLOAT3(0.f, 0.f, 0.f));
		_currentModel->SetSize(XMFLOAT3(1.f, 1.f, 1.f));
		_currentModel->SetRotate(XMFLOAT3(0.f, 0.f, 0.f));
		_currentModel->SetNormalize(false);
	}

	UpdateControl();
}

//�븻������ üũ�ڽ� �̺�Ʈ
void ModelDlg::OnBnClickedModeldlgModelNormalizeCheck()
{
	if (!_currentModel) { return; }

	if (_checkModelNormalize.GetCheck()) {
		_currentModel->SetNormalize(true);
	}
	else {
		_currentModel->SetNormalize(false);
	}
}

//�ִϸ��̼� ��� ��ư�̺�Ʈ
void ModelDlg::OnBnClickedModeldlgAniplayBtn()
{
	auto idx = _lstAniList.GetNextItem(-1, LVNI_SELECTED);
	
	if (idx < 0) {
		AfxMessageBox(L"Not Selected Animaiton!");
		return;
	}
	_currentModel->PlayAni(idx);
}


//�ִϸ��̼� �Ͻ����� ��ư�̺�Ʈ
void ModelDlg::OnBnClickedModeldlgAnipauseBtn()
{
	auto idx = _lstAniList.GetNextItem(-1, LVNI_SELECTED);
	if (idx < 0)	return;

	_currentModel->PauseAni();
}

//�ִϸ��̼� ���� ��ư�̺�Ʈ
void ModelDlg::OnBnClickedModeldlgAnistopBtn()
{
	auto idx = _lstAniList.GetNextItem(-1, LVNI_SELECTED);
	if (idx < 0)	return;

	_currentModel->StopAni();
}


//�ִϸ��̼� ����Ʈ ��Ʈ�� Ŭ�� �̺�Ʈ
void ModelDlg::OnNMClickModeldlgAniListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	auto idx = _lstAniList.GetNextItem(-1, LVNI_SELECTED);

	if (idx >= 0) {
		_checkAniRepeat.SetCheck(_currentModel->GetAnimationList()[idx].IsRepeat());
	}
		
	
}

//�ִϸ��̼� �ݺ� ��� üũ�ڽ� �̺�Ʈ
void ModelDlg::OnBnClickedModeldlgModelAnirepeatCheck()
{
	if (!_currentModel) { return; }

	auto idx = _lstAniList.GetNextItem(-1, LVNI_SELECTED);
	if (idx < 0)	return;

	_currentModel->GetAnimationList()[idx].TurnRepeat();
}


//�ִϸ��̼� ����Ʈ ��Ʈ�� ������ ���콺 Ŭ�� �̺�Ʈ
void ModelDlg::OnNMRClickModeldlgAniListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (!_currentModel)
		return;

	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;


	CPoint pt;
	GetCursorPos(&pt);

	CMenu menu, *pmenu;
	menu.LoadMenu(IDR_MODELDLG_MODELLIST_POPUP);

	pmenu = menu.GetSubMenu(1);
	pmenu->EnableMenuItem(ID_LOAD_ANIMATION, MF_DISABLED | MF_GRAYED);
	
	if(index < 0)
		pmenu->EnableMenuItem(ID_LOAD_ANIMATION, MF_ENABLED);

	pmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

//�ִϸ��̼� �߰� �̺�Ʈ
void ModelDlg::OnLoadAnimation()
{
	ModelLoader load;

	CFileDialog fileDlg(TRUE); // ���Ͽ���
	if (fileDlg.DoModal() != IDOK) {
		return;
	}

	wstring path = fileDlg.GetPathName();
	LoadModelStateDlg stateDlg(TRUE);

	if (stateDlg.DoModal() != IDOK) {
		return;
	}

	auto flag = stateDlg.GetAiState();
	load.LoadAnimation(path.c_str(), _currentModel, flag);
	UpdateAnimationListCtrl();
}
