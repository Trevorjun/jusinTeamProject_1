#include "pch.h"
#include "CChaserBullet.h"
#include "CStageManager.h"

CChaserBullet::CChaserBullet()
    : m_pTarget(nullptr), m_pMonsterList(nullptr), m_hPen(nullptr)
{
}

CChaserBullet::~CChaserBullet()
{
}

void CChaserBullet::Initialize()
{
    m_vPivot = { WINCX / 2.f, 600.f };
    m_vSize = { 15.f, 15.f };
    m_vDir = { 0.f, -1.f };
    m_fSpeed = 1.f;
    

    m_hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 0));
    m_pMonsterList = CStageManager::Get_Instance()->GetMonsterList();
    SetTarget();
}

int CChaserBullet::Update()
{
    if (m_bDestroy) return OBJ_DESTROY;

    __super::UpdateRect();

    if (m_pTarget)
    {
        Vector2 vSrc(m_pTarget->GetPivot());
        Vector2 vDst = vSrc - m_vPivot;
        float fDeg = acosf(vDst.x / sqrtf(vDst.GetSquared())) * 180.f / PI;
        
        if (vDst.y < 0.f) fDeg *= -1.f;
        m_vPivot += m_vDir.Rotate(fDeg) * m_fSpeed;
    }
    else
    {
        m_vPivot += m_vDir * m_fSpeed;

        //SetTarget();
    }

    return OBJ_NOEVENT;
}

void CChaserBullet::Render(HDC _hDC)
{
    BeginPaint(g_hWnd, 0);
    HGDIOBJ hPrevPen = SelectObject(_hDC, (HPEN)m_hPen);

    Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    SelectObject(_hDC, (HPEN)hPrevPen);
    EndPaint(g_hWnd, 0);
}

bool CChaserBullet::OnCollision(CObject* _pColObj)
{
    
    

    return false;
}

void CChaserBullet::SetTarget()
{
    if (m_pTarget || m_pMonsterList->size() == 0 ) return;

    CObject*    pClosest = nullptr;
    float       vDistance = WINCX;
    for (auto& pObj : *m_pMonsterList)
    {
        if (pClosest == nullptr)
        {
            pClosest = pObj;
            vDistance = GetHypotenuse(m_vPivot, pObj->GetPivot());
            continue;
        }

        if (GetHypotenuse(m_vPivot, pObj->GetPivot()) < vDistance)
            pClosest = pObj;
    }

    if (pClosest) m_pTarget = pClosest;
}

float CChaserBullet::GetHypotenuse(Vector2 _vForm, Vector2 _vTo)
{
    Vector2 vDst = _vTo - _vForm;
    return sqrtf(vDst.GetSquared());
}
