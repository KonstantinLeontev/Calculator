#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"

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
	void MatrixCalculator::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLvnItemchangedMatrix1(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CListCtrl m_clMatrix1;
	CImageList m_ciImageList; // This one is only for changing list's row height.
};

