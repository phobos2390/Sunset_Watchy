#include "Sunset_Watchface_Stepcounter.h"
#include "bma.h"

#define DAYS_STEP_HISTORY 31

struct Step_counter::Impl
{
  BMA423* m_p_sensor;

  uint16_t Steps_History [DAYS_STEP_HISTORY];
  uint8_t Current_Day;
  uint8_t Days_For_Average;
  
	Impl(BMA423* p_sensor)
	  :m_p_sensor(p_sensor)
    ,Steps_History()
    ,Current_Day(0)
    ,Days_For_Average(1)
	{
      memset(&Steps_History[0], 0, sizeof(Steps_History));
	}
	
	~Impl(){}
};

extern RTC_DATA_ATTR BMA423 sensor;
RTC_DATA_ATTR Step_counter::Impl g_impl(&sensor);

Step_counter::Step_counter()
    : m_p_impl(&g_impl)
{
	
}

Step_counter::~Step_counter()
{
  m_p_impl = 0;
}

uint16_t Step_counter::Get_Step_Count()
{
  uint16_t ret_val = 0;
  if(m_p_impl && m_p_impl->m_p_sensor)
  {
    ret_val = m_p_impl->m_p_sensor->getCounter();
  }
	return ret_val;
}

uint16_t Step_counter::Get_Average_Step_Count()
{
  uint64_t total = 0;
  for(size_t i = 0; i < m_p_impl->Days_For_Average; i++)
  {
    total += m_p_impl->Steps_History[i];
  }
  return (uint16_t)total/m_p_impl->Days_For_Average;
}

void Step_counter::Next_Day()
{
  uint32_t stepCount = m_p_impl->m_p_sensor->getCounter();
  m_p_impl->m_p_sensor->resetStepCounter();
  m_p_impl->Steps_History[m_p_impl->Current_Day] = stepCount;
  m_p_impl->Current_Day = (m_p_impl->Current_Day + 1) % DAYS_STEP_HISTORY;
  if(m_p_impl->Current_Day == 0)
  {
    m_p_impl->Days_For_Average = DAYS_STEP_HISTORY;
  }
  else
  {
    m_p_impl->Days_For_Average++;
  }
}
