//====================================================================
//			## LoadModelStateDlg ## (Set Load Model Option)
//====================================================================
#pragma once
#include "afxwin.h"


// LoadModelStateDlg ��ȭ �����Դϴ�.
class LoadModelStateDlg : public CDialogEx
{

	DECLARE_DYNAMIC(LoadModelStateDlg)

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_LOADMODEL_STATE };
#endif

/******************************************** ��� �Լ� *****************************************/
public:
	LoadModelStateDlg(BOOL isAniInfo = FALSE, CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~LoadModelStateDlg();

	//���¿� �°� assimp ���� flag ��ȯ
	UINT	GetAiState()	{	return _aiFlag;	 };

protected:
	//���̾�α� �̺�Ʈ �Լ�
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	

	afx_msg void OnBnClickedLmsOk();
	DECLARE_MESSAGE_MAP()

/******************************************** ��� ���� *****************************************/
private:
	//��Ʈ�� ����
	CButton _checkHierarchy;
	CButton _checkFlipUV;
	CButton _checkFlipWind;
	CButton _checkConvertLeftHand;
	CButton _checkGenNormal;

	UINT	_aiFlag;		//assimp model load flag
	BOOL	_isAniInfo;		//only animation load

};
