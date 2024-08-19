#include"Archer.h"

Archer::Archer()
{
	SetBasicInfo();
}
Archer::~Archer()
{

}
void Archer::SetBasicInfo()
{
	m_basic_info.str = 10;
	m_basic_info.dex = 20;
	m_basic_info.luck = 10;
}
