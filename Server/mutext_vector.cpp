#include<iostream>
#include<vector>
#include<mutex>
#include<Windows.h>

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

class Base {
public:
	Base()
	{

	}
	~Base()
	{

	}
	virtual BOOL ProcessPacket() = 0;
private:
	virtual BOOL ProcessSignal() = 0;
};

class PacketProcessTest : Base
{
public:
	PacketProcessTest()
	{

	}
	~PacketProcessTest()
	{

	}
	virtual BOOL ProcessPacket() override
	{
		m_packet_lock_test.lock();
		ProcessSignal();
		return FALSE;
	}
private:
	virtual BOOL ProcessSignal()	override
	{
		std::lock_guard<std::mutex>lock(m_signal_lock);
		m_packet_lock_test.unlock();
		std::cout << "Mutext Clear" << std::endl;
		return FALSE;
	}
private:
	std::mutex m_packet_lock_test;
	std::mutex m_signal_lock;
};

class PacketProcessTest2 : Base
{
public:
	PacketProcessTest2()
	{

	}
	~PacketProcessTest2()
	{

	}
	virtual BOOL ProcessPacket() override
	{
		m_packet_lock_test.lock();
		ProcessSignal();
		return FALSE;
	}
private:
	virtual BOOL ProcessSignal()	override
	{
		std::lock_guard<std::mutex>lock(m_signal_lock);
		m_packet_lock_test.unlock();
		std::cout << "PacketProcessTest2 Mutext Clear" << std::endl;
		return FALSE;
	}
private:
	std::mutex m_packet_lock_test;
	std::mutex m_signal_lock;
};
void WorkerThread(LPVOID arg)
{
	Base* ptr = (Base*)arg;
	while (true)
	{
		ptr->ProcessPacket();
	}
	return;
}

int main()
{
	std::vector<Base*> m_pvec;
	m_pvec.clear();
	m_pvec.push_back((Base*)new PacketProcessTest());
	m_pvec.push_back((Base*)new PacketProcessTest2());

	std::vector<std::thread> v_thread;
	v_thread.emplace_back(std::thread(WorkerThread, m_pvec[0]));
	v_thread.emplace_back(std::thread(WorkerThread, m_pvec[1]));
	//for (int i = 0; i < 10; i++)
	//{
	//	v_thread.emplace_back(std::thread(WorkerThread, m_pvec[0]));
	//}

	while (1)
	{

	}
	for (int i = 0; i < v_thread.size(); i++)
	{
		v_thread[i].join();
	}

	return 0;
}