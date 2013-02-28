#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

__gc class SimpleForm : public Form
{
public:
	SimpleForm();
private:
	PictureBox *PictBox;
};

SimpleForm::SimpleForm()
{
	// The caption of the form
	this->Text = S"Picture Box Example";

	PictBox = new PictureBox;
	PictBox->BorderStyle = BorderStyle::FixedSingle;
	PictBox->BackColor = Drawing::Color::White;
	PictBox->Location = Point(16, 16);
	PictBox->Size = Drawing::Size(240, 180);
	// After creating the control, add it to the
	// group of controls of the form
	Controls->Add(PictBox);
}

int __stdcall WinMain()
{
	SimpleForm *SF = new SimpleForm();
	Application::Run(SF);

	return 0;
}