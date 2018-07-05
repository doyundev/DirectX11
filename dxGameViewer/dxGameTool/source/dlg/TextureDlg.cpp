#include "stdafx.h"
#include "dxGameTool.h"
#include "TextureDlg.h"
#include "afxdialogex.h"


// TextureDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TextureDlg, CDialogEx)

TextureDlg::TextureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_TEXTURE, pParent)
{

}

TextureDlg::~TextureDlg()
{
}

void TextureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//��Ʈ�� ������� ���� ����
	DDX_Control(pDX, IDC_TEXDLG_TEXTURE_LISTCTRL, _lstTexInfo);
	DDX_Control(pDX, IDC_TEXDLG_COMBO_MODELLIST, _cmbModelList);
	DDX_Control(pDX, IDC_TEXDLG_TREE_OBJLIST, _treeObjInfo);
	DDX_Control(pDX, IDC_TEXDLG_COMBO_DIFFUSE, _cmbDiffuseMap);
	DDX_Control(pDX, IDC_TEXDLG_COMBO_ALPHA, _cmbAlphaMap);
	DDX_Control(pDX, IDC_TEXDLG_COMBO_BUMP, _cmbBumpMap);
}


BEGIN_MESSAGE_MAP(TextureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_COMMAND(ID_INSERT_TEXTURE, &TextureDlg::OnInsertInserttexture)
	ON_COMMAND(ID_DELETE_TEXTURE, &TextureDlg::OnDeleteDeletetexture)
	ON_CBN_DROPDOWN(IDC_TEXDLG_COMBO_MODELLIST, &TextureDlg::OnCbnDropdownTexdlgComboModellist)
	ON_NOTIFY(NM_CLICK, IDC_TEXDLG_TEXTURE_LISTCTRL, &TextureDlg::OnNMClickTexdlgTextureListctrl)
	ON_NOTIFY(NM_RCLICK, IDC_TEXDLG_TEXTURE_LISTCTRL, &TextureDlg::OnNMRClickTexdlgTextureListctrl)
	ON_CBN_SELCHANGE(IDC_TEXDLG_COMBO_MODELLIST, &TextureDlg::OnCbnSelchangeTexdlgComboModellist)
	ON_NOTIFY(NM_CLICK, IDC_TEXDLG_TREE_OBJLIST, &TextureDlg::OnNMClickTexdlgTreeObjlist)
	ON_CBN_DROPDOWN(IDC_TEXDLG_COMBO_DIFFUSE, &TextureDlg::OnCbnDropdownTexdlgComboDiffuse)
	ON_CBN_DROPDOWN(IDC_TEXDLG_COMBO_ALPHA, &TextureDlg::OnCbnDropdownTexdlgComboAlpha)
	ON_CBN_DROPDOWN(IDC_TEXDLG_COMBO_BUMP, &TextureDlg::OnCbnDropdownTexdlgComboBump)
	ON_CBN_SELCHANGE(IDC_TEXDLG_COMBO_DIFFUSE, &TextureDlg::OnCbnSelchangeTexdlgComboDiffuse)
	ON_CBN_SELCHANGE(IDC_TEXDLG_COMBO_ALPHA, &TextureDlg::OnCbnSelchangeTexdlgComboAlpha)
	ON_CBN_SELCHANGE(IDC_TEXDLG_COMBO_BUMP, &TextureDlg::OnCbnSelchangeTexdlgComboBump)
	ON_NOTIFY(NM_DBLCLK, IDC_TEXDLG_TREE_OBJLIST, &TextureDlg::OnNMDblclkTexdlgTreeObjlist)
END_MESSAGE_MAP()


// TextureDlg �޽��� ó�����Դϴ�.



BOOL TextureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect winSize;
	this->GetWindowRect(&winSize);
	
	//�ؽ��� ǥ���� �׷� ��Ʈ�� ũ��
	CRect rc;
	this->GetDlgItem(IDC_TEX_IMGFRAME_GROUP)->GetWindowRect(&rc);
	ScreenToClient(&rc);

	//DX�� ������ �� ������� ��ũ�� ����
	_pWindow = DEVICEMANAGER.InitRenderScreen(m_hWnd, winSize.Width(), winSize.Height(), 0.1f, 10.f);
	
	_pWindow->viewport.TopLeftX = (float)rc.left + 12;		_pWindow->viewport.TopLeftY = (float)rc.top + 14;
	_pWindow->viewport.Width = (float)rc.Width() - 2;		_pWindow->viewport.Height = (float)rc.Height() - 2;

	

	//��Ʈ�� ������ �ʱ�ȭ
	_lstTexInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	_lstTexInfo.InsertColumn(0, L"Name", LVCFMT_LEFT, 120);

	//���̾�α� ���� ���� �ʱ�ȭ
	COLORREF color = GetSysColor(COLOR_3DFACE);		
	_bgColor = XMFLOAT3{ (float)GetRValue(color) / 255.f,	(float)GetGValue(color) / 255.f,	(float)GetBValue(color) / 255.f};
	

	_textureImage = new SimpleTextureModel;
	 
	//�޺��ڽ� ���� �ʱ�ȭ.
	_cmbDiffuseMap.EnableWindow(false);
	_cmbAlphaMap.EnableWindow(false);
	_cmbBumpMap.EnableWindow(false);

	UpdateTextureList();

	_dc = DEVICEMANAGER.GetDeviceContext();
	return TRUE;  			  
}


