#include"Warrior.h"

Warrior::Warrior()
{
	SetBasicInfo();
}
Warrior:: ~Warrior()
{

}

void Warrior::SetBasicInfo()
{
	m_basic_info.str = 20;
	m_basic_info.dex = 10;
	m_basic_info.luck = 10;
}
