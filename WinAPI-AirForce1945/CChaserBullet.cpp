#include "pch.h"
#include "CChaserBullet.h"
#include "CStageManager.h"

CChaserBullet::CChaserBullet()
    : m_pTarget(nullptr), m_pMonsterList(nullptr), m_hBrush(nullptr)
{
}

CChaserBullet::~CChaserBullet()
{
}

void CChaserBullet::Initialize()
{
    m_eObjectType = OBJECT_TYPE::PLAYER_BULLET;
    m_vPivot = { WINCX / 2.f, 600.f };
    m_vSize = { 15.f, 15.f };
    m_vDir = { 0.f, -1.f };
    m_fSpeed = 1.f;
    
    
    m_hBrush = CreateSolidBrush(RGB(255, 255, 0));
    m_pMonsterList = CStageManager::Get_Instance()->Get_MonsterList();
    SetTarget();
}

int CChaserBullet::Update()
{
    if (m_bDestroy) return OBJ_DESTROY;

    __super::UpdateRect();

    if (GetCollision()) return OBJ_NOEVENT;

    if (m_pTarget)
    {
        Vector2 vSrc(m_pTarget->GetPivot());
        Vector2 vDst = vSrc - m_vPivot;
        m_fShootDeg = acosf(vDst.x / sqrtf(vDst.GetSquared())) * 180.f / PI;
        
        if (vDst.y > 0.f) m_fShootDeg *= -1.f;
        m_vPivot += m_vDir.Rotate(m_fShootDeg) * m_fSpeed;
    }
    else
    {
        m_vPivot += m_vDir * m_fSpeed;
        //SetTarget();
    }

    return OBJ_NOEVENT;
}

void CChaserBullet::LateUpdate()
{
    if (GetCollision())
    {
        m_bDestroy = true;
    }

    __super::HandleOutOfBound(IsOutOfBound(50));
}

void CChaserBullet::Render(HDC _hDC)
{
    PAINTSTRUCT ps{};
    BeginPaint(g_hWnd, &ps);
    HGDIOBJ hPrevBrush = SelectObject(_hDC, (HPEN)m_hBrush);

    Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

    SelectObject(_hDC, (HBRUSH)hPrevBrush);
    EndPaint(g_hWnd, &ps);
}

void CChaserBullet::Release()
{
    DeleteObject((HBRUSH)m_hBrush);
}

bool CChaserBullet::OnCollision(CObject* _pColObj)
{
    __super::OnCollision(_pColObj);
    
    // 폭발과 같이 크기가 커진 후 소멸
    m_vSize = { 50.f, 50.f };

    return false;
}

void CChaserBullet::SetTarget()
{
    if (m_pTarget || m_pMonsterList == NULL ) return;

    CObject*    pClosest = nullptr;
    float       vDistance = 2000.f;
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
