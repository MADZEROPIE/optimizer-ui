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
	/// Summary for TaskGeneratorSettingsWindow
	/// </summary>
	public ref class TaskGeneratorSettingsWindow : public System::Windows::Forms::Form
	{
	public:
		TaskGeneratorSettingsWindow(TaskGeneratorSettings %settings)
		{
			InitializeComponent();

			gklsDimensionNumericUpDown->Value = settings.GKLSDimension;
			dllPathTextBox->Text = settings.dllPath;

			currentSettings = %settings;
		}
	private: System::Windows::Forms::GroupBox^  gklsGroupBox;
	public:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  gklsDimensionNumericUpDown;
	private: System::Windows::Forms::GroupBox^ customGroupBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ dllPathTextBox;

	protected:
		TaskGeneratorSettings ^currentSettings;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TaskGeneratorSettingsWindow()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->gklsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->gklsDimensionNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->customGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->dllPathTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->gklsGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gklsDimensionNumericUpDown))->BeginInit();
			this->customGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// gklsGroupBox
			// 
			this->gklsGroupBox->Controls->Add(this->label1);
			this->gklsGroupBox->Controls->Add(this->gklsDimensionNumericUpDown);
			this->gklsGroupBox->Location = System::Drawing::Point(12, 12);
			this->gklsGroupBox->Name = L"gklsGroupBox";
			this->gklsGroupBox->Size = System::Drawing::Size(332, 51);
			this->gklsGroupBox->TabIndex = 0;
			this->gklsGroupBox->TabStop = false;
			this->gklsGroupBox->Text = L"GKLS generator";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Dimension:";
			// 
			// gklsDimensionNumericUpDown
			// 
			this->gklsDimensionNumericUpDown->Location = System::Drawing::Point(109, 18);
			this->gklsDimensionNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
			this->gklsDimensionNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->gklsDimensionNumericUpDown->Name = L"gklsDimensionNumericUpDown";
			this->gklsDimensionNumericUpDown->Size = System::Drawing::Size(43, 20);
			this->gklsDimensionNumericUpDown->TabIndex = 0;
			this->gklsDimensionNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->gklsDimensionNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &TaskGeneratorSettingsWindow::gklsDimensionNumericUpDown_ValueChanged);
			// 
			// customGroupBox
			// 
			this->customGroupBox->Controls->Add(this->dllPathTextBox);
			this->customGroupBox->Controls->Add(this->label2);
			this->customGroupBox->Location = System::Drawing::Point(12, 80);
			this->customGroupBox->Name = L"customGroupBox";
			this->customGroupBox->Size = System::Drawing::Size(332, 51);
			this->customGroupBox->TabIndex = 2;
			this->customGroupBox->TabStop = false;
			this->customGroupBox->Text = L"Custom problem loader";
			// 
			// dllPathTextBox
			// 
			this->dllPathTextBox->Location = System::Drawing::Point(109, 19);
			this->dllPathTextBox->Name = L"dllPathTextBox";
			this->dllPathTextBox->Size = System::Drawing::Size(217, 20);
			this->dllPathTextBox->TabIndex = 2;
			this->dllPathTextBox->TextChanged += gcnew System::EventHandler(this, &TaskGeneratorSettingsWindow::dllPathTextBox_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"DLL path:";
			// 
			// TaskGeneratorSettingsWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(353, 153);
			this->Controls->Add(this->customGroupBox);
			this->Controls->Add(this->gklsGroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(369, 192);
			this->MinimumSize = System::Drawing::Size(369, 192);
			this->Name = L"TaskGeneratorSettingsWindow";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings of problem generator";
			this->gklsGroupBox->ResumeLayout(false);
			this->gklsGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gklsDimensionNumericUpDown))->EndInit();
			this->customGroupBox->ResumeLayout(false);
			this->customGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void gklsDimensionNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		if (currentSettings)
		{
			currentSettings->GKLSDimension = Convert::ToUInt32(gklsDimensionNumericUpDown->Value);
		}
	}
	private: System::Void dllPathTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings)
		{
			currentSettings->dllPath = dllPathTextBox->Text;
		}
	}
};
}
