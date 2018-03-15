#ifndef _DUMMYESC_
#define _DUMMYESC_

#include "Module.h"
#include "Globals.h"
#include <conio.h>

class DummyESC : public Module
{
public:
	DummyESC() {};
	~DummyESC(){};

	update_status Update()
	{
		update_status ret = update_status::UPDATE_CONTINUE;
		if (_kbhit())
			ret = update_status::UPDATE_STOP;

		return ret;
	};
};

#endif