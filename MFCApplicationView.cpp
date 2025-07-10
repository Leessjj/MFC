
// MFCApplicationView.cpp: CMFCApplicationView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication.h"
#endif

#include "MFCApplicationDoc.h"
#include "MFCApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationView

IMPLEMENT_DYNCREATE(CMFCApplicationView, CView)

BEGIN_MESSAGE_MAP(CMFCApplicationView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplicationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(RChannel, &CMFCApplicationView::OnViewChannelR)
	ON_COMMAND(GChannel, &CMFCApplicationView::OnViewChannelG)
	ON_COMMAND(BChannel, &CMFCApplicationView::OnViewChannelB)
END_MESSAGE_MAP()

// CMFCApplicationView 생성/소멸

CMFCApplicationView::CMFCApplicationView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplicationView::~CMFCApplicationView()
{
}

BOOL CMFCApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationView 그리기

void CMFCApplicationView::OnDraw(CDC* pDC)
{
	/*CMFCApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc->m_image.IsNull()) // 이미지가 있으면
	{
		pDoc->m_image.Draw(pDC->GetSafeHdc(), 0, 0); // 화면 출력
	}*/

	CMFCApplicationDoc* pDoc = GetDocument();
	switch (m_selectedChannel) {
	case CHANNEL_R:
		if (!pDoc->m_channelR.IsNull())
			pDoc->m_channelR.Draw(pDC->GetSafeHdc(), 0, 0);
		break;
	case CHANNEL_G:
		if (!pDoc->m_channelG.IsNull())
			pDoc->m_channelG.Draw(pDC->GetSafeHdc(), 0, 0);
		break;
	case CHANNEL_B:
		if (!pDoc->m_channelB.IsNull())
			pDoc->m_channelB.Draw(pDC->GetSafeHdc(), 0, 0);
		break;
	default:
		if (!pDoc->m_image.IsNull())
			pDoc->m_image.Draw(pDC->GetSafeHdc(), 0, 0);
	}
}


// CMFCApplicationView 인쇄


void CMFCApplicationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplicationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplicationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplicationView 진단

#ifdef _DEBUG
void CMFCApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationDoc* CMFCApplicationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationDoc)));
	return (CMFCApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationView 메시지 처리기

void CMFCApplicationView::OnViewChannelR()
{
	m_selectedChannel = CHANNEL_R;
	GetDocument()->ExtractRGBChannel('R');
	Invalidate();
}
void CMFCApplicationView::OnViewChannelG()
{
	m_selectedChannel = CHANNEL_G;
	GetDocument()->ExtractRGBChannel('G');
	Invalidate();
}
void CMFCApplicationView::OnViewChannelB()
{
	m_selectedChannel = CHANNEL_B;
	GetDocument()->ExtractRGBChannel('B');
	Invalidate();
}
