#pragma once
#include "MatrixCalculator.h"

//------------------------------------------------------------------
// Initialization
//------------------------------------------------------------------

// Connect controls with corresponding member variables, so we don't need
// explicitly get control from dialog.
void MatrixCalculator::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MATRIX_A, m_clMatrixA);
	DDX_Control(pDX, IDC_MATRIX_B, m_clMatrixB);
	DDX_Control(pDX, IDC_MATRIX_RESULT, m_clMatrixResult);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_VALUE_A, m_cEditDefaultValueA);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_VALUE_B, m_cEditDefaultValueB);
	DDX_Control(pDX, IDC_EDIT_ROWSNO_A, m_cEditRowsNoA);
	DDX_Control(pDX, IDC_EDIT_COLNO_A, m_cEditColNoA);
	DDX_Control(pDX, IDC_EDIT_ROWSNO_B, m_cEditRowsNoB);
	DDX_Control(pDX, IDC_EDIT_COLNO_B, m_cEditColNoB);
}

// Setup matrices here.
BOOL MatrixCalculator::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set matricies to default values.
	m_clMatrixA.Initialize();
	m_clMatrixB.Initialize();
	m_clMatrixResult.Initialize();

	// Default value for matrix cells.
	m_cEditDefaultValueA.SetWindowText(m_clMatrixA.GetDefaultValue());
	m_cEditDefaultValueB.SetWindowText(m_clMatrixB.GetDefaultValue());

	// Default values for rows and columns numbers.
	CString csDefaultValue;
	csDefaultValue.Format(_T("%d"), m_clMatrixA.GetRowsNo());
	m_cEditRowsNoA.SetWindowText(csDefaultValue);
	csDefaultValue.Format(_T("%d"), m_clMatrixA.GetColumnsNo());
	m_cEditColNoA.SetWindowText(csDefaultValue);
	csDefaultValue.Format(_T("%d"), m_clMatrixB.GetRowsNo());
	m_cEditRowsNoB.SetWindowText(csDefaultValue);
	csDefaultValue.Format(_T("%d"), m_clMatrixB.GetColumnsNo());
	m_cEditColNoB.SetWindowText(csDefaultValue);

	return 0;
}

BEGIN_MESSAGE_MAP(MatrixCalculator, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_MATRIX_A, OnNMClickA)
	ON_NOTIFY(NM_CLICK, IDC_MATRIX_B, OnNMClickB)
	ON_MESSAGE(WM_NOTIFY_DESCRIPTION_EDITED, OnNotifyDescriptionEdited)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_A, &MatrixCalculator::OnBnClickedButtonClearA)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_B, &MatrixCalculator::OnBnClickedButtonClearB)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RESULT, &MatrixCalculator::OnBnClickedButtonClearResult)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &MatrixCalculator::OnBnClickedButtonEqual)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_VALUE_A, &MatrixCalculator::OnEnChangeEditDefaultValueA)
	ON_EN_CHANGE(IDC_EDIT_DEFAULT_VALUE_B, &MatrixCalculator::OnEnChangeEditDefaultValueB)
	ON_EN_CHANGE(IDC_EDIT_ROWSNO_A, &MatrixCalculator::OnEnChangeEditRowsnoA)
	ON_EN_CHANGE(IDC_EDIT_COLNO_A, &MatrixCalculator::OnEnChangeEditColnoA)
	ON_EN_CHANGE(IDC_EDIT_ROWSNO_B, &MatrixCalculator::OnEnChangeEditRowsnoB)
	ON_EN_CHANGE(IDC_EDIT_COLNO_B, &MatrixCalculator::OnEnChangeEditColnoB)
END_MESSAGE_MAP()

//------------------------------------------------------------------
// Input handlers
//------------------------------------------------------------------

