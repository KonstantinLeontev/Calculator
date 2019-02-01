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

	// Start columns and rows building.
	//--------------------------------------

	// Check for initial column's number from class constructor.
	int iNewNo = 4; // Default for 4x4 matrix.
	if (m_iColumnsNo)
	{
		// m_iColumnsNo != 0, so we have a custom size for our matrix.
		if (m_iColumnsNo < 0)
		{
			// The number must be greater then zero.
			m_iColumnsNo *= -1;
		}
		// Greater then 20 is too much for now.
		if (m_iColumnsNo > 20)
		{
			m_iColumnsNo = 20;
		}
		iNewNo = m_iColumnsNo; // Get initial value.
		m_iColumnsNo = 0; // And drop it to zero for correct work of AddColumns() method. 
	}
	// Insert columns. It's 5 - because first of them is a row's label.
	AddColumns(iNewNo);

	// Check for initial rows's number from class constructor.
	iNewNo = 4; // Default for 4x4 matrix.
	if (m_iRowsNo)
	{
		// We have a custom size for our matrix.
		if (m_iRowsNo < 0)
		{
			// The number must be greater then zero.
			m_iRowsNo *= -1;
		}
		// Greater then 20 is too much for now.
		if (m_iRowsNo > 20)
		{
			m_iRowsNo = 20;
		}
		iNewNo = m_iRowsNo; // Get initial value.
		m_iRowsNo = 0; // And drop it to zero. 
	}
	// Insert Items to comlete full 4 x 4 matrix.
	AddRows(iNewNo);

	// Make vector given size for digital values from list control.
	m_vecDigitValues.resize(m_iRowsNo, std::vector<double>(m_iColumnsNo, 0));
}

void Matrix::Clear(const CString &csDefaultValue)
{
	for (int i = 0; i < m_iRowsNo; i++)
	{
		for (int j = 1; j < m_iColumnsNo + 1; j++)
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
	if (m_iColumn < 1 || m_iColumn >= m_iColumnsNo + 1) return NULL;

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

// Resize vector for product calculation.
void Matrix::ResizeDigitStorage()
{
	if (m_vecDigitValues.size() != m_iRowsNo)
	{
		m_vecDigitValues.resize(m_iRowsNo);
	}

	for (int i = 0; i < m_iRowsNo; i++)
	{
		if (m_vecDigitValues[i].size() != m_iColumnsNo)
		{
			m_vecDigitValues[i].resize(m_iColumnsNo);
		}
	}
}

// Prepare digits array for multiplication.
void Matrix::ConvertToDigitValues()
{
	// Convert strings to digit values.
	for (int i = 0; i < m_iRowsNo; i++)
	{
		for (int j = 0; j < m_iColumnsNo; j++)
		{
			CString csTempValue = GetItemText(i, j + 1); // First column is a row's lable.
			m_vecDigitValues[i][j] = _wtof(csTempValue); // Array's column starts with zero.
		}
	}
}

// Convert doubles from multiplication result to strings for matrix cells.
void Matrix::ConvertToStringValues()
{
	for (int i = 0; i < m_iRowsNo; i++)
	{
		for (int j = 0; j < m_iColumnsNo; j++)
		{
			CString csTempValue;
			csTempValue.Format(L"%g", m_vecDigitValues[i][j]);
			SetItemText(i, j + 1, csTempValue); // First column - is a label.
		}
	}
}

// Resize matrix when row's quantity was changed.
void Matrix::ResizeByRowsNo(const int & iNewRowsNo, const CString &csDefaultText)
{
	if (iNewRowsNo > m_iRowsNo)
	{
		// Add rows.
		AddRows(iNewRowsNo, csDefaultText);
	}
	else
	{
		// Remove rows.
		RemoveRows(iNewRowsNo);
	}
}

// Resize matrix when column's quantity was changed.
void Matrix::ResizeByColsNo(const int & iNewColNo, const CString &csDefaultText)
{
	if (iNewColNo > m_iColumnsNo)
	{
		// Add columns.
		AddColumns(iNewColNo, csDefaultText);
	}
	else
	{
		// Remove columns.
		RemoveColumns(iNewColNo);
	}
}

void Matrix::AddRows(const int & iNewRowsNo, const CString &csDefaultText)
{
	// Insert Items
	LVITEM lvItem;
	for (int i = m_iRowsNo; i < iNewRowsNo; i++)
	{
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		CString csRowCaption = "";
		csRowCaption.Format(L"Row %d", i + 1); // Number of row in matrix should start with 1 instead of 0.
		lvItem.pszText = csRowCaption.GetBuffer(csRowCaption.GetLength());
		InsertItem(&lvItem);
		// Set text for subitems.
		for (int j = 1; j <= m_iColumnsNo; j++) // Column 0 is for row's label, so actual columns number is greater for 1.
		{
			SetItemText(i, j, csDefaultText);
		}
	}
	// Set new rows quantity.
	m_iRowsNo = iNewRowsNo;
}

// Remove rows when the new rows number is less than existent.
void Matrix::RemoveRows(const int & iNewRowsNo)
{
	for (int i = m_iRowsNo; i >= iNewRowsNo; i--)
	{
		DeleteItem(i);
	}
	// Set new rows quantity.
	m_iRowsNo = iNewRowsNo;
}

// Create columns when matrix created or size was changed.
void Matrix::AddColumns(const int &iNewColNo, const CString &csDefaultText)
{
	// Insert columns.
	LVCOLUMN lvColumn;
	for (int i = (m_iColumnsNo) ? (m_iColumnsNo + 1) : 0; i < (iNewColNo + 1); i++) // +1 because column 0 is for rows labels.
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

		// Set text for new subitems in this column.
		for (int j = 0; j < m_iRowsNo; j++)
		{
			SetItemText(j, i, csDefaultText);
		}
	}
	// Set new col quantity.
	m_iColumnsNo = iNewColNo;
}

// Removes columns if the new column's number is less then existent.
void Matrix::RemoveColumns(const int & iNewColNo)
{
	for (int i = m_iColumnsNo; i > iNewColNo; i--)
	{
		DeleteColumn(i);
	}
	// Set new col quantity.
	m_iColumnsNo = iNewColNo;
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

// Setters and getters.
void Matrix::SetRow(const int & iRow)
{
	m_iRow = iRow;
}

void Matrix::SetColumn(const int & iCol)
{
	m_iColumn = iCol;
}

int Matrix::GetRow() const
{
	return m_iRow;
}

int Matrix::GetColumn() const
{
	return m_iColumn;
}

void Matrix::SetRowsNo(const int & iRowsNo)
{
	m_iRowsNo = iRowsNo;
}

void Matrix::SetColumnsNo(const int & iColNo)
{
	m_iColumnsNo = iColNo;
}

int Matrix::GetRowsNo() const
{
	return m_iRowsNo;
}

int Matrix::GetColumnsNo() const
{
	return m_iColumnsNo;
}

CString Matrix::GetDefaultValue() const
{
	return m_csDefaultValue;
	;
}

void Matrix::SetDefaultValue(const CString & csDefaultValue)
{
	m_csDefaultValue = csDefaultValue;
}
