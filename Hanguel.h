#ifndef HANGUEL_H
#define HANGUEL_H

#include <iterator>
#include <map>
#include <regex>

#include "stdafx.h"

#define KOREAN std::map<SCode, HanGuel> 

typedef CString HanGuel;
typedef CString SCode;

#define FILE_CHO		"chosung.txt"
#define FILE_JUNG		"jungsung.txt"
#define FILE_JONG		"jongsung.txt"

#define REGULAR_CHO		"[ㄱ|ㄲ|ㄴ|ㄷ|ㄸ|ㄹ|ㅁ|ㅂ|ㅃ|ㅅ|ㅆ|ㅇ|ㅈ|ㅉ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ]"
#define REGULAR_JUNG	"[ㅏ|ㅐ|ㅑ|ㅒ|ㅓ|ㅔ|ㅕ|ㅖ|ㅗ|ㅘ|ㅙ|ㅚ|ㅛ|ㅜ|ㅝ|ㅞ|ㅟ|ㅠ|ㅡ|ㅣ|ㅢ]"
#define REGULAR_JONG	"[ㄱ|ㄲ|ㄳ|ㄴ|ㄵ|ㄶ|ㄷ|ㄹ|ㄺ|ㄻ|ㄼ|ㄽ|ㄾ|ㄿ|ㅀ|ㅁ|ㅂ|ㅄ|ㅅ|ㅆ|ㅇ|ㅈ|ㅊ|ㅋ|ㅌ|ㅍ|ㅎ]"

#define QUESTION_MARK _T("?")

class Korean {

protected :
	KOREAN map;

public : 
	//TODO duplicate 처리
	virtual void registerHanguel(SCode scode, HanGuel hanguel) {
		map.insert(scode, hanguel);
	}
	virtual HanGuel find(SCode scode) {
		KOREAN::iterator iter = map.find(scode);

		if (iter != map.end())
			iter->second = QUESTION_MARK;

		return iter->second;
	}
};

class Cho : protected Korean {
private : 
	
public :
	//open file and fill map
	Cho() {
		
	}

	//학습. map에 추가. need test
	void registerHanguel(SCode scode, HanGuel hanguel) {
		if (!std::regex_match((std::string)hanguel, (std::regex) (REGULAR_CHO)))
			//cannot register
			return ;

		this->registerHanguel(scode, hanguel);
	}
	HanGuel find(const SCode& scode);

	//map에 있는거 file에 저장
	~Cho() {
		
	}
};

class Jung : protected Korean {
public:
	//open file and fill map
	Jung() {
		//open file and fill map
	}

	//학습. map에 추가
	void registerHanguel(SCode scode, HanGuel hanguel);
	HanGuel find(const SCode& scode);

	//map에 있는거 file에 저장
	~Jung() {

	}
};

class Jong : protected Korean {
public:
	//open file and fill map
	Jong() {

	}

	//학습. map에 추가
	void registerHanguel(SCode scode, HanGuel hanguel);
	HanGuel find(const SCode& scode);

	//map에 있는거 file에 저장
	~Jong() {

	}
};

#endif