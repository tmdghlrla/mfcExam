
// gLimExamDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gLimExam.h"
#include "gLimExamDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgLimExamDlg 대화 상자



CgLimExamDlg::CgLimExamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMEXAM_DIALOG, pParent)
	, m_nX(0)
	, m_nY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgLimExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POS_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_nY);	
}

BEGIN_MESSAGE_MAP(CgLimExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CgLimExamDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CgLimExamDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CgLimExamDlg::OnBnClickedBtnLoad)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CgLimExamDlg 메시지 처리기

BOOL CgLimExamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgLimExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgLimExamDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgLimExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgLimExamDlg::OnBnClickedBtnImage()
{
	int nWidth = 1200;
	int nHeight = 800;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	//  이미지가 흑백 (8비트 그레이스케일)로 생성될 때 처리를 따로 해줘야 한다.
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	// 이미지의 바이트 수 저장
	int nPitch = m_image.GetPitch();

	// 위에서 만든 image의 시작 주소 값을 가져온다.
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	UpdateDisplay();
}

int repeat = 100;
int* posX = new int[repeat];
int* posY = new int[repeat];
bool check = false;
void CgLimExamDlg::OnBnClickedBtnAction()
{
	int nEditX = GetDlgItemInt(IDC_EDIT_POS_X);
	int nEditY = GetDlgItemInt(IDC_EDIT_POS_Y);		

	CString message;
	CString g_strFilePath;

	// 이미지 생성이 안됐을 때 처리	
	if (!m_image) {
		AfxMessageBox(_T("먼저 이미지 생성을 하세요."));
		return;
	}

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	message.Format(_T("X 값: 0 ~ %d \nY 값: 0 ~ %d"), nWidth, nHeight);

	// x, y 값이 최대값을 초과했는지 확인
	if (nEditX > nWidth || nEditY > nHeight) {
		AfxMessageBox(message);
		return;
	}	

	check = true;
	for (int i = 0; i < repeat; i++) {
		moveCircle(nEditX, nEditY, i);
		g_strFilePath.Format(_T("C:\\image\\save%d.bmp"), i);
		m_image.Save(g_strFilePath);
		Sleep(10);
	}
}

void CgLimExamDlg::moveCircle(int nEditX, int nEditY, int i) {
	static int nSttX = nEditX;
	static int nSttY = nEditY;

	int nGray = 80;

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	int nRadius = 10;

	// 이미지의 바이트 수 저장
	int nPitch = m_image.GetPitch();
	// 위에서 만든 image의 시작 주소 값을 가져와 저장
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 파라미터 첫번째 설정하려는 메모리 시작 주소값
	// 두번째 설정하려는 값
	// 세번째 바이트 수	
	drawCircle(fm, nSttX, nSttY, nRadius, 0xff, repeat);
	drawCircle(fm, ++nSttX, ++nSttY, nRadius, nGray, i);

	UpdateDisplay();
}

void CgLimExamDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray, int i) {
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	if (i != repeat) {
		posX[i] = nCenterX;
		posY[i] = nCenterY;
	}

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			// 원의 반지름 보다 작으면 그린다.
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

bool CgLimExamDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius) {
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CgLimExamDlg::UpdateDisplay() {
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CgLimExamDlg::OnBnClickedBtnLoad()
{	
	if (!check) {
		AfxMessageBox(_T("먼저 Action 버튼을 눌러 이미지를 저장하세요"));
		return;
	}

	if (m_image != NULL) {
		m_image.Destroy();
	}

	CString filePath;

	int nRand = rand() % repeat;
	filePath.Format(_T("C:\\image\\save%d.bmp"), nRand);
	m_image.Load(filePath);

	int nPosX = posX[nRand];
	int nPosY = posY[nRand];
	
	std::cout << "원의 중앙 좌표값 (" << nPosX << ", " << nPosY  << ")" << std::endl;
	

	UpdateDisplay();
}


void CgLimExamDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	/*if (m_image) {
		delete m_image;
	}*/
}
