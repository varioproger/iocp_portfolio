#pragma once
#include"ServerGlobalDef.h"
class ItemBase
{
public:
	ItemBase();
	~ItemBase();
public:
	ItemType m_type;
	unsigned int m_uuid; // ����Ű
	unsigned int m_idx; // ���̺� ��
	unsigned int m_visual_idx; // ������ ��
};