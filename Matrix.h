#pragma once
#include "afxcmn.h"
#include <memory>
#include "CInPlaceEdit.h"
#include "resource.h"

class Matrix : public CListCtrl
{
public:
	Matrix(int iRows = 4, int iColumns = 5)
		: m_pCEdit(NULL), m_iRow(0), m_iColumn(1), m_iRowsNo(iRows), m_iColumnsNo(iColumns), m_bIsChanged(FALSE) {}

	bool GetRowAndColumn(UINT nFlags, CPoint cpPoint);
	CEdit* EditSubLabel();
	void OnLButtonDown(UINT nFlags, CPoint cpPoint);
	void Initialize(); // Makes columns and rows and set matrix cells to zeroes.
	void Clear(CString csDefaultValue);
	void ConvertToDigitValues(); // Prepare digits array for next multiplication.
	void ConvertToStringValues(); // Convert digits array's values to strings and put back into the matrix control.

public:
	CEdit* m_pCEdit; // Used for hadling dialog's OnOK and OnCancel to prevent unexpected dialog closing.
	CImageList m_ciImageList; // This one is only for changing list's row height.
	int m_iRow;
	int m_iColumn;
	int m_iRowsNo;
	int m_iColumnsNo;
	// Array for double values of matrix's cells. Calculates right before each multiplication if there's any changes in matrix.
	double m_arrDigitValues[4][4];
	bool m_bIsChanged;
};