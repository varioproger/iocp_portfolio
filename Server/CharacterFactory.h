#pragma once
#include<memory>
#include"Factory.h"
#include"Character.h"

// ĳ���� Ư��ȭ
template <>
class MethodFactory<Character> {
public:
	MethodFactory() { }
	MethodFactory(const MethodFactory& _rhs) { }
	virtual ~MethodFactory() {  }// �Ҹ��ڸ� ���� �Լ��� �������� ������ ��ĳ������ ��� �ڽ� Ŭ������ �Ҹ��ڴ� ���� ȣ����� �ʴ´�.
public:
	virtual Character&& Create() = 0;
};

class Warrior : public MethodFactory<Character> {
public:
	Warrior() {  }
	Warrior(const Warrior& _rhs) {  }
	virtual ~Warrior() {  } // ����� �� �����ϱ� �׳� �� �Ҹ��ڿ��� virtual�� ���� ������
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
