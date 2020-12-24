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

			gklsDimentionNumericUpDown->Value = settings.GKLSDimention;

			currentSettings = %settings;
		}
	private: System::Windows::Forms::GroupBox^  gklsGroupBox;
	public:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  gklsDimentionNumericUpDown;

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
			this->gklsDimentionNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->gklsGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gklsDimentionNumericUpDown))->BeginInit();
			this->SuspendLayout();
			//
			// gklsGroupBox
			//
			this->gklsGroupBox->Controls->Add(this->label1);
			this->gklsGroupBox->Controls->Add(this->gklsDimentionNumericUpDown);
			this->gklsGroupBox->Location = System::Drawing::Point(12, 12);
			this->gklsGroupBox->Name = L"gklsGroupBox";
			this->gklsGroupBox->Size = System::Drawing::Size(332, 102);
			this->gklsGroupBox->TabIndex = 0;
			this->gklsGroupBox->TabStop = false;
			this->gklsGroupBox->Text = L"GKLS generator";
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Dimension:";
			//
			// gklsDimentionNumericUpDown
			//
			this->gklsDimentionNumericUpDown->Location = System::Drawing::Point(109, 18);
			this->gklsDimentionNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 6, 0, 0, 0 });
			this->gklsDimentionNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->gklsDimentionNumericUpDown->Name = L"gklsDimentionNumericUpDown";
			this->gklsDimentionNumericUpDown->Size = System::Drawing::Size(43, 20);
			this->gklsDimentionNumericUpDown->TabIndex = 0;
			this->gklsDimentionNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->gklsDimentionNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &TaskGeneratorSettingsWindow::gklsDimentionNumericUpDown_ValueChanged);
			//
			// TaskGeneratorSettingsWindow
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(353, 123);
			this->Controls->Add(this->gklsGroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(369, 162);
			this->MinimumSize = System::Drawing::Size(369, 162);
			this->Name = L"TaskGeneratorSettingsWindow";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings of problem generator";
			this->gklsGroupBox->ResumeLayout(false);
			this->gklsGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gklsDimentionNumericUpDown))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void gklsDimentionNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		if (currentSettings)
		{
			currentSettings->GKLSDimention = Convert::ToUInt32(gklsDimentionNumericUpDown->Value);
		}
	}
	};
}
