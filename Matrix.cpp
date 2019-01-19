#pragma once
#include "Matrix.h"

//------------------------------------------------------------------
// Initialization
//------------------------------------------------------------------

// Set matrix cells to zeroes.
void Matrix::Initialize()
{
	// Populate the List Control with items.
	//--------------------------------------
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);

	// Row height
	int iRowHeight = 30;
	m_ciImageList.Create(1, iRowHeight, ILC_COLOR, 1, 1);
	SetImageList(&m_ciImageList, LVSIL_SMALL);

	// Insert columns.
	LVCOLUMN lvColumn;
	for (int i = 0; i < 5; i++)
	{
		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		// We don't need the first colummn's caption.
		CString csColumnCaption = "";
		if (i)
		{
			lvColumn.fmt = LVCFMT_RIGHT;
			lvColumn.cx = 65;
			csColumnCaption.Format(L"Col %d", i);
		}
		else
		{
			// First column must be left aligned.
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.cx = 40;
		}
		lvColumn.pszText = csColumnCaption.GetBuffer(csColumnCaption.GetLength());
		InsertColumn(i, &lvColumn);
	}

	// Insert Items
	LVITEM lvItem;
	for (int i = 0; i < 4; i++)
	{
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		CString csRowCaption = "";
		csRowCaption.Format(L"Row %d", i + 1); // Number of row in matrix should start with 1 instead of 0.
		lvItem.pszText = csRowCaption.GetBuffer(csRowCaption.GetLength());
		InsertItem(&lvItem);
		for (int j = 1; j < 5; j++)
		{
			CString csItemText = "";
			csItemText.Format(L"%d", 0); // Fill with zeroes.
										 // csItemText.Format(L"%d%d", i + 1, j); // Put the row and column numbers.
			SetItemText(i, j, csItemText);
		}
	}
}

void Matrix::Clear(CString csDefaultValue)
{
	for (int i = 0; i < m_iRowsNo; i++)
	{
		for (int j = 1; j < m_iColumnsNo; j++)
		{
			SetItemText(i, j, csDefaultValue);
		}
	}
}

//------------------------------------------------------------------
// Setup an edit box for input.
//------------------------------------------------------------------

// Check a mouse click and create an edit control if it's the case. 
void Matrix::OnLButtonDown(UINT nFlags, CPoint cpPoint)
{
	CListCtrl::OnLButtonDown(nFlags, cpPoint);
	// Make the labels editable.
	ModifyStyle(0, LVS_EDITLABELS);
	// If subitem was located correctly.
	if (GetRowAndColumn(nFlags, cpPoint))
	{
		// Process for edit box creating. 
		EditSubLabel();
	}
}

// Determines the row and column number that the cursor falls on.
bool Matrix::GetRowAndColumn(UINT nFlags, CPoint cpPoint)
{
	// Determines which list - view item or subitem is located at a given position.
	LVHITTESTINFO hitTestInfo;
	hitTestInfo.pt = cpPoint;
	hitTestInfo.flags = nFlags;
	// Fill this structure with received info.
	int iResult = SubItemHitTest(&hitTestInfo);
	if (iResult != -1)
	{
		// Get current row and column values.
		m_iRow = hitTestInfo.iItem;
		m_iColumn = hitTestInfo.iSubItem;
		return true;
	}
	return false;
}

// Get the pointer to the subItem's CEdit field or NULL if it's not the case.
CEdit* Matrix::EditSubLabel()
{
	// Make sure that column number is valid.
	// We don't need to edit column 0, because it's just a const label of row.
	if (m_iColumn < 1 || m_iColumn >= m_iColumnsNo) return NULL;

	// Get the rectangle of current subitem.
	CRect crSubItemRect;
	GetSubItemRect(m_iRow, m_iColumn, LVIR_BOUNDS, crSubItemRect);

	// Get the pointer to the new CEdit field.
	DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_RIGHT;
	CString csEditText = GetItemText(m_iRow, m_iColumn);
	CEdit* pEdit = new CInPlaceEdit(m_iRow, m_iColumn, csEditText);
	pEdit->Create(dwStyle, crSubItemRect, this, IDC_MATRIX_A);

	// Put ref into the member variable for using in the dialog classe's OnOK().
	m_pCEdit = pEdit;
	return pEdit;
}

//------------------------------------------------------------------
// Calculations.
//------------------------------------------------------------------

// Prepare digits array for multiplication.
void Matrix::ConvertToDigitValues()
{
	for (int i = 0; i < m_iRowsNo; i++)
	{
		for (int j = 1; j < m_iColumnsNo; j++) // First column is a row's lable.
		{
			CString csTempValue = GetItemText(i, j);
			m_arrDigitValues[i][j - 1] = _wtof(csTempValue); // Array's column starts with zero.
		}
	}
}

// Convert doubles from multiplication result to strings for matrix cells.
void Matrix::ConvertToStringValues()
{
	for (int i = 0; i < m_iRowsNo; i++)
	{
		for (int j = 1; j < m_iColumnsNo; j++) // First column is a row's lable.
		{
			CString csTempValue;
			csTempValue.Format(L"%g", m_arrDigitValues[i][j - 1]); // Array's column starts with zero.
			SetItemText(i, j, csTempValue);
		}
	}
}

// Set different background color for row's headers.
COLORREF Matrix::OnGetCellBkColor(int nRow, int nColumn)
{
	if (!nColumn)
	{
		COLORREF colRowHeaderBack = ::GetSysColor(COLOR_3DFACE);
		return colRowHeaderBack;
	}

	return CMFCListCtrl::OnGetCellBkColor(nRow, nColumn);
}
