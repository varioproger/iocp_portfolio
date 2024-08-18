#pragma once
#include<memory>
#include"Factory.h"
#include"Warrior.h"
#include"Archer.h"
// ĳ���� Ư��ȭ
template <>
class MethodFactory<CharacterBase> {
public:
	MethodFactory() { }
	virtual ~MethodFactory() {  }// �Ҹ��ڸ� ���� �Լ��� �������� ������ ��ĳ������ ��� �ڽ� Ŭ������ �Ҹ��ڴ� ���� ȣ����� �ʴ´�.
public:
	virtual CharacterBase* Create() = 0;
};

class WarriorFactory : public MethodFactory<CharacterBase> {
public:
	WarriorFactory() {  }
	virtual ~WarriorFactory() {  } // ����� �� �����ϱ� �׳� �� �Ҹ��ڿ��� virtual�� ���� ������
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
