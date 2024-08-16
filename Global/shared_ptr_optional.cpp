#include <iostream>
#include <map>
#include <string>
#include<optional>
#include<memory>

/*
std::optional 의 한 가지 단점으로는 일반적인 방법으로는 레퍼런스를 포함할 수 없다는 점입니다. 예를 들어서 아래와 같이 레퍼런스에 대한 optional 객체를 정의하고 한다면
std::reference_wrapper 를 사용해서 레퍼런스 처럼 동작하는 wrapper 객체를 정의하면 됩니다.
*/
class A {
public:
	A() { std::cout << "디폴트 생성" << std::endl; }

	A(const A& a) { std::cout << "복사 생성" << std::endl; }
};

int main() {
	std::optional<std::shared_ptr<A>> maybe_a = std::make_shared<A>();
}