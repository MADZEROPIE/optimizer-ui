#pragma once

namespace optimizerui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;

	/// <summary>
	/// Summary for IsolinesGraphWindow
	/// </summary>
	public ref class IsolinesGraphWindow : public System::Windows::Forms::Form
	{
	public:
		IsolinesGraphWindow(array<unsigned char, 1>^ rawImage, int width, int height)
		{
			InitializeComponent();

			int crop = 200;
			height -= crop;

			Bitmap ^bmp = gcnew Bitmap(width, height, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
			Rectangle rect = Rectangle(0, 0, width, height);
			BitmapData ^bitmapData = bmp->LockBits(rect, ImageLockMode::WriteOnly, bmp->PixelFormat);
			IntPtr imgData = bitmapData->Scan0;
			System::Runtime::InteropServices::Marshal::Copy(rawImage, 0, imgData, rawImage->Length - width*crop*3);
			bmp->UnlockBits(bitmapData);

			graphPictureBox->Image = bmp;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~IsolinesGraphWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  graphPictureBox;
	private: System::Windows::Forms::SaveFileDialog^  savePictureDialog;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  Ù‡ÈÎToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
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
      this->graphPictureBox = (gcnew System::Windows::Forms::PictureBox());
      this->savePictureDialog = (gcnew System::Windows::Forms::SaveFileDialog());
      this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
      this->Ù‡ÈÎToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graphPictureBox))->BeginInit();
      this->menuStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // graphPictureBox
      // 
      this->graphPictureBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
      this->graphPictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
      this->graphPictureBox->Location = System::Drawing::Point(0, 24);
      this->graphPictureBox->Name = L"graphPictureBox";
      this->graphPictureBox->Size = System::Drawing::Size(594, 637);
      this->graphPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
      this->graphPictureBox->TabIndex = 0;
      this->graphPictureBox->TabStop = false;
      // 
      // savePictureDialog
      // 
      this->savePictureDialog->DefaultExt = L"png";
      this->savePictureDialog->Filter = L"PNG|*.png|BMP|*.bmp";
      this->savePictureDialog->Title = L"Save image";
      // 
      // menuStrip1
      // 
      this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->Ù‡ÈÎToolStripMenuItem });
      this->menuStrip1->Location = System::Drawing::Point(0, 0);
      this->menuStrip1->Name = L"menuStrip1";
      this->menuStrip1->Size = System::Drawing::Size(594, 24);
      this->menuStrip1->TabIndex = 1;
      this->menuStrip1->Text = L"menuStrip";
      // 
      // Ù‡ÈÎToolStripMenuItem
      // 
      this->Ù‡ÈÎToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->saveToolStripMenuItem });
      this->Ù‡ÈÎToolStripMenuItem->Name = L"Ù‡ÈÎToolStripMenuItem";
      this->Ù‡ÈÎToolStripMenuItem->Size = System::Drawing::Size(37, 20);
      this->Ù‡ÈÎToolStripMenuItem->Text = L"File";
      // 
      // saveToolStripMenuItem
      // 
      this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
      this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
      this->saveToolStripMenuItem->Size = System::Drawing::Size(138, 22);
      this->saveToolStripMenuItem->Text = L"Save";
      this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &IsolinesGraphWindow::saveToolStripMenuItem_Click);
      // 
      // IsolinesGraphWindow
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackColor = System::Drawing::SystemColors::ActiveBorder;
      this->ClientSize = System::Drawing::Size(594, 661);
      this->Controls->Add(this->graphPictureBox);
      this->Controls->Add(this->menuStrip1);
      this->MainMenuStrip = this->menuStrip1;
      this->MinimumSize = System::Drawing::Size(200, 200);
      this->Name = L"IsolinesGraphWindow";
      this->ShowIcon = false;
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"Isolines";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->graphPictureBox))->EndInit();
      this->menuStrip1->ResumeLayout(false);
      this->menuStrip1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
	private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (savePictureDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			graphPictureBox->Image->Save(savePictureDialog->FileName);
		}
	}
};
}