// Handler for messages sent by Matrix A (a list-view control) when the user clicks an item with the left mouse button.
void MatrixCalculator::OnNMClickA(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Example from Microsoft docs for CListCtrl::SubItemHitTest.
	// LPNMITEMACTIVATE contains information about an LVN_ITEMACTIVATE notification code,
	// sent by a list-view control when the user activates an item.
	LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
	POINT pntMousePoint = pia->ptAction;

	if (pntMousePoint.x && pntMousePoint.y)
	{
		m_clMatrixA.OnLButtonDown(MK_LBUTTON, pntMousePoint);
	}

	*pResult = 0;
}

// Handler for messages sent by Matrix B (a list-view control) when the user clicks an item with the left mouse button.
void MatrixCalculator::OnNMClickB(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Example from Microsoft docs for CListCtrl::SubItemHitTest.
	// LPNMITEMACTIVATE contains information about an LVN_ITEMACTIVATE notification code,
	// sent by a list-view control when the user activates an item.
	LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
	POINT pntMousePoint = pia->ptAction;

	if (pntMousePoint.x && pntMousePoint.y)
	{
		m_clMatrixB.OnLButtonDown(MK_LBUTTON, pntMousePoint);
	}

	*pResult = 0;
}

// A notifier for handling every instance when the edit control has been updated.
LRESULT MatrixCalculator::OnNotifyDescriptionEdited(WPARAM wParam, LPARAM lParam)
{
	// Get the changed Description field text via the callback.
	LV_DISPINFO* dispinfo = reinterpret_cast<LV_DISPINFO*>(lParam);

	// Check which one of the matricies we change.
	if (m_clMatrixA.m_pCEdit != NULL && IsWindow(m_clMatrixA.m_pCEdit->m_hWnd))
	{
		// Put text into the matrix cell.
		m_clMatrixA.SetItemText(dispinfo->item.iItem, dispinfo->item.iSubItem, dispinfo->item.pszText);
	}
	else if (m_clMatrixB.m_pCEdit != NULL && IsWindow(m_clMatrixB.m_pCEdit->m_hWnd))
	{
		// Put text into the matrix cell.
		m_clMatrixB.SetItemText(dispinfo->item.iItem, dispinfo->item.iSubItem, dispinfo->item.pszText);
	}	

	return 0;
}

// There's no any OK buttons, but program calls it anyway, so dialog closes immediately after press Enter.
// CInPlaceEdit::PreTranslatedMessage doesen't help in this case.
void MatrixCalculator::OnOK()
{
	// If there's an edit box, change focus to parent matrix.
	if (m_clMatrixA.m_pCEdit != NULL && IsWindow(m_clMatrixA.m_pCEdit->m_hWnd))
	{
		CInPlaceEdit* p_cEditTemp = static_cast<CInPlaceEdit*>(m_clMatrixA.m_pCEdit);
		p_cEditTemp->OnKillFocus(NULL);
		// Now we don't need this pointer because current Edit control is already destroyed.
		m_clMatrixA.m_pCEdit = NULL;
	}
	else if (m_clMatrixB.m_pCEdit != NULL && IsWindow(m_clMatrixB.m_pCEdit->m_hWnd))
	{
		CInPlaceEdit* p_cEditTemp = static_cast<CInPlaceEdit*>(m_clMatrixB.m_pCEdit);
		p_cEditTemp->OnKillFocus(NULL);
		// Now we don't need this pointer because current Edit control is already destroyed.
		m_clMatrixB.m_pCEdit = NULL;
	}
	else // Otherwise just close the dialog window.
	{
		CDialog::OnOK();
	}
}

