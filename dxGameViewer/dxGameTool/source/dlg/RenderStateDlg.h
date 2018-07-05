//====================================================================
//			## RenderStateDlg ## (DX11 Device Render Control)
//====================================================================
#pragma once

class RenderStateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RenderStateDlg)

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_RENDER_STATE };
#endif

public:
	RenderStateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~RenderStateDlg();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	//�޽��� �̺�Ʈ
	afx_msg void OnBnClickedRenderdlgRendermodeSolidRadio();
	afx_msg void OnBnClickedRenderdlgRendermodeWireframeRadio();

	afx_msg void OnBnClickedRenderdlgCullmodeNoneRadio();
	afx_msg void OnBnClickedRenderdlgCullmodeFrontfaceRadio();
	afx_msg void OnBnClickedRenderdlgCullmodeBackfaceRadio();
	DECLARE_MESSAGE_MAP()
};
