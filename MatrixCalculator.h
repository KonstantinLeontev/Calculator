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

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClickA(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickB(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnNotifyDescriptionEdited(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonClearA();
	afx_msg void OnBnClickedButtonClearB();
	afx_msg void OnBnClickedButtonClearResult();
	afx_msg void OnBnClickedButtonEqual();

private:
	Matrix m_clMatrixA;
	Matrix m_clMatrixB;
	Matrix m_clMatrixResult;	
};

