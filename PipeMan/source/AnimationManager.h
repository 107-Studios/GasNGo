////////////////////////////////////////////////////////////////////////////////////////////////////
// File:		AnimationManager.h
// Author:		Samuel Ratledge Jr.
// Date:		December 08, 2010
// Purpose:		Encapsulates all the data required for animations.
// Revisions:	(Add date if revised)
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Animation.h"
#include <fstream>
using std::fstream;
using std::ios_base;

#define FILE_PATH "resources/"

class CTexture;
class CRenderManager;


class CAnimationManager
{
public:		// Public enum
	enum eAnimation{ DEFAULT = 0 };

private:	// Private Structures
	struct tAnimationData
	{
		char *				szFileName;
		CTexture *			pTexture;
		vector<CAnimation*> arrAnimations;
		int					nCurrentAnimation;

		tAnimationData(void)
		{
			szFileName = NULL;
			pTexture = NULL;
			arrAnimations.clear();
#pragma warning(push)
#pragma warning(disable : 4482)
			nCurrentAnimation = (int)eAnimation::DEFAULT;
#pragma warning(pop)
		}

		~tAnimationData(void)
		{
			ClearName();
			ClearList();
			pTexture = NULL;
		}

		void SetName(char const * _szFileName)
		{
			ClearName();

			if(_szFileName)
			{
				int nLength = strlen(_szFileName)+1;
				szFileName = new char[nLength];
				strcpy_s(szFileName, nLength, _szFileName);
			}
		}

		void ClearName(void)
		{
			if(szFileName)
			{
				delete[] szFileName;
				szFileName = NULL;
			}
		}

		void AddAnimation(CAnimation * _pAnimation)
		{
			arrAnimations.push_back(_pAnimation);
		}

		void ClearList(void)
		{
			int nSize = arrAnimations.size();
			for(int nIndex = 0; nIndex < nSize; ++nIndex)
				delete arrAnimations[nIndex];
			
			arrAnimations.clear();
			pTexture = NULL;
		}
	};

private:	// Private Data
	vector<tAnimationData*>	m_arrFileData;
	CRenderManager *		m_pRM;

public:		// Public Functions
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Initialize
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Starts the manager and sets all the values needed.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Initialize(CRenderManager * _pRM);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Shutdown
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Shuts down the manager and clears any data dynamic memory.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		GetInstance
	// Parameter(s):	void
	// Return:			CAnimationManager *
	// Purpose:			Returns the instance created so there is only one instance at all times.
	////////////////////////////////////////////////////////////////////////////////////////////////
	static CAnimationManager * GetInstance(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		LoadFile
	// Parameter(s):	char const * _szFileName		- Load in the filename
	//					unsigned long const	_dwColorKey - Alpha color value
	// Return:			int		Returns the index at which the animation is stored in the list,
	//							otherwise returns -1 if the file wasn't loaded.
	// Purpose:			Loads in the file (.ani) and creates the animations.
	////////////////////////////////////////////////////////////////////////////////////////////////
	int LoadFile(char const * _szFileName, D3DCOLOR const _ColorKey = 0);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Update
	// Parameter(s):	int const _nFileIndex			- Which file to update
	//					float const _fTime				- Time since last Update
	// Return:			void
	// Purpose:			Updates the animation.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(int const _nFileIndex, float const _fTime);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Render
	// Parameter(s):	void
	// Parameter(s):	int const _nImageIndex				- Specified image
	//					int const _nAnimationIndex			- Specified animation
	// 					D3DXVECTOR2 const & _vPosition		- Position
	// 					CColor const & _Color				- Color to render
	// 					D3DXVECTOR2 const & _vScale			- Scale
	// 					float const _fRotation				- Rotation amount
	// 					D3DXVECTOR2 const & _vRotationPoint	- Rotation value
	// Return:			void
	// Purpose:			Displays the animation to the screen.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Render(int const _nFileIndex,
				int const _nAnimationIndex,
				D3DXVECTOR2 const & _vPosition,
				D3DCOLOR const & _ColorKey				= 0xFFFFFFFF,
				D3DXVECTOR2 const & _vScale				= D3DXVECTOR2(1.0f, 1.0f),
				float const _fLocalRotation				= 0.0f,
				float const _fGlobalRotation			= 0.0f,
				D3DXVECTOR2 const & _vRotationPoint		= D3DXVECTOR2(0.0f, 0.0f)) const;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		GetFileByName
	// Parameter(s):	char const * _szFileName		- Name to find
	// Return:			int		Returns the index where the file is located, otherwise returns -1
	// Purpose:			Returns the index into the list of all the files.
	////////////////////////////////////////////////////////////////////////////////////////////////
	int GetFileIndexByName(char const * _szFileName);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		GetAnimationByName
	// Parameter(s):	int const _nFileIndex			- Index into the files list
	//					char const * _szName			- Name to find
	// Return:			int		Returns the index where the animation is located, otherwise -1
	// Purpose:			Returns the index into the list of all the animations.
	////////////////////////////////////////////////////////////////////////////////////////////////
	int GetAnimationIndexByName(int const _nFileIndex, char const * _szName);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		ChangeAnimation
	// Parameter(s):	int const _nFileIndex			- Index into the files list
	//					eAnimation const _eAnim			- The animation to change to
	// Return:			void
	// Purpose:			Changes the animation.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void ChangeAnimation(int const _nFileIndex, eAnimation const _eAnim);

private:	// "Do-nothing" functions
	CAnimationManager(void);
	~CAnimationManager(void);
	CAnimationManager(CAnimationManager const &);
	CAnimationManager & operator=(CAnimationManager const &);
};