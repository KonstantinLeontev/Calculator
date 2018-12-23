#pragma once
#include "CalculatorMainWindow.h"
#include "MatrixCalculator.h"

void CalculatorMainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DISPLAY, m_csDigitDisplay);
	DDX_Control(pDX, IDC_BTN_0, m_button0);
	DDX_Control(pDX, IDC_BTN_1, m_button1);
	DDX_Control(pDX, IDC_BTN_2, m_button2);
	DDX_Control(pDX, IDC_BTN_3, m_button3);
	DDX_Control(pDX, IDC_BTN_4, m_button4);
	DDX_Control(pDX, IDC_BTN_5, m_button5);
	DDX_Control(pDX, IDC_BTN_6, m_button6);
	DDX_Control(pDX, IDC_BTN_7, m_button7);
	DDX_Control(pDX, IDC_BTN_8, m_button8);
	DDX_Control(pDX, IDC_BTN_9, m_button9);
	DDX_Control(pDX, IDC_BTN_DIVISION, m_buttonDivision);
	DDX_Control(pDX, IDC_BTN_PRODUCT, m_buttonProduct);
	DDX_Control(pDX, IDC_BTN_MINUS, m_buttonMinus);
	DDX_Control(pDX, IDC_BTN_PLUS, m_buttonPlus);
	DDX_Control(pDX, IDC_BTN_COMMA, m_buttonComma);
	DDX_Control(pDX, IDC_BTN_EQUAL, m_buttonEqual);
	DDX_Control(pDX, IDC_BTN_BACKSPACE, m_buttonBackspace);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_buttonClear);
	DDX_Control(pDX, IDC_EDIT_DISPLAY, m_ceDisplay);
	DDX_Control(pDX, IDC_BTN_MATRIXCALC, m_cbtnMatrixCalc);
}

