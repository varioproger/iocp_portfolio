#pragma once
#include<vector>
#include<memory>
#include"Singleton.h"
#include"CharacterFactory.h"
#include"ServerGlobalDef.h"

class Prototype : Singleton<Prototype>{
private:
    std::vector<std::unique_ptr<MethodFactory<Character>>> m_prototypes;

public:
    Prototype() {
        m_prototypes.emplace_back(std::make_unique<Warrior>());
        m_prototypes.emplace_back(std::make_unique<Archer>());
    }
    /**
     * Notice here that you just need to specify the type of the prototype you
     * want and the method will create from the object with this type.
     */
    Character&& CreatePrototype(CharacterType type) {
        return m_prototypes[(int)type]->Create();
    }
};