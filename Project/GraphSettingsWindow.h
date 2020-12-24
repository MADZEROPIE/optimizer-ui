#pragma once
#include "SettingsClasses.h"
namespace optimizerui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GraphSettingsWindow
	/// </summary>
	public ref class GraphSettingsWindow : public System::Windows::Forms::Form
	{
	public:
		GraphSettingsWindow(GraphSettings %settings)
		{
			InitializeComponent();
			this->numbersCheckBox->Checked = settings.numersOnIsolinesPlot;
			this->colorCheckBox->Checked = settings.isIsolinesColored;
			this->isGraphwindowModalCheckBox->Checked = settings.isGraphAppearsInNewWindow;
			this->showOneDimGraphCheckBox->Checked = settings.showOneDimSolutionGraph;
			currentSettings = %settings;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GraphSettingsWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:
	private: System::Windows::Forms::CheckBox^  numbersCheckBox;
	private: System::Windows::Forms::CheckBox^  colorCheckBox;
			 GraphSettings ^currentSettings;
	private: System::Windows::Forms::CheckBox^  isGraphwindowModalCheckBox;
	private: System::Windows::Forms::CheckBox^  showOneDimGraphCheckBox;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->isGraphwindowModalCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->numbersCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->colorCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->showOneDimGraphCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->showOneDimGraphCheckBox);
			this->panel1->Controls->Add(this->isGraphwindowModalCheckBox);
			this->panel1->Controls->Add(this->numbersCheckBox);
			this->panel1->Controls->Add(this->colorCheckBox);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(375, 101);
			this->panel1->TabIndex = 0;
			//
			// isGraphwindowModalÑheckBox
			//
			this->isGraphwindowModalCheckBox->AutoSize = true;
			this->isGraphwindowModalCheckBox->Location = System::Drawing::Point(12, 57);
			this->isGraphwindowModalCheckBox->Name = L"isGraphwindowModalÑheckBox";
			this->isGraphwindowModalCheckBox->Size = System::Drawing::Size(327, 17);
			this->isGraphwindowModalCheckBox->TabIndex = 4;
			this->isGraphwindowModalCheckBox->Text = L"Show graphs in new windows";
			this->isGraphwindowModalCheckBox->UseVisualStyleBackColor = true;
			this->isGraphwindowModalCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GraphSettingsWindow::isGraphwindowModalCheckBox_CheckedChanged);
			//
			// numbersCheckBox
			//
			this->numbersCheckBox->AutoSize = true;
			this->numbersCheckBox->Location = System::Drawing::Point(12, 35);
			this->numbersCheckBox->Name = L"numbersCheckBox";
			this->numbersCheckBox->Size = System::Drawing::Size(282, 17);
			this->numbersCheckBox->TabIndex = 3;
			this->numbersCheckBox->Text = L"Show values on isolines plot";
			this->numbersCheckBox->UseVisualStyleBackColor = true;
			this->numbersCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GraphSettingsWindow::numbersCheckBox_CheckedChanged);
			//
			// colorCheckBox
			//
			this->colorCheckBox->AutoSize = true;
			this->colorCheckBox->Location = System::Drawing::Point(12, 12);
			this->colorCheckBox->Name = L"colorCheckBox";
			this->colorCheckBox->Size = System::Drawing::Size(142, 17);
			this->colorCheckBox->TabIndex = 2;
			this->colorCheckBox->Text = L"Colored isolines";
			this->colorCheckBox->UseVisualStyleBackColor = true;
			this->colorCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GraphSettingsWindow::colorCheckBox_CheckedChanged);
			//
			// showOneDimGraphCheckBox
			//
			this->showOneDimGraphCheckBox->AutoSize = true;
			this->showOneDimGraphCheckBox->Location = System::Drawing::Point(12, 80);
			this->showOneDimGraphCheckBox->Name = L"showOneDimGraphCheckBox";
			this->showOneDimGraphCheckBox->Size = System::Drawing::Size(243, 17);
			this->showOneDimGraphCheckBox->TabIndex = 5;
			this->showOneDimGraphCheckBox->Text = L"Show one dimentional graph of solution";
			this->showOneDimGraphCheckBox->UseVisualStyleBackColor = true;
			this->showOneDimGraphCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GraphSettingsWindow::showOneDimGraphCheckBox_CheckedChanged);
			//
			// GraphSettingsWindow
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(375, 101);
			this->Controls->Add(this->panel1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(391, 140);
			this->MinimumSize = System::Drawing::Size(391, 140);
			this->Name = L"GraphSettingsWindow";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings of gaphs";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void colorCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (currentSettings)
			currentSettings->isIsolinesColored = !currentSettings->isIsolinesColored;
	}
	private: System::Void numbersCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (currentSettings)
			currentSettings->numersOnIsolinesPlot = !currentSettings->numersOnIsolinesPlot;
	}
	private: System::Void isGraphwindowModalCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (currentSettings)
			currentSettings->isGraphAppearsInNewWindow = !currentSettings->isGraphAppearsInNewWindow;
	}
private: System::Void showOneDimGraphCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (currentSettings)
		currentSettings->showOneDimSolutionGraph = !currentSettings->showOneDimSolutionGraph;
}
};
}
