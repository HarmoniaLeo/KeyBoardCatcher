// kbMsgCth.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "kbMsgCth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#pragma data_seg("YCIShared")
HWND g_hWndCaller = NULL;
HHOOK g_hHook = NULL;
#pragma data_seg

HMODULE WINAPI ModuleFromAddress(PVOID pv)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (::VirtualQuery(pv, &mbi, sizeof(mbi)) != 0)
		return (HMODULE)mbi.AllocationBase;
	else
		return NULL;
}

LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	::PostMessage(g_hWndCaller, HM_KEY, wParam, lParam);
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

BOOL WINAPI SetKeyHook(HWND hwnd)
{
	g_hWndCaller = hwnd;
	g_hHook = ::SetWindowsHookEx(WH_KEYBOARD, KeyHookProc, ModuleFromAddress(KeyHookProc), 0);
	return g_hHook == NULL ? 0 : 1;
}

BOOL WINAPI RemoveKeyHook()
{
	bool is=::UnhookWindowsHookEx(g_hHook);
	g_hHook = NULL;
	return is;
}
