#include "MatrixCalculator.h"

void MatrixCalculator::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MATRIX1, m_clMatrix1);
}

BOOL MatrixCalculator::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Populate the List Control with items.
	//--------------------------------------
	m_clMatrix1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE);

	// Row height
	int iRowHeight = 30;
	m_ciImageList.Create(1, iRowHeight, ILC_COLOR, 1, 1);
	m_clMatrix1.SetImageList(&m_ciImageList, LVSIL_SMALL);

	// Insert columns.
	LVCOLUMN lvColumn;
	for (int i = 0; i < 5; i++)
	{
		lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		// We don't need the first colummn's caption.
		CString csColumnCaption = "";
		if (i)
		{
			lvColumn.fmt = LVCFMT_RIGHT;
			lvColumn.cx = 65;
			csColumnCaption.Format(L"Col %d", i);
		}
		else
		{
			// First column must be left aligned.
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.cx = 40;
		}
		lvColumn.pszText = csColumnCaption.GetBuffer(csColumnCaption.GetLength());
		m_clMatrix1.InsertColumn(i, &lvColumn);
	}

	// Insert Items
	LVITEM lvItem;
	for (int i = 0; i < 4; i++)
	{
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		CString csRowCaption = "";
		csRowCaption.Format(L"Row %d", i);
		lvItem.pszText = csRowCaption.GetBuffer(csRowCaption.GetLength());
		m_clMatrix1.InsertItem(&lvItem);
		for (int j = 1; j < 5; j++)
		{
			CString csItemText = "";
			csItemText.Format(L"%d%d", i, j);
			m_clMatrix1.SetItemText(i, j, csItemText);
		}
	}

	return 0;
}
BEGIN_MESSAGE_MAP(MatrixCalculator, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MATRIX1, &MatrixCalculator::OnLvnItemchangedMatrix1)
END_MESSAGE_MAP()


void MatrixCalculator::OnLvnItemchangedMatrix1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}