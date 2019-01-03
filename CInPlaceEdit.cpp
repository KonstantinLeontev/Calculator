#include "CInPlaceEdit.h"

BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_CHAR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// Translate window message before they are dispatched to the TranslateMessage and DispatchMessage.
BOOL CInPlaceEdit::PreTranslatedMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || pMsg->wParam == VK_ESCAPE || GetKeyState(VK_CONTROL))
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}

// Called immediately before losing the input focus.
void CInPlaceEdit::OnKillFocus(CWnd * pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	CString str;
	GetWindowText(str);

	DestroyWindow();
}

// Called when nonclient area is being destroyed.
void CInPlaceEdit::OnNcDestroy()
{
	CEdit::OnNcDestroy();
	delete this;
}

// Called for nonsystem character keystrokes.
void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (nChar == VK_ESCAPE)
		{
			m_bESC = TRUE;
		}

		GetParent()->SetFocus();
		return;
	}

	// Filter for non-digit characters or minus, dot or comma.
	if ((nChar < 0x30 || nChar > 0x39) /*&& (nChar != VK_OEM_MINUS || nChar != VK_OEM_COMMA || nChar != VK_OEM_PERIOD)*/)
	{
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);

	// Resize edit control if needed 
	CString str;
	GetWindowText(str);
	CWindowDC dc(this);
	CFont *pFont = GetParent()->GetFont();
	CFont *pFontDC = dc.SelectObject(pFont);
	CSize size = dc.GetTextExtent(str);
	dc.SelectObject(pFontDC);
	size.cx += 5;

	// Get the client rectangle 
	CRect rect, parentrect;
	GetClientRect(&rect);
	GetParent()->GetClientRect(&parentrect);

	// Transform rectangle to parent coordinates    
	ClientToScreen(&rect);
	GetParent()->ScreenToClient(&rect);

	// Check whether control needs resizing and if sufficient space to grow
	if (size.cx > rect.Width())
	{
		if (size.cx + rect.left < parentrect.right)
		{
			rect.right = rect.left + size.cx;
		}
		else
		{
			rect.right = parentrect.right;
		}

		MoveWindow(&rect);
	}

	// Construct list control item data
	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;
	dispinfo.item.mask = LVIF_TEXT;
	dispinfo.item.iItem = m_iRow;
	dispinfo.item.iSubItem = m_iColumn;
	dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
	dispinfo.item.cchTextMax = str.GetLength();

	// Send this Notification to parent of ListView ctrl    
	CWnd* pWndViewAttachmentsDlg = GetParent()->GetParent();

	if (pWndViewAttachmentsDlg)
	{
		pWndViewAttachmentsDlg->SendMessage(WM_NOTIFY_DESCRIPTION_EDITED,
			GetParent()->GetDlgCtrlID(),
			(LPARAM)&dispinfo);
	}
}

// Called when application requests the window be created by calling the Create/CreateEx
// member function.
int CInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// Set the proper font  
	CFont* font = GetParent()->GetFont();
	SetFont(font);
	SetWindowText(m_sInitText);
	SetFocus();
	SetSel(0, -1);
	return 0;
}