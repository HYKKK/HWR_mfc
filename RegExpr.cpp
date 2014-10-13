// RegExpr.cpp: implementation of the CRegExpr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WriteDown.h"
#include "RegExpr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegExpr::CRegExpr()
{

}

CRegExpr::~CRegExpr()
{

}

///////////////////////////////////////////////////////////////////////////////
//
// 정규 표현식에 의한 패턴 매칭을 테스트 함
//
// 리턴값 : TRUE, FALSE, EXPR_ERROR
//
///////////////////////////////////////////////////////////////////////////////
int CRegExpr::Evaluate(char *src, char *ptn)
{
	int ptn_p = 0, src_p = 0, src_len, token_len;
	char token[50];

	src_len = strlen(src);

	for (;;){
		switch (GetToken(&ptn[ptn_p], token, &ptn_p, &token_len)){
		case TERMINATED:
			if (src_p == src_len) return TRUE;
			else return FALSE;
		case SINGLE_STRING:
			if (strncmp(&src[src_p], token, token_len)) return FALSE;
			else src_p += token_len;
			break;
		case STAR_CLOSURE:
			while (!strncmp(&src[src_p], token, token_len)){
				if (Evaluate(&src[src_p], &ptn[ptn_p]) == TRUE) return TRUE;

				src_p += token_len;
				if (src_p >= src_len) break;
			}
			break;
		case POSITIVE_CLOSURE:
			if (strncmp(&src[src_p], token, token_len)) return FALSE;
			else{
				src_p += token_len;

				while (!strncmp(&src[src_p], token, token_len)){
					if (Evaluate(&src[src_p], &ptn[ptn_p]) == TRUE) return TRUE;

					src_p += token_len;
					if (src_p >= src_len) break;
				}
			}
			break;
		case ZERO_OR_ONE:
			if (!strncmp(&src[src_p], token, token_len)){
				if (Evaluate(&src[src_p], &ptn[ptn_p]) == TRUE) return TRUE;

				src_p += token_len;
			}
			break;
		case EXPR_ERROR:
			return EXPR_ERROR;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// 이 함수는 RegExpr 함수에 의해서만 사용됨
//
// 리턴값 : 정의된 토큰
//
///////////////////////////////////////////////////////////////////////////////
int CRegExpr::GetToken(char *ptn, char *token, int *ptn_p, int *token_len)
{
	int len = strlen(ptn);

	if (len == 0) return TERMINATED;

/*
	// 괄호처리는 못하였음
	if (ptn[0] == '('){
		int i = 1, paran = 1;

		while (i < len){
			if (ptn[i] == ')'){
				paran--;
				if (paran == 0) break;
			} else if (ptn[i] == '(') paran++;

			token[i-1] = ptn[i];
		}

		if (paran) return EXPR_ERROR;

		token[i-1] = NULL;
		*ptn_p += i+1;
		*token_len = i-1;

		return EXPRESSION;
	}
*/
	if (isalnum(ptn[0]) == FALSE) return EXPR_ERROR;

	if (len >= 2){
		if (ptn[1] == '*'){
			token[0] = ptn[0];
			token[1] = NULL;
			*ptn_p += 2;
			*token_len = 1;

			return STAR_CLOSURE;
		}
		
		if (ptn[1] == '+'){
			token[0] = ptn[0];
			token[1] = NULL;
			*ptn_p += 2;
			*token_len = 1;

			return POSITIVE_CLOSURE;
		}

		if (ptn[1] == '?'){
			token[0] = ptn[0];
			token[1] = NULL;
			*ptn_p += 2;
			*token_len = 1;

			return ZERO_OR_ONE;
		}
	}

	token[0] = ptn[0];
	token[1] = NULL;
	*ptn_p += 1;
	*token_len = 1;

	return SINGLE_STRING;
}

