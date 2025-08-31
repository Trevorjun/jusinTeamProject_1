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
    bool OnCollision(CObject* _pObjCol) override;
    void Render(HDC _hDC) override;
    void Release() override;

public:
    virtual void Move();
    virtual bool Check_InBound();
    virtual void Apply_Effect(CObject* pObj) PURE;
};

