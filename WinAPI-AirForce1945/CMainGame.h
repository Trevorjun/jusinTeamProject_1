#pragma once
#include "Define.h"

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
	HDC			m_hDC;

};

