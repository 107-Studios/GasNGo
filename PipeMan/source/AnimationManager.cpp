////////////////////////////////////////////////////////////////////////////////////////////////////
// File:		AnimationManager.cpp
// Author:		Samuel Ratledge Jr.
// Date:		December 08, 2010
// Purpose:		Encapsulates all the data required for animations.
// Revisions:	(Add Date Revised)
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AnimationManager.h"
#include "RenderManager.h"


CAnimationManager * CAnimationManager::GetInstance(void)
{
	static CAnimationManager Instance;
	return &Instance;
}

CAnimationManager::CAnimationManager(void)
{
	m_arrFileData.clear();
	m_pRM = NULL;
}

CAnimationManager::~CAnimationManager(void)
{
	Shutdown();
}

void CAnimationManager::Initialize(CRenderManager * _pRM)
{
	// NOTE: If either of the pointers passed in are NULL, don't initialize because both of them are
	// needed to render the image.
	if(NULL == _pRM)
	{
		MessageBox(0, "RenderManager pointer is invalid.", "CAnimationManager::Initialize", MB_OK);
		return;
	}

	m_pRM = _pRM;
}

void CAnimationManager::Shutdown( void )
{
	m_pRM = NULL;

	// Clear out all the animation data
	int nSize = m_arrFileData.size();
	for(int nIndex = 0; nIndex < nSize; ++nIndex)
		delete m_arrFileData[nIndex];

	m_arrFileData.clear();
}

int CAnimationManager::LoadFile(char const * _szFileName, D3DCOLOR const _ColorKey)
{
	if(NULL == _szFileName)
	{
		MessageBox(0, "File name is invalid.", "CAnimationManager::LoadFile", MB_OK);
		return -1;
	}

	// Check to see if the file already exists
	int const nArraySize = m_arrFileData.size();
	for(int nIndex = 0; nIndex < nArraySize; ++nIndex)
		if(0 == strcmp(m_arrFileData[nIndex]->szFileName, _szFileName))
			return -1;

	// Create a new animation
	tAnimationData * pData = new tAnimationData();

	// Create a stream to read the file
	fstream readFile(_szFileName, ios_base::in | ios_base::binary);

	// Load the name of the image file
	int nNameLength = 0;
	char buffer[50] = {0};
	readFile.read((char*)&nNameLength, sizeof(int));
	readFile.read(buffer, nNameLength);

	char filepath[65] = FILE_PATH;
	strcat_s(filepath, nNameLength+11, buffer);

	// Store the texture
	pData->pTexture = m_pRM->LoadTexture(filepath, _ColorKey);

	if(!pData->pTexture)
	{
		delete pData;
		pData = NULL;
		return -1;
	}

	// Set the name so to not load the same file again, only to return the index located.
	pData->SetName(_szFileName);

	// Read in the number of animations
	int nNumAnimations = 0;
	readFile.read((char*)&nNumAnimations, sizeof(int));

	// Loop through all the animations
	for(int nAnimation = 0; nAnimation < nNumAnimations; ++nAnimation)
	{
		CAnimation * pAnimation = new CAnimation();

		// Read in the number of letters for the name
		nNameLength = 0;
		readFile.read((char*)&nNameLength, sizeof(int));

		// Read in the name
		memset(&buffer, NULL, 50);
		readFile.read(buffer, nNameLength);
		pAnimation->SetName(buffer);

		// Read in the number of frames
		int nNumFrames = 0;
		readFile.read((char*)&nNumFrames, sizeof(int));

		// Loop through all the frames
		for(int nFrame = 0; nFrame < nNumFrames; ++nFrame)
		{
			CFrame * pFrame = new CFrame();

			int nX = 0;
			int nY = 0;
			int nWidth = 0;
			int nHeight = 0;

			// Read in the frame dimensions
			readFile.read((char*)&nX, sizeof(int));
			readFile.read((char*)&nY, sizeof(int));
			readFile.read((char*)&nWidth, sizeof(int));
			readFile.read((char*)&nHeight, sizeof(int));

			CRect rDimensions;
			rDimensions.m_nY = (long)nY;
			rDimensions.m_nHeight = (long)(nHeight);
			rDimensions.m_nX = (long)nX;
			rDimensions.m_nWidth = (long)(nWidth);
			pFrame->SetRect(rDimensions);
			
			// Read in the time delay
			float fTime = 0.0f;
			readFile.read((char*)&fTime, sizeof(float));
			pFrame->SetTimeDelay(fTime);

			// Read in the Anchor data
			bool bHasAnchor = false;
			readFile.read((char*)&bHasAnchor, sizeof(bool));

			if(true == bHasAnchor)
			{
				nX = 0;
				nY = 0;

				readFile.read((char*)&nX, sizeof(int));
				readFile.read((char*)&nY, sizeof(int));
				pFrame->SetAnchorData(true, nX, nY);
			}
			
			// Read in Collision Data
			bool bHasCollision = false;
			readFile.read((char*)&bHasCollision, sizeof(bool));
			
			if(true == bHasCollision)
			{
				// Read the number of Collision RECTs
				int nNumRECTs = 0;
				readFile.read((char*)&nNumRECTs, sizeof(int));

				// Loop through all the RECTs
				for(int nRECT = 0; nRECT < nNumRECTs; ++nRECT)
				{
					CFrame::tCollisionData * pCollData = new CFrame::tCollisionData();

					nX = 0;
					nY = 0;
					nWidth = 0;
					nHeight = 0;

					readFile.read((char*)&nX, sizeof(int));
					readFile.read((char*)&nY, sizeof(int));
					readFile.read((char*)&nWidth, sizeof(int));
					readFile.read((char*)&nHeight, sizeof(int));

					rDimensions.m_nY	  = (long)nY;
					rDimensions.m_nHeight = (long)nHeight;
					rDimensions.m_nX	  = (long)nX;
					rDimensions.m_nWidth  = (long)nWidth;

					pCollData->SetRect(true, rDimensions);

					bool bHasTriggers = false;
					readFile.read((char*)&bHasTriggers, sizeof(bool));

					if(true == bHasTriggers)
					{
						int nNumTriggers = 0;
						readFile.read((char*)&nNumTriggers, sizeof(int));

						for(int nTrigger = 0; nTrigger < nNumTriggers; ++nTrigger)
						{
							memset(buffer, NULL, 50);
							nNameLength = 0;

							// Read in the number of triggers
							readFile.read((char*)&nNameLength, sizeof(int));
							readFile.read(buffer, nNameLength);

							pCollData->AddTrigger(buffer);
						}
					}
					pFrame->AddCollisionData(pCollData);
				}
			}
			pAnimation->AddFrame(pFrame);
		}
		pData->AddAnimation(pAnimation);
	}

	// Check for available slots, append if none are available
	for(int nIndex = 0; nIndex < nArraySize; ++nIndex)
	{
		if(NULL == m_arrFileData[nIndex])
		{
			m_arrFileData[nIndex] = pData;
			return nIndex;
		}
	}

	m_arrFileData.push_back(pData);
	return (m_arrFileData.size()-1);
}

