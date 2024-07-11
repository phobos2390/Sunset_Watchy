#include "time.h"

Watchface::Watchface()
  :m_currentTime()
  ,m_p_currentScreen(NULL)
  ,m_p_backScreen(NULL)
{
	(void)memset(&m_currentTime,0,sizeof(m_currentTime));
}

Watchface::~Watchface()
{
}

void Watchface::UpdateTime(const tmElements_t& updatedTime)
{
	(void)memcpy(&m_currentTime,&updatedTime,sizeof(m_currentTime));
}

void Watchface::OnButtonPress(IRenderer&, WatchyButton& button)
{
	switch(button)
	{
		case watchy_Button_Lower_Left:
			m_p_currentScreen = m_p_backScreen;
			break;
		case watchy_Button_Upper_Left:
		case watchy_Button_Upper_Right:
		case watchy_Button_Lower_Right:
		default:
			break;
	}
}

void Watchface::setCurrentScreen(IWatchyScreen* p_currentScreen)
{
	m_p_currentScreen = p_currentScreen;
}

void Watchface::setBackScreen(IWatchyScreen* p_backScreen)
{
	m_p_backScreen = p_backScreen;
}
