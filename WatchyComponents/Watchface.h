#include "time.h"

class Watchface : public IWatchyScreen
{
public:
	Watchface();
	~Watchface();
	void UpdateTime(const tmElements_t& currentTime);
	void OnRender(IRenderer& renderer)=0;
	void OnButtonPress(IRenderer& renderer, WatchyButton& button);
	void setCurrentScreen(IWatchyScreen* p_currentScreen);
	void setBackScreen(IWatchyScreen* p_backScreen);
private:
	tmElements_t m_currentTime;
	IWatchyScreen* m_p_currentScreen;
	IWatchyScreen* m_p_backScreen;
}