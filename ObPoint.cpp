// ObPoint.cpp: implementation of the CObPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WriteDown.h"
#include "ObPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObPoint::CObPoint(int _x, int _y) : x(_x), y(_y)
{

}

CObPoint::~CObPoint()
{

}
