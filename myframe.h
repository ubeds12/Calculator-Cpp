class myframe : public CFrameWnd
{
	private :

		myedit m_e ;	
		CRect m_editrect ;

		CButton m_b[30] ;
		CRect m_buttonrect[30] ;

		CStatic m_st ;

		CString m_str ;	
		double m_num, m_num1, m_num2, m_mem ;
		char m_oper ;
		bool m_over , m_decipoint ;

		static CString m_helpstrings[30] ;

	public :

		myframe( ) ;
		BOOL PreCreateWindow ( CREATESTRUCT& cs ) ;
		int OnCreate ( LPCREATESTRUCT l ) ;
		void myabout( ) ;
		void back( ) ;
		void c( ) ;
		void ce( ) ;
		void numbers0to9 ( int id ) ;
		void plusminus( ) ;
		void onebyx( ) ;
		void squareroot( ) ;
		void percentage( ) ;
		void point( ) ;
		void plus( ) ;
		void minus( ) ;
		void multiply( ) ;
		void divide( ) ;
		void equalto( ) ;
		void memorystore( ) ;
		void memoryrecall( ) ;
		void memorycancel( ) ;
		void memoryplus( ) ;
		void OnParentNotify ( long int m, unsigned long int p ) ;
		void OnKeyDown ( UINT ch, UINT rep, UINT flag ) ;

	DECLARE_MESSAGE_MAP( )
} ;
