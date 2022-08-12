#pragma once

#include "Modules/ModuleManager.h"
#include "HIDHandeler.h"

class FRAWControllerModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	FWindowsApplication* GetApplication() const;

private:
	FControllerHandeler Handler;

};
