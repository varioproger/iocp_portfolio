#include<iostream>
#include<memory>
#include<map>
#include<Windows.h>


class A {
public:
	int num;
	A()
	{
		num = 0;
	}
	~A()
	{

	}
};


int main()
{
	std::shared_ptr<A> elem = std::make_shared<A>();

	elem->num = 1;
	std::cout <<"num "<< elem->num<< "  "<< elem.use_count() << std::endl;

	ULONG_PTR test = reinterpret_cast<ULONG_PTR>(elem.get());
	((A*)test)->num = 2;
	std::cout << "num " << elem->num << elem.use_count() << std::endl;

	std::shared_ptr<A> test2 = elem;
	test2->num = 3;
	std::cout << "num " << test2->num << "  " << elem.use_count() << std::endl;

	getchar();
	return 1;
}