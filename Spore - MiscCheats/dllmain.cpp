// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "SetGameSpeed.h"
#include "giveitem.h"
#include "removeitem.h"
#include "TASCheat.h"
#include "SetGameMode.h"
#include "SkipSpaceTutorial.h"
#include "GiveInventoryItem.h"

void Initialize()
{
	CheatManager.AddCheat("setGameSpeed", new SetGameSpeed());
	CheatManager.AddCheat("giveItem", new GiveItem(), true);
	CheatManager.AddCheat("removeItem", new RemoveItem());
	//CheatManager.AddCheat("TASCheat", new TASCheat());
	CheatManager.AddCheat("setGameMode", new SetGameMode());
	CheatManager.AddCheat("skipSpaceTutorial", new SkipSpaceTutorial());
	CheatManager.AddCheat("giveInventoryItem", new GiveInventoryItem(), true);
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

