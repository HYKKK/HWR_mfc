#ifndef HANGUEL_H
#define HANGUEL_H

#include <iterator>
#include <regex>

#include <map>
#include "stdafx.h"

#define KOREAN	std::map<SCode, HanGuel> 

typedef CString HanGuel;
typedef CString SCode;

#define FILE_CHO		"chosung.txt"
#define FILE_JUNG		"jungsung.txt"
#define FILE_JONG		"jongsung.txt"

#define REGULAR_CHO		"[��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��]"
#define REGULAR_JUNG	"[��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��]"
#define REGULAR_JONG	"[��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��]"

#define QUESTION_MARK _T("?")

static CString buf;
class Korean {

protected:
	KOREAN map;
	CStdioFile file;
public:
	virtual void training(CString FILENAME) {
		CString hanguel;
		CString scode;

		if (0 == file.Open(FILENAME, CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL)) {//  ���� ������ �б� ��� | �ٸ� ���μ��������� ����(�б�, ���⸦ ���ϰ� ��)
			AfxMessageBox(FILENAME + " OPEN ERROR!");
			return;
		}

		while (file.ReadString(buf)) {
			AfxExtractSubString(hanguel, buf, 0, '|');
			AfxExtractSubString(scode, buf, 1, '|');

			this->registerHanguel(scode, hanguel, 0);
		}
	}
	//TODO duplicate ó��
	// if option == 1 db.file insert else if option = 0, just insert map
	virtual void registerHanguel(SCode scode, HanGuel hanguel, int option) {
		map.insert(KOREAN::value_type(scode, hanguel));
		//map.insert(std::make_pair(scode, hanguel));
		if (option)  {
			file.SeekToEnd();
			file.WriteString("\n" + (CString)hanguel + "|" + scode);
		}
	}
	HanGuel find(SCode scode) {
		KOREAN::iterator iter = map.find(scode);

		if (iter == map.end())
			return QUESTION_MARK;

		return iter->second;
	}
};

class Cho : public Korean {
private:

public:
	//open file and fill map
	Cho() {
		training(FILE_CHO);
	}

	//�н�. map�� �߰�. need test
	void registerHanguel(SCode scode, HanGuel hanguel) {
		if (!std::regex_match((std::string)hanguel, (std::regex) (REGULAR_CHO)) || scode == _T(""))
			//cannot register
			return;

		Korean::registerHanguel(scode, hanguel, 1);
	}
	HanGuel find(const SCode& scode){
		return Korean::find(scode);
	}

	~Cho() {

	}
};

class Jung : protected Korean {
public:
	//open file and fill map
	Jung() {
		//open file and fill map
		training(FILE_JUNG);
	}

	//�н�. map�� �߰�
	void registerHanguel(SCode scode, HanGuel hanguel){
		Korean::registerHanguel(scode, hanguel, 1);
	}
	HanGuel find(const SCode& scode) {
		return Korean::find(scode);
	}

	~Jung() {
	}
};

class Jong : protected Korean {
public:
	//open file and fill map
	Jong() {
		training(FILE_JONG);
	}

	//�н�. map�� �߰�
	void registerHanguel(SCode scode, HanGuel hanguel){
		Korean::registerHanguel(scode, hanguel, 1);
	}
	HanGuel find(const SCode& scode) {
		return Korean::find(scode);
	}

	~Jong() {

	}
};

#endif