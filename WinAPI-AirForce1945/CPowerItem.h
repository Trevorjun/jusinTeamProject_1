#pragma once

#include "CItem.h"

class CPowerItem : public CItem
{
public:
    CPowerItem();
    ~CPowerItem() override;

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC _hDC) override;
    void Release() override;

public:
    void Apply_Effect(CObject* pObj) override;
};

