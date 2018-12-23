#pragma once
#include "CalculatorApp.h"

BOOL CalculatorApp::InitInstance()
{
	CWinApp::InitInstance();
	SetRegistryKey(L"Simple Calculator");
	CalculatorMainWindow dlgCalcMain;
	m_pMainWnd = &dlgCalcMain;
	INT_PTR nResponse = dlgCalcMain.DoModal();
	return FALSE;
}

// The app starts here
CalculatorApp Calculator;