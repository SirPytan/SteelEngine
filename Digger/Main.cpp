#include "SteelEnginePCH.h"
#include "DiggerGame.h"

#if _DEBUG
//// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

int main()
{
	DiggerGame digger;
	digger.Run(600, 480);
}