BOOL CalculatorMainWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add some fonts.
	//---------------------------------------
	// Buttons
	m_cfCalcButtonFont.CreateFont(28, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, L"Microsoft Sans Serif");
	m_button0.SetFont(&m_cfCalcButtonFont);
	m_button1.SetFont(&m_cfCalcButtonFont);
	m_button2.SetFont(&m_cfCalcButtonFont);
	m_button3.SetFont(&m_cfCalcButtonFont);
	m_button4.SetFont(&m_cfCalcButtonFont);
	m_button5.SetFont(&m_cfCalcButtonFont);
	m_button6.SetFont(&m_cfCalcButtonFont);
	m_button7.SetFont(&m_cfCalcButtonFont);
	m_button8.SetFont(&m_cfCalcButtonFont);
	m_button9.SetFont(&m_cfCalcButtonFont);
	m_buttonDivision.SetFont(&m_cfCalcButtonFont);
	m_buttonProduct.SetFont(&m_cfCalcButtonFont);
	m_buttonMinus.SetFont(&m_cfCalcButtonFont);
	m_buttonPlus.SetFont(&m_cfCalcButtonFont);
	m_buttonComma.SetFont(&m_cfCalcButtonFont);
	m_buttonEqual.SetFont(&m_cfCalcButtonFont);
	m_buttonBackspace.SetFont(&m_cfCalcButtonFont);
	m_buttonClear.SetFont(&m_cfCalcButtonFont);
	//m_cbtnMatrixCalc.SetFont(&m_cfCalcButtonFont);
	// Display
	m_cfCalcDisplayFont.CreateFont(22, 0, 0, 0, FW_ULTRALIGHT, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, L"Lucida Console");
	m_ceDisplay.SetFont(&m_cfCalcDisplayFont);
	// Matrix Calc button
	m_cfCalcButtonMatrixFont.CreateFont(16, 0, 0, 0, FW_ULTRALIGHT, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, L"Lucida Console");
	m_cbtnMatrixCalc.SetFont(&m_cfCalcButtonMatrixFont);

	// Vertical align text inside the calculator's display.
	CRect crEditRect;
	m_ceDisplay.GetRect(&crEditRect);
	// Reduce the formatting rect of the edit control by
	// 10 pixels on each side.
	if (crEditRect.Height() > 20)
	{
		crEditRect.DeflateRect(0, 20, 0, 0);
		m_ceDisplay.SetRect(&crEditRect);
	}

	// Change the buttons colors.
	//---------------------------
	// Digit buttons
	m_button0.EnableWindowsTheming(FALSE);
	m_button0.SetFaceColor(m_crfDigitBtnColor);
	m_button0.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button1.EnableWindowsTheming(FALSE);
	m_button1.SetFaceColor(m_crfDigitBtnColor);
	m_button1.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button2.EnableWindowsTheming(FALSE);
	m_button2.SetFaceColor(m_crfDigitBtnColor);
	m_button2.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button3.EnableWindowsTheming(FALSE);
	m_button3.SetFaceColor(m_crfDigitBtnColor);
	m_button3.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button4.EnableWindowsTheming(FALSE);
	m_button4.SetFaceColor(m_crfDigitBtnColor);
	m_button4.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button5.EnableWindowsTheming(FALSE);
	m_button5.SetFaceColor(m_crfDigitBtnColor);
	m_button5.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button6.EnableWindowsTheming(FALSE);
	m_button6.SetFaceColor(m_crfDigitBtnColor);
	m_button6.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button7.EnableWindowsTheming(FALSE);
	m_button7.SetFaceColor(m_crfDigitBtnColor);
	m_button7.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button8.EnableWindowsTheming(FALSE);
	m_button8.SetFaceColor(m_crfDigitBtnColor);
	m_button8.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_button9.EnableWindowsTheming(FALSE);
	m_button9.SetFaceColor(m_crfDigitBtnColor);
	m_button9.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	// Equals sign and comma
	m_buttonEqual.EnableWindowsTheming(FALSE);
	m_buttonEqual.SetFaceColor(m_crfEqualBtnColor);
	m_buttonEqual.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_buttonComma.EnableWindowsTheming(FALSE);
	m_buttonComma.SetFaceColor(m_crfEqualBtnColor);
	m_buttonComma.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	// Math operations
	m_buttonDivision.EnableWindowsTheming(FALSE);
	m_buttonDivision.SetFaceColor(m_crfMathOperationsBtnColor);
	m_buttonDivision.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_buttonProduct.EnableWindowsTheming(FALSE);
	m_buttonProduct.SetFaceColor(m_crfMathOperationsBtnColor);
	m_buttonProduct.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_buttonMinus.EnableWindowsTheming(FALSE);
	m_buttonMinus.SetFaceColor(m_crfMathOperationsBtnColor);
	m_buttonMinus.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	m_buttonPlus.EnableWindowsTheming(FALSE);
	m_buttonPlus.SetFaceColor(m_crfMathOperationsBtnColor);
	m_buttonPlus.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	// Clear button
	m_buttonClear.EnableWindowsTheming(FALSE);
	m_buttonClear.SetFaceColor(m_crfClearBtnColor);
	m_buttonClear.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	// Backspace
	m_buttonBackspace.EnableWindowsTheming(FALSE);
	m_buttonBackspace.SetFaceColor(m_crfBackSpaceBtnColor);
	m_buttonBackspace.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	// Matrix Calc
	m_cbtnMatrixCalc.EnableWindowsTheming(FALSE);
	m_cbtnMatrixCalc.SetFaceColor(m_crfBackSpaceBtnColor);
	m_cbtnMatrixCalc.m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
	//m_cbtnMatrixCalc.SetButtonStyle(BS_VCENTER); // A vertical alignment by this way just kills other style tweaks.

	return TRUE;
}

