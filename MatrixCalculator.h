//*************************************************************************************
// Matrix calculator dialog.
// -------------------------
// Only for multiplying two 4x4 matricies at the moment.
// There's an ability to clear and set initial values for operands and clear for result
// matrix.
// A CList control in report mode creates a matrix grid with column's headers in the 
// first row and row labels in the first column. Edit box for user input creates on the
// fly for each click on the matrix cell.
// Base implementation was borrowed from "Editable MFC List Controls" post:
// https://www.technical-recipes.com/2014/making-a-mfc-list-control-editable/.
//*************************************************************************************

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"
#include "Matrix.h"

class MatrixCalculator : public CDialog
{
public:
	MatrixCalculator(CWnd* pParent = NULL)
		: CDialog(MatrixCalculator::IDD, pParent) {}

	// Dialog's ID
	enum { IDD = IDD_MATRIXCALC};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	void OnCancel(); // Prevents dialog from colsing when ESC pressed.
	void OnOK(); // Prevents dialog from colsing when Enter pressed.
	void Multiplication(); // Calculate Matrix A x Matrix B.
	bool IsProductDefined(); // Check if A x B is defined.

	// Get new matrix rows number from edit control and resize matrix.
	void ChangeEditRowsNo(CEdit *pEditCtrl, Matrix *pMatrix);
	// Get new matrix columns number from edit control and resize matrix.
	void ChangeEditColNo(CEdit *pEditCtrl, Matrix *pMatrix);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClickA(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnNotifyDescriptionEdited(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonClearA();
	afx_msg void OnBnClickedButtonClearB();
	afx_msg void OnBnClickedButtonClearResult();
	afx_msg void OnBnClickedButtonEqual();
	afx_msg void OnEnChangeEditDefaultValueA();
	afx_msg void OnEnChangeEditDefaultValueB();
	afx_msg void OnEnChangeEditRowsnoA();
	afx_msg void OnEnChangeEditColnoA();
	afx_msg void OnEnChangeEditRowsnoB();
	afx_msg void OnEnChangeEditColnoB();

protected:
	Matrix m_clMatrixA;
	Matrix m_clMatrixB;
	Matrix m_clMatrixResult;

	// Controls.
	CEdit m_cEditDefaultValueA;
	CEdit m_cEditDefaultValueB;
	CEdit m_cEditRowsNoA;
	CEdit m_cEditColNoA;	
	CEdit m_cEditRowsNoB;
	CEdit m_cEditColNoB;
};

