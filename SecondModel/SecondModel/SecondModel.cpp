// SecondModel.cpp : main project file.

#include "stdafx.h"
#include "Start_Page.h"

using namespace SecondModel;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Start_Page());
	return 0;
}