//���� �׸� ������ �������� ȣ��ȴ�. 
void TextureDlg::OnPaint()
{
	CPaintDC dc(this);

	if (!_textureImage->GetTexture()) { return; }

	//���õ� �ؽ��İ� ������ ȭ�鿡 �׷��ش�.
	DEVICEMANAGER.BeginScene(_pWindow, _bgColor.x, _bgColor.y, _bgColor.z, 1);

	//proj, view ��Ʈ������ ������ �°� ��ȯ�Ѵ�.
	XMMATRIX matIdentity = XMMatrixIdentity();
	RM_SHADER.SetShaderParameters(_dc, matIdentity, matIdentity);


	//���ĺ��� Ȱ��ȭ, ���� ���� ����
	DEVICEMANAGER.TurnZBufferOff();
	DEVICEMANAGER.TurnOnAlphaBlending();

	//����
	_textureImage->Render(_dc);
	
	DEVICEMANAGER.TurnOffAlphaBlending();
	DEVICEMANAGER.TurnZBufferOn();

	DEVICEMANAGER.EndScene(_pWindow);

}


//�� ����Ʈ ������ ���콺 ��ư Ŭ�� �̺�Ʈ
//�ؽ��ĸ� �߰��ϰų�, �����Ѵ�.
void TextureDlg::OnNMRClickTexdlgTextureListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	NM_LISTVIEW* pNMView = (NM_LISTVIEW*)pNMHDR;
	int index = pNMView->iItem;

	CPoint pt;
	GetCursorPos(&pt);

	CMenu menu, *pmenu;
	menu.LoadMenu(IDR_TEXDLG_TEXLIST_POPUP);
	pmenu = menu.GetSubMenu(0);

	//���õ� �������� �ִ� ��� ���� �޴���, ���� ��� �߰� �޴��� Setting �Ѵ�.
	if (index < 0) {
		pmenu->EnableMenuItem(ID_DELETE_TEXTURE, MF_DISABLED | MF_GRAYED);
	}
	else {
		pmenu->EnableMenuItem(ID_DELETE_TEXTURE, MF_ENABLED);
		
	}

	//���콺 ��ġ�� �޴� ����
	pmenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);

	*pResult = 0;
}


//�ؽ��� �߰� �޴� ���� �̺�Ʈ
void TextureDlg::OnInsertInserttexture()
{
	//���� ���� ���� ���̾�α� ȣ��
	CFileDialog dlg(TRUE); 
	if (dlg.DoModal() == IDOK) {
		if (!RM_TEXTURE.AddResource((wstring)dlg.GetPathName(), &dlg.GetFileExt())) {
			//�ؽ��� �ε� �����ϸ� �޽��� �ڽ� ȣ��
			AfxMessageBox(L"Load Failed");		
		} else {			
			//�����ϸ� ���� ����
			UpdateTextureList();
		}
	}
}


