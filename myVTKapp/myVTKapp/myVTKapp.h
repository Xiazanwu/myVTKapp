#pragma once
#include "windows.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"

static HANDLE hinst;
long FAR PASCAL WndProc(HWND, UINT, UINT, LONG);

class myVTKapp
{
public:
	myVTKapp(HWND parent);
	~myVTKapp();
private:
	vtkRenderWindow *renWin;
	vtkRenderer *renderer;
	vtkRenderWindowInteractor *iren;
	vtkConeSource *cone;
	vtkPolyDataMapper *coneMapper;
	vtkActor *coneActor;
};
