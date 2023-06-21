#include "Sunset_Watchface_Stepcounter.h"

struct Step_counter::Impl
{
	
	
	Impl(){}
	
	~Impl(){}
	
	
};


Step_counter::Step_counter()
    : m_p_impl(new Impl())
{
	
}

Step_counter::~Step_counter()
{
}

uint32_t Step_counter::Get_Step_Count()
{
	return 0;
}

uint32_t Step_counter::Get_Average_Step_Count()
{
	return 0;
}


