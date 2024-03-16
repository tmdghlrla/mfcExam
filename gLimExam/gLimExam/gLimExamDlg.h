
// gLimExamDlg.h: 헤더 파일
//

#pragma once


// CgLimExamDlg 대화 상자
class CgLimExamDlg : public CDialogEx
{
private:
	CImage m_image;
// 생성입니다.
public:
	CgLimExamDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMEXAM_DIALOG };
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBtnAction();
	void UpdateDisplay();
	void moveCircle(int nEditX, int nEditY, int i);
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray, int k);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	int m_nX;
	int m_nY; 
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnDestroy();
};