// There's no any CANCEL buttons, but program calls it anyway, so dialog closes immediately after press Enter.
// CInPlaceEdit::PreTranslatedMessage doesen't help in this case.
void MatrixCalculator::OnCancel()
{
	// If there's an edit box, change focus to parent matrix.
	if (m_clMatrixA.m_pCEdit != NULL && IsWindow(m_clMatrixA.m_pCEdit->m_hWnd))
	{
		CInPlaceEdit* p_cEditTemp = static_cast<CInPlaceEdit*>(m_clMatrixA.m_pCEdit);
		p_cEditTemp->OnKillFocus(NULL);
		// Now we don't need this pointer because current Edit control is already destroyed.
		m_clMatrixA.m_pCEdit = NULL;
	}
	else if (m_clMatrixB.m_pCEdit != NULL && IsWindow(m_clMatrixB.m_pCEdit->m_hWnd))
	{
		CInPlaceEdit* p_cEditTemp = static_cast<CInPlaceEdit*>(m_clMatrixB.m_pCEdit);
		p_cEditTemp->OnKillFocus(NULL);
		// Now we don't need this pointer because current Edit control is already destroyed.
		m_clMatrixB.m_pCEdit = NULL;
	}
	else // Otherwise just close the dialog window.
	{
		CDialog::OnCancel();
	}
}

//------------------------------------------------------------------
// Buttons and edit controls
//------------------------------------------------------------------

// Button 'Clear A' - clear and set default value to matrix A.
void MatrixCalculator::OnBnClickedButtonClearA()
{
	m_clMatrixA.Clear(m_clMatrixA.GetDefaultValue());
}

// Button 'Clear B' - clear and set default value to matrix B.
void MatrixCalculator::OnBnClickedButtonClearB()
{
	m_clMatrixB.Clear(m_clMatrixB.GetDefaultValue());
}

// Button 'Clear Result' - clear and set default value '0' to result matrix.
void MatrixCalculator::OnBnClickedButtonClearResult()
{
	m_clMatrixResult.Clear();
}

// Button '=' - start matrix mutiplication.
void MatrixCalculator::OnBnClickedButtonEqual()
{
	Multiplication();
}

// Edit box for A matrix default value.
void MatrixCalculator::OnEnChangeEditDefaultValueA()
{
	CString csDefaultValue;
	m_cEditDefaultValueA.GetWindowText(csDefaultValue);
	m_clMatrixA.SetDefaultValue(csDefaultValue);
}

// Edit box for B matrix default value.
void MatrixCalculator::OnEnChangeEditDefaultValueB()
{
	CString csDefaultValue;
	m_cEditDefaultValueB.GetWindowText(csDefaultValue);
	m_clMatrixB.SetDefaultValue(csDefaultValue);
}

//------------------------------------------------------------------
// Calculations
//------------------------------------------------------------------

// Calculate Matrix A x Matrix B (4 x 4 at this moment).
void MatrixCalculator::Multiplication()
{
	// Check if we actualy can do that.
	if (!IsProductDefined())
	{
		return;
	}

	// Resize digit storages for A and B.
	m_clMatrixA.ResizeDigitStorage();
	m_clMatrixB.ResizeDigitStorage();

	// Fill matrix arrays with digits first.
	m_clMatrixA.ConvertToDigitValues();
	m_clMatrixB.ConvertToDigitValues();

	// Define the new size for result matrix.
	int iNewRowsNo = m_clMatrixA.GetRowsNo();
	int iNewColumnsNo = m_clMatrixB.GetColumnsNo();
	int iColNo = m_clMatrixA.GetColumnsNo();

	// Resize the result matrix.
	m_clMatrixResult.ResizeByRowsNo(iNewRowsNo);
	m_clMatrixResult.ResizeByColsNo(iNewColumnsNo);
	m_clMatrixResult.ResizeDigitStorage();

	// Perform actual multiplication with arrays.
	for (int i = 0; i < iNewRowsNo; i++)
	{
		for (int j = 0; j < iNewColumnsNo; j++)
		{
			// Perform vector dot product.
			m_clMatrixResult.m_vecDigitValues[i][j] = 0;
			// Multiply corresponding values.
			for (int k = 0; k < iColNo; k++)
			{
				m_clMatrixResult.m_vecDigitValues[i][j] += m_clMatrixA.m_vecDigitValues[i][k] * m_clMatrixB.m_vecDigitValues[k][j];
				/*m_clMatrixResult.m_arrDigitValues[i][j] = m_clMatrixA.m_arrDigitValues[i][0] * m_clMatrixB.m_arrDigitValues[0][j] +
															m_clMatrixA.m_arrDigitValues[i][1] * m_clMatrixB.m_arrDigitValues[1][j] +
															m_clMatrixA.m_arrDigitValues[i][2] * m_clMatrixB.m_arrDigitValues[2][j] +
															m_clMatrixA.m_arrDigitValues[i][3] * m_clMatrixB.m_arrDigitValues[3][j];*/
			}
		}
	}

	// Fill result matrix control with strings.
	m_clMatrixResult.ConvertToStringValues();
}

