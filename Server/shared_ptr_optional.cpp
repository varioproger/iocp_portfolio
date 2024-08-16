#include <iostream>
#include <map>
#include <string>
#include<optional>
#include<memory>

/*
std::optional �� �� ���� �������δ� �Ϲ����� ������δ� ���۷����� ������ �� ���ٴ� ���Դϴ�. ���� �� �Ʒ��� ���� ���۷����� ���� optional ��ü�� �����ϰ� �Ѵٸ�
std::reference_wrapper �� ����ؼ� ���۷��� ó�� �����ϴ� wrapper ��ü�� �����ϸ� �˴ϴ�.
*/
class A {
public:
	A() { std::cout << "����Ʈ ����" << std::endl; }

	A(const A& a) { std::cout << "���� ����" << std::endl; }
};

int main() {
	std::optional<std::shared_ptr<A>> maybe_a = std::make_shared<A>();
}