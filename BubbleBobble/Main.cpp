#include "SteelEnginePCH.h"
#include "BubbleBobbleGame.h"

#if _DEBUG
//// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

int main()
{
	BubbleBobbleGame bubbleBobble;
	bubbleBobble.Run();
}