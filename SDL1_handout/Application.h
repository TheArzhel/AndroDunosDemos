#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "DummyESC.h"

#define NUM_MODULES 2

class Application
{
public:

	Module* modules[NUM_MODULES];

public:

	Application()
	{
		modules[0] = new ModuleDummy();
		modules[1] = new DummyESC();
		// TODO 7: Create your new module "DummyESC"
		// it should check if player it ESC key use kbhit()
		// http://www.cprogramming.com/fod/kbhit.html
	}

	// INIT all modules
	bool Init()
	{
		bool ret = true;
		for (int i = 0; i < NUM_MODULES; ++i)
		{
			ret = modules[i]->Init();
			if (!ret)
				break;
		}
	
		
		// TODO 5: Make sure that if Init() / PreUpdate/Update/PostUpdate/CleanUP return
		// an exit code App exits correctly.
		return ret; 
	}

	// TODO 4: Add PreUpdate and PostUpdate calls

	// UPDATE all modules
	// TODO 2: Make sure all modules receive its update
	update_status Update() {
		update_status ret = update_status::UPDATE_CONTINUE;

		for (int i = 0; i < NUM_MODULES; ++i)
		{
			ret = modules[i]->PreUpdate();
			if (ret != update_status::UPDATE_CONTINUE)
				return ret;
		}

		for (int i = 0; i < NUM_MODULES; ++i)
		{
			ret = modules[i]->Update();
			if (ret != update_status::UPDATE_CONTINUE)
				return ret;
		}

		for (int i = 0; i < NUM_MODULES; ++i)
		{
			ret = modules[i]->PostUpdate();
			if (ret != update_status::UPDATE_CONTINUE)
				break;
		}

		return ret;
	}

	// EXIT Update 
	// TODO 3: Make sure all modules have a chance to cleanup
	bool CleanUp()
	{
		bool ret = true;

		for (int i = NUM_MODULES-1; i > -1; --i)
		{
			ret = modules[i]->CleanUp();
			if (!ret)
				break;
			
		}

		for (int i = NUM_MODULES - 1; i > -1; --i)
		{
			delete modules[i];
		}
		return ret;
	}

};

#endif // __APPLICATION_H__