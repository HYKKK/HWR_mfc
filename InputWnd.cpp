// InputWnd.cpp : implementation file
//

#include <iostream>

#include <string>

#include "stdafx.h"
#include "WriteDown.h"
#include "InputWnd.h"

using namespace std;



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CInputWnd

CInputWnd::CInputWnd()
{
	mX = 0;
	mY = 0;
	endY = 0;
	pEndY = 0;
	ppEndY = 0;

	choTmp = _T("");
	jungTmp = _T("");
	jongTmp = _T("");

	choCode = _T("");
	jungCode = _T("");
	jongCode = _T("");


	cho = false;
	jung = false;

	bTmp = false;
	bTmp2 = false;
	rb = 0;
}

CInputWnd::~CInputWnd()
{
	CObPoint *pPoint;

	// 메모리 해제
	for (int i = m_Points.GetCount(); i; i--)
	{
		pPoint = (CObPoint*)m_Points.GetTail();
		delete pPoint;

		m_Points.RemoveTail();
	}
}


BEGIN_MESSAGE_MAP(CInputWnd, CWnd)
	//{{AFX_MSG_MAP(CInputWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInputWnd message handlers

void CInputWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	initX = point.x;
	initY = point.y;
	pmX = mX;
	pmY = mY;



	// 포인트 추가

	/*
	CString str;
	str.Format("%d %d",pmX, pmY);
	m_pDebug->SetWindowText(str);
	*/
	initX = point.x;
	initY = point.y;
	CObPoint* pPoint = new CObPoint(point.x, point.y);
	m_Points.AddTail(pPoint);
	m_PrevInputDir = NULL;

	char dir;

	// 입력이 계속 되는 경우
	if (m_PrevInputPoint.x >= 0)
	{
		int dx = point.x - m_PrevInputPoint.x;
		int dy = point.y - m_PrevInputPoint.y;

		// 입력 데이터 추가 (거리 측정 없음)
		dir = EvalDirection(dx, dy);

		m_Input += dir;

		if ((m_InputDetail.GetLength()) > 0)
			m_InputDetail += "-";

		m_InputPoints.AddTail(pPoint);


		m_pPatternEdit->SetWindowText(m_InputDetail);



		// 입력 포인트 찍기
		CClientDC dc(this);
		DrawInputPoint(dc);
	}

	m_PrevInputPoint = point;

	CWnd::OnLButtonDown(nFlags, point);
}

void CInputWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	ppEndY = pEndY;
	pEndY = endY;
	endX = point.x;
	endY = point.y;

	Simplification(m_InputDetail);
	m_pSCodeEdit->SetWindowText(m_SCode);

	// 끊어진 것을 나타내는 포인트 추가
	CObPoint* pPoint = new CObPoint(-1, -1);
	m_Points.AddTail(pPoint);

	getKorean(m_SCode);


	CWnd::OnLButtonUp(nFlags, point);
}

void CInputWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) && m_Points.GetCount()){
		CClientDC dc(this);
		CPen pen, *oldPen;
		CObPoint* pPoint;

		// 펜 선택
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0xFF));
		oldPen = (CPen*)dc.SelectObject(&pen);

		// 바로 전 포인트
		pPoint = (CObPoint*)m_Points.GetTail();

		// 선 그리기
		dc.MoveTo(pPoint->x, pPoint->y);
		dc.LineTo(point.x, point.y);

		// 포인트 추가
		pPoint = new CObPoint(point.x, point.y);
		m_Points.AddTail(pPoint);

		int dx = point.x - m_PrevInputPoint.x;
		int dy = point.y - m_PrevInputPoint.y;

		// 두 점사이의 간격이 일정값 이상일때 데이터에 추가함
		if (dx * dx + dy * dy > 40){

			// 입력 데이터 추가
			m_PrevInputDir = EvalDirection(dx, dy, m_PrevInputDir);
			m_Input += m_PrevInputDir;
			m_InputDetail += m_PrevInputDir;
			m_InputPoints.AddTail(pPoint);
			m_PrevInputPoint = point;
			m_pPatternEdit->SetWindowText(m_InputDetail);


		}

		dc.SelectObject(oldPen);
		pen.DeleteObject();

		// 입력 포인트 찍기
		DrawInputPoint(dc);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CInputWnd::OnPaint()
{
	CPaintDC dc(this);
	POSITION pos;
	CObPoint* pPoint;
	CPoint * Point;
	CRect rect;
	CPen pen, *oldPen;



}

