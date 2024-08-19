#pragma once

class SingletonBase
{
private:
	// 복사 생성자
	SingletonBase(SingletonBase&) = delete;
	SingletonBase(const SingletonBase&) = delete;
	// 복사 오퍼레이터
	SingletonBase& operator=(SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&) = delete;
	SingletonBase& operator=(const SingletonBase&&) = delete;

	// 이동 생성자
	SingletonBase(SingletonBase&&) = delete;
	SingletonBase(const SingletonBase&&) = delete;

protected:
	SingletonBase() = default; // Default 생성자 사용 (필요시 생성자를 원하는데로 수정해서 사용해도 됨) 
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
T* Singleton<T>::m_selfInstance = 0;

