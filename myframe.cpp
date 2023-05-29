#include <afxwin.h>
#include "myedit.h"
#include "myframe.h"
#include "aboutdialog.h"
#include <math.h>
#include "resource.h"

BEGIN_MESSAGE_MAP ( myframe, CFrameWnd )
		
	ON_WM_CREATE( )

	ON_COMMAND ( 1001, myabout )
	
	ON_COMMAND_RANGE ( 1, 10, numbers0to9 ) 

	ON_COMMAND ( 101, back )
	ON_COMMAND ( 102, ce ) 
	ON_COMMAND ( 103, c ) 
	ON_COMMAND ( 106, memorycancel ) 
	ON_COMMAND ( 107, divide )
	ON_COMMAND ( 108, squareroot ) 
	ON_COMMAND ( 109, memoryrecall ) 
	ON_COMMAND ( 110, multiply ) 
	ON_COMMAND ( 111, percentage ) 
	ON_COMMAND ( 112, memorystore ) 
	ON_COMMAND ( 113, minus )
	ON_COMMAND ( 114, onebyx ) 
	ON_COMMAND ( 115, memoryplus ) 
	ON_COMMAND ( 117, plusminus ) 
	ON_COMMAND ( 118, point ) 
	ON_COMMAND ( 119, plus ) 
	ON_COMMAND ( 120, equalto ) 
	
	ON_WM_PARENTNOTIFY( )

	ON_WM_KEYDOWN( )

END_MESSAGE_MAP()

CString myframe::m_helpstrings[] = {
									"No help topic is associated with this item.",
									"Delete the last digit of the displayed number.",
									"Clears the displayed number.",
									"Clears the current calculation.",
									"",
									"",
									"Clears any number stored in memory.",
									"Puts this number in the calculator display.",
									"Puts this number in the calculator display.",
									"Puts this number in the calculator display.",
									"Divdes.",
									"Calculates the square root of the displayed number.",
									"Recalls the number stored in memory. The number remains in the memory.",
									"Puts this number in the calculator display.",
									"Puts this number in the calculator display.",
									"Puts this number in the calculator display.",
									"Multiplies.",
									"Displays the result of the multiplication as percentage.",
									"Stores the displayed number in the memory.",
									"Puts this number in the calculator display.",
									"Puts this number in the calculator display.",
									"Puts this number in the calculator display.",
									"Subracts.",
									"Calculates the reciprocal of the displayed number.",
									"Adds the displayed number to any number already in memory.",
									"Puts this number in the calculator display.",
									"Changes the sign of the displayed number.",
									"Inserts a decimal point.",
									"Adds.",
									"Performs any operation on the previous two numbers. To repeat he last operation click again."
								} ;	

myframe::myframe( )
{
	CString mywindowclass ;
	CBrush mybrush ;
	mybrush.CreateStockObject ( LTGRAY_BRUSH ) ;
	mywindowclass = AfxRegisterWndClass ( CS_HREDRAW | CS_VREDRAW,
											AfxGetApp( ) -> LoadStandardCursor ( IDC_ARROW ),
											mybrush, 
											AfxGetApp( ) -> LoadIcon ( IDI_ICON1 ) ) ;
											
	Create ( mywindowclass, "Calculator", WS_SYSMENU | WS_MINIMIZEBOX, CRect ( 100, 100, 400, 400 ), 0, MAKEINTRESOURCE ( IDR_MENU1 ) ) ;
}

BOOL myframe::PreCreateWindow ( CREATESTRUCT& cs ) 
{
	CFrameWnd::PreCreateWindow ( cs ) ;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE ;

	return TRUE ;
}

