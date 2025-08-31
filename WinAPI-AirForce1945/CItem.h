#pragma once
#include "CObject.h"
class CItem : public CObject
{
public:
    CItem();
    virtual ~CItem() override;

public:
    void        Initialize()                    override;
    int         Update()                        override;
    void        LateUpdate()                    override;
    bool        OnCollision(CObject* _pColObj)  override;
    void        Render(HDC _hDC)                override;
    void        Release()                       override;

private:
};

