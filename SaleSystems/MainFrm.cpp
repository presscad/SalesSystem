
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SaleSystems.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "UserDialog.h"
#include "SaleDialog.h"
#include "Kucun.h"
#include "AddDialog.h"
#include "DelKuCun.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)

	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32775, &CMainFrame::On32775)
	ON_COMMAND(ID_32776, &CMainFrame::On32776)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//设置图标，IDI_ICON_WIN为图标资源ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON2));
	//设置标题
	SetTitle(TEXT("2018/7/24"));
	//设置窗口大小
	MoveWindow(0, 0, 800, 600);
	//设置居中显示
	CenterWindow();

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

//静态拆分窗口
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	//拆分成一行两列
	spliter.CreateStatic(this, 1, 2);
	//左右侧的内容
	spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView),CSize(200,500),pContext);
	spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);
	return TRUE;
}

//自定义消息处理
LRESULT CMainFrame::OnMyChange(WPARAM wparm, LPARAM lparam)
{
	CCreateContext context;
	if (wparm==NM_A)
	{
		//挂载界面
		context.m_pNewViewClass = RUNTIME_CLASS(CUserDialog);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)spliter.GetPane(0, 1);
		spliter.DeleteView(0, 1);
		spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDialog), CSize(600, 600), &context);
		CUserDialog *pNewView = (CUserDialog *)spliter.GetPane(0, 1);
		spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		spliter.SetActivePane(0, 1);

	}else if (wparm == NM_B)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CSaleDialog);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CSaleDialog *)spliter.GetPane(0, 1);
		spliter.DeleteView(0, 1);
		spliter.CreateView(0, 1, RUNTIME_CLASS(CSaleDialog), CSize(600, 600), &context);
		CSaleDialog *pNewView = (CSaleDialog *)spliter.GetPane(0, 1);
		spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		spliter.SetActivePane(0, 1);
	}else if (wparm == NM_C)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CKucun);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CKucun *)spliter.GetPane(0, 1);
		spliter.DeleteView(0, 1);
		spliter.CreateView(0, 1, RUNTIME_CLASS(CKucun), CSize(600, 600), &context);
		CKucun *pNewView = (CKucun *)spliter.GetPane(0, 1);
		spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		spliter.SetActivePane(0, 1);
	}else if (wparm == NM_D)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CAddDialog);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CAddDialog *)spliter.GetPane(0, 1);
		spliter.DeleteView(0, 1);
		spliter.CreateView(0, 1, RUNTIME_CLASS(CAddDialog), CSize(600, 600), &context);
		CAddDialog *pNewView = (CAddDialog *)spliter.GetPane(0, 1);
		spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		spliter.SetActivePane(0, 1);
	}else if (wparm == NM_E)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CDelKuCun);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CDelKuCun *)spliter.GetPane(0, 1);
		spliter.DeleteView(0, 1);
		spliter.CreateView(0, 1, RUNTIME_CLASS(CDelKuCun), CSize(600, 600), &context);
		CDelKuCun *pNewView = (CDelKuCun *)spliter.GetPane(0, 1);
		spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		spliter.SetActivePane(0, 1);
	}
	return 0;
}


//退出
void CMainFrame::On32771()
{
	exit(0);
}


//个人信息
void CMainFrame::On32772()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}

//销售管理
void CMainFrame::On32773()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}



//库存信息
void CMainFrame::On32774()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
}

//库存添加
void CMainFrame::On32775()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
}

//库存删除
void CMainFrame::On32776()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
}