void CAnimationManager::Update(int const _nFileIndex, float const _fTime)
{
	// Update only the current animation
	m_arrFileData[_nFileIndex]->arrAnimations[m_arrFileData[_nFileIndex]->nCurrentAnimation]->Update(_fTime);
}

void CAnimationManager::Render(int const _nFileIndex,
							   int const _nAnimationIndex,
							   D3DXVECTOR2 const & _vPosition,
							   D3DCOLOR const & _ColorKey,
							   D3DXVECTOR2 const & _vScale,
							   float const _fLocalRotation,
							   float const _fGlobalRotation,
							   D3DXVECTOR2 const & _vRotationPoint) const

{
	CTexture const * pTexture = m_arrFileData[_nFileIndex]->pTexture;
	CAnimation const * pAnimation = m_arrFileData[_nFileIndex]->arrAnimations[_nAnimationIndex];
	CFrame const * pFrame = pAnimation->GetCurrentFrame();
	D3DXVECTOR2 vPosition = _vPosition;

	// If the image has an anchor, offset the image by that point. Otherwise just render the image
	// at the desired location.
	if(pFrame->GetAnchorData().bHasAnchor)
	{
		vPosition.x -= (pFrame->GetAnchorData().nX - pFrame->GetRect().m_nX);
		vPosition.y -= (pFrame->GetAnchorData().nY - pFrame->GetRect().m_nY);
	}

	m_pRM->Render(pTexture, &pFrame->GetRect(), vPosition, _vScale, _ColorKey, D3DXVECTOR2(0, 0),
				  _fLocalRotation, _fGlobalRotation, _vRotationPoint);
}

int CAnimationManager::GetFileIndexByName(char const * _szFileName)
{
	// Look through all the files and return the index if the names match.
	int const nArraySize = m_arrFileData.size();
	for(int nIndex = 0; nIndex < nArraySize; ++nIndex)
		if(0 == strcmp(_szFileName, m_arrFileData[nIndex]->szFileName))
			return nIndex;

	return -1;
}

int CAnimationManager::GetAnimationIndexByName(int const _nFileIndex, char const * _szName)
{
	// Look through all the animations and return the index if the names match.
	int const nArraySize = m_arrFileData[_nFileIndex]->arrAnimations.size();
	for(int nIndex = 0; nIndex < nArraySize; ++nIndex)
		if(0 == strcmp(_szName, m_arrFileData[_nFileIndex]->arrAnimations[nIndex]->GetName()))
			return nIndex;

	return -1;
}

void CAnimationManager::ChangeAnimation(int const _nFileIndex, eAnimation const _eAnim)
{
	// Update the current index and current animation.
#pragma warning(push)
#pragma warning(disable : 4482)
	m_arrFileData[_nFileIndex]->nCurrentAnimation = (int) _eAnim;
#pragma warning(pop)
	m_arrFileData[_nFileIndex]->arrAnimations[m_arrFileData[_nFileIndex]->nCurrentAnimation];
}