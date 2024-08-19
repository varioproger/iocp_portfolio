#pragma once
#include"CharacterBase.h"

class Warrior : public CharacterBase {

public:
	Warrior();
	~Warrior();
protected:
	virtual void SetBasicInfo() override;
};