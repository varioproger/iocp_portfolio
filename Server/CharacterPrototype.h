#pragma once
#include<vector>
#include<memory>
#include"ServerGlobalDef.h"
#include"Prototype.h"
#include"Singleton.h"
#include"Warrior.h"
#include"Archer.h"


// 캐릭터 특수화
class WarriorPrototype : public Prototype<CharacterBase> {
public:
    WarriorPrototype() {  }
    virtual ~WarriorPrototype() {  } // 까먹을 수 있으니까 그냥 다 소멸자에는 virtual을 갖다 붙이자
public:
    virtual CharacterBase* Create() {
        return new Warrior();
    }
};

class ArcherPrototype : public Prototype<CharacterBase> {
public:
    ArcherPrototype() {}
    virtual ~ArcherPrototype() {}
public:
    virtual CharacterBase* Create() {
        return new Archer();
    }
};

class CharacterPrototypeFactory : public Singleton<CharacterPrototypeFactory>{
private:
    std::vector<std::unique_ptr<Prototype<CharacterBase>>> m_prototypes;
public:
    virtual ~CharacterPrototypeFactory() {}
    void Init()
    {
        m_prototypes.emplace_back(std::make_unique<WarriorPrototype>());
        m_prototypes.emplace_back(std::make_unique<ArcherPrototype>());
    }
    /**
     * Notice here that you just need to specify the type of the prototype you
     * want and the method will create from the object with this type.
     */
    CharacterBase* CreatePrototype(CharacterType type) {
        return m_prototypes[(int)type]->Create();
    }
};

#define CharacterPrototypeFactory CharacterPrototypeFactory::getInstance()