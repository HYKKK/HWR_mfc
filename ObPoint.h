// ObPoint.h: interface for the CObPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBPOINT_H__EE752892_2863_4DD1_83A2_3C0E7333B3ED__INCLUDED_)
#define AFX_OBPOINT_H__EE752892_2863_4DD1_83A2_3C0E7333B3ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObPoint : public CObject  
{
public:
	int y;
	int x;
	CObPoint(int _x, int _y);
	virtual ~CObPoint();

};

#endif // !defined(AFX_OBPOINT_H__EE752892_2863_4DD1_83A2_3C0E7333B3ED__INCLUDED_)
