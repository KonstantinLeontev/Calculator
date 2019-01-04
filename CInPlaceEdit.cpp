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
	// nChar contains the character code value of the key, not a virtual code!
	// VK_ESCAPE and VK_RETURN matches ASCII code.
	if (nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if (nChar == VK_ESCAPE)
		{
			m_bESC = TRUE;
		}

		GetParent()->SetFocus();
		return;
	}

	// Filter for non-digit characters or minus or dot.
	if ((nChar < 0x30 || nChar > 0x39) && nChar != CHAR_MINUS && nChar != CHAR_PERIOD)
	{
		return;
	}

	// Get the text that is already inside the edit box.
	CString str;
	GetWindowText(str);

	// Ignore all '-' except first place.
	if (nChar == CHAR_MINUS)
	{
		// First check for other minus in the string.
		int iFindResult = str.Find('-');
		if (iFindResult != -1)
		{
			// There's already one '-' here.
			return;
		}
		else
		{
			// Check current caret position.
			int iCurChar = CharFromPos(GetCaretPos());
			int iCharIndex = LOWORD(iCurChar);
			if (iCharIndex)
			{
				// It's not a first position.
				return;
			}
		}	
	}

	// Ignore all '.' except first one.
	if (nChar == CHAR_PERIOD)
	{
		// Check for other dots in the string.
		int iFindResult = str.Find('.');
		if (iFindResult != -1)
		{
			// There's already one '.' here.
			return;
		}
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
	// Get the updated text again.
	GetWindowText(str);

	// Resize edit control if needed 
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