CString CInputWnd::Simplification(CString src)
{
	char* ssrc = (LPSTR)(LPCTSTR)src;

	char* buffer = new char[strlen(ssrc) + 1];//토크나이즈하면 원본이 보존되지 않기 때문에 버퍼생성
	memset(buffer, NULL, strlen(ssrc) + 1);
	strcpy(buffer, ssrc);

	char* sret = new char[strlen(ssrc) + 1];
	memset(sret, NULL, strlen(ssrc) + 1);
	char* tok = NULL;

	char* ret = new char[strlen(ssrc)];
	memset(ret, NULL, strlen(ssrc)); // 줄일거





	//'ㅇ'인지 판별해서 9로 바꾼다.

	tok = strtok(buffer, "-");
	while (1)
	{
		char fst1 = 0;
		char fst2 = 0;
		int cnt1 = 0;
		int cnt2 = 0;
		int zeroflg = 0;
		for (int i = 0; i < strlen(tok) - 1; i++)
		{

			if (((((tok[i]) - 48) + 1) % 8) == (((tok[i + 1]) - 48) % 8))
			{
				if (fst1 != 0 && ((((fst2)-48) + 1) % 8) == (((tok[i + 1]) - 48) % 8))
				{
					fst1 = tok[i + 1];
					cnt1++;
				}
				else
				{
					fst1 = tok[i + 1];
					cnt1++;
				}
			}

			if (((((tok[i]) - 48) - 1) % 8) == (((tok[i + 1]) - 48) % 8))
			{
				if (fst2 != 0 && ((((fst2)-48) - 1) % 8) == (((tok[i + 1]) - 48) % 8))
				{
					fst2 = tok[i + 1];
					cnt2++;
				}
				else
				{
					fst2 = tok[i + 1];
					cnt2++;
				}
			}

			if ((cnt1 >= 8) || (cnt2 >= 8))
			{
				zeroflg = 1;
				break;
			}
		}
		if (zeroflg == 1)
			strcat(sret, "9");
		else
			strcat(sret, tok);

		tok = strtok(NULL, "-");
		if (tok == NULL)
			break;
		strcat(sret, "-");
	}


	unsigned int cnt = 1, j = 0;   // j는 ret index
	char ch;

	for (unsigned int i = 0; i < strlen(sret); i++){
		if (i == 0)
		{
			ch = sret[0];

			if (sret[i] == '9')
			{
				lastS += ch;
				ret[j] = '9';
				j++;
				cnt = 1;
			}
		}

		else if (sret[i] == '-')
		{
			if (cnt >= 3)
			{
				if (ret[j - 1] != ch)
				{
					ret[j] = ch;
					j++;
				}
			}
			lastS = "";
			ret[j] = '&';
			j++;
			cnt = 1;
		}

		else if (sret[i] == '9')
		{
			lastS += ch;
			ret[j] = '9';
			j++;
			cnt = 1;
		}

		else if (sret[i] == sret[i - 1])
			cnt++;

		else{
			if (cnt >= 3)
			{
				if (ret[j - 1] != ch)
				{
					lastS += ch;
					ret[j] = ch;
					j++;
				}
			}
			ch = sret[i];
			cnt = 1;
		}




		if (i == (strlen(sret) - 1))
		{
			if (cnt >= 3)
			{
				if (ret[j - 1] != ch)
				{
					lastS += ch;
					ret[j] = ch;
					j++;
				}
			}

			ret[j] = '\0';
		}
	}

	m_SCode = (CString)ret;

	delete[] sret;
	delete[] buffer;
	delete[] ret;

	return m_SCode;
}

