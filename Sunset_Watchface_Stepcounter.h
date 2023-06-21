#ifndef SUNSET_WATCHFACE_STEPCOUNTER_H
#include <stdint.h>

class Step_counter
{
public:
	Step_counter();
	virtual ~Step_counter();
	
  /// @return the sensors current step count
	uint16_t Get_Step_Count();

  /// @return the average step count over the past 31 days
	uint16_t Get_Average_Step_Count();

  /// Advance Count to the next day
  void Next_Day();
	
public:
	struct Impl;
private:
	Impl* m_p_impl;
};


#endif /*SUNSET_WATCHFACE_STEPCOUNTER_H*/