int myframe::OnCreate ( LPCREATESTRUCT l )
{
	CFrameWnd::OnCreate ( l ) ;

	struct buttoninfo
	{
		char m_str[5] ;
		int id ;
	} ;	
			
	buttoninfo m[30] = 
						{
							"", 100,
							"Back", 101,
							"CE", 102,
							"C", 103,
							"", 104,
							"", 105,
									
							"MC", 106,
							"7", 8,
							"8", 9,
							"9", 10,
							"/", 107,
							"Sqrt", 108,
    
							"MR", 109,
							"4", 5,
							"5", 6,
							"6", 7,
							"*", 110,
							"%", 111,

							"MS", 112,
							"1", 2,
							"2", 3,
							"3", 4,
							"-", 113,
							"1/x", 114,

							"M+", 115,
							"0", 1,
							"+/-", 117,
							".", 118,
							"+", 119,
							"=", 120    
						} ;

	m_editrect = CRect ( 10, 10, 275, 35 ) ;
	m_e.CreateEx ( WS_EX_CLIENTEDGE, "EDIT", "0.", WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_MULTILINE, m_editrect, this, 30 ) ;

	int  x1 = 10, y1 = 50, x2, y2 ;

	for ( int i = 0 ; i <= 29 ; i++ )
	{
		x2 = x1 + 40 ;
		y2 = y1 + 30 ;

		m_buttonrect[i] = CRect ( x1, y1, x2, y2 ) ;
		if ( i != 0 && i != 4 && i != 5 )
			m_b[i].Create ( m[i].m_str, BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, m_buttonrect[i], this, m[i].id ) ;

		if ( i == 0 )
			m_st.CreateEx ( WS_EX_CLIENTEDGE, "STATIC", "", WS_VISIBLE | WS_CHILD | SS_NOTIFY, m_buttonrect[i], this, m[i].id ) ;

		x1 += 45 ;
		if ( ( i + 1 ) % 6 == 0 ) 
		{
			x1 = 10 ;
			y1 = y1 + 40 ;
		}
	}

	m_oper = ' ' ;
	m_over = true;
	m_decipoint = false ;
	m_mem = 0 ;
		
	return 0 ;
}

void myframe::myabout( )
{
	aboutdialog d ;
	d.DoModal( ) ;
}

void myframe::back()
{
	CString lf, rt ;
	
	m_e.GetWindowText ( m_str ) ;
			
	lf = m_str.Left ( m_str.GetLength( ) - 1 ) ;
	rt = m_str.Right ( 1 ) ;

	if ( rt == "." )
	{
		m_decipoint = false ;

		if ( m_str == "0." )
			m_over = true ;
		else
			m_str = lf ;
	}
	else
	{
		if ( lf.Right ( 1 ) == "." )
		{
			m_decipoint = false ;

			if ( lf == "0." )
			{
				m_str = "0." ;
				m_over = true ;
			}
			else
				m_str = lf.Left ( lf.GetLength( ) - 1 ) ;
		}
		else
		{
			if ( lf == "" )
			{
				m_str = "0." ;
				m_over = true ;
			}
			else
				m_str = lf ;
		}
	}

	m_e.SetWindowText ( m_str ) ;
	}

void myframe::c( )
{
	m_num1 = m_num2 = 0 ;
	m_over = true ;
	m_decipoint = false ;
	m_str = "0." ;
	m_e. SetWindowText(m_str) ;
}

