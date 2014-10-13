// RegExpr.h: interface for the CRegExpr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGEXPR_H__2E457ECE_93E3_4451_B3F8_4578D6EECA50__INCLUDED_)
#define AFX_REGEXPR_H__2E457ECE_93E3_4451_B3F8_4578D6EECA50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include <ctype.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define EXPR_ERROR -1
#define TERMINATED 0	
#define SINGLE_STRING 1
#define STAR_CLOSURE 2
#define POSITIVE_CLOSURE 3
#define ZERO_OR_ONE 4

class CRegExpr  
{
public:
	int Evaluate(char *src, char *ptn);
	CRegExpr();
	virtual ~CRegExpr();

private:
	int GetToken(char *ptn, char *token, int *ptn_p, int *token_len);
};

#endif // !defined(AFX_REGEXPR_H__2E457ECE_93E3_4451_B3F8_4578D6EECA50__INCLUDED_)
