#include <afxwin.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string>
#include "GameMap.h"
#include <thread>
#include <iostream>
#include <WinSock2.h>

using namespace std;

class FrameWnd : public CFrameWnd {
public:
	CClientDC* dc;
	CDC* mdc;
	CBitmap* bg, * bkbg, * bksd, * p1, * p2, * bksds, * p1s, * p2s, * rs;
	GameMap gamemap;
	int f = 0;

	char p1pic[9] = "p10s.bmp";
	char p2pic[9] = "p20s.bmp";
	char mappic[6] = "m.bmp";
	char r[6] = "w.bmp";

	LPDIRECTSOUND pDS;
	LPDIRECTSOUNDBUFFER pDSB_BG;
	HRESULT result;

	FrameWnd();
	LPDIRECTSOUNDBUFFER CreateSecondaryBuffer(LPSTR filename);
	int recv();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

class GameApp : public CWinApp {
public:
	FrameWnd* pf;
	BOOL InitInstance();
};

BOOL GameApp::InitInstance() {
	pf = new FrameWnd;

	pf->ShowWindow(m_nCmdShow);
	pf->UpdateWindow();
	this->m_pMainWnd = pf;

	pf->MoveWindow(NULL, NULL, 1000, 800);
	return TRUE;
}
GameApp gameapp;

BEGIN_MESSAGE_MAP(FrameWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

FrameWnd::FrameWnd() 
{
	GameMap* gm = &gamemap;
	Create(NULL, "SeekMyFriendY", WS_OVERLAPPEDWINDOW);

	result = DirectSoundCreate(NULL, &pDS, NULL);
	result = pDS->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY);

	pDSB_BG = CreateSecondaryBuffer(const_cast <LPSTR>("bg.wav"));
	//pDSB_BG->Play(0, 0, 1);
	dc = new CClientDC(this);
	mdc = new CDC;
	mdc->CreateCompatibleDC(dc);
	bg = new CBitmap;
	bg->m_hObject = (HBITMAP)::LoadImage(NULL, mappic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bkbg = new CBitmap;
	bkbg->m_hObject= (HBITMAP)::LoadImage(NULL, "bkbg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p1 = new CBitmap;
	p1->m_hObject = (HBITMAP)::LoadImage(NULL, p1pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p1s = new CBitmap;
	p1s->m_hObject= (HBITMAP)::LoadImage(NULL, p1pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p2 = new CBitmap;
	p2->m_hObject = (HBITMAP)::LoadImage(NULL, p2pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p2s = new CBitmap;
	p2s->m_hObject = (HBITMAP)::LoadImage(NULL, p2pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bksd = new CBitmap;
	bksd->m_hObject= (HBITMAP)::LoadImage(NULL, "bksd.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bksds = new CBitmap;
	bksds->m_hObject= (HBITMAP)::LoadImage(NULL, "bksd.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	rs = new CBitmap;
	rs->m_hObject = (HBITMAP)::LoadImage(NULL, r, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

}

int FrameWnd::recv() {
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err;
	err = WSAStartup(wVersionRequested, &wsaData);
	if (0 != err)
		return 0;
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
		return 0;

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6600);


	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	char recvBuf[100];
	SOCKADDR_IN addrClient;
	int lenAddr = sizeof(SOCKADDR);
	//sendto()
	do {

		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &lenAddr);
		gamemap.move(2, recvBuf[0]);
	} while (true);
	closesocket(sockSrv);
	WSACleanup();
}

LPDIRECTSOUNDBUFFER FrameWnd::CreateSecondaryBuffer(LPSTR filename) {
	HMMIO hmmio;
	MMRESULT mmresult;

	hmmio = mmioOpen(filename, NULL, NULL);

	MMCKINFO ckriff;

	ckriff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmresult = mmioDescend(hmmio, &ckriff, NULL, MMIO_FINDRIFF);
	MMCKINFO ckinfo;
	ckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmresult = mmioDescend(hmmio, &ckinfo, &ckriff, MMIO_FINDCHUNK);
	WAVEFORMATEX swfmt;
	if (-1 == mmioRead(hmmio, (HPSTR)&swfmt, sizeof(swfmt)));
	mmioAscend(hmmio, &ckinfo, 0);
	ckinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmresult = mmioDescend(hmmio, &ckinfo, &ckriff, MMIO_FINDCHUNK);
	LPDIRECTSOUNDBUFFER pTempBuf;
	DSBUFFERDESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.lpwfxFormat = &swfmt;
	desc.dwFlags = DSBCAPS_STATIC;
	desc.dwBufferBytes = ckinfo.cksize;
	result = pDS->CreateSoundBuffer(&desc, &pTempBuf, NULL);
	LPVOID pAudio;
	DWORD BytesAudio;

	pTempBuf->Lock(0, ckinfo.cksize, &pAudio, &BytesAudio, NULL, NULL, NULL);
	mmioRead(hmmio, (HPSTR)pAudio, BytesAudio);
	pTempBuf->Unlock(pAudio, BytesAudio, NULL, NULL);
	mmioClose(hmmio, 0);
	return pTempBuf;
}


void FrameWnd::OnPaint()
{
	CPaintDC dc(this);
	CRect rect_window;
	GetClientRect(&rect_window);
	int   winwidth = rect_window.Width();
	int   winheight = rect_window.Height();
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bm;
	bm.CreateCompatibleBitmap(&dc, winwidth, winheight);
	dcMem.SelectObject(&bm);
	CBrush  brush(RGB(255, 255, 255));
	dcMem.SelectObject(&brush);
	CRect rect2(0, 0, winwidth, winheight);
	dcMem.Rectangle(&rect2);

	int i = 0, j = 0, a = 7, b = 11, c = 0, d = 0;
	do {
		do {
			if (gamemap.map[i][j] == 1) {
				a = i;
				b = j;
			}
			if (gamemap.map[i][j] == 2) {
				c = i;
				d = j;
			}
			j++;
		} while (j < 8);
		j = 0;
		i++;
	} while (i < 12);

	mdc->SelectObject(bkbg);
	dc.BitBlt(0, 0, 1000, 800, mdc, 0, 0, SRCCOPY);

	mdc->SelectObject(bg);
	dc.BitBlt((400 - 200 * b), (300 - 200 * a), 1600, 2400, mdc, 0, 0, SRCCOPY);

	mdc->SelectObject(p1s);
	dc.BitBlt(400, 300, 200, 200, mdc, 0, 200, SRCPAINT);
	mdc->SelectObject(p1);
	dc.BitBlt(400, 300, 200, 200, mdc, 0, 0, SRCAND);

	mdc->SelectObject(p2s);
	dc.BitBlt((400 + 200 * (d - b)), (300 + 200 * (c - a)), 200, 200, mdc, 0, 200, SRCPAINT);
	mdc->SelectObject(p2);
	dc.BitBlt((400 + 200 * (d - b)), (300 + 200 * (c - a)), 200, 200, mdc, 0, 0, SRCAND);

	mdc->SelectObject(bksds);
	dc.BitBlt(0, 0, 1000, 800, mdc, 0, 800, SRCPAINT);
	mdc->SelectObject(bksd);
	dc.BitBlt(0, 0, 1000, 800, mdc, 0, 0, SRCAND);

	if (gamemap.endFlag == 1)
	{
		mdc->SelectObject(rs);
		dc.BitBlt(0, 0, 1000, 800, mdc, 0, 0, SRCCOPY);
	}
	else if (gamemap.endFlag == -1) {
		r[0] = 'l';
		rs->m_hObject = (HBITMAP)::LoadImage(NULL, r, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		mdc->SelectObject(rs);
		dc.BitBlt(0, 0, 1000, 800, mdc, 0, 0, SRCCOPY);
	}

	SetTimer(1, 100, NULL);
}

BOOL FrameWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	//CFrameWnd::OnEraseBkgnd(pDC);
	return true;

}


void FrameWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (this->gamemap.endFlag == -1 || this->gamemap.endFlag == 1)
		return;
	char d = 'a';
	switch (nChar) {
	case (38):
		gamemap.move(1, 'w');
		d = 'w';
		break;
	case(40):
		gamemap.move(1, 's');
		d = 's';
		break;
	case(37):
		gamemap.move(1, 'a');
		d = 'a';
		break;
	case(39):
		gamemap.move(1, 'd');
		d = 'd';
		break;
	}
	if (p1pic[2] == '0')
		p1pic[2] = '1';
	else
		p1pic[2] = '0';
	p1pic[3] = d;

	bg->m_hObject = (HBITMAP)::LoadImage(NULL, mappic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p1->m_hObject = (HBITMAP)::LoadImage(NULL, p1pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p1s->m_hObject = (HBITMAP)::LoadImage(NULL, p1pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p2->m_hObject = (HBITMAP)::LoadImage(NULL, p2pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	p2s->m_hObject = (HBITMAP)::LoadImage(NULL, p2pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Invalidate(true);
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void FrameWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	//Invalidate(true);
	f++;
	if (p2d != 0)
	{
		gamemap.move(2, p2d);
		p2d = 0;
		Invalidate(true);
	}
	if (f > 200 && gamemap.win() != 1)
		gamemap.endFlag = -1;
	CFrameWnd::OnTimer(nIDEvent);
}