void myframe::ce( )
{
	if ( m_oper == ' ' )
		m_num1 = 0 ;
	else
		m_num2 = 0 ;
			
	m_str= "0." ;
	m_e. SetWindowText ( m_str ) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::numbers0to9 ( int id )
{
	CString temp ;
	temp.Format ( "%d", id - 1 ) ;

	if ( m_over == false )
	{
		m_e.GetWindowText ( m_str ) ;
		if ( m_str == "0." )
			return ;

		if ( m_str.GetLength( ) == 13 )
		{
			::MessageBeep ( 1 ) ;
		}
		else
		{
			m_str = m_str + temp ;
			m_e.SetWindowText ( m_str ) ;
		}
	}
	else
	{
		m_e.SetWindowText ( temp ) ;
		m_over = false ;
	}
}
	
void myframe::plusminus( )
{
	m_e.GetWindowText ( m_str ) ;

	m_num = atof ( m_str ) ;
	if ( m_num != 0 )
		m_num = m_num * -1 ;

	m_str.Format ( "%.8g", m_num ) ;
			
	m_e. SetWindowText ( m_str ) ;
	m_over = true ;
}

void myframe::onebyx( )
{
	m_e.GetWindowText ( m_str ) ;

	m_num = atof ( m_str ) ;
	if ( m_num != 0 )
		m_num = 1 / m_num ;

	m_str.Format ( "%.8g", m_num ) ;

	m_e.SetWindowText ( m_str ) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::squareroot( )
{
	m_e.GetWindowText ( m_str ) ;

	m_num = atof ( m_str ) ;
	if ( m_num != 0 )
		m_num = sqrt ( m_num ) ;

	m_str.Format( "%.8g", m_num ) ;

	m_e.SetWindowText(m_str) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::percentage()
{
	double num3 ;

	if ( m_oper != ' ' )
	{
		m_e.GetWindowText ( m_str ) ;
		m_num2 = atof ( m_str ) ;
		num3 = m_num2 * m_num1 ;
		num3 = num3 / 100 ;
		m_str.Format( "%.8g", num3 ) ;
		m_e.SetWindowText ( m_str ) ;

		m_over = true ;
		m_decipoint = false ;
		m_oper = ' ' ;
	}
}

void myframe::point( )
{
	if ( m_decipoint == false )
	{
		if ( m_over == true ) 
		{
			m_e.SetWindowText ( "0." ) ;
			m_over = false ;
		}
		else
		{
			m_e.GetWindowText ( m_str ) ;
			if ( m_str == "0." )
				return ;
			else
			{
				m_str = m_str + "." ;
				m_e. SetWindowText ( m_str ) ;
			}
		}

		m_decipoint = true ;
	}
	else
		::MessageBeep ( 1 ) ;
}

void myframe::plus( )
{
	if ( m_oper != ' ' )
		equalto( ) ;

	m_oper = '+' ;
	m_e.GetWindowText ( m_str ) ;
	m_num1 = atof ( m_str ) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::minus( )
{
	if ( m_oper != ' ' )
		equalto( ) ;

	m_oper = '-' ;
	m_e.GetWindowText ( m_str ) ;
	m_num1 = atof ( m_str ) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::multiply( )
{
	if ( m_oper != ' ' )
		equalto( ) ;

	m_oper = '*' ;
	m_e.GetWindowText ( m_str ) ;
	m_num1 = atof ( m_str ) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::divide( )
{
	if ( m_oper != ' ' )
		equalto( ) ;

	m_oper = '/' ;
	m_e.GetWindowText ( m_str ) ;
	m_num1 = atof ( m_str ) ;
	m_over = true ;
	m_decipoint = false ;
}

void myframe::equalto( )
{
	if ( m_oper == ' ' )
		return ;

	double num3 ;
			
	m_e.GetWindowText ( m_str ) ;
	m_num2 = atof ( m_str ) ;
		
	switch ( m_oper )
	{
		case '+' :

			num3 = m_num1 + m_num2 ;
			break ;

		case '-' :

			num3 = m_num1 - m_num2 ;
			break ;

		case '*' :

			num3 = m_num1 * m_num2 ;
			break ;

		case '/' :

			if ( m_num2 == 0 )
			{
				m_over = true ;
				m_decipoint = false ;
				m_e.SetWindowText ( "Cannot divide by zero." ) ;
				return ;
			}
			else
				num3 = m_num1 / m_num2 ;
	}

	m_str.Format ( "%.8g", num3 ) ;

	if ( m_str == "0" )
		m_str = "0." ;

	m_over = true ;
	m_decipoint = false ;
	m_oper = ' ' ;
	m_e.SetWindowText ( m_str ) ;
}

void myframe::memorystore( )
{
	m_e.GetWindowText ( m_str ) ;
	m_mem = atof ( m_str ) ;
	m_st.SetWindowText ( "M" ) ;

	m_over = true ;
	m_decipoint = false ;
	m_oper = ' ' ;
}

void myframe::memoryrecall( )
{
	m_str.Format( "%.8g", m_mem ) ;
	m_e.SetWindowText ( m_str ) ;

	m_over = true ;
	m_decipoint = false ;
	m_oper = ' ' ;
}
		
void myframe::memorycancel( )
{
	m_mem = 0 ;
	m_st.SetWindowText ( "" ) ;
}

void myframe::memoryplus( )
{
	m_e.GetWindowText ( m_str ) ;
	m_num = atof ( m_str ) ; 
	m_mem = m_mem + m_num ; 
	m_st.SetWindowText ( "M" ) ;
			
	m_over = true ;
	m_decipoint = false ;
	m_oper = ' ' ;
}

void myframe::OnParentNotify ( long int m, unsigned long int p )
{
	int mousebutton = LOWORD ( m ) ;

	if ( mousebutton == WM_RBUTTONDOWN )
	{
		int x = LOWORD ( p ) ;
		int y = HIWORD ( p ) ;
	
		CPoint pt ( x, y ) ;

		if ( m_editrect.PtInRect ( pt ) )
			MessageBox ( "Shows the result.", "Help...", MB_OK | MB_ICONQUESTION ) ;			

		for ( int i = 0 ; i <= 29 ; i++ )
		{
			if ( m_buttonrect[i].PtInRect ( pt ) )
				MessageBox ( m_helpstrings[i], "Help...", MB_OK | MB_ICONQUESTION ) ;			
		}
	}
}

void myframe::OnKeyDown ( UINT ch, UINT rep, UINT flag )
{
	switch ( ch )
	{
		case VK_BACK :

			back( );
			break ;
	
		case VK_NUMPAD7 :
		case '7' :

			m_b[7].SetState ( 1 ) ;
			numbers0to9 ( 8 ) ;
			Sleep ( 20 ) ;
			m_b[7].SetState ( 0 ) ;
			break ;
			
		case VK_NUMPAD8 :
		case '8' :

			m_b[8].SetState ( 1 ) ;
			numbers0to9 ( 9 ) ;
			Sleep ( 20 ) ;
			m_b[8].SetState ( 0 ) ;
			break ;
			
		case VK_NUMPAD9 :
		case '9' :

			m_b[9].SetState ( 1 ) ;
			numbers0to9 ( 10 ) ;
			Sleep ( 20 ) ;
			m_b[9].SetState ( 0 ) ;
			break ;
			
		case VK_DIVIDE :

			m_b[10].SetState ( 1 ) ;
			divide( );
			Sleep ( 20 ) ;
			m_b[10].SetState ( 0 ) ;
			break ;

		case VK_NUMPAD4 :
		case '4' :

			m_b[13].SetState ( 1 ) ;
			numbers0to9 ( 5 ) ;
			Sleep ( 20 ) ;
			m_b[13].SetState ( 0 ) ;
			break ;
			
		case VK_NUMPAD5 :
		case '5' :

			m_b[14].SetState ( 1 ) ;
			numbers0to9 ( 6 ) ;
			Sleep ( 20 ) ;
			m_b[14].SetState ( 0 ) ;
			break ;
			
		case VK_NUMPAD6 :
		case '6' :

			m_b[15].SetState ( 1 ) ;
			numbers0to9 ( 7 ) ;
			Sleep ( 20 ) ;
			m_b[15].SetState ( 0 ) ;
			break ;
			
		case VK_MULTIPLY :

			m_b[16].SetState ( 1 ) ;
			multiply( ) ;
			Sleep ( 20 ) ;
			m_b[16].SetState ( 0 ) ;
			break ;
					
		case VK_NUMPAD1 :
		case '1' :

			m_b[19].SetState ( 1 ) ;
			numbers0to9 ( 2 ) ;
			Sleep ( 20 ) ;
			m_b[19].SetState ( 0 ) ;
			break ;
			
		case VK_NUMPAD2 :
		case '2' :

			m_b[20].SetState ( 1 ) ;
			numbers0to9 ( 3 ) ;
			Sleep ( 20 ) ;
			m_b[20].SetState ( 0 ) ;
			break ;
			
		case VK_NUMPAD3 :
		case '3' :

			m_b[21].SetState ( 1 ) ;
			numbers0to9 ( 4 ) ;
			Sleep ( 20 ) ;
			m_b[21].SetState ( 0 ) ;
			break ;
			
		case VK_SUBTRACT :

			m_b[22].SetState ( 1 ) ;
			minus( );
			Sleep ( 20 ) ;
			m_b[22].SetState ( 0 ) ;
			break ;
					
		case VK_NUMPAD0 :
		case '0' :

			m_b[25].SetState ( 1 ) ;
			numbers0to9 ( 1 ) ;
			Sleep ( 20 ) ;
			m_b[25].SetState ( 0 ) ;
			break ;
					
		case VK_DECIMAL :

			m_b[27].SetState ( 1 ) ;
			point( ) ;
			Sleep ( 20 ) ;
			m_b[27].SetState ( 0 ) ;
			break ;
			
		case VK_ADD :

			m_b[28].SetState ( 1 ) ;
			plus( ) ;
			Sleep ( 20 ) ;
			m_b[28].SetState ( 0 ) ;
			break ;
			
		case VK_RETURN :

			m_b[29].SetState ( 1 ) ;
			equalto( ) ;
			Sleep ( 20 ) ;
			m_b[29].SetState ( 0 ) ;
			break ;
	}
}
