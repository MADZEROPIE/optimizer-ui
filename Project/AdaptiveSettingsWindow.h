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
	/// Сводка для MyForm
	/// </summary>
	public ref class AdaptiveSettingsWindow : public System::Windows::Forms::Form
	{
	public:
		AdaptiveSettingsWindow(AdaptiveNestedSettings% settings, LanguageSettings %lan)
		{
			InitializeComponent();
			radioButton1->Checked = settings.globalM;
			radioButton2->Checked = settings.localM;
			radioButton3->Checked = settings.levelM;
			radioButton4->Checked = settings.adaptiveM;

			radioButton7->Checked = settings.noneZ;
			radioButton5->Checked = settings.localZ;
			radioButton6->Checked = settings.globalZ;

			radioButton8->Checked = settings.halfPnt;
			radioButton9->Checked = settings.medianPnt;

            radioButton10->Checked = settings.notMonotonous;
            radioButton11->Checked = settings.Monotonous;

			currentSettings = %settings;
			languageSettings = % lan;
			setLanguage();
		}

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::RadioButton^ radioButton6;
	private: System::Windows::Forms::RadioButton^ radioButton5;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RadioButton^ radioButton7;
	private: System::Windows::Forms::RadioButton^ radioButton8;
	private: System::Windows::Forms::RadioButton^ radioButton9;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::RadioButton^ radioButton4;




	public:

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		AdaptiveNestedSettings^ currentSettings;

        private:
                System::Windows::Forms::Label ^ label4;

            protected:
            private:
                System::Windows::Forms::Panel ^ panel4;

            private:
                System::Windows::Forms::RadioButton ^ radioButton10;

            private:
            System::Windows::Forms::RadioButton ^ radioButton11;
            LanguageSettings ^ languageSettings;
		~AdaptiveSettingsWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::Label^ label1;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
                    this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
                    this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
                    this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
                    this->label1 = (gcnew System::Windows::Forms::Label());
                    this->panel1 = (gcnew System::Windows::Forms::Panel());
                    this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
                    this->panel2 = (gcnew System::Windows::Forms::Panel());
                    this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
                    this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
                    this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
                    this->label2 = (gcnew System::Windows::Forms::Label());
                    this->radioButton8 = (gcnew System::Windows::Forms::RadioButton());
                    this->radioButton9 = (gcnew System::Windows::Forms::RadioButton());
                    this->label3 = (gcnew System::Windows::Forms::Label());
                    this->panel3 = (gcnew System::Windows::Forms::Panel());
                    this->label4 = (gcnew System::Windows::Forms::Label());
                    this->panel4 = (gcnew System::Windows::Forms::Panel());
                    this->radioButton10 = (gcnew System::Windows::Forms::RadioButton());
                    this->radioButton11 = (gcnew System::Windows::Forms::RadioButton());
                    this->panel1->SuspendLayout();
                    this->panel2->SuspendLayout();
                    this->panel3->SuspendLayout();
                    this->panel4->SuspendLayout();
                    this->SuspendLayout();
                    //
                    // radioButton1
                    //
                    this->radioButton1->AutoSize = true;
                    this->radioButton1->Location = System::Drawing::Point(3, 3);
                    this->radioButton1->Name = L"radioButton1";
                    this->radioButton1->Size = System::Drawing::Size(119, 17);
                    this->radioButton1->TabIndex = 0;
                    this->radioButton1->TabStop = true;
                    this->radioButton1->Text = L"Global (all subtasks)";
                    this->radioButton1->UseVisualStyleBackColor = true;
                    this->radioButton1->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton1_CheckedChanged);
                    //
                    // radioButton2
                    //
                    this->radioButton2->AutoSize = true;
                    this->radioButton2->Location = System::Drawing::Point(3, 26);
                    this->radioButton2->Name = L"radioButton2";
                    this->radioButton2->Size = System::Drawing::Size(77, 17);
                    this->radioButton2->TabIndex = 1;
                    this->radioButton2->TabStop = true;
                    this->radioButton2->Text = L"Single-task";
                    this->radioButton2->UseVisualStyleBackColor = true;
                    this->radioButton2->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton2_CheckedChanged);
                    //
                    // radioButton3
                    //
                    this->radioButton3->AutoSize = true;
                    this->radioButton3->Location = System::Drawing::Point(3, 49);
                    this->radioButton3->Name = L"radioButton3";
                    this->radioButton3->Size = System::Drawing::Size(91, 17);
                    this->radioButton3->TabIndex = 2;
                    this->radioButton3->TabStop = true;
                    this->radioButton3->Text = L"Level of tasks";
                    this->radioButton3->UseVisualStyleBackColor = true;
                    this->radioButton3->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton3_CheckedChanged);
                    //
                    // label1
                    //
                    this->label1->AutoSize = true;
                    this->label1->Location = System::Drawing::Point(12, 13);
                    this->label1->Name = L"label1";
                    this->label1->Size = System::Drawing::Size(157, 13);
                    this->label1->TabIndex = 3;
                    this->label1->Text = L"Evaluation of Lipschitz constant";
                    //
                    // panel1
                    //
                    this->panel1->Controls->Add(this->radioButton4);
                    this->panel1->Controls->Add(this->radioButton1);
                    this->panel1->Controls->Add(this->radioButton2);
                    this->panel1->Controls->Add(this->radioButton3);
                    this->panel1->Location = System::Drawing::Point(15, 29);
                    this->panel1->Name = L"panel1";
                    this->panel1->Size = System::Drawing::Size(200, 93);
                    this->panel1->TabIndex = 5;
                    //
                    // radioButton4
                    //
                    this->radioButton4->AutoSize = true;
                    this->radioButton4->Location = System::Drawing::Point(3, 72);
                    this->radioButton4->Name = L"radioButton4";
                    this->radioButton4->Size = System::Drawing::Size(67, 17);
                    this->radioButton4->TabIndex = 3;
                    this->radioButton4->TabStop = true;
                    this->radioButton4->Text = L"Adaptive";
                    this->radioButton4->UseVisualStyleBackColor = true;
                    this->radioButton4->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton4_CheckedChanged);
                    //
                    // panel2
                    //
                    this->panel2->Controls->Add(this->radioButton7);
                    this->panel2->Controls->Add(this->radioButton6);
                    this->panel2->Controls->Add(this->radioButton5);
                    this->panel2->Location = System::Drawing::Point(247, 32);
                    this->panel2->Name = L"panel2";
                    this->panel2->Size = System::Drawing::Size(101, 72);
                    this->panel2->TabIndex = 6;
                    //
                    // radioButton7
                    //
                    this->radioButton7->AutoSize = true;
                    this->radioButton7->Location = System::Drawing::Point(4, 3);
                    this->radioButton7->Name = L"radioButton7";
                    this->radioButton7->Size = System::Drawing::Size(51, 17);
                    this->radioButton7->TabIndex = 2;
                    this->radioButton7->TabStop = true;
                    this->radioButton7->Text = L"None";
                    this->radioButton7->UseVisualStyleBackColor = true;
                    this->radioButton7->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton7_CheckedChanged);
                    //
                    // radioButton6
                    //
                    this->radioButton6->AutoSize = true;
                    this->radioButton6->Location = System::Drawing::Point(4, 46);
                    this->radioButton6->Name = L"radioButton6";
                    this->radioButton6->Size = System::Drawing::Size(64, 17);
                    this->radioButton6->TabIndex = 1;
                    this->radioButton6->TabStop = true;
                    this->radioButton6->Text = L"All tasks";
                    this->radioButton6->UseVisualStyleBackColor = true;
                    this->radioButton6->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton6_CheckedChanged);
                    //
                    // radioButton5
                    //
                    this->radioButton5->AutoSize = true;
                    this->radioButton5->Location = System::Drawing::Point(4, 23);
                    this->radioButton5->Name = L"radioButton5";
                    this->radioButton5->Size = System::Drawing::Size(77, 17);
                    this->radioButton5->TabIndex = 0;
                    this->radioButton5->TabStop = true;
                    this->radioButton5->Text = L"Single task";
                    this->radioButton5->UseVisualStyleBackColor = true;
                    this->radioButton5->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton5_CheckedChanged);
                    //
                    // label2
                    //
                    this->label2->AutoSize = true;
                    this->label2->Location = System::Drawing::Point(248, 13);
                    this->label2->Name = L"label2";
                    this->label2->Size = System::Drawing::Size(71, 13);
                    this->label2->TabIndex = 7;
                    this->label2->Text = L"Index method";
                    //
                    // radioButton8
                    //
                    this->radioButton8->AutoSize = true;
                    this->radioButton8->Location = System::Drawing::Point(3, 3);
                    this->radioButton8->Name = L"radioButton8";
                    this->radioButton8->Size = System::Drawing::Size(44, 17);
                    this->radioButton8->TabIndex = 8;
                    this->radioButton8->TabStop = true;
                    this->radioButton8->Text = L"Half";
                    this->radioButton8->UseVisualStyleBackColor = true;
                    this->radioButton8->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton8_CheckedChanged);
                    //
                    // radioButton9
                    //
                    this->radioButton9->AutoSize = true;
                    this->radioButton9->Location = System::Drawing::Point(3, 26);
                    this->radioButton9->Name = L"radioButton9";
                    this->radioButton9->Size = System::Drawing::Size(60, 17);
                    this->radioButton9->TabIndex = 9;
                    this->radioButton9->TabStop = true;
                    this->radioButton9->Text = L"Median";
                    this->radioButton9->UseVisualStyleBackColor = true;
                    this->radioButton9->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton9_CheckedChanged);
                    //
                    // label3
                    //
                    this->label3->AutoSize = true;
                    this->label3->Location = System::Drawing::Point(423, 13);
                    this->label3->Name = L"label3";
                    this->label3->Size = System::Drawing::Size(56, 13);
                    this->label3->TabIndex = 10;
                    this->label3->Text = L"New Point";
                    //
                    // panel3
                    //
                    this->panel3->Controls->Add(this->radioButton8);
                    this->panel3->Controls->Add(this->radioButton9);
                    this->panel3->Location = System::Drawing::Point(397, 32);
                    this->panel3->Name = L"panel3";
                    this->panel3->Size = System::Drawing::Size(120, 72);
                    this->panel3->TabIndex = 11;
                    //
                    // label4
                    //
                    this->label4->AutoSize = true;
                    this->label4->Location = System::Drawing::Point(570, 13);
                    this->label4->Name = L"label4";
                    this->label4->Size = System::Drawing::Size(66, 13);
                    this->label4->TabIndex = 12;
                    this->label4->Text = L"Monotonous";
                    this->label4->Click += gcnew System::EventHandler(this, &AdaptiveSettingsWindow::label4_Click);
                    //
                    // panel4
                    //
                    this->panel4->Controls->Add(this->radioButton10);
                    this->panel4->Controls->Add(this->radioButton11);
                    this->panel4->Location = System::Drawing::Point(537, 32);
                    this->panel4->Name = L"panel4";
                    this->panel4->Size = System::Drawing::Size(120, 72);
                    this->panel4->TabIndex = 13;
                    //
                    // radioButton10
                    //
                    this->radioButton10->AutoSize = true;
                    this->radioButton10->Location = System::Drawing::Point(3, 3);
                    this->radioButton10->Name = L"radioButton10";
                    this->radioButton10->Size = System::Drawing::Size(39, 17);
                    this->radioButton10->TabIndex = 8;
                    this->radioButton10->TabStop = true;
                    this->radioButton10->Text = L"No";
                    this->radioButton10->UseVisualStyleBackColor = true;
                    this->radioButton10->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton10_CheckedChanged);
                    //
                    // radioButton11
                    //
                    this->radioButton11->AutoSize = true;
                    this->radioButton11->Location = System::Drawing::Point(3, 26);
                    this->radioButton11->Name = L"radioButton11";
                    this->radioButton11->Size = System::Drawing::Size(84, 17);
                    this->radioButton11->TabIndex = 9;
                    this->radioButton11->TabStop = true;
                    this->radioButton11->Text = L"Monotonous";
                    this->radioButton11->UseVisualStyleBackColor = true;
                    this->radioButton11->CheckedChanged +=
                        gcnew System::EventHandler(this, &AdaptiveSettingsWindow::radioButton11_CheckedChanged);
                    //
                    // AdaptiveSettingsWindow
                    //
                    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                    this->ClientSize = System::Drawing::Size(659, 134);
                    this->Controls->Add(this->panel4);
                    this->Controls->Add(this->label4);
                    this->Controls->Add(this->panel3);
                    this->Controls->Add(this->label3);
                    this->Controls->Add(this->label2);
                    this->Controls->Add(this->panel2);
                    this->Controls->Add(this->panel1);
                    this->Controls->Add(this->label1);
                    this->Name = L"AdaptiveSettingsWindow";
                    this->Text = L"Adaptive Nested Scheme Settings";
                    this->panel1->ResumeLayout(false);
                    this->panel1->PerformLayout();
                    this->panel2->ResumeLayout(false);
                    this->panel2->PerformLayout();
                    this->panel3->ResumeLayout(false);
                    this->panel3->PerformLayout();
                    this->panel4->ResumeLayout(false);
                    this->panel4->PerformLayout();
                    this->ResumeLayout(false);
                    this->PerformLayout();
                }
