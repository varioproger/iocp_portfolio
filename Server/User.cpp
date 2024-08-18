#include "User.h"
#include"CharacterPrototype.h"
User::User()
{
    m_vcharacter.emplace_back(CharacterPrototype::getInstance()->CreatePrototype(CharacterType::WARRIOR));
    m_vcharacter.emplace_back(CharacterPrototype::getInstance()->CreatePrototype(CharacterType::ARCHER));
}

User::~User()
{
}
