#pragma once
#include"Singleton.h"

template <typename T>
class Prototype {
public:
    Prototype() { }
    virtual ~Prototype() {  }// �Ҹ��ڸ� ���� �Լ��� �������� ������ ��ĳ������ ��� �ڽ� Ŭ������ �Ҹ��ڴ� ���� ȣ����� �ʴ´�.
public:
    virtual T* Create() = 0;
};