#pragma endregion
	// Lipshitz Constant
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->globalM = radioButton1->Checked;  // Should be enough, but why not ?
			currentSettings->localM = radioButton2->Checked;
			currentSettings->levelM = radioButton3->Checked;
			currentSettings->adaptiveM = radioButton4->Checked;
		}
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->globalM = radioButton1->Checked;
			currentSettings->localM = radioButton2->Checked;
			currentSettings->levelM = radioButton3->Checked;
			currentSettings->adaptiveM = radioButton4->Checked;
		}
	}
	private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->globalM = radioButton1->Checked;
			currentSettings->localM = radioButton2->Checked;
			currentSettings->levelM = radioButton3->Checked;
			currentSettings->adaptiveM = radioButton4->Checked;
		}
	}
	private: System::Void radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->globalM = radioButton1->Checked;
			currentSettings->localM = radioButton2->Checked;
			currentSettings->levelM = radioButton3->Checked;
			currentSettings->adaptiveM = radioButton4->Checked;
		}
	}
	// Index method
	private: System::Void radioButton7_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->noneZ = radioButton7->Checked;
			currentSettings->localZ = radioButton5->Checked;
			currentSettings->globalZ = radioButton6->Checked;
		}
	}
	private: System::Void radioButton5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->noneZ = radioButton7->Checked;
			currentSettings->localZ = radioButton5->Checked;
			currentSettings->globalZ = radioButton6->Checked;
		}
	}
	private: System::Void radioButton6_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->noneZ = radioButton7->Checked;
			currentSettings->localZ = radioButton5->Checked;
			currentSettings->globalZ = radioButton6->Checked;
		}
	}
	// New point
	private: System::Void radioButton8_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->halfPnt = radioButton8->Checked;
			currentSettings->medianPnt = radioButton9->Checked;
		}
	}
	private: System::Void radioButton9_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (currentSettings) {
			currentSettings->halfPnt = radioButton8->Checked;
			currentSettings->medianPnt = radioButton9->Checked;
		}
    }

    private:  System::Void radioButton10_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e) {
            if (currentSettings) {
                currentSettings->notMonotonous = radioButton10->Checked;
                currentSettings->Monotonous = radioButton11->Checked;
            }
    }

    private:
        System::Void radioButton11_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e) {
            if (currentSettings) {
                currentSettings->notMonotonous = radioButton10->Checked;
                currentSettings->Monotonous = radioButton11->Checked;
            }
        }
	private: System::Void setLanguage() {
		if (languageSettings) {
			if (languageSettings->english) {
				this->Text = L"Adaptive Nested Scheme Settings";
			}
			else {
				this->Text = L"Настройки адаптивной вложенной схемы";
			}
		}
	}

private:
        System::Void label4_Click(System::Object ^ sender, System::EventArgs ^ e) {
        }


            };
            }
