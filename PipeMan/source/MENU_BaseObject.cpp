#include "MENU_BaseObject.h"
#include "RenderManager.h"

MENU_BaseObject::MENU_BaseObject( void )
{
	m_rBoundingBox= NULL;
	m_pCurrentMovementPoint= NULL;
	m_pImage= NULL;
	m_rImageDrawRect= NULL;
	m_pScale= NULL;
	m_pCenter= NULL;
	m_pParent= NULL;
	m_fMovementSpeed= 10.0f;
	m_bUpdate= true;
	m_bRender= true;
	m_bScaling= true;
	m_bAnimate= false;
	m_bAnimationComplete= false;
	m_bEnabled= true;
}

MENU_BaseObject::~MENU_BaseObject( void )
{
	if (m_rBoundingBox)
		delete m_rBoundingBox;

	if (m_rImageDrawRect)
		delete m_rImageDrawRect;

	if (m_pScale)
		delete m_pScale;

	if ( m_vMovementPoints )
	{
		while( m_vMovementPoints->size() )
		{
			delete (*m_vMovementPoints)[0];
			m_vMovementPoints->erase(m_vMovementPoints->begin());
		}
		delete m_vMovementPoints;
	}

	m_pScale= NULL;
	m_rBoundingBox= NULL;
	m_rImageDrawRect= NULL;
	m_vMovementPoints= NULL;
	m_pCurrentMovementPoint= NULL;
}

void MENU_BaseObject::Init( void )
{
	m_rBoundingBox= new CRectangleF(0.0f, 0.0f, 128.0f, 64.0f);
	m_rImageDrawRect= new CRectangleF(0.0f, 0.0f, 128.0f, 64.0f);
	m_vMovementPoints= new vector<D3DXVECTOR2*>();
	m_pScale= new D3DXVECTOR2(1.0f, 1.0f);
	m_pCenter= new D3DXVECTOR2(0.0f, 0.0f);
}

void MENU_BaseObject::Update( float fTime )
{
	if (!m_bUpdate)
		return;

	if (m_bAnimate && m_vMovementPoints && m_pCurrentMovementPoint )
		HeadTowards(m_pCurrentMovementPoint, fTime);

}

void MENU_BaseObject::Render( void )
{
	if (!m_bRender)
		return;

	if ( m_pImage )
	CRenderManager::GetInstance()->Render(m_pImage, 
											new CRect(long(m_rImageDrawRect->m_fX), long(m_rImageDrawRect->m_fY), long(m_rImageDrawRect->m_fWidth), long(m_rImageDrawRect->m_fHeight)), 
											m_pParent ? D3DXVECTOR2(this->m_rBoundingBox->m_fX + m_pParent->XPosition(), this->m_rBoundingBox->m_fY + m_pParent->YPosition()) : D3DXVECTOR2(this->m_rBoundingBox->m_fX, this->m_rBoundingBox->m_fY),
											m_bScaling ? D3DXVECTOR2(m_pImage->GetWidth()/m_rBoundingBox->m_fWidth, m_pImage->GetHeight()/m_rBoundingBox->m_fHeight) : *m_pScale,
											m_d3dColor);
}

void MENU_BaseObject::AddMovementPoint( D3DXVECTOR2* pNewPoint )
{
	if (!pNewPoint)
		return;

	m_vMovementPoints->push_back(pNewPoint);
	m_pCurrentMovementPoint= (*m_vMovementPoints)[0];
}

void MENU_BaseObject::HeadTowards( D3DXVECTOR2* pDestination , float fTime)
{
	D3DXVECTOR2 vDirection = *pDestination - D3DXVECTOR2(m_rBoundingBox->m_fX, m_rBoundingBox->m_fY);
	float fDistance= D3DXVec2Length(&vDirection);

	// has it reached the destination
	if ( fDistance <= 1.0f)
	{
		m_rBoundingBox->m_fX= m_pCurrentMovementPoint->x;
		m_rBoundingBox->m_fY= m_pCurrentMovementPoint->y;
		
		NextPoint();
		return;
	}

	D3DXVECTOR2 vNormDirection;
	D3DXVec2Normalize(&vNormDirection, &vDirection);

	m_rBoundingBox->m_fX+= fTime * (m_fMovementSpeed * vNormDirection.x);
	m_rBoundingBox->m_fY+= fTime * (m_fMovementSpeed * vNormDirection.y);
}

bool MENU_BaseObject::HeadTowardVector( D3DXVECTOR2* pObjectToMove, D3DXVECTOR2* pDestination, float fTime, float fSpeed )
{
	D3DXVECTOR2 vDirection = *pDestination - *pObjectToMove;
	float fDistance= D3DXVec2Length(&vDirection);

	// has it reached the destination
	if ( fDistance <= 1.0f)
		return true;

	D3DXVECTOR2 vNormDirection;
	D3DXVec2Normalize(&vNormDirection, &vDirection);

	pObjectToMove->x+= fTime * (fSpeed * vNormDirection.x);
	pObjectToMove->y+= fTime * (fSpeed * vNormDirection.y);

	return false;
}

bool MENU_BaseObject::HeadToward( float &pObjectToMove, float pDestination, float fTime, float fSpeed )
{
	if ( pObjectToMove < pDestination )
		pObjectToMove+= fSpeed*fTime;

	if ( pObjectToMove > pDestination)
		pObjectToMove-= fSpeed*fTime;

	if ( pObjectToMove <= pDestination + 0.9f &&
		 pObjectToMove >= pDestination - 0.1f )
		pObjectToMove= pDestination;

	// has it reached the destination
	if ( pObjectToMove == pDestination )
		 return true;
	else
		return false;

}

void MENU_BaseObject::NextPoint( void )
{
	if (m_vMovementPoints->size() >= 1)
	{
		delete (*m_vMovementPoints)[0];
		m_vMovementPoints->erase(m_vMovementPoints->begin());

		if ( m_vMovementPoints->size() != 0)
			m_pCurrentMovementPoint= (*m_vMovementPoints)[0];
	}

	if ( m_vMovementPoints->size() == 0)
	{
		m_pCurrentMovementPoint= NULL;
		m_bAnimate= false;
		m_bAnimationComplete= true;
	}
}

void MENU_BaseObject::Resize( void )
{
	if (!m_pImage)
		return;

	m_rBoundingBox->m_fWidth= float(m_pImage->GetWidth());
	m_rBoundingBox->m_fHeight= float(m_pImage->GetHeight());
	m_rImageDrawRect->m_fWidth= m_rBoundingBox->m_fWidth;
	m_rImageDrawRect->m_fHeight= m_rBoundingBox->m_fHeight;
}
