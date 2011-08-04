#include "IGameState.h"

#include "InputManager.h"
#include "RenderManager.h"
#include "SaveInfo.h"

#include <fstream>
using std::ifstream;

#include <assert.h>

IGameState::IGameState( char* szMSFName ) : m_szMSFName( szMSFName ) , ppTextures( NULL ) , m_uiImageCount( 0 ) , m_uiTriggerCount( 0 ) , ppTriggers( NULL )
{
	pRenderMan = CRenderManager::GetInstance();
	pSaveInfo = CSaveInfo::GetInstance();
}
IGameState::~IGameState()
{
}
void IGameState::Enter()
{
	//Load state file

	ifstream binReader( m_szMSFName , std::ios_base::binary | std::ios_base::in );

	if ( !binReader.is_open() )
	{
		assert( !"State file cannot be found. Sincerely, IGameState" );
		return;
	}

#pragma region Load_Images

	binReader.read( (char*)&m_uiImageCount, 4 );

	if ( m_uiImageCount == 0 )
	{
		//No images/objects/positions to load
		m_bRunning = true;
		return;
	}

	ppTextures = new CTexture*[ m_uiImageCount ];

	CRenderManager* pRenderMan = CRenderManager::GetInstance();

	//Space on stack to temporarily store the file name and path
	char szImageName[52] = "resources/"; //Load in at char[10] so automatically have resources infront

	//Length of the filename
	unsigned char ucLength;

	for ( unsigned uiImages = 0; uiImages < m_uiImageCount; ++uiImages )
	{
		binReader.read( (char*)&ucLength , 1 );
		binReader.read( &(szImageName[10]) , ucLength );

		//Force the null terminator behind the loaded file name
		szImageName[ 10 + ucLength ] = '\0';

		ppTextures[ uiImages ] = pRenderMan->LoadTexture( szImageName );
	}

#pragma endregion Load_Images

#pragma region Load_Objects

	unsigned uiObjectCount;
	binReader.read( (char*)&uiObjectCount, 4 );

	m_lObjects.resize( uiObjectCount );

	unsigned uiImageID = 0;

	unsigned eType = TYPE_IMAGE;

	for ( unsigned uiObjects = 0; uiObjects < uiObjectCount; ++uiObjects )
	{
		//TODO:: When using multiple object types, setup to create the object in the matter appropiate
		tMenuBaseObject* pObj = NULL;

		binReader.read( (char*)&eType , 4 );

		switch( eType )
		{
		case TYPE_ANIM:
			{
				//No animation objects yet
			}
			break;
		case TYPE_BUTTON:
			{
				tMenuObjButton* pButton = new tMenuObjButton();

				binReader.read( (char*)&pButton->aDrawRects[1].m_nX , 4 );
				binReader.read( (char*)&pButton->aDrawRects[1].m_nY , 4 );
				binReader.read( (char*)&pButton->aDrawRects[1].m_nWidth , 4 );
				binReader.read( (char*)&pButton->aDrawRects[1].m_nHeight , 4 );

				binReader.read( (char*)&pButton->aDrawRects[2].m_nX , 4 );
				binReader.read( (char*)&pButton->aDrawRects[2].m_nY , 4 );
				binReader.read( (char*)&pButton->aDrawRects[2].m_nWidth , 4 );
				binReader.read( (char*)&pButton->aDrawRects[2].m_nHeight , 4 );

				binReader.read( (char*)&uiImageID , 4 );

				binReader.read( (char*)&pButton->aDrawRects[0].m_nX , 4 );
				binReader.read( (char*)&pButton->aDrawRects[0].m_nY , 4 );
				binReader.read( (char*)&pButton->aDrawRects[0].m_nWidth , 4 );
				binReader.read( (char*)&pButton->aDrawRects[0].m_nHeight , 4 );

				pObj = pButton;
			}
			break;
		case TYPE_IMAGE:
			{
				tMenuObjImage* pImage = new tMenuObjImage();
				
				binReader.read( (char*)&uiImageID , 4 );
				
				binReader.read( (char*)&pImage->rDrawRect.m_nX , 4 );
				binReader.read( (char*)&pImage->rDrawRect.m_nY , 4 );
				binReader.read( (char*)&pImage->rDrawRect.m_nWidth , 4 );
				binReader.read( (char*)&pImage->rDrawRect.m_nHeight , 4 );

				pObj = pImage;
			}
			break;
		}

		pObj->eType = eType;

		pObj->pTexture = ppTextures[ uiImageID ];

		m_lObjects[ uiObjects ] = pObj;
	}

#pragma endregion Load_Objects

#pragma region Load_Positions

	unsigned uiPositionCount;
	binReader.read( (char*)&uiPositionCount, 4 );

	m_lPositions.resize( uiPositionCount );

	unsigned uiObjectID = 0;
	m_uiTriggerCount = 0;

	for ( unsigned uiPositions = 0; uiPositions < uiPositionCount; ++uiPositions )
	{
		//TODO:: When using multiple object types, setup to create the object in the matter appropiate
		tMenuBaseObjPosition* pPosition = NULL;

		binReader.read( (char*)&uiObjectID , 4 );

		switch ( m_lObjects[ uiObjectID ]->eType )
		{
		case TYPE_ANIM:
			{
				//No animated objects yet
			}
			break;
		case TYPE_BUTTON:
			{
				pPosition = new tMenuObjButtonPosition();
				++m_uiTriggerCount;
			}
			break;
		case TYPE_IMAGE:
			{
				pPosition = new tMenuObjImagePosition();
			}
			break;
		}

		pPosition->pObject = m_lObjects[ uiObjectID ];

		binReader.read( (char*)&pPosition->vPosition.x , 4 );
		binReader.read( (char*)&pPosition->vPosition.y , 4 );
		binReader.read( (char*)&pPosition->vScale.x , 4 );
		binReader.read( (char*)&pPosition->vScale.y , 4 );

		m_lPositions[ uiPositions ] = pPosition;
	}

#pragma endregion Load_Positions

	binReader.close();

	ppTriggers = (bool (**)(IGameState*))malloc( m_uiTriggerCount << 2 );

	memset( ppTriggers , 0 , m_uiTriggerCount << 2 );

	m_bRunning = true;
}
void IGameState::Exit()
{
	CRenderManager* pRenderMan = CRenderManager::GetInstance();

	if ( m_uiImageCount != 0 )
	{
		for ( unsigned uiImages = 0; uiImages < m_uiImageCount; ++uiImages )
		{
			pRenderMan->UnloadTexture( ppTextures[ uiImages ] );
		}

		delete[] ppTextures;

		for ( std::vector< tMenuBaseObject* >::iterator iter = m_lObjects.begin(); iter != m_lObjects.end(); ++iter )
		{
			delete (*iter);
		}

		m_lObjects.clear();
		
		for ( std::vector< tMenuBaseObjPosition* >::iterator iter = m_lPositions.begin(); iter != m_lPositions.end(); ++iter )
		{
			delete (*iter);
		}

		m_lPositions.clear();
	}
}
void IGameState::Input()
{
	//TODO:: Get collisions boxs up and start triggers
	CInputManager* pInput = CInputManager::GetInstance();
	POINT vTempMousePosition = pInput->GetCursorPosition();

	float fScreenWidth = (float)pSaveInfo->GetScreenWidth();
	float fScreenHeight = (float)pSaveInfo->GetScreenHeight();

	D3DXVECTOR2 vMousePosition = D3DXVECTOR2( (float)vTempMousePosition.x / fScreenWidth ,
											(float)vTempMousePosition.y / fScreenHeight );

	unsigned uiTriggers = 0;
	for ( std::vector< tMenuBaseObjPosition* >::iterator iter = m_lPositions.begin(); iter != m_lPositions.end(); ++iter )
	{
		//TODO::Get mouse position and do collision detection
		if ( (*iter)->pObject->eType == TYPE_BUTTON )
		{
			tMenuObjButtonPosition* pPosition = (tMenuObjButtonPosition*)(*iter);

			D3DXVECTOR2 vTempScale = pPosition->vScale;

			tMenuObjButton* pButton = (tMenuObjButton*)pPosition->pObject;
			vTempScale.x *= (float)pButton->aDrawRects[pPosition->eState].m_nWidth;
			vTempScale.y *= (float)pButton->aDrawRects[pPosition->eState].m_nHeight;

			if ( vMousePosition.x > (*iter)->vPosition.x && vMousePosition.y > (*iter)->vPosition.y &&
				vMousePosition.x - (*iter)->vPosition.x < vTempScale.x &&
				vMousePosition.y - (*iter)->vPosition.y < vTempScale.y )
			{
				if (pInput->MouseClicked(pInput->LEFT_CLICK))
				{
					//Set state to down
					pPosition->eState = STATE_DOWN;
				}
				else if (pInput->MouseReleasedBuffered(pInput->LEFT_CLICK))
				{
					//Trigger Button
					if ( ppTriggers[uiTriggers] != NULL )
					{
						//If the trigger returns true, exit
						if ( ppTriggers[uiTriggers]( this ) )
						{
							m_bRunning = false;
							return;
						}
					}

					//Set state to hover
					pPosition->eState = STATE_HOVER;
				}
				else
				{
					//Set state to hover
					pPosition->eState = STATE_HOVER;
				}
			}
			else
			{
				//Set state to up
				pPosition->eState = STATE_UP;
			}
			++uiTriggers;
		}
	}
}
bool IGameState::Update(float fElapsedTime)
{
	//TODO:: Update the objects (Don't have any objects that update yet)
	return m_bRunning;
}
void IGameState::Render()
{
	for ( std::vector< tMenuBaseObjPosition* >::iterator iter = m_lPositions.begin(); iter != m_lPositions.end(); ++iter )
	{
		(*iter)->Render( this );
	}
	//Render everything
}
void IGameState::RenderImage( tMenuObjImagePosition * pPosition )
{
	float fScreenWidth = (float)pSaveInfo->GetScreenWidth();
	float fScreenHeight = (float)pSaveInfo->GetScreenHeight();

	D3DXVECTOR2 vTempPos = D3DXVECTOR2(	pPosition->vPosition.x * fScreenWidth,
										pPosition->vPosition.y * fScreenHeight );
	D3DXVECTOR2 vTempScale = D3DXVECTOR2(	pPosition->vScale.x * fScreenWidth,
											pPosition->vScale.y * fScreenHeight );

// 	pRenderMan->RenderTexture( pPosition->pObject->pTexture ,
// 		&((tMenuObjImage*)pPosition->pObject)->rDrawRect,
// 		-1, vTempPos, vTempScale );

	pRenderMan->Render(pPosition->pObject->pTexture,
					   &((tMenuObjImage*)pPosition->pObject)->rDrawRect,
					   vTempPos, vTempScale);
}
void IGameState::RenderButton( tMenuObjButtonPosition * pPosition )
{
	float fScreenWidth = (float)pSaveInfo->GetScreenWidth();
	float fScreenHeight = (float)pSaveInfo->GetScreenHeight();

	D3DXVECTOR2 vTempPos = D3DXVECTOR2(	pPosition->vPosition.x * fScreenWidth,
										pPosition->vPosition.y * fScreenHeight );
	D3DXVECTOR2 vTempScale = D3DXVECTOR2(	pPosition->vScale.x * fScreenWidth,
											pPosition->vScale.y * fScreenHeight );

// 	pRenderMan->RenderTexture( pPosition->pObject->pTexture ,
// 		&((tMenuObjButton*)pPosition->pObject)->aDrawRects[pPosition->eState],
// 		-1, vTempPos, vTempScale );

	pRenderMan->Render(pPosition->pObject->pTexture,
					   &((tMenuObjButton*)pPosition->pObject)->aDrawRects[pPosition->eState],
					   vTempPos, vTempScale);
}