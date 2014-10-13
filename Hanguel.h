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

#define REGULAR_CHO		"[��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��]"
#define REGULAR_JUNG	"[��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��]"
#define REGULAR_JONG	"[��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��|��]"

#define QUESTION_MARK _T("?")

class Korean {

protected :
	KOREAN map;

public : 
	//TODO duplicate ó��
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

	//�н�. map�� �߰�. need test
	void registerHanguel(SCode scode, HanGuel hanguel) {
		if (!std::regex_match((std::string)hanguel, (std::regex) (REGULAR_CHO)))
			//cannot register
			return ;

		this->registerHanguel(scode, hanguel);
	}
	HanGuel find(const SCode& scode);

	//map�� �ִ°� file�� ����
	~Cho() {
		
	}
};

class Jung : protected Korean {
public:
	//open file and fill map
	Jung() {
		//open file and fill map
	}

	//�н�. map�� �߰�
	void registerHanguel(SCode scode, HanGuel hanguel);
	HanGuel find(const SCode& scode);

	//map�� �ִ°� file�� ����
	~Jung() {

	}
};

class Jong : protected Korean {
public:
	//open file and fill map
	Jong() {

	}

	//�н�. map�� �߰�
	void registerHanguel(SCode scode, HanGuel hanguel);
	HanGuel find(const SCode& scode);

	//map�� �ִ°� file�� ����
	~Jong() {

	}
};

#endif