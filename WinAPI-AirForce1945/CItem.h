#pragma once
#include "CObject.h"
class CItem : public CObject
{
public:
    CItem();
    virtual ~CItem();

public:
    void Initialize() override;

    int Update() override;

    void LateUpdate() override;

    void Render(HDC _hDC) override;

    void Release() override;

};

