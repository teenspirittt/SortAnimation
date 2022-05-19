#include <GL/freeglut.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 500

const double area_length = 2.6;            // window length
const double coefficient = 1.5;         // interval's coefficient

int numbers_array[N];
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC *, HGLRC *);

void DisableOpenGL(HWND, HDC, HGLRC);

void rectangle(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);

void bubble_sort(HDC hDC);

void quick_sort(HDC hDC, int first, int last);

void cocktail_sort(HDC hDC);

void insertion_sort(HDC hDC);

void draw_rectangles(HDC hDC);

void rand_generator();

int max_num();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  WNDCLASSEX wcex;
  HWND hwnd;
  HDC hDC;
  HGLRC hRC;
  MSG msg;
  BOOL bQuit = FALSE;

  /* register window class */
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_OWNDC;
  wcex.lpfnWndProc = WindowProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = "GLSample";
  wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wcex))
    return 0;

  /* create main window */
  hwnd = CreateWindowEx(0,
                        "GLSample",
                        "OpenGL Sample",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        1280,
                        720,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

  ShowWindow(hwnd, nCmdShow);

  /* enable OpenGL for the window */
  EnableOpenGL(hwnd, &hDC, &hRC);
  rand_generator();
  /* program main loop */
  while (!bQuit) {
    /* check for messages */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      /* handle or dispatch messages */
      if (msg.message == WM_QUIT) {
        bQuit = TRUE;
      } else {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    } else {
      // quick_sort( hDC, 0, q_columns-1);
      // bubble_sort(hDC);
      cocktail_sort(hDC);
      // insertion_sort( hDC);
    }
  }

  /* shutdown OpenGL */
  DisableOpenGL(hwnd, hDC, hRC);
  /* destroy the window explicitly */
  DestroyWindow(hwnd);
  return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_CLOSE:PostQuitMessage(0);
      break;
    case WM_DESTROY:return 0;
    case WM_KEYDOWN: {
      switch (wParam) {
        case VK_ESCAPE:PostQuitMessage(0);
          break;
      }
    }
      break;
    default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}

void EnableOpenGL(HWND hwnd, HDC *hDC, HGLRC *hRC) {
  PIXELFORMATDESCRIPTOR pfd;
  int iFormat;
  /* get the device context (DC) */
  *hDC = GetDC(hwnd);
  /* set the pixel format for the DC */
  ZeroMemory(&pfd, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  iFormat = ChoosePixelFormat(*hDC, &pfd);
  SetPixelFormat(*hDC, iFormat, &pfd);
  /* create and enable the render context (RC) */
  *hRC = wglCreateContext(*hDC);
  wglMakeCurrent(*hDC, *hRC);
}

/*function which draw rectangles */
void rectangle(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4) {
  glBegin(GL_QUADS);
  glColor3f(0.43f, 0.43f, 0.40f);
  glVertex2f(x1, y1);
  glColor3f(0.43f, 0.43f, 0.40f);
  glVertex2f(x2, y2);
  glColor3f(0.43f, 0.43f, 0.40f);
  glVertex2f(x3, y3);
  glColor3f(0.43f, 0.43f, 0.40f);
  glVertex2f(x4, y4);
  glEnd();
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hRC);
  ReleaseDC(hwnd, hDC);
}

void rand_generator() {
  for (int i = 0; i < N; ++i) {
    numbers_array[i] = rand() % 500;
  }
}

/*function which find max number in the array*/
int max_num() {
  int max = 0;
  for (int i = 0; i < N; i++)
    if (max < abs(numbers_array[i]))
      max = abs(numbers_array[i]);
  return max;
}

void bubble_sort(HDC hDC) {
  int tmp;
  for (int i = 0; i < N - 1; i++) {

    for (int j = 0; j < N - i - 1; j++) {
      if (numbers_array[j] > numbers_array[j + 1]) {
        tmp = numbers_array[j];
        numbers_array[j] = numbers_array[j + 1];
        numbers_array[j + 1] = tmp;

      }

      Sleep(1);
      draw_rectangles(hDC);

    }

  }
}

void quick_sort(HDC hDC, int first, int last) {
  int i, j, pivot, temp;

  if (first < last) {
    pivot = first;
    i = first;
    j = last;

    while (i < j) {
      while (numbers_array[i] <= numbers_array[pivot] && i < last)
        i++;
      while (numbers_array[j] > numbers_array[pivot])
        j--;
      if (i < j) {
        temp = numbers_array[i];
        numbers_array[i] = numbers_array[j];
        numbers_array[j] = temp;
      }

      draw_rectangles(hDC);

    }

    temp = numbers_array[pivot];
    numbers_array[pivot] = numbers_array[j];
    numbers_array[j] = temp;
    quick_sort(hDC, first, j - 1);
    quick_sort(hDC, j + 1, last);

  }

}

void cocktail_sort(HDC hDC) {
  bool swapped = true;
  int start = 0;
  int end = N - 1;
  int tmp;

  while (swapped) {
    swapped = false;
    for (int i = start; i < end; ++i) {
      if (numbers_array[i] > numbers_array[i + 1]) {
        tmp = numbers_array[i];
        numbers_array[i] = numbers_array[i + 1];
        numbers_array[i + 1] = tmp;
        swapped = true;
      }
    }

    if (!swapped)
      break;

    swapped = false;

    --end;

    for (int i = end - 1; i >= start; --i) {
      if (numbers_array[i] > numbers_array[i + 1]) {
        tmp = numbers_array[i];
        numbers_array[i] = numbers_array[i + 1];
        numbers_array[i + 1] = tmp;
        swapped = true;

        //Sleep(1);
        draw_rectangles(hDC);
      }
    }
    ++start;
  }
}

void insertion_sort(HDC hDC) {
  int i, tmp, j;
  for (i = 1; i < N; i++) {
    tmp = numbers_array[i];
    j = i - 1;

    while (j >= 0 && numbers_array[j] > tmp) {
      numbers_array[j + 1] = numbers_array[j];
      j = j - 1;
    }
    numbers_array[j + 1] = tmp;

    draw_rectangles(hDC);
  }
}

/*function which draw rectangles*/
void draw_rectangles(HDC hDC) {
  double x1, x2, x3, x4,
      y1, y2, y3, y4;
  double r_width, r_height, interval;

  r_width = (area_length * coefficient / (coefficient * N + 1)) * 0.5; // width equation

  interval = r_width / coefficient; // interval equation

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();
  glTranslatef(-1, 0, 0);
  double i = 0;
  if (max_num() > 100)

    for (int j = 0; (j < N); j++) {

      r_height = (double) numbers_array[j] / max_num(); // height equation for numbers which bigger then 100

      x1 = i;
      y1 = 0;
      x2 = x1;
      y2 = y1 + r_height;
      x3 = x1 + r_width;
      y3 = y2;
      x4 = x3;
      y4 = y1;

      rectangle(x1, x2, x3, x4, y1, y2, y3, y4);
      i += (interval + r_width);
    }

  else {
    for (int j = 0; j < N; j++) {

      r_height = (double) numbers_array[j] / 100; // height equation for numbers which doesn't exceed 100
      x1 = i;
      y1 = 0;
      x2 = x1;
      y2 = y1 + r_height;
      x3 = x1 + r_width;
      y3 = y2;
      x4 = x3;
      y4 = y1;

      rectangle(x1, x2, x3, x4, y1, y2, y3, y4);
      i += (interval + r_width);

    }
  }

  glPopMatrix();
  SwapBuffers(hDC);
}

