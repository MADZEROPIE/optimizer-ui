#using <System.dll>
#using <System.Windows.Forms.dll>
#include "MainWindow.h"

using namespace optimizerui;

[STAThreadAttribute]

int main(void)
{
    using namespace System;
    using namespace System::Windows::Forms;
    
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MainWindow window;
	  Application::Run(% window);
}