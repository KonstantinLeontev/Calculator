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
	Matrix(int iRows = 0, int iColumns = 0)
		: m_pCEdit(NULL), m_iRow(0), m_iColumn(1), m_iRowsNo(iRows), m_iColumnsNo(iColumns), m_bIsChanged(FALSE) {}

	bool GetRowAndColumn(UINT nFlags, CPoint cpPoint);
	CEdit* EditSubLabel();
	void OnLButtonDown(UINT nFlags, CPoint cpPoint);
	void Initialize(); // Makes columns and rows and set matrix cells to zeroes.
	void Clear(CString csDefaultValue);
	void ConvertToDigitValues(); // Prepare digits array for next multiplication.
	void ConvertToStringValues(); // Convert digits array's values to strings and put back into the matrix control.

	// Resize matrix when row's quantity was changed.
	void ResizeByRowsNo(const int &iNewRowsNo);
	// Resize matrix when column's quantity was changed.
	void ResizeByColsNo(const int &iNewColNo);

	// Create rows when matrix created or size was changed.
	void AddRows(const int &iNewRowsNo);
	void RemoveRows(const int &iNewRowsNo);

	// Create columns when matrix created or size was changed.
	void AddColumns(const int &iNewColNo);
	void RemoveColumns(const int &iNewColNo);

	// Set different background color for row's headers.
	virtual COLORREF OnGetCellBkColor(int nRow, int nColumn);

	// Setters and getters.
	void SetRow(const int &iRow);
	void SetColumn(const int &iCol);
	int GetRow() const;
	int GetColumn() const;
	void SetRowsNo(const int &iRowsNo);
	void SetColumnsNo(const int &iColNo);
	int GetRowsNo() const;
	int GetColumnsNo() const;

public:
	CEdit* m_pCEdit;
	CImageList m_ciImageList; // This one is only for changing list's row height.
	
	// Array for double values of matrix's cells. Calculates right before each multiplication if there's any changes in matrix.
	double m_arrDigitValues[4][4];
	// Vector for dynamically changing matrix's size.
	std::vector<std::vector<double> > m_vecDigitValues; 
	bool m_bIsChanged;

private:
	int m_iRow;
	int m_iColumn;
	int m_iRowsNo;
	int m_iColumnsNo;
};