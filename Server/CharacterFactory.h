#pragma once
#include<memory>
#include"Factory.h"
#include"Warrior.h"
#include"Archer.h"
// 캐릭터 특수화
template <>
class MethodFactory<CharacterBase> {
public:
	MethodFactory() { }
	virtual ~MethodFactory() {  }// 소멸자를 가상 함수로 선언하지 않으면 업캐스팅일 경우 자식 클래스의 소멸자는 결코 호출되지 않는다.
public:
	virtual CharacterBase* Create() = 0;
};

class WarriorFactory : public MethodFactory<CharacterBase> {
public:
	WarriorFactory() {  }
	virtual ~WarriorFactory() {  } // 까먹을 수 있으니까 그냥 다 소멸자에는 virtual을 갖다 붙이자
public:
	virtual CharacterBase* Create() {
		return new Warrior();
	}
};

class ArcherFactory : public MethodFactory<CharacterBase> {
public:
	ArcherFactory() {}
	virtual ~ArcherFactory() {}
public:
	virtual CharacterBase* Create() {
		return new Archer();
	}
};
