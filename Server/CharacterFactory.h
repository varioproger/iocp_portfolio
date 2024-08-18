#pragma once
#include<memory>
#include"Factory.h"
#include"Character.h"

// 캐릭터 특수화
template <>
class MethodFactory<Character> {
public:
	MethodFactory() { }
	MethodFactory(const MethodFactory& _rhs) { }
	virtual ~MethodFactory() {  }// 소멸자를 가상 함수로 선언하지 않으면 업캐스팅일 경우 자식 클래스의 소멸자는 결코 호출되지 않는다.
public:
	virtual Character&& Create() = 0;
};

class Warrior : public MethodFactory<Character> {
public:
	Warrior() {  }
	Warrior(const Warrior& _rhs) {  }
	virtual ~Warrior() {  } // 까먹을 수 있으니까 그냥 다 소멸자에는 virtual을 갖다 붙이자
public:
	virtual Character&& Create() {
		return std::move(Character());
	}
};

class Archer : public MethodFactory<Character> {
public:
	Archer() {}
	Archer(const Archer& _rhs) {}
	virtual ~Archer() {}

public:
	virtual Character&& Create() {
		return std::move(Character());
	}
};
