#pragma once

namespace optimizerui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for OneDimGraphWindow
	/// </summary>
	public ref class OneDimGraphWindow : public System::Windows::Forms::Form
	{
	public:
		OneDimGraphWindow(array<float, 1>^ xRay, array<float, 1>^ yRay, String^ graphTitle, array<float, 2>^ searchSequence)
		{
			InitializeComponent();
      this->mapChart->ChartAreas[0]->AxisX->LabelStyle->Format = "{0:0.00}";

			int arraySize = xRay->GetLength(0);
			double max = yRay[0], min = yRay[0];

			for (int i = 0; i < arraySize; i++)
			{
				mapChart->Series["Series1"]->Points->AddXY(xRay[i], yRay[i]);
				if (yRay[i] < min)
					min = yRay[i];
				if (yRay[i] > max)
					max = yRay[i];
			}

			mapChart->Series["Series1"]->ChartType = SeriesChartType::Line;
			mapChart->Series["Series1"]->Name = graphTitle;

			if (searchSequence)
			{
				Series^  series2 = gcnew Series();
				series2->Name = "Series2";
				mapChart->Series->Add(series2);
				mapChart->Series["Series2"]->ChartType = SeriesChartType::Point;
				mapChart->Series["Series2"]->Color = Color::Red;

				int searchInfSize = searchSequence->GetLength(1);
				for (int i = 0; i < searchInfSize; i++)
					mapChart->Series["Series2"]->Points->AddXY(searchSequence[0, i], searchSequence[1, i]);

				mapChart->Series["Series2"]->Name = "Trials points";
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OneDimGraphWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  mapChart;
  private: System::Windows::Forms::MenuStrip^  menuStrip1;
  private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
  private: System::Windows::Forms::SaveFileDialog^  saveGraphDialog;
  protected:

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
      System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
      System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
      System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
      this->mapChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
      this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
      this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
      this->saveGraphDialog = (gcnew System::Windows::Forms::SaveFileDialog());
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mapChart))->BeginInit();
      this->menuStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // mapChart
      // 
      chartArea1->AxisX->MajorGrid->Interval = 0;
      chartArea1->Name = L"ChartArea1";
      this->mapChart->ChartAreas->Add(chartArea1);
      this->mapChart->Dock = System::Windows::Forms::DockStyle::Fill;
      legend1->Alignment = System::Drawing::StringAlignment::Far;
      legend1->DockedToChartArea = L"ChartArea1";
      legend1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
      legend1->IsDockedInsideChartArea = false;
      legend1->LegendStyle = System::Windows::Forms::DataVisualization::Charting::LegendStyle::Row;
      legend1->MaximumAutoSize = 60;
      legend1->Name = L"Legend1";
      this->mapChart->Legends->Add(legend1);
      this->mapChart->Location = System::Drawing::Point(0, 24);
      this->mapChart->Name = L"mapChart";
      series1->ChartArea = L"ChartArea1";
      series1->Legend = L"Legend1";
      series1->Name = L"Series1";
      this->mapChart->Series->Add(series1);
      this->mapChart->Size = System::Drawing::Size(583, 360);
      this->mapChart->TabIndex = 0;
      this->mapChart->Text = L"chart1";
      // 
      // menuStrip1
      // 
      this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
      this->menuStrip1->Location = System::Drawing::Point(0, 0);
      this->menuStrip1->Name = L"menuStrip1";
      this->menuStrip1->Size = System::Drawing::Size(583, 24);
      this->menuStrip1->TabIndex = 1;
      this->menuStrip1->Text = L"menuStrip1";
      // 
      // fileToolStripMenuItem
      // 
      this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->saveToolStripMenuItem });
      this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
      this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
      this->fileToolStripMenuItem->Text = L"File";
      // 
      // saveToolStripMenuItem
      // 
      this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
      this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
      this->saveToolStripMenuItem->Size = System::Drawing::Size(138, 22);
      this->saveToolStripMenuItem->Text = L"Save";
      this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &OneDimGraphWindow::saveToolStripMenuItem_Click);
      // 
      // saveGraphDialog
      // 
      this->saveGraphDialog->DefaultExt = L"png";
      this->saveGraphDialog->Filter = L"PNG|*.png";
      // 
      // OneDimGraphWindow
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(583, 384);
      this->Controls->Add(this->mapChart);
      this->Controls->Add(this->menuStrip1);
      this->MainMenuStrip = this->menuStrip1;
      this->MinimumSize = System::Drawing::Size(200, 150);
      this->Name = L"OneDimGraphWindow";
      this->ShowIcon = false;
      this->Text = L"One dimensional graph";
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mapChart))->EndInit();
      this->menuStrip1->ResumeLayout(false);
      this->menuStrip1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    if (saveGraphDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
      mapChart->SaveImage(saveGraphDialog->FileName, ChartImageFormat::Png);
  }
};
}
