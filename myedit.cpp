#include <afxwin.h>
#include "myedit.h"

BEGIN_MESSAGE_MAP ( myedit, CEdit )

	ON_WM_CREATE( )
	ON_WM_LBUTTONDOWN( )
	ON_WM_MOUSEMOVE( )

END_MESSAGE_MAP( )

int myedit::OnCreate ( LPCREATESTRUCT l ) 
{
	CEdit::OnCreate ( l ) ;
	m_cur = AfxGetApp( ) -> LoadStandardCursor ( IDC_ARROW ) ;
	return 0 ;
}

void myedit::OnLButtonDown ( UINT flags, CPoint pt )
{
}

void myedit::OnMouseMove ( UINT flags, CPoint pt )
{
	SetCursor ( m_cur ) ;
}
