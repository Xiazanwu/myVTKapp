#include "pch.h"
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
///////////////////////////////////
#include "myVTKapp.h"

myVTKapp::myVTKapp(HWND hwnd)
{
	// we create the basic parts of a pipeline and connect them
	this->renderer = vtkRenderer::New();
	this->renWin = vtkRenderWindow::New();
	this->renWin->AddRenderer(this->renderer);

	// setup the parent window
	this->renWin->SetParentId(hwnd);
	this->iren = vtkRenderWindowInteractor::New();
	this->iren->SetRenderWindow(this->renWin);

	//Data
	this->cone = vtkConeSource::New();
	this->cone->SetHeight(4.0);
	this->cone->SetRadius(2.0);
	this->cone->SetResolution(20);//???

	this->coneMapper = vtkPolyDataMapper::New();
	this->coneMapper->SetInputConnection(this->cone->GetOutputPort());
	this->coneActor = vtkActor::New();
	this->coneActor->SetMapper(this->coneMapper);
	////////
	this->renderer->AddActor(this->coneActor);
	this->renderer->SetBackground(0.2, 0.3, 0.4);
	this->renWin->SetSize(800, 800);

	//finally we start the interactor so that event will be handle
	this->renWin->Render();
}
myVTKapp::~myVTKapp()
{
	renWin->Delete();
	renderer->Delete();
	iren->Delete();

	cone->Delete();
	coneMapper->Delete();
	coneActor->Delete();

}

///////////////////////////////////////
//WinMain
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	static char szAppName[] = "Win32Cone";
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	if (!hPrevInstance)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.lpszMenuName = NULL;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszClassName = szAppName;
		RegisterClass(&wndclass);
	}
	hinst = hInstance;
	hwnd = CreateWindow(szAppName,
		"Draw Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		800,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

long FAR PASCAL WndProc(HWND hwnd, UINT message,
	UINT wParam, LONG lParam)
{
	static HWND ewin;
	static myVTKapp *theVTKApp;
	switch (message)
	{
	case WM_CREATE:
	{
		ewin = CreateWindow("button", "Exit",
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			0, 800, 800, 60,
			hwnd, (HMENU)2,
			(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
			NULL);
		theVTKApp = new myVTKapp(hwnd);
		return 0;
	}
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case 2:
			PostQuitMessage(0);
			if (theVTKApp)
			{
				delete theVTKApp;
				theVTKApp = NULL;
			}
			break;
		}
	}
	}
}
int main()
{
	return 0;
}