#pragma once
#include "MatrixCalculator.h"

void MatrixCalculator::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MATRIX_A, m_clMatrixA);
	DDX_Control(pDX, IDC_MATRIX_B, m_clMatrixB);
	DDX_Control(pDX, IDC_MATRIX_RESULT, m_clMatrixResult);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_VALUE_A, m_cEditDefaultValueA);
	DDX_Control(pDX, IDC_EDIT_DEFAULT_VALUE_B, m_cEditDefaultValueB);
}

BOOL MatrixCalculator::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set matricies to zeroe values.
	m_clMatrixA.Initialize();
	m_clMatrixB.Initialize();
	m_clMatrixResult.Initialize();
	// Default value for matrix cells.
	m_csDefaultValueA = "0";
	m_cEditDefaultValueA.SetWindowText(m_csDefaultValueA);
	m_csDefaultValueB = "0";
	m_cEditDefaultValueB.SetWindowText(m_csDefaultValueB);

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
END_MESSAGE_MAP()

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

LRESULT MatrixCalculator::OnNotifyDescriptionEdited(WPARAM wParam, LPARAM lParam)
{
	// Get the changed Description field text via the callback
	LV_DISPINFO* dispinfo = reinterpret_cast<LV_DISPINFO*>(lParam);

	// Persist the selected attachment details upon updating its text
	if (m_clMatrixA.m_pCEdit != NULL && IsWindow(m_clMatrixA.m_pCEdit->m_hWnd))
	{
		m_clMatrixA.SetItemText(dispinfo->item.iItem, dispinfo->item.iSubItem, dispinfo->item.pszText);
	}
	else if (m_clMatrixB.m_pCEdit != NULL && IsWindow(m_clMatrixB.m_pCEdit->m_hWnd))
	{
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

// Calculate Matrix A x Matrix B (4 x 4 at this moment).
void MatrixCalculator::Multiplication()
{
	// Fill matrix arrays with digits first.
	m_clMatrixA.ConvertToDigitValues();
	m_clMatrixB.ConvertToDigitValues();

	// Perform actual multiplication with arrays.
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			// Perform vector dot product.
			m_clMatrixResult.m_arrDigitValues[i][j] = 0;
			// Multiply corresponding values.
			for (int k = 0; k < 4; k++)
			{
				m_clMatrixResult.m_arrDigitValues[i][j] += m_clMatrixA.m_arrDigitValues[i][k] * m_clMatrixB.m_arrDigitValues[k][j];
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

void MatrixCalculator::OnBnClickedButtonClearA()
{
	m_clMatrixA.Clear(m_csDefaultValueA);
}


void MatrixCalculator::OnBnClickedButtonClearB()
{
	m_clMatrixB.Clear(m_csDefaultValueB);
}


void MatrixCalculator::OnBnClickedButtonClearResult()
{
	m_clMatrixResult.Clear("0");
}


void MatrixCalculator::OnBnClickedButtonEqual()
{
	Multiplication();
}

void MatrixCalculator::OnEnChangeEditDefaultValueA()
{
	m_cEditDefaultValueA.GetWindowText(m_csDefaultValueA);
}


void MatrixCalculator::OnEnChangeEditDefaultValueB()
{
	m_cEditDefaultValueB.GetWindowText(m_csDefaultValueB);
}
