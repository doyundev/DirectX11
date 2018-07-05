//====================================================================
//			## TextureDlg ## (Texture Management Dlg)
//====================================================================
#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "model\SimpleTextureModel.h"
#include "model\SkinModel.h"


class TextureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TextureDlg)

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_TEXTURE };
#endif
/*************************************** ��� �Լ� *************************************/
public:
	TextureDlg(CWnd* pParent = NULL);  
	virtual ~TextureDlg();

protected:
	//���̾�α� �����Լ�
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//���̾�α� �޽��� �Լ�
	afx_msg void OnPaint();
	afx_msg void OnInsertInserttexture();
	afx_msg void OnDeleteDeletetexture();

	//�ؽ��� ����Ʈ ��Ʈ�� �޽��� �̺�Ʈ
	afx_msg void OnNMClickTexdlgTextureListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTexdlgTextureListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	
	//�� �޺��ڽ� ��Ӵٿ� �޽��� �̺�Ʈ
	afx_msg void OnCbnDropdownTexdlgComboModellist();
	afx_msg void OnCbnSelchangeTexdlgComboModellist();

	//OBJ TREE CTRL �̺�Ʈ
	afx_msg void OnNMClickTexdlgTreeObjlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTexdlgTreeObjlist(NMHDR *pNMHDR, LRESULT *pResult);

	//�ؽ��� �޺� �ڽ� �̺�Ʈ
	afx_msg void OnCbnDropdownTexdlgComboDiffuse();
	afx_msg void OnCbnDropdownTexdlgComboAlpha();
	afx_msg void OnCbnDropdownTexdlgComboBump();
	afx_msg void OnCbnSelchangeTexdlgComboDiffuse();
	afx_msg void OnCbnSelchangeTexdlgComboAlpha();
	afx_msg void OnCbnSelchangeTexdlgComboBump();
	

	DECLARE_MESSAGE_MAP()

private:
	void UpdateTextureList();						//�ؽ��� ����Ʈ ������Ʈ �̺�Ʈ
	void UpdateSelectTexItem();						//�ؽ��� ���� �̺�Ʈ
	void UpdateObjList();							//���� ������Ʈ ���� ������Ʈ
	void UpdateObjInfo();							//���õ� ������Ʈ ������ ������Ʈ

	//�޺��ڽ� ��Ӵٿ� �� ����Ʈ ������Ʈ
	void UpdateCmbDropDownEvent(CComboBox* pCmb,	vector<CString> itmList);		



/************************************** ��� ���� ***************************************/
private:
	PWindowRender				_pWindow;			//���̾�α� �����쿡�� ���� DX11 ���� ����
	XMFLOAT3					_bgColor;			//���̾�α� ������
	SimpleTextureModel*			_textureImage;		//���� ���õ� �ؽ��ĸ� ǥ���ϱ����� Square ��
	SkinModel*					_currentModel;
	HierarchyMesh*				_currentMesh;			

	//��Ʈ�� ������ ����							
	CListCtrl					_lstTexInfo;		//�ؽ��� ����Ʈ�� �����ִ� ����Ʈ ��Ʈ�Ѱ� ����� ����
	CCustomTreeCtrl				_treeObjInfo;		//������Ʈ ������ �����ִ� Ʈ�� ��Ʈ�Ѱ� ����� ����
	CComboBox					_cmbModelList;		//�� ����Ʈ �����ϴ� �޺��ڽ��� ����� ����
													
	CComboBox					_cmbDiffuseMap;		//��ǻ�� �ؽ��� �޺��ڽ� ���� ����
	CComboBox					_cmbAlphaMap;		//���� �ؽ��� �޺��ڽ� ���� ����
	CComboBox					_cmbBumpMap;		//�븻 �ؽ��� �޺��ڽ� ���� ����

	ID3D11DeviceContext*		_dc;
};

