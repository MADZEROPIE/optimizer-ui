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
	/// Summary for AlgorhytnSettingsWindow
	/// </summary>
	public ref class AlgorithmSettingsWindow : public System::Windows::Forms::Form
	{
	public:
		AlgorithmSettingsWindow(AlgorithmSettings %settings)
		{
			InitializeComponent();

			localverificationCheckBox->Checked = settings.localVerification;
			locPowNumericUpDown->Value = settings.alpha;
			localTrackBar->Value = settings.localMix;
			startIterationNumericUpDown->Value = settings.localStartIteration;
			localAdaptationComboBox->SelectedIndex = settings.localAdaptationMode;

			currentSettings = %settings;
		}
	private: System::Windows::Forms::Label^  label1;
	public:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::NumericUpDown^  startIterationNumericUpDown;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  localverificationCheckBox;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::ComboBox^  localAdaptationComboBox;
	private: System::Windows::Forms::Label^  label7;






	protected:
		AlgorithmSettings ^currentSettings;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AlgorithmSettingsWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::NumericUpDown^  locPowNumericUpDown;
	protected:

	protected:
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TrackBar^  localTrackBar;
	private: System::Windows::Forms::Label^  label14;

	protected:

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
			this->locPowNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->localTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->startIterationNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->localverificationCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->localAdaptationComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->locPowNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->localTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->startIterationNumericUpDown))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			//
			// locPowNumericUpDown
			//
			this->locPowNumericUpDown->Location = System::Drawing::Point(213, 84);
			this->locPowNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->locPowNumericUpDown->Name = L"locPowNumericUpDown";
			this->locPowNumericUpDown->Size = System::Drawing::Size(58, 20);
			this->locPowNumericUpDown->TabIndex = 25;
			this->locPowNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
			this->locPowNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &AlgorithmSettingsWindow::locPowNumericUpDown_ValueChanged);
			//
			// label15
			//
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(7, 88);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(120, 13);
			this->label15->TabIndex = 24;
			this->label15->Text = L"Local tuning parameter:";
			//
			// localTrackBar
			//
			this->localTrackBar->LargeChange = 1;
			this->localTrackBar->Location = System::Drawing::Point(158, 25);
			this->localTrackBar->Maximum = 19;
			this->localTrackBar->Minimum = 1;
			this->localTrackBar->Name = L"localTrackBar";
			this->localTrackBar->Size = System::Drawing::Size(423, 45);
			this->localTrackBar->TabIndex = 23;
			this->localTrackBar->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->localTrackBar->Value = 10;
			this->localTrackBar->ValueChanged += gcnew System::EventHandler(this, &AlgorithmSettingsWindow::localTrackBar_ValueChanged);
			//
			// label14
			//
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 40);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(114, 13);
			this->label14->TabIndex = 22;
			this->label14->Text = L"Mix method:";
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(127, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 13);
			this->label1->TabIndex = 26;
			this->label1->Text = L"global";
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(542, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 13);
			this->label2->TabIndex = 27;
			this->label2->Text = L"local";
			//
			// label3
			//
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(360, 57);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(22, 13);
			this->label3->TabIndex = 28;
			this->label3->Text = L"1:1";
			//
			// label4
			//
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(155, 57);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(28, 13);
			this->label4->TabIndex = 29;
			this->label4->Text = L"10:1";
			//
			// label5
			//
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(559, 57);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(28, 13);
			this->label5->TabIndex = 30;
			this->label5->Text = L"1:10";
			//
			// label6
			//
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(7, 117);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(150, 13);
			this->label6->TabIndex = 31;
			this->label6->Text = L"Nubber of iterations before enable:";
			//
			// startIterationNumericUpDown
			//
			this->startIterationNumericUpDown->Location = System::Drawing::Point(213, 110);
			this->startIterationNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000000, 0, 0, 0 });
			this->startIterationNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->startIterationNumericUpDown->Name = L"startIterationNumericUpDown";
			this->startIterationNumericUpDown->Size = System::Drawing::Size(58, 20);
			this->startIterationNumericUpDown->TabIndex = 32;
			this->startIterationNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			this->startIterationNumericUpDown->ValueChanged += gcnew System::EventHandler(this, &AlgorithmSettingsWindow::startIterationNumericUpDown_ValueChanged);
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->startIterationNumericUpDown);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label15);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->locPowNumericUpDown);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->localTrackBar);
			this->groupBox1->Location = System::Drawing::Point(2, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(618, 136);
			this->groupBox1->TabIndex = 33;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Local tuned algorithm";
			//
			// localverificationCheckBox
			//
			this->localverificationCheckBox->AutoSize = true;
			this->localverificationCheckBox->Location = System::Drawing::Point(10, 19);
			this->localverificationCheckBox->Name = L"localverificationCheckBox";
			this->localverificationCheckBox->Size = System::Drawing::Size(229, 17);
			this->localverificationCheckBox->TabIndex = 33;
			this->localverificationCheckBox->Text = L"Local refinement of global solution";
			this->localverificationCheckBox->UseVisualStyleBackColor = true;
			this->localverificationCheckBox->CheckedChanged += gcnew System::EventHandler(this, &AlgorithmSettingsWindow::localverificationCheckBox_CheckedChanged);
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->localAdaptationComboBox);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->localverificationCheckBox);
			this->groupBox2->Location = System::Drawing::Point(2, 143);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(618, 77);
			this->groupBox2->TabIndex = 34;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Other settings";
			//
			// localAdaptationComboBox
			//
			this->localAdaptationComboBox->FormattingEnabled = true;
			this->localAdaptationComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"global", L"local additive", L"local additive-adaptive" });
			this->localAdaptationComboBox->Location = System::Drawing::Point(205, 46);
			this->localAdaptationComboBox->Name = L"localAdaptationComboBox";
			this->localAdaptationComboBox->Size = System::Drawing::Size(150, 21);
			this->localAdaptationComboBox->TabIndex = 34;
			this->localAdaptationComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &AlgorithmSettingsWindow::localAdaptationComboBox_SelectedIndexChanged);
			//
			// label7
			//
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(10, 49);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(189, 13);
			this->label7->TabIndex = 33;
			this->label7->Text = L"Method of Holder constant evaluation:";
			//
			// AlgorithmSettingsWindow
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(622, 226);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(638, 265);
			this->MinimumSize = System::Drawing::Size(638, 265);
			this->Name = L"AlgorithmSettingsWindow";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Settings of algorithm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->locPowNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->localTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->startIterationNumericUpDown))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void locPowNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		if (currentSettings)
			currentSettings->alpha = Convert::ToInt32(locPowNumericUpDown->Value);
	}
private: System::Void localTrackBar_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (currentSettings)
		currentSettings->localMix = localTrackBar->Value;
}
private: System::Void startIterationNumericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (currentSettings)
		currentSettings->localStartIteration = Convert::ToInt32(startIterationNumericUpDown->Value);
}
private: System::Void localverificationCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (currentSettings)
		currentSettings->localVerification = !currentSettings->localVerification;
}
private: System::Void localAdaptationComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (currentSettings)
		currentSettings->localAdaptationMode = localAdaptationComboBox->SelectedIndex;
}
};
}
