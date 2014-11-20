#ifndef HANGUEL_H
#define HANGUEL_H

#include <iterator>
#include <regex>

#include <unordered_map>
#include "stdafx.h"

#define KOREAN	std::unordered_map<SCode, HanGuel> 
#define HANGUEL std::pair<SCode, HanGuel>

typedef LPCTSTR HanGuel;
typedef LPCTSTR SCode;

#define FILE_CHO		"chosung.txt"
#define FILE_JUNG		"jungsung.txt"
#define FILE_JONG		"jongsung.txt"

#define REGULAR_CHO		"[ㄱ|ㄲ|ㄴ|ㄷ|ㄸ|ㄹ|ㅁ|ㅂ|ㅃ|ㅅ|ㅆ|ㅇ|ㅈ|ㅉ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ]"
#define REGULAR_JUNG	"[ㅏ|ㅐ|ㅑ|ㅒ|ㅓ|ㅔ|ㅕ|ㅖ|ㅗ|ㅘ|ㅙ|ㅚ|ㅛ|ㅜ|ㅝ|ㅞ|ㅟ|ㅠ|ㅡ|ㅣ|ㅢ]"
#define REGULAR_JONG	"[ㄱ|ㄲ|ㄳ|ㄴ|ㄵ|ㄶ|ㄷ|ㄹ|ㄺ|ㄻ|ㄼ|ㄽ|ㄾ|ㄿ|ㅀ|ㅁ|ㅂ|ㅄ|ㅅ|ㅆ|ㅇ|ㅈ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ]"

#define QUESTION_MARK _T("?")

static CString buf;
class Korean {

protected :
	KOREAN map;
	CStdioFile file;
public : 
	virtual void training(CString FILENAME) {
		CString hanguel;
		CString scode;

		if (!file.Open(FILENAME, CFile::modeRead | CFile::shareDenyRead | CFile::shareDenyWrite, NULL)) {//  기존 파일을 읽기 모드 | 다른 프로세스에서의 접근(읽기, 쓰기를 못하게 함)
			AfxMessageBox(FILENAME + " OPEN ERROR!");
			return;
		}
	
		while (file.ReadString(buf)) {
			AfxExtractSubString(hanguel, buf, 0, '|');
			AfxExtractSubString(scode, buf, 1, '|');

			this->registerHanguel(scode, hanguel, 0);
		}
	}
	//TODO duplicate 처리
	// if option == 1 db.file insert else if option = 0, just insert map
	virtual void registerHanguel(SCode scode, HanGuel hanguel, int option) {
		map.insert( KOREAN::value_type(scode, hanguel));
		if (option)  {
			file.SeekToEnd();
			file.WriteString("\n" + (CString)hanguel + "|" + scode);
		}
	}
	virtual HanGuel find(SCode scode) {
		KOREAN::iterator iter = map.find(scode);

		if (iter == map.end())
			iter->second = QUESTION_MARK;

		return iter->second;
	}
};

class Cho : protected Korean {
private : 
	
public :
	//open file and fill map
	Cho() {	
		training(FILE_CHO);
	}

	//학습. map에 추가. need test
	void registerHanguel(SCode scode, HanGuel hanguel) {
		if (!std::regex_match((std::string)hanguel, (std::regex) (REGULAR_CHO)))
			//cannot register
			return ;

		this->registerHanguel(scode, hanguel);
	}
	HanGuel find(const SCode& scode);

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

	//학습. map에 추가
	void registerHanguel(SCode scode, HanGuel hanguel);
	HanGuel find(const SCode& scode);

	~Jung() {
	}
};

class Jong : protected Korean {
public:
	//open file and fill map
	Jong() {
		training(FILE_JUNG);
	}

	//학습. map에 추가
	void registerHanguel(SCode scode, HanGuel hanguel);
	HanGuel find(const SCode& scode);

	~Jong() {

	}
};

#endif