//�ؽ��� ���� ����� ������ ������Ʈ �Ѵ�.
void TextureDlg::UpdateTextureList()
{
	//���� ������ ���� ����
	_lstTexInfo.DeleteAllItems();

	//�ؽ��� �Ŵ����� ��ϵ� ����Ʈ �����ͼ� ������ �籸���Ѵ�.
	if (!RM_TEXTURE.GetResource().empty()) {
		map<wstring, Texture*> _texItemList = RM_TEXTURE.GetResource();
		map<wstring, Texture*>::iterator iterBegin = _texItemList.begin();
		map<wstring, Texture*>::iterator iterEnd = _texItemList.end();

		int index = 0;
		for (iterBegin; iterBegin != iterEnd; iterBegin++) {
			CString name = MYUTIL::getFileName(iterBegin->first.c_str());
			_lstTexInfo.InsertItem(index, name);
			index++;
		}
	}
	
	//���õ� �ؽ��� ������ ������Ʈ �Ѵ�.
	UpdateSelectTexItem();

}



//�޽��� ó�� �Լ�
BOOL TextureDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	
	//���� �߰��Ǹ� �ؽ��� ���� ������Ʈ
	if (message == WM_INSERT_MODEL) {
		UpdateTextureList();
	}
	//���� �����Ǹ�
	else if (message == WM_DELETE_MODEL) {
		if (_currentModel == (SkinModel*)wParam) {
			_currentModel = NULL;
			_currentMesh = NULL;

			_cmbModelList.SetCurSel(-1);
			UpdateObjList();
			UpdateObjInfo();
		}
	}

	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}


//�ؽ��� ����Ʈ ���� �̺�Ʈ
void TextureDlg::OnNMClickTexdlgTextureListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	//�ֱ� ������ �ؽ��� ���� ����
	UpdateSelectTexItem();

	*pResult = 0;
}


//�ؽ��� ���� �޴� �̺�Ʈ
//���õ� �ؽ��ĸ� �����Ѵ�.
void TextureDlg::OnDeleteDeletetexture()
{
	//������ �ؽ��� ������ �����´�.
	int index = _lstTexInfo.GetNextItem(-1, LVNI_SELECTED);
	Texture* tex = RM_TEXTURE.GetResourceData(index);

	//�����Ǵ� �ؽ��ĸ� ����  ��� �� Ž�� �� null �ʱ�ȭ
	auto modelList = RM_MODEL.GetResource();

	for (auto data : modelList) {
		auto model = data.second;
		
		if (model == NULL) continue;
		
		for (auto& mData : model->GetMaterialList()) {
			if (tex == mData.diffuseMap) {
				mData.diffuseMap = NULL;
			}
			if (tex == mData.alphaMap) {
				mData.alphaMap = NULL;
			}
			if (tex == mData.normalMap) {
				mData.normalMap = NULL;
			}
		}
	}

	//�ؽ��� ���� ����
	RM_TEXTURE.RemoveResource(RM_TEXTURE.GetResourceKey(index)->c_str());
	//�ؽ��� ���� ������Ʈ
	UpdateTextureList();
	
}

//Texture Item Select Event
void TextureDlg::UpdateSelectTexItem()
{
	int index = _lstTexInfo.GetNextItem(-1, LVNI_SELECTED);

	//������ �ؽ��� ����� ���� ���
	if (index < 0) { 
		_textureImage->SetTexture(NULL);
		SetDlgItemText(IDC_TEXDLG_PATH_EDIT, L"");
	}
	//�ؽ��� ����Ʈ���� ������ ���
	else {
		_textureImage->SetTexture(RM_TEXTURE.GetResourceData(index)->data);
		SetDlgItemText(IDC_TEXDLG_PATH_EDIT, RM_TEXTURE.GetResourceKey(index)->c_str());
	}

	Invalidate(); 
}

//������Ʈ Ʈ�� ��Ʈ�� ������Ʈ
void TextureDlg::UpdateObjList()
{
	_treeObjInfo.DeleteAllItems();

	if (!_currentModel) { return; }

	//���õ� �� �̸��� ��Ʈ ���� ���
	HTREEITEM  hitem = _treeObjInfo.InsertItem(_currentModel->GetName().c_str(), TVI_ROOT, TVI_LAST);
	_treeObjInfo.SetCheck(hitem, true);

	for (auto& mesh : _currentModel->GetMeshList())
		_treeObjInfo.CreateItem(hitem, mesh->name.c_str(), (DWORD_PTR)mesh);
}


