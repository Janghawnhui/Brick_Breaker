//{{NO_DEPENDENCIES}}
// Microsoft Visual C++에서 생성한 포함 파일입니다.
// 다음에서 사용 Brick_Breaker.rc

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_BRICKBREAKER_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_BRICKBREAKER			107
#define IDI_SMALL				108
#define IDC_BRICKBREAKER			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif
// 다음은 새 개체에 사용할 기본값입니다.
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif

///영역 정의

///윈도우창 크기 정의
//HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU, CW_USEDEFAULT, 0, 1130, 800, nullptr, nullptr, hInstance, nullptr);

#define WINDOW_WIDTH 1130
#define WINDOW_HEIGHT 800

///게임 영역 	
//Rectangle(hdc, 10, 30, 1000, 830);
#define GAME_AREA_LEFT 10
#define GAME_AREA_TOP 30
#define GAME_AREA_RIGHT 1100
#define GAME_AREA_BOTTOM 730

///객체 정의 (공, 벽돌, 패들)

///패들 크기 및 위치
//Paddle paddle(50, 650, 150, 20);
#define PADDLE_LEFT 50
#define PADDLE_TOP 650
#define PADDLE_RIGHT 150
#define PADDLE_BOTTOM 20


