// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif

#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPatternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CPatternGeneratorView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_RESUME, &CPatternGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

CPatternGeneratorView::CPatternGeneratorView() noexcept
{
	m_pCurrentThread = NULL;
	//m_iCounter = 0;
	x = 300+150*cos(0); // mercury x coordinate
	y = 200+100*sin(0);

	x1 = 300 + 200 * cos(5);// venus x coordinate
	y1 = 200 + 150 * sin(5);

	x2 = 300 + 250 * cos(10); // earth x coordinate
	y2 = 200 + 200 * sin(10); // earth y  coordinate
	// TODO: add construction code here

}

CPatternGeneratorView::~CPatternGeneratorView()
{
}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing

void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->Ellipse(550, 400, 50, 0); //earth

	pDC->Ellipse(500, 350, 100, 50); // venus

	pDC->Ellipse(450, 300, 150, 100); // mercury 

	CBrush brushyellow(RGB(255, 0, 0));
	CBrush* pO1dBrush = pDC->SelectObject(&brushyellow);
	pDC->Ellipse(330, 230, 270, 170);      // Sun
	pDC->SelectObject(pO1dBrush);

	CBrush brushBlack1(RGB(80, 78, 81));
	CBrush* pO2dBrush = pDC->SelectObject(&brushBlack1);//mercury size
	pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);
	pDC->SelectObject(pO2dBrush);

	CBrush brushBlack2(RGB(173, 141, 84));
	CBrush* pO3dBrush = pDC->SelectObject(&brushBlack2);//venus
	pDC->Ellipse(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	pDC->SelectObject(pO3dBrush);

	CBrush brushBlack3(RGB(0, 255, 0));
	CBrush* pO4dBrush = pDC->SelectObject(&brushBlack3);//earth
	pDC->Ellipse(x2 + 10, y2 + 10, x2 - 10, y2 - 10); 

	// TODO: add draw code for native data here
}


// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternGeneratorDoc)));
	return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers


void CPatternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Start"));
	m_pCurrentThread = AfxBeginThread(CPatternGeneratorView::StartThread, this);
}


void CPatternGeneratorView::OnButtonSuspend()
{
	// TODO: Add your command handler code here
	//AfxMessageBox(_T("Suspend"));
	m_pCurrentThread->SuspendThread();
}


void CPatternGeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	 //AfxMessageBox(_T("Resume"));
	m_pCurrentThread->ResumeThread();
}


UINT CPatternGeneratorView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CPatternGeneratorView* pView = (CPatternGeneratorView*)Param;
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		
		pView->x = 300 + 150 * cos(j); //l
		pView->y = 200 + 100 * sin(j); //b
		pView->x1 = 300 + 200 * cos(j + 3);
		pView->y1 = 200 + 150 * sin(j + 3);

		pView->x2 = 300 + 250 * cos(j + 6);
		pView->y2 = 200 + 200 * sin(j + 6);
		j = j + 6;
		pView->Invalidate();
		Sleep(100);
	} 
	return 0;
}
