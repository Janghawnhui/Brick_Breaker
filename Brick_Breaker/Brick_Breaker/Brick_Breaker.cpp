// Brick_Breaker.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Brick_Breaker.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BRICKBREAKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BRICKBREAKER));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRICKBREAKER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BRICKBREAKER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
       CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
/// 전역변수 정의

int brick_x = 40;
int brick_y = 40;
GameArea paintSquare;

Paddle paddle(PADDLE_LEFT, PADDLE_TOP, PADDLE_RIGHT, PADDLE_BOTTOM);


//(brick_x, brick_y, brick_x + 70, brick_y + 15);

Brick* brick[6][10];
std::vector<Item*> items;

Ball ball(1000, 700, 5, 5, 10, -10); // 초기 위치와 크기, 속도를 설정

RECT tmpRect;

int g_num = 10;

int brick_width = 50;
int brick_height = 40;
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
bool isBallLaunched = false; // 공이 발사되었는지 여부
bool isGameCleared = false;
float ballSpeedX = 0.0f; // 공의 X축 속도
float ballSpeedY = 0.0f; // 공의 Y축 속도


bool areAllBricksDestroyed()
{
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < g_num; i++) {
            if (!brick[j][i]->isDestroyed) {
                return false;  // 아직 부서지지 않은 벽돌이 있으면 false 반환
            }
        }
    }
    return true;  // 모든 벽돌이 부서졌다면 true 반환
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        for (int j = 0; j < 6; j++) { // 0부터 3까지
            for (int i = 0; i < g_num; i++) { // 0부터 g_num-1까지
                brick[j][i] = new Brick(brick_width +100* i, brick_height+ 50 * j, brick_width+ 100*i+50, brick_height+50*j+40); // x, y 위치를 다르게 설정
            }
        }
        SetTimer(hWnd, 1, 20, NULL);
        break;
    case WM_TIMER:
    {
        // 공의 이전 위치 계산
        RECT prevBallRect = { ball.x, ball.y, ball.x + ball.width, ball.y + ball.height };

        // Paddle 위치 업데이트
        RECT paddlemove = paddle.getRect();
        ball.area_updatePosition(GAME_AREA_LEFT, GAME_AREA_TOP, GAME_AREA_RIGHT, GAME_AREA_BOTTOM,hWnd, ball);
        ball.paddle_updatePosition(paddlemove.left, paddlemove.top, paddlemove.right, paddlemove.bottom);
        if (ball.speedX == 0 && ball.speedY == 0) {
            KillTimer(hWnd, 1); // 타이머 종료
   
            break;
        }
        // 벽돌 충돌 체크 및 공 업데이트
        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < g_num; i++) {
                RECT brickRect = brick[j][i]->getRect();
                if (!brick[j][i]->isDestroyed) {
                    ball.brick_updatePosition(brickRect.left, brickRect.top, brickRect.right, brickRect.bottom);
                    //items.push_back(brick[j][i]->item); // 아이템 리스트에 추가
                     //brick[j][i]->item = nullptr;       // 벽돌과 아이템 연결 해제
                }
                RECT ballRect = { ball.x, ball.y, ball.x + ball.width, ball.y + ball.height };
                if (IntersectRect(&tmpRect, &brickRect, &ballRect)) {
                    brick[j][i]->destroy(); // 벽돌을 파괴 상태로 표시
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
        }
        if (areAllBricksDestroyed() && !isGameCleared) {
            MessageBox(hWnd, L"게임 클리어!", L"축하합니다", MB_OK | MB_ICONINFORMATION);
            isGameCleared = true;
            KillTimer(hWnd, 1);  // 타이머 종료
        }
        // 공의 새로운 위치 계산
        RECT newBallRect = { ball.x, ball.y, ball.x + ball.width, ball.y + ball.height };

        // 이전 위치와 새로운 위치를 합친 영역만 다시 그리기
        RECT updateRect;
        UnionRect(&updateRect, &prevBallRect, &newBallRect);
        InvalidateRect(hWnd, &updateRect, FALSE);

        break;
    }

    //case WM_TIMER:
    //    // 공의 위치 업데이트
 
    //    RECT paddlemove = paddle.getRect();

    //    ball.area_updatePosition(GAME_AREA_LEFT, GAME_AREA_TOP, GAME_AREA_RIGHT, GAME_AREA_BOTTOM);
    //    ball.paddle_updatePosition(paddlemove.left, paddlemove.top, paddlemove.right, paddlemove.bottom);
    //    for (int j = 0; j < 6; j++) {
    //        for (int i = 0; i < g_num; i++) {
    //            RECT brickRect = brick[j][i]->getRect();
    //            if (!brick[j][i]->isDestroyed) {
    //                ball.brick_updatePosition(brickRect.left, brickRect.top, brickRect.right, brickRect.bottom);
    //            }
    //            RECT ballRect = { ball.x, ball.y, ball.x + ball.width, ball.y + ball.height };
    //            if (IntersectRect(&tmpRect, &brickRect, &ballRect)) {
    //                brick[j][i]->destroy(); // 벽돌을 파괴 상태로 표시
    //                //brick[j][i] = nullptr;
    //            }
    //        }
    //    }
    //    InvalidateRect(hWnd, NULL, TRUE);
    //    break;
    case WM_MOUSEMOVE:
    {
        int mouseX = LOWORD(lParam);

        // Paddle의 이전 위치 가져오기
        RECT prevPaddleRect = paddle.getRect();

        // Paddle을 새 위치로 이동
        paddle.move(mouseX);

        // Paddle의 새 위치 가져오기
        RECT newPaddleRect = paddle.getRect();

        // 이전 위치와 새 위치를 합친 영역만 다시 그리기
        RECT updateRect;
        UnionRect(&updateRect, &prevPaddleRect, &newPaddleRect);

        // 합쳐진 영역을 다시 그리기
        InvalidateRect(hWnd, &updateRect, FALSE);

        break;
    }

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 더블 버퍼링을 위한 메모리 DC 생성
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP memBitmap = CreateCompatibleBitmap(hdc, GAME_AREA_RIGHT, GAME_AREA_BOTTOM);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

        // 메모리 DC 배경 초기화
        FillRect(memDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // 게임 영역 그리기
        paintSquare.makeSquare(memDC);

        // Paddle 그리기
        paddle.draw(memDC);

        // 벽돌 그리기
        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < g_num; i++) {
                if (brick[j][i] != nullptr && !brick[j][i]->isDestroyed) {
                    brick[j][i]->draw(memDC);
                }
            }
        }
        for (auto& item : items) {
            item->draw(memDC);
        }

        // 공 그리기
        Ellipse(memDC, ball.x, ball.y, ball.x + ball.width, ball.y + ball.height);

        // 메모리 DC를 실제 화면 DC로 복사
        BitBlt(hdc, 0, 0, GAME_AREA_RIGHT, GAME_AREA_BOTTOM, memDC, 0, 0, SRCCOPY);

        // 메모리 DC 리소스 정리
        SelectObject(memDC, oldBitmap);
        DeleteObject(memBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
