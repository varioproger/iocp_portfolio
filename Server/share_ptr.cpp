#include<iostream>
#include<memory>
#include<map>
#include<Windows.h>

struct PTR {
	LPVOID ptr;
};


class A {
public:
	A()
	{
		ptr.ptr = this;
	}
	~A()
	{

	}
	PTR ptr;
};


int main()
{
	std::map<int, std::shared_ptr<A>> m_elem;
	m_elem.insert(std::make_pair(1, std::make_shared<A>()));
	
	auto elem = m_elem.find(1);

	std::cout << elem->second.use_count() << std::endl;

	auto test = elem->second->ptr;

	std::cout << elem->second.use_count() << std::endl;

	getchar();
	return 1;
}