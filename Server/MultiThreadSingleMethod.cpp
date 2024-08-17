#include<iostream>
#include<Windows.h>
#include<thread>
#include<mutex>
#include<vector>
#include<random>
#include<atomic>
// 시드값을 얻기 위한 random_device 생성.
std::random_device rd;

// random_device 를 통해 난수 생성 엔진을 초기화 한다.
std::mt19937 gen(rd());

// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
std::uniform_int_distribution<int> dis(0, 9);

int one;
int two;

class TestConn {
public:
	TestConn(int num) : m_num(num)
	{
		m_type = 1;
	}
	~TestConn()
	{

	}
	int m_num;
	int m_type;
};
TestConn* before;
TestConn* after;

std::vector<TestConn> v_conn;
constexpr int MaxConn = 10;
class PacketProcessTest
{
public:
	PacketProcessTest()
	{

	}
	~PacketProcessTest()
	{

	}
	BOOL ProcessPacket(TestConn* ptr)
	{
		m_packet_lock_test.lock();
		before = ptr;
		one = ptr->m_num;
		if (ptr->m_type == 1)
		{
			ProcessSignal(nullptr, ptr);
		}
		return FALSE;
	}
private:
	BOOL ProcessSignal(char* packet, TestConn* ptr)
	{
		std::lock_guard<std::mutex>lock(m_signal_lock);
		two = ptr->m_num;
		m_packet_lock_test.unlock();
		if (one != two)
		{
			std::cout << "Wrong "<< two << "  "<< ptr->m_num << std::endl;
			Sleep(1000);
		}
		else
		{
			std::cout << two << "  " << ptr->m_num << std::endl;
		}
		return FALSE;
	}
private:
	std::mutex m_packet_lock_test;
	std::mutex m_signal_lock;
};

void WorkerThread(LPVOID arg)
{
	PacketProcessTest* ptr = (PacketProcessTest*)arg;
	while (true)
	{
		ptr->ProcessPacket(&v_conn[dis(gen)]);
	}
	return ;
}
int main()
{

	v_conn.clear();
	for (int i = 0; i < MaxConn; i++)
	{
		v_conn.emplace_back(i + 1);
	}

	std::vector<std::thread> v_thread;
	PacketProcessTest* pprocess = new PacketProcessTest();
	for (int i = 0; i < 10; i++)
	{
		v_thread.emplace_back(std::thread(WorkerThread, pprocess));
	}

	while (1)
	{

	}
	for (int i = 0; i < v_thread.size(); i++)
	{
		v_thread[i].join();
	}
	return 0;

}