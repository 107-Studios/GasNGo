#include "RectangleF.h"

bool CRectangleF::Collision( CRectangleF* rectA )
{
	if ( rectA == NULL ) return false;

	if ( this->m_fY + this->m_fHeight < rectA->m_fY ) return false;
	if ( this->m_fY > rectA->m_fY + rectA->m_fHeight ) return false;

	if ( this->m_fX + this->m_fWidth < rectA->m_fX) return false;
	if ( this->m_fX > rectA->m_fX + rectA->m_fWidth ) return false;

	return true;
}

bool CRectangleF::Collision( CRectangleF* rectA, CRectangleF* rectB )
{
	if ( rectA == NULL ) return false;
	if ( rectB == NULL ) return false;

	if ( rectB->m_fY + rectB->m_fHeight < rectA->m_fY ) return false;
	if ( rectB->m_fY > rectA->m_fY + rectA->m_fHeight ) return false;

	if ( rectB->m_fX + rectB->m_fWidth < rectA->m_fX) return false;
	if ( rectB->m_fX > rectA->m_fX + rectA->m_fWidth ) return false;

	return false;
}
