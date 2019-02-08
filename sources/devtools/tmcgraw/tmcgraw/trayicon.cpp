#include <windows.h>
#include <stdio.h>
#pragma warning(disable : 4996) // unsafe

NOTIFYICONDATA nidApp;
HMENU hPopMenu;
#define	WM_USER_SHELLICON WM_USER + 100
#define IDM_ABOUT	10
#define IDM_SEP		11
#define IDM_EXIT	12

char buff[1000];

extern void _tmcglfinishgraph();

LRESULT CALLBACK TrayIconWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
		int wmId, wmEvent;
    POINT lpClickPoint;
	UINT uFlag;

	switch (message)
	{

	case WM_USER_SHELLICON: 
		// systray msg callback 
		switch(LOWORD(lParam)) 
		{   
			case WM_RBUTTONDOWN: 
				uFlag = MF_BYPOSITION|MF_STRING;
				GetCursorPos(&lpClickPoint);
				hPopMenu = CreatePopupMenu();
     
				InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,IDM_EXIT, L"Exit" );
				InsertMenu(hPopMenu,0xFFFFFFFF,MF_SEPARATOR,IDM_SEP, L"SEP" );				
				InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,IDM_ABOUT, L"About TMC Graphics" );
									
				SetForegroundWindow(hWnd);
				TrackPopupMenu(hPopMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_BOTTOMALIGN,lpClickPoint.x, lpClickPoint.y,0,hWnd,NULL);
				return TRUE; 

		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			case IDM_ABOUT:
				MessageBox(NULL,L"TMCGRA module v1.0" ,L"About TMC Graphics",MB_OK|MB_ICONINFORMATION);
			//	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				// exit application.
				_tmcglfinishgraph();
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}
return 0;
}

void ShowTray()
{
HINSTANCE hInstance = NULL;
    HICON hMainIcon = NULL;
	HWND hWnd;

   	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= TrayIconWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_INFORMATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_SYSTRAYDEMO);
	wcex.lpszClassName	= L"tmcgrax1Z43sdrgr";
	wcex.hIconSm		= LoadIcon(NULL, IDI_INFORMATION);

	RegisterClassEx(&wcex);

   hWnd = CreateWindow(L"tmcgrax1Z43sdrgr", L"tmcgrax1Z43sdrgrT", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hMainIcon = LoadIcon(hInstance,IDI_INFORMATION); 

   nidApp.cbSize = sizeof(NOTIFYICONDATA); // sizeof the struct in bytes 
   nidApp.hWnd = hWnd;              //handle of the window which will process this app. messages 
   nidApp.uID = 101;           //ID of the icon that willl appear in the system tray 
   nidApp.uFlags = NIF_ICON | NIF_MESSAGE |  NIF_TIP; //ORing of all the flags 
   nidApp.hIcon = hMainIcon; // handle of the Icon to be displayed, obtained from LoadIcon 
   nidApp.uCallbackMessage =  WM_USER_SHELLICON; 
   wcscpy(nidApp.szTip ,   L"tmcgra");
 //  LoadString(hInstance, IDS_APPTOOLTIP,nidApp.szTip,MAX_LOADSTRING);
   Shell_NotifyIcon(NIM_ADD, &nidApp); 


}

