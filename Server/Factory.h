#pragma once

template <typename T>
class MethodFactory {
public:
	MethodFactory() { }
	MethodFactory(const MethodFactory& _rhs) { }
	virtual ~MethodFactory() {  }// �Ҹ��ڸ� ���� �Լ��� �������� ������ ��ĳ������ ��� �ڽ� Ŭ������ �Ҹ��ڴ� ���� ȣ����� �ʴ´�.
public:
	virtual T&& Create() = 0;
};
