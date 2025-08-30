#pragma once
#include "Define.h"

class CObject;
class CMainGame
{
public:
	CMainGame();
	virtual ~CMainGame();
public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();
private:
	HDC				m_hDC;
	list<CObject*>	m_ObjectList[OBJ_END];
};

