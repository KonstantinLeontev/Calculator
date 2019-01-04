#pragma once
#include "afxwin.h"
#include "resource.h"
#include "CalculatorGlobals.h"

class CInPlaceEdit : public CEdit
{
public:
	CInPlaceEdit(int iRow, int iColumn, CString csInitText)
		: m_iRow(iRow), m_iColumn(iColumn), m_bESC(FALSE), m_sInitText(csInitText), m_bFirstCharFlag(TRUE), m_bDotCharFlag(TRUE) {}

public:
	// Determines whether certain key strokes make it to the edit control.
	virtual BOOL PreTranslatedMessage(MSG* pMsg);

public:	virtual ~CInPlaceEdit() {}

// Message map functions.
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd); //  Send LVN_ENDLABELEDIT and destroys the edit control

protected:
	afx_msg void OnNcDestroy(); // Destroy the C++ object.
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags); // Terminates editing if the Escape or the Enter key is pressed
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()

private:
	int m_iRow;
	int m_iColumn;
	CString m_sInitText;
	BOOL m_bESC;
	BOOL m_bFirstCharFlag; // Need this to allow '-' char input if it goes to the first place.
	BOOL m_bDotCharFlag; // Allows put '.' only once as decimal separator.
};

