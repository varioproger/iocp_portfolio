#pragma once

template <typename T>
class MethodFactory {
public:
	MethodFactory() { }
	MethodFactory(const MethodFactory& _rhs) { }
	virtual ~MethodFactory() {  }// 소멸자를 가상 함수로 선언하지 않으면 업캐스팅일 경우 자식 클래스의 소멸자는 결코 호출되지 않는다.
public:
	virtual T&& Create() = 0;
};
