#include "MenuObjects.h"
#include "IGameState.h"

void tMenuObjImagePosition::Render( IGameState * pState )
{
	pState->RenderImage( this );
}
void tMenuObjButtonPosition::Render( IGameState * pState )
{
	pState->RenderButton( this );
}