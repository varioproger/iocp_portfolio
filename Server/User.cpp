#include "User.h"
#include"CharacterPrototype.h"
User::User()
{
    m_vcharacter.emplace_back(CharacterPrototypeFactory->CreatePrototype(CharacterType::Warrior));
    m_vcharacter.emplace_back(CharacterPrototypeFactory->CreatePrototype(CharacterType::Archer));
}

User::~User()
{
}

SRWLock& User::GetLock()
{
    return m_lock;
}