//������Ʈ ���� ǥ�� ��Ʈ�� ������Ʈ
void TextureDlg::UpdateObjInfo()
{
	_cmbDiffuseMap.ResetContent();
	_cmbAlphaMap.ResetContent();
	_cmbBumpMap.ResetContent();

	_cmbDiffuseMap.EnableWindow(false);
	_cmbAlphaMap.EnableWindow(false);
	_cmbBumpMap.EnableWindow(false);
	
	if (!_currentMesh)		{	return; 	}
	if (_currentMesh->matIdx == -1) {	return;		}

	_cmbDiffuseMap.EnableWindow(true);
	/*_cmbAlphaMap.EnableWindow(true);
	_cmbBumpMap.EnableWindow(true);*/

	_cmbDiffuseMap.AddString(L"None");
	_cmbAlphaMap.AddString(L"None");
	_cmbBumpMap.AddString(L"None");

	_cmbDiffuseMap.SetCurSel(0);
	_cmbAlphaMap.SetCurSel(0);
	_cmbBumpMap.SetCurSel(0);

	bool flag[3] = { false, };
	int texCnt = _lstTexInfo.GetItemCount();
	
	for (int i = 0; i < texCnt; i++) {
		Texture* pTex = RM_TEXTURE.GetResourceData(i);
		CString texName = pTex->name.c_str();

		auto materialList = _currentModel->GetMaterialList();

		if (materialList.empty()) 	continue;
	

		auto materialInfo = materialList[_currentMesh->matIdx];

		if (materialInfo.diffuseMap == pTex) {
			_cmbDiffuseMap.AddString(texName);
			_cmbDiffuseMap.SetCurSel(1);
			flag[0] = true;
		}
		if (materialInfo.alphaMap == pTex) {
			_cmbAlphaMap.AddString(texName);
			_cmbAlphaMap.SetCurSel(1);
			flag[1] = true;
		}
		if (materialInfo.normalMap == pTex) {
			_cmbBumpMap.AddString(texName);
			_cmbBumpMap.SetCurSel(1);
			flag[2] = true;
		}

		if (flag[0] && flag[1] && flag[2]) {
			break;
		}
	}
}

//�޺��ڽ� �̺�Ʈ
void TextureDlg::UpdateCmbDropDownEvent(CComboBox * pCmb, vector<CString> itmList)
{
	CString selStr;
	int selIdx = pCmb->GetCurSel();

	if (selIdx >= 0) {
		pCmb->GetLBText(pCmb->GetCurSel(), selStr);
	}
	
	pCmb->ResetContent();

	for (int i = 0; i < itmList.size(); i++) {
		CString insertStr = itmList[i];
		pCmb->AddString(insertStr);

		if (selStr == insertStr) {
			pCmb->SetCurSel(i);
		}
	}

}



//Ʈ�� ��Ʈ�ѿ� ǥ�õ� ������ ���� �̺�Ʈ
void TextureDlg::OnNMClickTexdlgTreeObjlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem = _treeObjInfo.HitEvent();
	if (!hItem) {
		_currentMesh = NULL;
	}
	else {
		_treeObjInfo.SelectItem(hItem);
		_currentMesh = (HierarchyMesh*)_treeObjInfo.GetItemData(hItem);
	}

	UpdateObjInfo();
	Invalidate(TRUE);

	*pResult = 0;
}

//ModelList Combox Drop Event
void TextureDlg::OnCbnDropdownTexdlgComboModellist()
{
	vector<CString> itmList;
	vector<DWORD_PTR> modelData;

	int itmCnt = (int)RM_MODEL.GetResource().size();
	itmList.reserve(itmCnt + 1);
	modelData.reserve(itmCnt + 1);

	itmList.push_back(L"None");
	modelData.push_back(NULL);

	for (int i = 0; i < itmCnt; i++) {
		auto model = RM_MODEL.GetResourceData(i);
		itmList.push_back(model->GetName().c_str());
		modelData.push_back((DWORD_PTR)model);
	}

	UpdateCmbDropDownEvent(&_cmbModelList, itmList);

	for (int i = 0; i < itmCnt+1; i++) {
		_cmbModelList.SetItemData(i, modelData[i]);
	}
}