bool MatrixCalculator::IsProductDefined()
{
	if (m_clMatrixA.GetColumnsNo() != m_clMatrixB.GetRowsNo())
	{
		MessageBox(L"The number of columns in matrix A must be equal the number of rows in matrix B.", L"A x B is not defined!", 1);
		return false;
	}
	return true;
}

// Set number of rows for Matrix A.
void MatrixCalculator::OnEnChangeEditRowsnoA()
{
	ChangeEditRowsNo(&m_cEditRowsNoA, &m_clMatrixA);
}

// Set number of columns for Matrix A.
void MatrixCalculator::OnEnChangeEditColnoA()
{
	ChangeEditColNo(&m_cEditColNoA, &m_clMatrixA);
}

// Set number of rows for Matrix B.
void MatrixCalculator::OnEnChangeEditRowsnoB()
{
	ChangeEditRowsNo(&m_cEditRowsNoB, &m_clMatrixB);
}

// Set number of columns for Matrix B.
void MatrixCalculator::OnEnChangeEditColnoB()
{
	ChangeEditColNo(&m_cEditColNoB, &m_clMatrixB);
}

// Set number of rows for Matrix.
void MatrixCalculator::ChangeEditRowsNo(CEdit *pEditCtrl, Matrix *pMatrix)
{
	CString csTemp;
	pEditCtrl->GetWindowText(csTemp);

	int iNewRowsNo = _wtoi(csTemp);
	// The number of rows in matrix must be > 0,
	// and I've chose an arbitrary small value for the upper bound.
	if ((iNewRowsNo > 0 && iNewRowsNo <= 20) && (pMatrix->GetRowsNo() != iNewRowsNo))
	{
		// Get the current default value for this matrix.
		csTemp = pMatrix->GetDefaultValue();
		// Resize matrix.
		pMatrix->ResizeByRowsNo(iNewRowsNo, csTemp);
	}
	else
	{
		// Current input isn't valid, so we should change it back.
		CString csCurRowsNo;
		csCurRowsNo.Format(L"%d", pMatrix->GetRowsNo());
		if (csTemp != csCurRowsNo)
		{
			pEditCtrl->SetWindowText(csCurRowsNo);
		}
	}
}

// Set number of columns for Matrix.
void MatrixCalculator::ChangeEditColNo(CEdit *pEditCtrl, Matrix *pMatrix)
{
	CString csTemp;
	pEditCtrl->GetWindowText(csTemp);

	int iNewColNo = _wtoi(csTemp);
	// The number of columns in matrix must be > 0,
	// and I've chose an arbitrary small value for the upper bound.
	if ((iNewColNo > 0 && iNewColNo <= 20) && (pMatrix->GetColumnsNo() != iNewColNo))
	{
		// Get the current default value for this matrix.
		csTemp = pMatrix->GetDefaultValue();
		// Resize matrix.
		pMatrix->ResizeByColsNo(iNewColNo, csTemp);
	}
	else
	{
		// Current input isn't valid, so we should change it back.
		CString csCurColumnsNo;
		csCurColumnsNo.Format(L"%d", pMatrix->GetColumnsNo());
		if (csTemp != csCurColumnsNo)
		{
			pEditCtrl->SetWindowText(csCurColumnsNo);
		}
	}
}