void CInputWnd::getKorean(CString scode)
{
	CString conting = "ㄱㄷㅂㅅㅈㄴ";
	CString lConting[5] = { "ㄲ", "ㄸ", "ㅃ", "ㅆ", "ㅉ" };
	CString buf;
	CString chBuf;
	CString codeBuf;
	CString jBuf;//중성의 형태를 구분하기 위한 값을 저장할 버퍼
	int jShape; //숫자로 표현된 중성의 형태 

	CString result = _T("");
	CString exCode = _T("");//인식된 초성문자코드를 제외한 정규화코드를 담을 변수

	CStdioFile choFile;
	CStdioFile jungFile;
	CStdioFile jongFile;

	if (!choFile.Open(_T("chosung.txt"), CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL))//  기존 파일을 읽기 모드 | 다른 프로세스에서의 접근(읽기, 쓰기를 못하게 함)
	{
		AfxMessageBox("초성파일 오픈 에러");
		return;
	}
	if (!jungFile.Open(_T("jungsung.txt"), CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL))//  기존 파일을 읽기 모드 | 다른 프로세스에서의 접근(읽기, 쓰기를 못하게 함)
	{
		AfxMessageBox("중성파일 오픈 에러");
		return;
	}
	if (!jongFile.Open(_T("jongsung.txt"), CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL))//  기존 파일을 읽기 모드 | 다른 프로세스에서의 접근(읽기, 쓰기를 못하게 함)
	{
		AfxMessageBox("종성파일 오픈 에러");
		return;
	}

	//ㅜ구분하기
	if ((cho == true) && (jung == false))
	{
		if ((((initY + endY) / 2) > pmY) && (jungTmp != ""))
		{
			if ((jungTmp == "ㅡ") && (lastS == "5"))
				jung = false;
			else if (jungTmp != "?")
				jung = true;
		}
	}

	//초성
	if ((cho == false))
	{
		if (bTmp == true)
			exCode = scode.Right(scode.GetLength() - choCode.GetLength() - 1);
		while (choFile.ReadString(buf))
		{
			buf.Trim();
			AfxExtractSubString(chBuf, buf, 0, '|');
			AfxExtractSubString(codeBuf, buf, 1, '|');
			if (bTmp == true)//이어질 수 있는 자음들 모음
			{
				if (exCode.Find("&") == -1)
				{
					if ((endY > pmY) && (initX < pmX))//choTmp보다 아래쪽에 획이 그어졌을때
					{
						if (choTmp == "ㄱ"&&exCode == "7")//'근'과 'ㄹ'을 구분하기 위한 조건문
						{
							if (endX > (pmX + 10))//'근'으로 판정
							{
								cho = true;
								bTmp = false;
								rb = 0;
								break;
							}
							else//ㄹ로 판정
							{
								if (scode != codeBuf)
									choTmp = "?";
								cho = false;
								bTmp = false;
								rb = 0;
								break;
							}
						}
						else
						{
							cho = true;
							bTmp = false;
							rb = 0;
							break;
						}
					}


					if (choTmp == "ㄴ")//'너'와 '나'와 'ㅂ'을 구분하기 위한 조건문
					{

						if (endX > (pmX + 10))//중성이 존재한다고 판정
						{

							cho = true;
							bTmp = false;
							rb = 0;
							break;
						}
						else//ㅂ이라고 판정
						{
							if (scode != codeBuf)
								choTmp = "?";
							cho = false;
							bTmp = false;
							rb = 0;
							break;

						}
					}

					else if ((initX < pmX) && (endX < (pmX*1.05)) && (initY < pmY) && (endY < (pmY*1.05)))//최대값 안에 획을 그릴때
					{
						if (scode == codeBuf)
						{
							//CString ttt = choTmp + jungTmp + jongTmp;

							choTmp = chBuf;
							choCode = scode;
							cho = true;
							bTmp = false;
							rb = 0;
							break;
						}
					}

					//ㄱ->ㅈ예외처리
					if (choTmp == "ㄱ" && exCode == "6")
					{
						choCode = scode;
						choTmp = "ㅈ";
						break;
					}

				}

				if (exCode.Find("&") != -1 && (((initY + endY) / 2) > pmY))//종성여부 확인
				{
					cho = true;
					jung = true;
					bTmp = false;
					break;
				}

				if (exCode == codeBuf && choTmp == chBuf)//맞는 된소리인지 확인
				{
					if (choTmp == "ㅂ")//'ㅂ'과 'ㅒ'를 구분
					{
						CString rbBTmp;
						CString chBTmp;
						CString codeBTmp;
						jungFile.SeekToBegin();

						while (jungFile.ReadString(buf))
						{
							buf.Trim();
							AfxExtractSubString(rbBTmp, buf, 0, '|');
							AfxExtractSubString(chBTmp, buf, 1, '|');
							AfxExtractSubString(codeBTmp, buf, 2, '|');
							if ((rbBTmp == "2") && (codeBTmp == exCode) && (chBTmp == "ㅒ"))
							{
								if ((pEndY + ((endY - initY)*0.2)) < endY && (ppEndY + ((endY - initY)*0.2)) < pEndY)//'ㅒ'인경우
								{

									cho = true;
									bTmp = false;
									rb = 0;
									break;
								}
							}
						}

						if (bTmp == false)
							break;
					}

					int contingIndex = conting.Find(choTmp);
					choTmp = lConting[(contingIndex / 2)];
					choCode = scode;


					rb = 0;
					jungTmp = "";
					jungCode = "";
					cho = true;
					bTmp = false;
					break;
				}



				if (exCode.GetLength() > 8)
				{
					cho = true;
					bTmp = false;
				}
			}

			else
			{
				if (scode == codeBuf)
				{

					choCode = scode;
					choTmp = chBuf;

					if (conting.Find(choTmp) != -1)
					{

						bTmp = true;
					}
					else
					{
						rb = 0;
						cho = true;
					}
					break;
				}
				else
					choTmp = "?";
			}
		}
	}

	//중성
	if (((cho == true) && (jung == false)) || (bTmp == true))
	{
		if ((rb != 3 && rb != 2) && (scode != choCode) && (bTmp == false))
		{
			if ((endY > pmY) && (initX < pmX))
				rb = 1;//Bottom
			else if ((rb == 1) && (endX > pmX))
				rb = 3;//Bottom x Right
			else if (endX > pmX)
				rb = 2;//Right
		}



		//CString str;
		///str.Format("%d", rb);
		jungFile.SeekToBegin();
		while (jungFile.ReadString(buf))
		{
			buf.Trim();
			AfxExtractSubString(jBuf, buf, 0, '|');
			AfxExtractSubString(chBuf, buf, 1, '|');
			AfxExtractSubString(codeBuf, buf, 2, '|');

			int jShape = atoi(jBuf);

			CString scode2 = scode.Right(scode.GetLength() - choCode.GetLength() - 1);

			if (bTmp == true && scode != choCode)
			{
				exCode = scode.Right(scode.GetLength() - choCode.GetLength() - 1);
				if ((jShape == 2) && (exCode == codeBuf))
				{
					jungCode = exCode;
					jungTmp = chBuf;
					break;
				}
				else if (exCode.GetLength() == 0)
					jungTmp = "";
				else
					jungTmp = "?";
			}
			else
			{
				if ((jShape == rb) && (scode2 == codeBuf))
				{
					jungCode = scode2;
					jungTmp = chBuf;
					if (jungTmp == "ㅜ")
						bTmp2 = true;//중성이 ㅜ 라고 판별될 경우
					if (bTmp2 == true && jungTmp != "ㅜ")
						bTmp2 = false;
					break;
				}

				else if (scode2.GetLength() == 0)
				{
					jungTmp == "";
					break;
				}
				else
				{
					jungTmp = "?";
				}
			}
		}
	}

	//종성
	if ((jung == true && cho == true) || bTmp2 == true)
	{
		if (bTmp2 == true)
		{
			if (jongCode == "")
			{
				jongCode = lastS;

			}
			else
				jongCode += ("&" + lastS);

		}
		//AfxMessageBox("asdf");

		while (jongFile.ReadString(buf))
		{
			buf.Trim();
			AfxExtractSubString(chBuf, buf, 0, '|');
			AfxExtractSubString(codeBuf, buf, 1, '|');


			CString scode3 = scode.Right(scode.GetLength() - choCode.GetLength() - 1 - jungCode.GetLength() - 1);
			if (bTmp2 == true)
			{
				if (jongTmp == "" && (jungTmp == "ㅜ" || jungTmp == "?") && (codeBuf == jongCode.Left(jongCode.GetLength())))
				{
					jungTmp = "ㅡ";
					jungCode = "7";
					jung = true;

					jongCode = codeBuf;
					jongTmp = chBuf;


					bTmp2 = false;
					break;
				}

				else if (jongCode != "5" && (((initY + endY) / 2) > (pmY + 10)))
				{
					jungTmp = "ㅜ";
					jungCode = "7&5";
					jung = true;
					jongCode = jongCode.Right(jongCode.GetLength() - 2);
					bTmp2 = false;
					if (jongCode == codeBuf)
					{
						jongTmp = chBuf;
						break;
					}
					else
						jongTmp = "?";



				}
				/*
				else if(jungTmp == "ㅜ"&&(((initY+endY)/2)+10>pmY)&&endX>pmX)
				{
				jungTmp = "ㅜ";
				jungCode = "7&5";
				jung = true;

				jongCode = codeBuf;
				jongTmp=chBuf;


				bTmp2=false;
				break;
				}
				*/
			}

			else
			{
				if (scode3 == codeBuf)
				{
					jongCode = scode3;
					jongTmp = chBuf;
					break;
				}
				else
					jongTmp = "?";
			}
		}
	}

	m_pDebug->SetWindowText(choTmp + " " + jungCode + " " + jongCode);

	if ((cho == true || bTmp == true) && jungTmp == "")
		m_pPatternEdit1->SetWindowText(choTmp);
	else
	{
		if ((choTmp == "?") || (jungTmp == "?") || (jongTmp == "?"))
			result = "?";
		else
			result = mergeJaso(choTmp, jungTmp, jongTmp);

		m_pPatternEdit1->SetWindowText(result);
	}


	choFile.Close();
	jungFile.Close();
	jongFile.Close();
}

