//====================================================================
//			## ModelDlg ## (Model Management Dlg)
//====================================================================
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "CustomTreeCtrl.h"


// ModelDlg ��ȭ �����Դϴ�.

class ModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModelDlg)

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MODEL };
#endif

/***************************************** ��� �Լ� ******************************************/
public:
	ModelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ModelDlg();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	//popup menu event
	afx_msg void OnLoadModel();
	afx_msg void OnLoadAnimation();
	afx_msg void OnDeleteModel();
	
	//tree & list ctrl event
	afx_msg void OnNMClickModelDlgModelListCtrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickModeldlgModelListctrl(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickModeldlgAniListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickModeldlgAniListctrl(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnNMClickModeldlgObjectTree(NMHDR *pNMHDR, LRESULT *pResult);

	//spin ctrl event
	afx_msg void OnDeltaposModeldlgPosxSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposModeldlgPosySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposModeldlgPoszSpin(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnDeltaposModeldlgRotxSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposModeldlgRotySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposModeldlgRotzSpin(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnDeltaposModeldlgSizexSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposModeldlgSizeySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposModeldlgSizezSpin(NMHDR *pNMHDR, LRESULT *pResult);

	
	
	//check box event
	afx_msg void OnBnClickedModeldlgModelNormalizeCheck();
	afx_msg void OnBnClickedModeldlgModelAnirepeatCheck();

	//reset btn event
	afx_msg void OnBnClickedButton1();

	//�ִϸ��̼� BTN Event
	afx_msg void OnBnClickedModeldlgAniplayBtn();
	afx_msg void OnBnClickedModeldlgAnipauseBtn();
	afx_msg void OnBnClickedModeldlgAnistopBtn();
	
	DECLARE_MESSAGE_MAP()

private:
	void InsertModel(CString name, CString path, SkinModel* model);		//����Ʈ ��Ʈ�ѿ� ���� �߰��Ѵ�.
	void UpdateControl();												//���̾�α׿� ��ġ�� ��Ʈ�� �����츦 ������Ʈ �Ѵ�.
	void UpdateTreeControl();											//Ʈ�� ��Ʈ�ѿ� ���õ� ���� ������ �����ش�.
	void UpdateTreeControlCheckEvent(HTREEITEM hItem);					//Ʈ�� ��Ʈ�� �������� üũ �ڽ� Ŭ���� �߻��ϴ� �̺�Ʈ�� ó���Ѵ�.
	void UpdateAnimationListCtrl();										//�ִϸ��̼� ��Ʈ�� ������Ʈ

/***************************************** ��� ���� ******************************************/
private:
	//���� ���õ� ��
	SkinModel*								_currentModel;

	//��Ʈ�� ����
	CButton									_checkModelNormalize;
	CButton									_checkAniRepeat;
	
	CListCtrl								_lstModelList;	
	CListCtrl								_lstAniList;
	
	CCustomTreeCtrl							_treeObjList;
	
	CEdit									_editModelPositionX;
	CEdit									_editModelPositionY;
	CEdit									_editModelPositionZ;
	CEdit									_editModelRotationX;
	CEdit									_editModelRotationY;
	CEdit									_editModelRotationZ;
	CEdit									_editModelSizeX;
	CEdit									_editModelSizeY;
	CEdit									_editModelSizeZ;
};
