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

	// �޸� ����
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



	// ����Ʈ �߰�

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

	// �Է��� ��� �Ǵ� ���
	if (m_PrevInputPoint.x >= 0)
	{
		int dx = point.x - m_PrevInputPoint.x;
		int dy = point.y - m_PrevInputPoint.y;

		// �Է� ������ �߰� (�Ÿ� ���� ����)
		dir = EvalDirection(dx, dy);

		m_Input += dir;

		if ((m_InputDetail.GetLength()) > 0)
			m_InputDetail += "-";

		m_InputPoints.AddTail(pPoint);


		m_pPatternEdit->SetWindowText(m_InputDetail);



		// �Է� ����Ʈ ���
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

	// ������ ���� ��Ÿ���� ����Ʈ �߰�
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

		// �� ����
		pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0xFF));
		oldPen = (CPen*)dc.SelectObject(&pen);

		// �ٷ� �� ����Ʈ
		pPoint = (CObPoint*)m_Points.GetTail();

		// �� �׸���
		dc.MoveTo(pPoint->x, pPoint->y);
		dc.LineTo(point.x, point.y);

		// ����Ʈ �߰�
		pPoint = new CObPoint(point.x, point.y);
		m_Points.AddTail(pPoint);

		int dx = point.x - m_PrevInputPoint.x;
		int dy = point.y - m_PrevInputPoint.y;

		// �� �������� ������ ������ �̻��϶� �����Ϳ� �߰���
		if (dx * dx + dy * dy > 40){

			// �Է� ������ �߰�
			m_PrevInputDir = EvalDirection(dx, dy, m_PrevInputDir);
			m_Input += m_PrevInputDir;
			m_InputDetail += m_PrevInputDir;
			m_InputPoints.AddTail(pPoint);
			m_PrevInputPoint = point;
			m_pPatternEdit->SetWindowText(m_InputDetail);


		}

		dc.SelectObject(oldPen);
		pen.DeleteObject();

		// �Է� ����Ʈ ���
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

	char* buffer = new char[strlen(ssrc) + 1];//��ũ�������ϸ� ������ �������� �ʱ� ������ ���ۻ���
	memset(buffer, NULL, strlen(ssrc) + 1);
	strcpy(buffer, ssrc);

	char* sret = new char[strlen(ssrc) + 1];
	memset(sret, NULL, strlen(ssrc) + 1);
	char* tok = NULL;

	char* ret = new char[strlen(ssrc)];
	memset(ret, NULL, strlen(ssrc)); // ���ϰ�





	//'��'���� �Ǻ��ؼ� 9�� �ٲ۴�.

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


	unsigned int cnt = 1, j = 0;   // j�� ret index
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
	CString conting = "������������";
	CString lConting[5] = { "��", "��", "��", "��", "��" };
	CString buf;
	CString chBuf;
	CString codeBuf;
	CString jBuf;//�߼��� ���¸� �����ϱ� ���� ���� ������ ����
	int jShape; //���ڷ� ǥ���� �߼��� ���� 

	CString result = _T("");
	CString exCode = _T("");//�νĵ� �ʼ������ڵ带 ������ ����ȭ�ڵ带 ���� ����

	CStdioFile choFile;
	CStdioFile jungFile;
	CStdioFile jongFile;

	if (!choFile.Open(_T("chosung.txt"), CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL))//  ���� ������ �б� ��� | �ٸ� ���μ��������� ����(�б�, ���⸦ ���ϰ� ��)
	{
		AfxMessageBox("�ʼ����� ���� ����");
		return;
	}
	if (!jungFile.Open(_T("jungsung.txt"), CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL))//  ���� ������ �б� ��� | �ٸ� ���μ��������� ����(�б�, ���⸦ ���ϰ� ��)
	{
		AfxMessageBox("�߼����� ���� ����");
		return;
	}
	if (!jongFile.Open(_T("jongsung.txt"), CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL))//  ���� ������ �б� ��� | �ٸ� ���μ��������� ����(�б�, ���⸦ ���ϰ� ��)
	{
		AfxMessageBox("�������� ���� ����");
		return;
	}

	//�̱����ϱ�
	if ((cho == true) && (jung == false))
	{
		if ((((initY + endY) / 2) > pmY) && (jungTmp != ""))
		{
			if ((jungTmp == "��") && (lastS == "5"))
				jung = false;
			else if (jungTmp != "?")
				jung = true;
		}
	}

	//�ʼ�
	if ((cho == false))
	{
		if (bTmp == true)
			exCode = scode.Right(scode.GetLength() - choCode.GetLength() - 1);
		while (choFile.ReadString(buf))
		{
			buf.Trim();
			AfxExtractSubString(chBuf, buf, 0, '|');
			AfxExtractSubString(codeBuf, buf, 1, '|');
			if (bTmp == true)//�̾��� �� �ִ� ������ ����
			{
				if (exCode.Find("&") == -1)
				{
					if ((endY > pmY) && (initX < pmX))//choTmp���� �Ʒ��ʿ� ȹ�� �׾�������
					{
						if (choTmp == "��"&&exCode == "7")//'��'�� '��'�� �����ϱ� ���� ���ǹ�
						{
							if (endX > (pmX + 10))//'��'���� ����
							{
								cho = true;
								bTmp = false;
								rb = 0;
								break;
							}
							else//���� ����
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


					if (choTmp == "��")//'��'�� '��'�� '��'�� �����ϱ� ���� ���ǹ�
					{

						if (endX > (pmX + 10))//�߼��� �����Ѵٰ� ����
						{

							cho = true;
							bTmp = false;
							rb = 0;
							break;
						}
						else//���̶�� ����
						{
							if (scode != codeBuf)
								choTmp = "?";
							cho = false;
							bTmp = false;
							rb = 0;
							break;

						}
					}

					else if ((initX < pmX) && (endX < (pmX*1.05)) && (initY < pmY) && (endY < (pmY*1.05)))//�ִ밪 �ȿ� ȹ�� �׸���
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

					//��->������ó��
					if (choTmp == "��" && exCode == "6")
					{
						choCode = scode;
						choTmp = "��";
						break;
					}

				}

				if (exCode.Find("&") != -1 && (((initY + endY) / 2) > pmY))//�������� Ȯ��
				{
					cho = true;
					jung = true;
					bTmp = false;
					break;
				}

				if (exCode == codeBuf && choTmp == chBuf)//�´� �ȼҸ����� Ȯ��
				{
					if (choTmp == "��")//'��'�� '��'�� ����
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
							if ((rbBTmp == "2") && (codeBTmp == exCode) && (chBTmp == "��"))
							{
								if ((pEndY + ((endY - initY)*0.2)) < endY && (ppEndY + ((endY - initY)*0.2)) < pEndY)//'��'�ΰ��
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

	//�߼�
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
					if (jungTmp == "��")
						bTmp2 = true;//�߼��� �� ��� �Ǻ��� ���
					if (bTmp2 == true && jungTmp != "��")
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

	//����
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
				if (jongTmp == "" && (jungTmp == "��" || jungTmp == "?") && (codeBuf == jongCode.Left(jongCode.GetLength())))
				{
					jungTmp = "��";
					jungCode = "7";
					jung = true;

					jongCode = codeBuf;
					jongTmp = chBuf;


					bTmp2 = false;
					break;
				}

				else if (jongCode != "5" && (((initY + endY) / 2) > (pmY + 10)))
				{
					jungTmp = "��";
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
				else if(jungTmp == "��"&&(((initY+endY)/2)+10>pmY)&&endX>pmX)
				{
				jungTmp = "��";
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
	CString ChoSungTbl = "��������������������������������������";
	CString JungSungTbl = "�������¤äĤŤƤǤȤɤʤˤ̤ͤΤϤФѤҤ�";
	CString JongSungTbl = "  ������������������������������������������������������";
	int m_UniCodeHangulBase = 0xAC00;

	int ChoSungPosition, JungSungPosition, JongSungPosition;
	int nUniCode;

	ChoSungPosition = ChoSungTbl.Find(choSung) / 2;     // �ʼ� ��ġ
	JungSungPosition = JungSungTbl.Find(jungSung) / 2;   // �߼� ��ġ
	JongSungPosition = JongSungTbl.Find(jongSung) / 2;   // ���� ��ġ


	// �ռ� ����� �� ����
	nUniCode = m_UniCodeHangulBase + (ChoSungPosition * 21 + JungSungPosition) * 28 + JongSungPosition;
	// �ڵ尪�� ���ڷ� ��ȯ
	wchar_t tmp = nUniCode;
	CString ret = tmp;
	return ret;
}

char CInputWnd::EvalDirection(int dx, int dy, char prev)
{
	float d;//����

	// y��� ������ �Է��� ���� ���⸦ ������ ū ������ ����
	if (dx == 0){
		dx = 1;
		if (dy > 0) d = 10.0;
		else d = -10.0;
	}
	else d = (float)dy / dx;


	// ������ ���� ���� ����
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

	// ��� ����Ʈ�� ����
	//for (int i = m_Points.GetCount(); i; i--)
	//{ 
	//	pPoint = (CObPoint*)m_Points.GetTail(); 
	//	delete pPoint; 

	//	m_Points.RemoveTail(); 
	//}

	//m_InputPoints.RemoveAll();

	// �Էµ� ���� �ʱ�ȭ
	//m_Input = "";
	//m_InputDetail = "";
	//m_SCode = "";
	m_pPatternEdit->SetWindowText("");//���� ���� �� ����
	//m_pSCodeEdit->SetWindowText("");//�����ڵ�
	m_pDebug->SetWindowText("");//�н��ڵ� �Ʒ��� �ִ� edit
	mX = 0;
	mY = 0;
	endY = 0;
	pEndY = 0;
	ppEndY = 0;
	m_pMaxXEdit->SetWindowText("");
	m_pMaxYEdit->SetWindowText("");
	//m_pPatternEdit1->SetWindowText("");//������â
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

	// ȭ���� ����
	//dc.SelectObject(GetStockObject(WHITE_PEN));
	//GetClientRect(rect);
	//dc.Rectangle(rect);
}
bool  CInputWnd::preventDupJung(CString sCode) {
	bool alreadyExist = false;
	CString sLine, sToken;
	CStdioFile file;

	file.Open(_T("jungsung.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);

	while (file.ReadString(sLine))  // �� �پ� �о����
	{
		//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','�� �Ľ�
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

	while (file.ReadString(sLine))  // �� �پ� �о����
	{
		//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','�� �Ľ�
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

	while (file.ReadString(sLine))  // �� �پ� �о����
	{
		//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','�� �Ľ�
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


while (file.ReadString(sLine))  // �� �پ� �о����
{

//for (int i=0;AfxExtractSubString(sToken, sLine, i, '|' );i++)    // ','�� �Ľ�
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
		AfxMessageBox("�ʼ����� ���� ����");
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
		AfxMessageBox("�������� ���� ����");
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

	if (jungsung == _T("��")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 1;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("��")) {
		jShape = 3;
		return jShape;
	}
	else if (jungsung == _T("��")) {
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
		AfxMessageBox("�߼����� ���� ����");
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

	// ��� ����Ʈ�� ����
	for (int i = m_Points.GetCount(); i; i--)
	{
		pPoint = (CObPoint*)m_Points.GetTail();
		delete pPoint;

		m_Points.RemoveTail();
	}

	m_InputPoints.RemoveAll();

	// �Էµ� ���� �ʱ�ȭ
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

	// ȭ���� ����
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

	// �Է� ����Ʈ ���
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