CString CInputWnd::mergeJaso(CString choSung, CString jungSung, CString jongSung)
{
	CString ChoSungTbl = "ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ";
	CString JungSungTbl = "ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ";
	CString JongSungTbl = "  ㄱㄲㄳㄴㄵㄶㄷㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅄㅅㅆㅇㅈㅊㅋㅌㅍㅎ";
	int m_UniCodeHangulBase = 0xAC00;

	int ChoSungPosition, JungSungPosition, JongSungPosition;
	int nUniCode;

	ChoSungPosition = ChoSungTbl.Find(choSung) / 2;     // 초성 위치
	JungSungPosition = JungSungTbl.Find(jungSung) / 2;   // 중성 위치
	JongSungPosition = JongSungTbl.Find(jongSung) / 2;   // 종성 위치


	// 앞서 만들어 낸 계산식
	nUniCode = m_UniCodeHangulBase + (ChoSungPosition * 21 + JungSungPosition) * 28 + JongSungPosition;
	// 코드값을 문자로 변환
	wchar_t tmp = nUniCode;
	CString ret = tmp;
	return ret;
}

char CInputWnd::EvalDirection(int dx, int dy, char prev)
{
	float d;//기울기

	// y축과 평행인 입력의 경우는 기울기를 임의의 큰 값으로 정함
	if (dx == 0){
		dx = 1;
		if (dy > 0) d = 10.0;
		else d = -10.0;
	}
	else d = (float)dy / dx;


	// 영역에 따른 값을 리턴
	if (dx > 0)
	{
		if (d > 2.4142) return '5'; // tan(3*pi/8)
		else if (d < -2.4142) return '1'; // -tan(3*pi/8)
		else if (d > 0.4142) return '6'; // tan(pi/8)
		else if (d < -0.4142) return '8'; // -tan(pi/8)
		else return '7';
	}
	else
	{
		if (d > 2.4142) return '1'; // 67.5
		else if (d < -2.4142) return '5'; // -tan(3*pi/8)
		else if (d > 0.4142) return '2'; // tan(pi/8)
		else if (d < -0.4142) return '4'; // -tan(pi/8)
		else return '3';
	}
}

