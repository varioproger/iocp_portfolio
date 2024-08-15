#include "ConnMap.h"

std::shared_ptr<Conn> ConnMap::Create(SOCKET sock)
{
	return std::shared_ptr<Conn>();
}

void ConnMap::Insert(SOCKET sock)
{

}

void ConnMap::Delete(SOCKET sock)
{
}

std::shared_ptr<Conn> ConnMap::Select()
{
	return std::shared_ptr<Conn>();
}
