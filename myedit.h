class myedit : public CEdit 
{
	private :

		HCURSOR m_cur ;

	public :

		int OnCreate ( LPCREATESTRUCT l ) ;
		void OnLButtonDown ( UINT flags, CPoint pt ) ;
		void OnMouseMove ( UINT flags, CPoint pt ) ;

	DECLARE_MESSAGE_MAP( )
} ;
