//*************************************************************************************
// Editable matrix grid.
// ---------------------
// A CList control in report mode creates a matrix grid with column's headers in the 
// first row and row labels in the first column. Edit box for user input creates on the
// fly for each click on the matrix cell.
//*************************************************************************************

#pragma once
#include "afxcmn.h"
#include "afxlistctrl.h"
#include <memory>
#include "CInPlaceEdit.h"
#include "resource.h"
#include <vector>

class Matrix : public CMFCListCtrl
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

	// Set different background color for row's headers.
	virtual COLORREF OnGetCellBkColor(int nRow, int nColumn);

public:
	CEdit* m_pCEdit; // Used for hadling dialog's OnOK and OnCancel to prevent unexpected dialog closing.
	CImageList m_ciImageList; // This one is only for changing list's row height.
	int m_iRow;
	int m_iColumn;
	int m_iRowsNo;
	int m_iColumnsNo;
	// Array for double values of matrix's cells. Calculates right before each multiplication if there's any changes in matrix.
	double m_arrDigitValues[4][4];
	// Vector for dynamically changing matrix's size.
	std::vector<std::vector<double> > m_vecDigitValues; 
	bool m_bIsChanged;
};