#pragma once
#include<vector>
#include<memory>
#include"Singleton.h"
#include"CharacterFactory.h"
#include"ServerGlobalDef.h"

class CharacterPrototype : public Singleton<CharacterPrototype>{
private:
    std::vector<std::unique_ptr<MethodFactory<CharacterBase>>> m_prototypes;
public:
    virtual ~CharacterPrototype() {}
    void Init()
    {
        m_prototypes.emplace_back(std::make_unique<WarriorFactory>());
        m_prototypes.emplace_back(std::make_unique<ArcherFactory>());
    }
    /**
     * Notice here that you just need to specify the type of the prototype you
     * want and the method will create from the object with this type.
     */
    CharacterBase* CreatePrototype(CharacterType type) {
        return m_prototypes[(int)type]->Create();
    }
};