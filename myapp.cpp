#include <afxwin.h>
#include "myapp.h"
#include "myedit.h"
#include "myframe.h"

myapp a ;

int myapp::InitInstance( )
{
	myframe *p ;
	p = new myframe ;
	p -> ShowWindow ( 1 ) ;
	m_pMainWnd = p ;

	return 1 ;
}
