//******************************************************************************
// The main window of the Calculator.
//
//******************************************************************************
#pragma once
#include <afxwin.h>
#include <afxbutton.h>
#include "resource.h"
#include <memory>

class CalculatorMainWindow : public CDialog
{
public:
	CalculatorMainWindow(CWnd* pParent = NULL)
		: CDialog(CalculatorMainWindow::IDD, pParent), m_csDigitDisplay("0"), m_csLeftOperand(""), m_csRightOperand(""), m_eMathOperation(NONE), m_dResult(0.0), m_bDisplayResult(false)
	{
		// Set colors for the controls.
		// Display
		m_crfDisplayBkColor = RGB(143, 188, 143); // darkseagreen
		m_hbrushDisplay = std::make_unique<CBrush>(m_crfDisplayBkColor);
		// Button's colors
		m_crfDigitBtnColor = RGB(255, 255, 255); // white
		m_crfEqualBtnColor = RGB(240, 230, 140); // khaki
		m_crfMathOperationsBtnColor = RGB(100, 149, 237); // cornflowerblue
		m_crfClearBtnColor = RGB(255, 69, 0); // orange red
		m_crfBackSpaceBtnColor = RGB(255, 215, 0); // gold
	}

	// Dialog's ID
	enum { IDD = IDD_CALCMAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	// Translate keyboard message to dialog. That's a litle bit easier then custom CEdit class with input processing on its side.
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	DECLARE_MESSAGE_MAP();

private:
	enum MATH { NONE, SUM, SUB, MULT, DIV };

	void AddDigitToDisplay(char cDigit);
	void AddMathOperation(MATH eOperation);
	void PerformMathOperation();

	MATH m_eMathOperation;
	CString  m_csDigitDisplay;
	CString  m_csLeftOperand;
	CString  m_csRightOperand;
	double m_dResult;
	bool m_bDisplayResult;
	CFont m_cfCalcButtonFont;
	CFont m_cfCalcButtonMatrixFont;
	CFont m_cfCalcDisplayFont;

public:
	afx_msg void OnBnClickedBtn0();
	afx_msg void OnBnClickedBtnBackspace();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	afx_msg void OnBnClickedBtn3();
	afx_msg void OnBnClickedBtn4();
	afx_msg void OnBnClickedBtn5();
	afx_msg void OnBnClickedBtn6();
	afx_msg void OnBnClickedBtn7();
	afx_msg void OnBnClickedBtn8();
	afx_msg void OnBnClickedBtn9();
	afx_msg void OnBnClickedBtnComma();
	afx_msg void OnBnClickedBtnDivision();
	afx_msg void OnBnClickedBtnProduct();
	afx_msg void OnBnClickedBtnMinus();
	afx_msg void OnBnClickedBtnPlus();
	afx_msg void OnBnClickedBtnEqual();
	afx_msg void OnBnClickedBtnMatrixcalc();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	// Buttons
	CMFCButton m_button0;
	CMFCButton m_button1;
	CMFCButton m_button2;
	CMFCButton m_button3;
	CMFCButton m_button4;
	CMFCButton m_button5;
	CMFCButton m_button6;
	CMFCButton m_button7;
	CMFCButton m_button8;
	CMFCButton m_button9;
	CMFCButton m_buttonDivision;
	CMFCButton m_buttonProduct;
	CMFCButton m_buttonMinus;
	CMFCButton m_buttonPlus;
	CMFCButton m_buttonComma;
	CMFCButton m_buttonEqual;
	CMFCButton m_buttonBackspace;
	CMFCButton m_buttonClear;
	CMFCButton m_cbtnMatrixCalc;

	// Edit text box - display
	CEdit m_ceDisplay;

	//Colors
	COLORREF m_crfDisplayBkColor;
	std::unique_ptr<CBrush> m_hbrushDisplay;
	COLORREF m_crfDigitBtnColor;
	COLORREF m_crfEqualBtnColor;
	COLORREF m_crfMathOperationsBtnColor;
	COLORREF m_crfClearBtnColor;
	COLORREF m_crfBackSpaceBtnColor;
};