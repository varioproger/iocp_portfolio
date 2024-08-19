#pragma once
#include<vector>
#include<memory>
#include"ServerGlobalDef.h"
#include"Prototype.h"
#include"Singleton.h"
#include"Potion.h"
#include"Equip.h"


// ������ Ư��ȭ
class PotionPrototype : public Prototype<ItemBase> {
public:
    PotionPrototype() {  }
    virtual ~PotionPrototype() {  } // ����� �� �����ϱ� �׳� �� �Ҹ��ڿ��� virtual�� ���� ������
public:
    virtual ItemBase* Create() {
        return new Potion();
    }
};

class EquipPrototype : public Prototype<ItemBase> {
public:
    EquipPrototype() {}
    virtual ~EquipPrototype() {}
public:
    virtual ItemBase* Create() {
        return new Equip();
    }
};

class ItemPrototypeFactory : public Singleton<ItemPrototypeFactory> {
private:
    std::vector<std::unique_ptr<Prototype<ItemBase>>> m_prototypes;
public:
    virtual ~ItemPrototypeFactory() {}
    void Init()
    {
        m_prototypes.emplace_back(std::make_unique<PotionPrototype>());
        m_prototypes.emplace_back(std::make_unique<EquipPrototype>());
    }
    /**
     * Notice here that you just need to specify the type of the prototype you
     * want and the method will create from the object with this type.
     */
    ItemBase* CreatePrototype(ItemType type) {
        return m_prototypes[(int)type]->Create();
    }
};