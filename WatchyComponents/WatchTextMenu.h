#include "IRenderer.h"
#include "IWatchyScreen.h"

class WatchTextMenu : public IWatchyScreen
{
public:
	WatchTextMenu(size_t MaxElementCount);
	~WatchTextMenu();
	void OnRender(IRenderer& renderer);
	void OnButtonPress(IRenderer& renderer, WatchyButton& button);
	void AddMenuItem(String name, IWatchyScreen* screen);
private:
    size_t MaxElementCount;
	size_t currentElementCount;
	size_t currentSelectedElement;
	struct MenuElement;
	{
		String name;
		IWatchyScreen* element;
	};
    MenuElement* elementList;
}