//�ؽ��� �޺� �ڽ� ��Ӵٿ� �̺�Ʈ
void TextureDlg::OnCbnDropdownTexdlgComboDiffuse()
{
	vector<CString> itmList;

	int itmCnt = _lstTexInfo.GetItemCount();
	itmList.reserve(itmCnt + 1);
	itmList.push_back(L"None");

	for (int i = 0; i < itmCnt; i++) {
		itmList.push_back(_lstTexInfo.GetItemText(i, 0));
	}

	UpdateCmbDropDownEvent(&_cmbDiffuseMap, itmList);
}

//���ĸ� �޺��ڽ� �̺�Ʈ
void TextureDlg::OnCbnDropdownTexdlgComboAlpha()
{
	vector<CString> itmList;

	int itmCnt = _lstTexInfo.GetItemCount();
	itmList.reserve(itmCnt + 1);
	itmList.push_back(L"None");

	for (int i = 0; i < itmCnt; i++) {
		itmList.push_back(_lstTexInfo.GetItemText(i, 0));
	}
	
	UpdateCmbDropDownEvent(&_cmbAlphaMap, itmList);
}

//�븻�� �޺��ڽ� �̺�Ʈ
void TextureDlg::OnCbnDropdownTexdlgComboBump()
{
	vector<CString> itmList;

	int itmCnt = _lstTexInfo.GetItemCount();
	itmList.reserve(itmCnt + 1);
	itmList.push_back(L"None");

	for (int i = 0; i < itmCnt; i++) {
		itmList.push_back(_lstTexInfo.GetItemText(i, 0));
	}

	UpdateCmbDropDownEvent(&_cmbBumpMap, itmList);
}



//ModelList Combox Change Event
void TextureDlg::OnCbnSelchangeTexdlgComboModellist()
{
	int selIdx = _cmbModelList.GetCurSel();

	if (selIdx < 0) {
		_currentModel = NULL;
	}
	else {

		_currentModel = (SkinModel*)_cmbModelList.GetItemData(selIdx);
	}
	
	UpdateObjList();
	Invalidate();
}


//��ǻ��� �޺��ڽ� ���� �̺�Ʈ
void TextureDlg::OnCbnSelchangeTexdlgComboDiffuse()
{
	int matIdx = _currentMesh->matIdx;

	if (matIdx < 0) return;

	int selIdx = _cmbDiffuseMap.GetCurSel() - 1;
	if (selIdx >= 0) {
		_currentModel->GetMaterialList()[matIdx].diffuseMap = RM_TEXTURE.GetResourceData(selIdx);
	}
	else {
		_currentModel->GetMaterialList()[matIdx].diffuseMap = NULL;
	}

	
}

//���ĸ� �޺��ڽ� ���� �̺�Ʈ
void TextureDlg::OnCbnSelchangeTexdlgComboAlpha()
{
	int matIdx = _currentMesh->matIdx;

	if (matIdx < 0) return;

	int selIdx = _cmbAlphaMap.GetCurSel() - 1;
	if (selIdx >= 0) {
		_currentModel->GetMaterialList()[matIdx].alphaMap = RM_TEXTURE.GetResourceData(selIdx);
	}
	else {
		_currentModel->GetMaterialList()[matIdx].alphaMap = NULL;
	}
}

//�븻�� �޺��ڽ� ���� �̺�Ʈ
void TextureDlg::OnCbnSelchangeTexdlgComboBump()
{
	int matIdx = _currentMesh->matIdx;

	if (matIdx < 0) return;

	int selIdx = _cmbBumpMap.GetCurSel() - 1;
	if (selIdx >= 0) {
		_currentModel->GetMaterialList()[matIdx].normalMap = RM_TEXTURE.GetResourceData(selIdx);
	}
	else {
		_currentModel->GetMaterialList()[matIdx].normalMap = NULL;
	}
}



//���� Ŭ������ Ʈ�� Ȯ��� ������ ��Ʈ�� ������Ʈ
void TextureDlg::OnNMDblclkTexdlgTreeObjlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	Invalidate();
	*pResult = 0;
}
