#include "WatchTextMenu.h"

WatchTextMenu::WatchTextMenu(size_t MaxElementCount)
	: MaxElementCount(MaxElementCount)
	, currentElementCount(0)
	, currentSelectedElement(0)
	, m_p_elementList(new MenuElement[MaxElementCount])
{
	(void)memset(m_p_elementList, 0, sizeof(MenuElement) * MaxElementCount);
}

WatchTextMenu::~WatchTextMenu()
{
	delete [] m_p_elementList;
}

void WatchTextMenu::OnRender(IRenderer& renderer)
{
	renderer.fillScreen(GxEPD_BLACK);
	renderer.setFont(&FreeMonoBold9pt7b);
	for(size_t i = 0; i < currentElementCount; i++)
	{
		if(i == currentSelectedElement)
		{
			renderer.getTextBounds(menuItems[i], 0, yPos, &x1, &y1, &w, &h);
			renderer.fillRect(x1 - 1, y1 - 10, 200, h + 15, GxEPD_WHITE);
			renderer.setTextColor(GxEPD_BLACK);
			renderer.println(m_p_elementList[i].name);
		}
		else
		{
			renderer.setTextColor(GxEPD_WHITE);
			renderer.println(m_p_elementList[i].name);
		}
		
	}
}

void WatchTextMenu::OnButtonPress(IRenderer& renderer, WatchyButton& button)
{
	switch(button)
	{
		case watchy_Button_Lower_Left:
			m_p_currentScreen = m_p_elementList[currentSelectedElement].element;
			m_p_currentScreen->OnRender(renderer);
		    break;
		case watchy_Button_Upper_Left:
			m_p_currentScreen = m_p_backScreen;
			m_p_currentScreen->OnRender(renderer);
			break;
		case watchy_Button_Upper_Right:
			currentSelectedElement = (currentSelectedElement + 1) % currentElementCount;
			OnRender(renderer);
			break;
		case watchy_Button_Lower_Right:
			currentSelectedElement = (currentSelectedElement - 1) % currentElementCount;
			OnRender(renderer);
			break;
		default:
			break;
	}
}

void WatchTextMenu::AddMenuItem(String name, IWatchyScreen* screen)
{
	if(currentElementCount + 1 < MaxElementCount)
	{
		m_p_elementList[currentElementCount].name = name;
		m_p_elementList[currentElementCount++].element = screen;
	}
}

void WatchTextMenu::setCurrentScreen(IWatchyScreen* p_currentScreen)
{
	m_p_currentScreen = p_currentScreen;
}

void WatchTextMenu::setBackScreen(IWatchyScreen* p_backScreen)
{
	m_p_backScreen = p_backScreen;
}