#include<iostream>
#include<vector>
#include<memory>

class SingletonBase
{
private:
	// ���� ������
	SingletonBase(SingletonBase&) = delete;
	SingletonBase(const SingletonBase&) = delete;
	// ���� ���۷�����
	SingletonBase& operator=(SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&&) = delete;

	// �̵� ������
	SingletonBase(SingletonBase&&) = delete;
	SingletonBase(const SingletonBase&&) = delete;

protected:
	SingletonBase() = default; // Default ������ ��� (�ʿ�� �����ڸ� ���ϴµ��� �����ؼ� ����ص� ��)
};

template<typename T>
class Singleton : public SingletonBase
{
private:
	static T* m_selfInstance;

public:
	static T* getInstance()
	{
		if (!m_selfInstance)
		{
			m_selfInstance = new T();
		}

		return (m_selfInstance);
	}

	static void	releaseInstance()
	{
		if (m_selfInstance != 0)
		{
			delete m_selfInstance;
			m_selfInstance = 0;
		}
	}
};

template < class T > 
T* Singleton< T >::m_selfInstance = 0;

class A : public Singleton<A> {
public:
	void init()
	{
		std::cout << "NONONO" << std::endl;
	}

};
int main()
{
	A::getInstance()->init();
	return 0;
}