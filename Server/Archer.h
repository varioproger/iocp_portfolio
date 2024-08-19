#pragma once
#include"CharacterBase.h"

class Archer : public CharacterBase {
public:
	Archer();
	~Archer();
protected:
	virtual void SetBasicInfo() override;
};