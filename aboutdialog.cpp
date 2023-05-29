#include <afxwin.h>
#include "aboutdialog.h"
#include <mmsystem.h>
#include "resource.h"

aboutdialog::aboutdialog( ) : CDialog ( IDD_DIALOG1 )
{
}

int aboutdialog::OnInitDialog( )
{
	::PlaySound ( "music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP ) ;
	return 1 ;
}

void aboutdialog::OnOK( ) 
{
	::PlaySound ( NULL, NULL, NULL ) ;
	CDialog::OnOK( ) ;
}

void aboutdialog::OnCancel( ) 
{
	::PlaySound ( NULL, NULL, NULL ) ;
	CDialog::OnCancel( ) ;
}
