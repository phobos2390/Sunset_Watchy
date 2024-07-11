#include "IRenderer.h"

enum WatchyButton
{
	watchy_Button_Upper_Left,
	watchy_Button_Lower_Left,
	watchy_Button_Upper_Right,
	watchy_Button_Lower_Right
};

class IWatchyScreen
{
public:
	void OnRender(IRenderer& renderer)=0;
	void OnButtonPress(IRenderer& renderer, WatchyButton& button)=0;
}