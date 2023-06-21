#ifndef SUNSET_WATCHFACE_STEPCOUNTER_H
#include <stdint.h>


class Step_counter
{
public:
	Step_counter();
	virtual ~Step_counter();
	
	uint32_t Get_Step_Count();
	uint32_t Get_Average_Step_Count();
	
private:
	struct Impl;
	Impl* m_p_impl;
};


#endif /*SUNSET_WATCHFACE_STEPCOUNTER_H*/
