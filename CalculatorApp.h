//******************************************************************************
// The application class of the Calculator - an entry point for the whole program.
//
//******************************************************************************

#pragma once
#include <afxwin.h>
#include "CalculatorMainWindow.h"

class CalculatorApp : public CWinApp
{
public:
	CalculatorApp() {}

public:
	virtual BOOL InitInstance();
};

// Message Map macros
BEGIN_MESSAGE_MAP(CalculatorMainWindow, CDialog)
	ON_BN_CLICKED(IDC_BTN_0, &CalculatorMainWindow::OnBnClickedBtn0)
	ON_BN_CLICKED(IDC_BTN_BACKSPACE, &CalculatorMainWindow::OnBnClickedBtnBackspace)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CalculatorMainWindow::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_1, &CalculatorMainWindow::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_2, &CalculatorMainWindow::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN_3, &CalculatorMainWindow::OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN_4, &CalculatorMainWindow::OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN_5, &CalculatorMainWindow::OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN_6, &CalculatorMainWindow::OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN_7, &CalculatorMainWindow::OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN_8, &CalculatorMainWindow::OnBnClickedBtn8)
	ON_BN_CLICKED(IDC_BTN_9, &CalculatorMainWindow::OnBnClickedBtn9)
	ON_BN_CLICKED(IDC_BTN_COMMA, &CalculatorMainWindow::OnBnClickedBtnComma)
	ON_BN_CLICKED(IDC_BTN_DIVISION, &CalculatorMainWindow::OnBnClickedBtnDivision)
	ON_BN_CLICKED(IDC_BTN_PRODUCT, &CalculatorMainWindow::OnBnClickedBtnProduct)
	ON_BN_CLICKED(IDC_BTN_MINUS, &CalculatorMainWindow::OnBnClickedBtnMinus)
	ON_BN_CLICKED(IDC_BTN_PLUS, &CalculatorMainWindow::OnBnClickedBtnPlus)
	ON_BN_CLICKED(IDC_BTN_EQUAL, &CalculatorMainWindow::OnBnClickedBtnEqual)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_MATRIXCALC, &CalculatorMainWindow::OnBnClickedBtnMatrixcalc)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()