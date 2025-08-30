#pragma once
#include "CItem.h"
class CLifeItem :  public CItem
{
public:
    CLifeItem();
    ~CLifeItem() override;

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC _hDC) override;
    void Release() override;

public:
    void Apply_Effect(CObject* pObj) override;
};