void  CInputWnd::clear() {
	CClientDC dc(this);
	CRect rect;
	CObPoint* pPoint;

	// 모든 포인트를 삭제
	//for (int i = m_Points.GetCount(); i; i--)
	//{ 
	//	pPoint = (CObPoint*)m_Points.GetTail(); 
	//	delete pPoint; 

	//	m_Points.RemoveTail(); 
	//}

	//m_InputPoints.RemoveAll();

	// 입력된 값을 초기화
	//m_Input = "";
	//m_InputDetail = "";
	//m_SCode = "";
	m_pPatternEdit->SetWindowText("");//직접 적은 긴 패턴
	//m_pSCodeEdit->SetWindowText("");//심플코드
	m_pDebug->SetWindowText("");//학습코드 아래에 있는 edit
	mX = 0;
	mY = 0;
	endY = 0;
	pEndY = 0;
	ppEndY = 0;
	m_pMaxXEdit->SetWindowText("");
	m_pMaxYEdit->SetWindowText("");
	//m_pPatternEdit1->SetWindowText("");//결과출력창
	//m_PrevInputPoint.x = -1;
	//m_PrevInputPoint.y = -1;

	choTmp = _T("");
	jungTmp = _T("");
	jongTmp = _T("");

	choCode = _T("");
	jungCode = _T("");
	jongCode = _T("");



	cho = false;
	jung = false;
	bTmp = false;
	bTmp2 = false;

	rb = 0;

	// 화면을 지움
	//dc.SelectObject(GetStockObject(WHITE_PEN));
	//GetClientRect(rect);
	//dc.Rectangle(rect);
}
bool  CInputWnd::preventDupJung(CString sCode) {
	bool alreadyExist = false;
	CString sLine, sToken;
	CStdioFile file;

	file.Open(_T("jungsung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);

	while (file.ReadString(sLine))  // 한 줄씩 읽어들임
	{
		//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','로 파싱
		AfxExtractSubString(sToken, sLine, 2, '|');

		if (sToken == sCode){
			alreadyExist = true;

			break;
		}
	}
	file.Close();
	return alreadyExist;
}
bool  CInputWnd::preventDupCho(CString sCode) {
	bool alreadyExist = false;
	CString sLine, sToken;
	CStdioFile file;

	file.Open(_T("chosung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);

	while (file.ReadString(sLine))  // 한 줄씩 읽어들임
	{
		//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','로 파싱
		AfxExtractSubString(sToken, sLine, 1, '|');

		if (sToken == sCode){
			alreadyExist = true;

			break;
		}
	}
	file.Close();
	return alreadyExist;
}

bool  CInputWnd::preventDupJong(CString sCode) {
	bool alreadyExist = false;
	CString sLine, sToken;
	CStdioFile file;

	file.Open(_T("jongsung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);

	while (file.ReadString(sLine))  // 한 줄씩 읽어들임
	{
		//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','로 파싱
		AfxExtractSubString(sToken, sLine, 1, '|');

		if (sToken == sCode){
			alreadyExist = true;

			break;
		}
	}
	file.Close();
	return alreadyExist;
}
/*
bool CInputWnd::preventDup(CStdioFile file ,CString sCode ) {

bool alreadyExist = false;
CString sLine, sToken;
//CStdioFile file;
//file.Open(_T("filename"), CStdioFile::modeRead);


while (file.ReadString(sLine))  // 한 줄씩 읽어들임
{

//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','로 파싱
AfxExtractSubString(sToken, sLine, 1, '|' );

if(sToken==sCode){

alreadyExist = true;
break;
}
}
return alreadyExist;
}
*/
void  CInputWnd::inputScodeToCho() {


	CStdioFile choFile;
	CString result = _T("err");

	CString chosung;
	CString sCode = m_SCode;

	bool skip = false;

	m_pDebug->GetWindowText(result);
	chosung = result;
	m_pPatternEdit1->SetWindowText(result);

	if (preventDupCho(sCode)) {
		skip = true;

	}

	if (!choFile.Open(_T("chosung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
	{
		AfxMessageBox("초성파일 오픈 에러");
		return;
	}

	if (!skip) {
		choFile.SeekToEnd();
		choFile.WriteString("\n" + chosung + "|" + sCode);

	}
	choFile.Close();


}
void  CInputWnd::inputScodeToJong() {

	CStdioFile jongFile;

	CString jongsung;
	CString result = _T("err");

	bool skip = false;

	CString sCode = m_SCode;

	m_pDebug->GetWindowText(result);
	jongsung = result;
	m_pPatternEdit1->SetWindowText(result);

	if (preventDupJong(sCode)) {
		skip = true;
	}

	if (!jongFile.Open(_T("jongsung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite)) {
		AfxMessageBox("종성파일 오픈 에러");
		return;
	}

	if (!skip) {
		jongFile.SeekToEnd();
		jongFile.WriteString("\n" + jongsung + "|" + sCode);
	}
	jongFile.Close();
}

int CInputWnd::makeJShape(CString jungsung) {
	int jShape;

	if (jungsung == _T("ㅗ")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("ㅛ")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("ㅜ")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("ㅠ")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("ㅡ")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("ㅘ")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("ㅙ")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("ㅚ")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("ㅝ")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("ㅞ")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("ㅟ")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("ㅢ")) {
		jShape = 3;
		return jShape;
	}
	else{
		jShape = 2;
		return jShape;
	}
}

void CInputWnd::inputScodeToJung() {

	CStdioFile jungFile;

	CString jungsung;
	CString result = _T("err");
	int jShape = 0;
	bool skip = false;

	CString sCode = m_SCode;

	m_pDebug->GetWindowText(result);
	jungsung = result;
	jShape = makeJShape(jungsung);
	m_pPatternEdit1->SetWindowText(result);

	if (preventDupJung(sCode)) {
		skip = true;
	}
	if (!jungFile.Open(_T("jungsung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
	{
		AfxMessageBox("중성파일 오픈 에러");
		return;
	}

	if (!skip) {
		jungFile.SeekToEnd();

		CString jung;
		jung.Format("%d", jShape);
		jungFile.WriteString("\n" + jung + "|" + jungsung + "|" + sCode);
	}
	jungFile.Close();
}

void CInputWnd::Clear()
{
	CClientDC dc(this);
	CRect rect;
	CObPoint* pPoint;

	// 모든 포인트를 삭제
	for (int i = m_Points.GetCount(); i; i--)
	{
		pPoint = (CObPoint*)m_Points.GetTail();
		delete pPoint;

		m_Points.RemoveTail();
	}

	m_InputPoints.RemoveAll();

	// 입력된 값을 초기화
	m_Input = "";
	m_InputDetail = "";
	m_SCode = "";
	m_pPatternEdit->SetWindowText("");
	m_pSCodeEdit->SetWindowText("");
	m_pDebug->SetWindowText("");
	mX = 0;
	mY = 0;
	endY = 0;
	pEndY = 0;
	ppEndY = 0;
	m_pMaxXEdit->SetWindowText("");
	m_pMaxYEdit->SetWindowText("");
	m_pPatternEdit1->SetWindowText("");
	m_PrevInputPoint.x = -1;
	m_PrevInputPoint.y = -1;

	choTmp = _T("");
	jungTmp = _T("");
	jongTmp = _T("");

	choCode = _T("");
	jungCode = _T("");
	jongCode = _T("");



	cho = false;
	jung = false;
	bTmp = false;
	bTmp2 = false;

	rb = 0;

	// 화면을 지움
	dc.SelectObject(GetStockObject(WHITE_PEN));
	GetClientRect(rect);
	dc.Rectangle(rect);
}

void CInputWnd::DrawInputPoint(CDC &dc)
{
	CPen pen, *oldPen;
	POSITION pos;
	CObPoint *pPoint;




	pen.CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0));
	oldPen = (CPen*)dc.SelectObject(&pen);

	// 입력 포인트 찍기
	pos = m_InputPoints.GetHeadPosition();
	while (pos){
		pPoint = (CObPoint *)m_InputPoints.GetNext(pos);
		dc.Ellipse(pPoint->x - 2, pPoint->y - 2, pPoint->x + 2, pPoint->y + 2);

		if (mX < (pPoint->x))
		{
			CString smX;
			mX = pPoint->x;
			smX.Format("%d", mX);
			m_pMaxXEdit->SetWindowText(smX);
		}
		if (mY < (pPoint->y))
		{
			CString smY;
			mY = pPoint->y;
			smY.Format("%d", mY);
			m_pMaxYEdit->SetWindowText(smY);
		}
	}

	dc.SelectObject(oldPen);
	pen.DeleteObject();
}