//------------------------------------------------------------------
// Start Buttons
//------------------------------------------------------------------
void CalculatorMainWindow::OnBnClickedBtnBackspace()
{
	int iLength = m_csDigitDisplay.GetLength();
	// Delete last character.
	if (iLength > 1)
	{
		// First we must check for math operation in last character.
		char cLastChar = m_csDigitDisplay.GetAt(iLength - 1);
		if (cLastChar == '/' || cLastChar == '*' || cLastChar == '-' || cLastChar == '+')
		{
			// Set current operation to NONE for preventing unexpected calculations.
			m_eMathOperation = NONE;
			// Clear the right operand.
			m_csRightOperand = "";
		}
		m_csDigitDisplay.Delete(iLength - 1);

		// Trim the right operand if it's the case.
		if (m_eMathOperation != NONE)
		{
			int iLenghtRight = m_csRightOperand.GetLength();
			if (iLenghtRight > 0)
			{
				m_csRightOperand.Delete(iLenghtRight - 1);
			}
		}
	}
	// If there are only one last number, just change it to zero.
	else
	{
		m_csDigitDisplay = "0";
	}
	UpdateData(FALSE);
}

void CalculatorMainWindow::OnBnClickedBtnClear()
{
	// Change things to default for a next work.
	m_csDigitDisplay = "0";
	m_csLeftOperand = "";
	m_csRightOperand = "";
	m_eMathOperation = NONE;
	m_bDisplayResult = false;
	UpdateData(FALSE);
}

void CalculatorMainWindow::AddDigitToDisplay(char cDigit)
{
	// Check for displayng result previouse calculation.
	if (m_bDisplayResult && m_eMathOperation == NONE)
	{
		m_csDigitDisplay = "0";
		m_bDisplayResult = false;
	}

	// Take care of any first zeroes.
	if (m_csDigitDisplay.GetLength() == 1 && m_csDigitDisplay.GetAt(0) == '0' && cDigit != '.')
	{
		// Just replace the first number.
		m_csDigitDisplay.SetAt(0, cDigit);
	}
	// Do the same if right operand is current.
	else if (m_csRightOperand.GetLength() == 1 && m_csRightOperand.GetAt(0) == '0' && cDigit != '.')
	{
		// Just replace the first number.
		m_csRightOperand.SetAt(0, cDigit);
	}
	else
	{
		// Special check for comma input.
		if (cDigit == '.')
		{
			// Are there any comma in the string?
			if (m_eMathOperation == NONE)
			{
				// A left operand's case, so we should check the display string.
				if (m_csDigitDisplay.Find('.') != -1)
				{
					// There's already one separator exists, so nothing to do here.
					return;
				}
			}
			else
			{
				// A right operand's case, so we should check the right operand string.
				if (m_csRightOperand.Find('.') != -1)
				{
					// There's already one separator exists, so nothing to do here.
					return;
				}
				if (!m_csRightOperand.GetLength())
				{
					// If comma is the first character here then add zero before it.
					m_csDigitDisplay += '0';
					m_csRightOperand += '0';
				}
			}
		}

		// Add character to the end of the display string.
		m_csDigitDisplay += cDigit;
		// Check for adding to the rhs operand.
		if (m_eMathOperation != NONE)
		{
			m_csRightOperand += cDigit;
		}
	}

	UpdateData(FALSE);
}

void CalculatorMainWindow::OnBnClickedBtn0()
{
	AddDigitToDisplay('0');
}

void CalculatorMainWindow::OnBnClickedBtn1()
{
	AddDigitToDisplay('1');
}

void CalculatorMainWindow::OnBnClickedBtn2()
{
	AddDigitToDisplay('2');
}


void CalculatorMainWindow::OnBnClickedBtn3()
{
	AddDigitToDisplay('3');
}


void CalculatorMainWindow::OnBnClickedBtn4()
{
	AddDigitToDisplay('4');
}


void CalculatorMainWindow::OnBnClickedBtn5()
{
	AddDigitToDisplay('5');
}


