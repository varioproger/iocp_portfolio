#include "User.h"
#include"CharacterPrototype.h"
User::User()
{
    m_vcharacter.emplace_back(CharacterPrototypeFactory::getInstance()->CreatePrototype(CharacterType::Warrior));
    m_vcharacter.emplace_back(CharacterPrototypeFactory::getInstance()->CreatePrototype(CharacterType::Archer));
}

User::~User()
{
}
