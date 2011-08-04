//////////////////////////////////////////////////////////////////////////
//	File:		Line.h
//	Purpose:	Line class, can be used for D3DX functions.
//////////////////////////////////////////////////////////////////////////
#ifndef _LINE_H_
#define _LINE_H_

class CLine
{
private:
	D3DXVECTOR2* m_vStart;
	D3DXVECTOR2* m_vEnd;
	D3DCOLOR	m_cColor;

public:

	CLine() { 
				m_vStart= NULL;
				m_vEnd= NULL;
				m_cColor= D3DCOLOR_ARGB(255, 255, 255, 255);
			}

	~CLine(){
				if (m_vStart)
				{
					delete m_vStart;
					m_vStart= NULL;
				}

				if (m_vEnd)
				{
					delete m_vEnd;
					m_vEnd= NULL;
				}
			}

	//Accessors
	inline D3DXVECTOR2* StartPoint() { return m_vStart; }
	inline D3DXVECTOR2* EndPoint() { return m_vEnd; }
	inline D3DCOLOR	LineColor() { return m_cColor; }

	//Mutators
	inline void StartPoint(D3DXVECTOR2* vPoint) { m_vStart= vPoint; }
	inline void EndPoint(D3DXVECTOR2* vPoint) { m_vEnd= vPoint; }
	inline void LineColor(D3DCOLOR cColor) { m_cColor= cColor; }

};

#endif