void CalculatorMainWindow::OnBnClickedBtn6()
{
	AddDigitToDisplay('6');
}


void CalculatorMainWindow::OnBnClickedBtn7()
{
	AddDigitToDisplay('7');
}


void CalculatorMainWindow::OnBnClickedBtn8()
{
	AddDigitToDisplay('8');
}


void CalculatorMainWindow::OnBnClickedBtn9()
{
	AddDigitToDisplay('9');
}

void CalculatorMainWindow::OnBnClickedBtnComma()
{
	AddDigitToDisplay('.');
}

// All math operations we do here.
void CalculatorMainWindow::PerformMathOperation()
{
	double dLeft = _wtof(m_csLeftOperand);
	double dRight = _wtof(m_csRightOperand);

	switch (m_eMathOperation)
	{
	case DIV: m_dResult = (dRight) ? dLeft / dRight : dRight; break;
	case MULT: m_dResult = dLeft * dRight; break;
	case SUB: m_dResult = dLeft - dRight; break;
	case SUM: m_dResult = dLeft + dRight; break;
	default: MessageBox(NULL, L"An arithmetic operation is not defined.", MB_OK); break;
	}
	// Get string for display.
	m_csDigitDisplay.Format(L"%f", m_dResult);
	// Get rid of all this trailing zeroes.
	// First check for separator.
	int iFindResult = m_csDigitDisplay.Find('.');
	if (iFindResult != -1)
	{
		m_csDigitDisplay.TrimRight('0');
		int iLength = m_csDigitDisplay.GetLength();
		char cLastCharacter = m_csDigitDisplay.GetAt(iLength - 1);
		if (cLastCharacter == '.')
		{
			m_csDigitDisplay.Delete(iLength - 1);
		}
	}

	// Change everything to default for a next work.
	m_eMathOperation = NONE;
	m_csLeftOperand = "";
	m_csRightOperand = "";
	m_bDisplayResult = true;
	UpdateData(FALSE);
}

void CalculatorMainWindow::AddMathOperation(MATH eOperation)
{
	// When previous calculation isn't finished yet.
	if (m_eMathOperation != NONE)
	{
		// Then we must perform exist operation first.
		PerformMathOperation();
	}
	m_eMathOperation = eOperation;
	m_csLeftOperand = m_csDigitDisplay;
	switch (eOperation)
	{
	case DIV: m_csDigitDisplay += " / "; break;
	case MULT: m_csDigitDisplay += " * "; break;
	case SUB: m_csDigitDisplay += " - "; break;
	case SUM: m_csDigitDisplay += " + "; break;
	default: MessageBox(NULL, L"An arithmetic operation is not defined.", MB_OK); break;
	}
	UpdateData(FALSE);
}

void CalculatorMainWindow::OnBnClickedBtnDivision()
{
	AddMathOperation(DIV);
}


void CalculatorMainWindow::OnBnClickedBtnProduct()
{
	AddMathOperation(MULT);
}


void CalculatorMainWindow::OnBnClickedBtnMinus()
{
	AddMathOperation(SUB);
}


void CalculatorMainWindow::OnBnClickedBtnPlus()
{
	AddMathOperation(SUM);
}


void CalculatorMainWindow::OnBnClickedBtnEqual()
{
	PerformMathOperation();
}


HBRUSH CalculatorMainWindow::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_EDIT:
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_DISPLAY)
		{
			pDC->SetBkColor(m_crfDisplayBkColor);
			//pDC->SetBkColor(RGB(255, 255, 255));
			return (HBRUSH)(m_hbrushDisplay->GetSafeHandle());
		}
	}

	return hbr;
}

// Open second dialog with matrix calculator inside.
void CalculatorMainWindow::OnBnClickedBtnMatrixcalc()
{
	MatrixCalculator MatrixCalc;
	MatrixCalc.DoModal();
}