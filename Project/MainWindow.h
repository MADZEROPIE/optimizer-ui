#pragma once
#include "OptimizerAlgorithm.hpp"
#include "OptimizerSpaceTransformation.hpp"
#include "OptimizerAlgorithmUnconstrained.hpp"
#include "CoreUtils.hpp"
#include "problem_manager.h"
#include "OptimizerFunctionWrappers.h"

#include "GraphSettingsWindow.h"
#include "AlgorithmSettingsWindow.h"
#include "LogWindow.h"
#include "OneDimGraphWindow.h"
#include "IsolinesGraphWindow.h"
#include "TaskGeneratorSettingsWindow.h"

#using <disnet.dll>

#include <msclr/marshal_cppstd.h>
#include <string>

using namespace optimizercore;

namespace optimizerui {

  using namespace System;
  using namespace System::Diagnostics;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::Windows::Forms::DataVisualization::Charting;
  using namespace System::Globalization;
  using namespace System::Threading;

  public ref class MainWindow : public System::Windows::Forms::Form
  {
  public:
    MainWindow(void)
    {
      mErrorValueString = gcnew String(" ");
      InitializeComponent();

      series_count = mCurrentTaskNumber = 0;
      currentSequence = nullptr;
      mAlgorithmSettings.localMix = 10;
      mCurrentAlgParams = new OptimizerParameters();
      mCurrentAlgParams->r = new double;
      mCurrentAlgParams->reserves = new double;

      MyCI = gcnew CultureInfo("ru-RU", false);
      nfi = MyCI->NumberFormat;
      nfi->NumberDecimalDigits = 10;
      nfi->NumberDecimalSeparator = ".";

      ExperimentsLog = gcnew String("");
      MapTypeComboBox->SelectedIndex = 0;
      saveFileDialog->InitialDirectory = System::IO::Directory::GetCurrentDirectory();
      saveFileDialog->Filter = "CSV file|*.csv";
    }

  protected:
    ~MainWindow()
    {
      if (components)
      {
        delete components;
      }
      if (currentSequence)
        delete currentSequence;
      delete mCurrentAlgParams->r;
      delete mCurrentAlgParams->reserves;
      delete mCurrentAlgParams;
    }
  private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
  private: System::Windows::Forms::Button^  solveSerieButton;



  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::GroupBox^  groupBox1;
  private: System::Windows::Forms::NumericUpDown^  map_tightness;

  private: System::Windows::Forms::NumericUpDown^  reliability_coeff;


  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::TextBox^  prec_text;
  private: System::Windows::Forms::Label^  label4;
  private: System::Windows::Forms::ProgressBar^  progressBar1;
  private: System::Windows::Forms::Button^  clear_button;
  private: System::Windows::Forms::Button^  drawIsolinesButton;

  private: System::ComponentModel::BackgroundWorker^  solveTaskSerieBackgroundWorker;

  private:
    int max_it_count, series_count, map_type, mCurrentTaskNumber;
    CultureInfo^ MyCI;
    NumberFormatInfo^ nfi;
    String^ ExperimentsLog, ^mErrorValueString;
    array<int, 1>^ mOperationCharacteristicData;
    GraphSettings mGraphSettings;
    AlgorithmSettings mAlgorithmSettings;
    TaskGeneratorSettings mTaskGeneratorSettings;
    OptimizerSearchSequence* currentSequence;
    OneDimGraphWindow^ mOneDimGraph;
    IsolinesGraphWindow^ mIsolinesGraph;
    OptimizerParameters *mCurrentAlgParams;

  private: System::Windows::Forms::NumericUpDown^  max_it_num;

  private: System::Windows::Forms::Label^  label5;
  private: System::Windows::Forms::GroupBox^  groupBox2;
  private: System::Windows::Forms::Label^  label6;
  private: System::Windows::Forms::Button^  solveSingleTaskButton;


  private: System::Windows::Forms::NumericUpDown^  task_number;

  private: System::Windows::Forms::GroupBox^  groupBox3;
  private: System::Windows::Forms::Label^  label8;
  private: System::Windows::Forms::Label^  label7;
  private: System::Windows::Forms::Label^  task_val_lbl;
  private: System::Windows::Forms::Label^  task_answ_lbl;
  private: System::Windows::Forms::Label^  it_count_lbl;
  private: System::Windows::Forms::Label^  label9;
  private: System::Windows::Forms::Label^  label10;
  private: System::Windows::Forms::Label^  error_val;
  private: System::Windows::Forms::CheckBox^  graph_checkBox;
  private: System::Windows::Forms::Button^  ShowLogButton;
  private: System::Windows::Forms::Label^  error_xy;
  private: System::Windows::Forms::Label^  label12;

  private: System::Windows::Forms::Label^  label11;
  private: System::Windows::Forms::ComboBox^  MapTypeComboBox;
  private: System::Windows::Forms::Button^  OneDimGraphButton;
  private: System::Windows::Forms::RadioButton^  gklsRadioButton2;

  private: System::Windows::Forms::RadioButton^  grishaginRadioButton;

  private: System::Windows::Forms::Label^  label13;



  private: System::Windows::Forms::RadioButton^  gklsHardRadioButton;



  private: System::Windows::Forms::CheckBox^  stopCheckBox;
  private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
  private: System::Windows::Forms::Panel^  panel1;
  private: System::Windows::Forms::Panel^  panel2;
  private: System::Windows::Forms::NumericUpDown^  threadsNumNumericUpDown;
  private: System::Windows::Forms::Label^  label16;
  private: System::Windows::Forms::MenuStrip^  menuStrip1;
  private: System::Windows::Forms::ToolStripMenuItem^  advSettingsToolStripMenuItem;
  private: System::Windows::Forms::Label^  lipConstLabel;
  private: System::Windows::Forms::Label^  label17;
  private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  saveOPToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  savePointsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  graphSettingsToolStripMenuItem;
  private: System::Windows::Forms::ToolStripMenuItem^  TaskGeneratorSettingsToolStripMenuItem;

  private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
  private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
  private: System::Windows::Forms::ToolStripMenuItem^  algSettingsToolStripMenuItem;
  private: System::Windows::Forms::CheckBox^  isLocalCheckBox;
  private: System::ComponentModel::BackgroundWorker^  solveSingleTaskBackgroundWorker;
private: System::Windows::Forms::ToolStripMenuItem^  saveOPChartToolStripMenuItem;
private: System::Windows::Forms::SaveFileDialog^  saveOPImgDialog;
private: System::Windows::Forms::RadioButton^ customProblemRadioButton;

  private:
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    void InitializeComponent(void)
    {
        System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
        System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
        this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
        this->solveSerieButton = (gcnew System::Windows::Forms::Button());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
        this->isLocalCheckBox = (gcnew System::Windows::Forms::CheckBox());
        this->threadsNumNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
        this->label16 = (gcnew System::Windows::Forms::Label());
        this->MapTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
        this->label11 = (gcnew System::Windows::Forms::Label());
        this->max_it_num = (gcnew System::Windows::Forms::NumericUpDown());
        this->label5 = (gcnew System::Windows::Forms::Label());
        this->prec_text = (gcnew System::Windows::Forms::TextBox());
        this->map_tightness = (gcnew System::Windows::Forms::NumericUpDown());
        this->reliability_coeff = (gcnew System::Windows::Forms::NumericUpDown());
        this->label3 = (gcnew System::Windows::Forms::Label());
        this->label4 = (gcnew System::Windows::Forms::Label());
        this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
        this->clear_button = (gcnew System::Windows::Forms::Button());
        this->drawIsolinesButton = (gcnew System::Windows::Forms::Button());
        this->solveTaskSerieBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
        this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
        this->customProblemRadioButton = (gcnew System::Windows::Forms::RadioButton());
        this->stopCheckBox = (gcnew System::Windows::Forms::CheckBox());
        this->gklsHardRadioButton = (gcnew System::Windows::Forms::RadioButton());
        this->gklsRadioButton2 = (gcnew System::Windows::Forms::RadioButton());
        this->grishaginRadioButton = (gcnew System::Windows::Forms::RadioButton());
        this->label13 = (gcnew System::Windows::Forms::Label());
        this->OneDimGraphButton = (gcnew System::Windows::Forms::Button());
        this->graph_checkBox = (gcnew System::Windows::Forms::CheckBox());
        this->solveSingleTaskButton = (gcnew System::Windows::Forms::Button());
        this->task_number = (gcnew System::Windows::Forms::NumericUpDown());
        this->label6 = (gcnew System::Windows::Forms::Label());
        this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
        this->lipConstLabel = (gcnew System::Windows::Forms::Label());
        this->label17 = (gcnew System::Windows::Forms::Label());
        this->error_xy = (gcnew System::Windows::Forms::Label());
        this->label12 = (gcnew System::Windows::Forms::Label());
        this->error_val = (gcnew System::Windows::Forms::Label());
        this->label10 = (gcnew System::Windows::Forms::Label());
        this->it_count_lbl = (gcnew System::Windows::Forms::Label());
        this->label9 = (gcnew System::Windows::Forms::Label());
        this->task_val_lbl = (gcnew System::Windows::Forms::Label());
        this->task_answ_lbl = (gcnew System::Windows::Forms::Label());
        this->label8 = (gcnew System::Windows::Forms::Label());
        this->label7 = (gcnew System::Windows::Forms::Label());
        this->ShowLogButton = (gcnew System::Windows::Forms::Button());
        this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
        this->panel1 = (gcnew System::Windows::Forms::Panel());
        this->panel2 = (gcnew System::Windows::Forms::Panel());
        this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
        this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->saveOPToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->savePointsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->saveOPChartToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->advSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->graphSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->TaskGeneratorSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->algSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
        this->solveSingleTaskBackgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
        this->saveOPImgDialog = (gcnew System::Windows::Forms::SaveFileDialog());
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
        this->groupBox1->SuspendLayout();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadsNumNumericUpDown))->BeginInit();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->max_it_num))->BeginInit();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->map_tightness))->BeginInit();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->reliability_coeff))->BeginInit();
        this->groupBox2->SuspendLayout();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->task_number))->BeginInit();
        this->groupBox3->SuspendLayout();
        this->tableLayoutPanel1->SuspendLayout();
        this->panel1->SuspendLayout();
        this->panel2->SuspendLayout();
        this->menuStrip1->SuspendLayout();
        this->SuspendLayout();
        // 
        // chart1
        // 
        chartArea1->Name = L"ChartArea1";
        this->chart1->ChartAreas->Add(chartArea1);
        this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
        this->chart1->Location = System::Drawing::Point(0, 24);
        this->chart1->Name = L"chart1";
        this->chart1->Size = System::Drawing::Size(485, 591);
        this->chart1->TabIndex = 0;
        this->chart1->Text = L"chart1";
        title1->Name = L"Title1";
        title1->Text = L"Operating characteristics";
        this->chart1->Titles->Add(title1);
        // 
        // solveSerieButton
        // 
        this->solveSerieButton->Location = System::Drawing::Point(9, 117);
        this->solveSerieButton->Name = L"solveSerieButton";
        this->solveSerieButton->Size = System::Drawing::Size(127, 23);
        this->solveSerieButton->TabIndex = 1;
        this->solveSerieButton->Text = L"Solve class";
        this->solveSerieButton->UseVisualStyleBackColor = true;
        this->solveSerieButton->Click += gcnew System::EventHandler(this, &MainWindow::button1_Click);
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Location = System::Drawing::Point(6, 26);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(106, 13);
        this->label1->TabIndex = 4;
        this->label1->Text = L"Reliability coefficient:";
        // 
        // label2
        // 
        this->label2->AutoSize = true;
        this->label2->Location = System::Drawing::Point(6, 50);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(55, 13);
        this->label2->TabIndex = 6;
        this->label2->Text = L"Accuracy:";
        // 
        // groupBox1
        // 
        this->groupBox1->Controls->Add(this->isLocalCheckBox);
        this->groupBox1->Controls->Add(this->stopCheckBox);
        this->groupBox1->Controls->Add(this->threadsNumNumericUpDown);
        this->groupBox1->Controls->Add(this->label16);
        this->groupBox1->Controls->Add(this->MapTypeComboBox);
        this->groupBox1->Controls->Add(this->label11);
        this->groupBox1->Controls->Add(this->max_it_num);
        this->groupBox1->Controls->Add(this->label5);
        this->groupBox1->Controls->Add(this->prec_text);
        this->groupBox1->Controls->Add(this->map_tightness);
        this->groupBox1->Controls->Add(this->reliability_coeff);
        this->groupBox1->Controls->Add(this->label3);
        this->groupBox1->Controls->Add(this->label1);
        this->groupBox1->Controls->Add(this->label2);
        this->groupBox1->Location = System::Drawing::Point(3, 3);
        this->groupBox1->Name = L"groupBox1";
        this->groupBox1->Size = System::Drawing::Size(275, 200);
        this->groupBox1->TabIndex = 7;
        this->groupBox1->TabStop = false;
        this->groupBox1->Text = L"Parameters of algorithm";
        // 
        // isLocalCheckBox
        // 
        this->isLocalCheckBox->AutoSize = true;
        this->isLocalCheckBox->Location = System::Drawing::Point(6, 173);
        this->isLocalCheckBox->Name = L"isLocalCheckBox";
        this->isLocalCheckBox->Size = System::Drawing::Size(127, 17);
        this->isLocalCheckBox->TabIndex = 24;
        this->isLocalCheckBox->Text = L"Local tuned algorithm";
        this->isLocalCheckBox->UseVisualStyleBackColor = true;
        // 
        // threadsNumNumericUpDown
        // 
        this->threadsNumNumericUpDown->Location = System::Drawing::Point(215, 141);
        this->threadsNumNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 64, 0, 0, 0 });
        this->threadsNumNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
        this->threadsNumNumericUpDown->Name = L"threadsNumNumericUpDown";
        this->threadsNumNumericUpDown->Size = System::Drawing::Size(47, 20);
        this->threadsNumNumericUpDown->TabIndex = 23;
        this->threadsNumNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
        // 
        // label16
        // 
        this->label16->AutoSize = true;
        this->label16->Location = System::Drawing::Point(6, 148);
        this->label16->Name = L"label16";
        this->label16->Size = System::Drawing::Size(87, 13);
        this->label16->TabIndex = 22;
        this->label16->Text = L"Threads number:";
        // 
        // MapTypeComboBox
        // 
        this->MapTypeComboBox->FormattingEnabled = true;
        this->MapTypeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"injective", L"semi-linear", L"non-injective" });
        this->MapTypeComboBox->Location = System::Drawing::Point(133, 116);
        this->MapTypeComboBox->Name = L"MapTypeComboBox";
        this->MapTypeComboBox->Size = System::Drawing::Size(128, 21);
        this->MapTypeComboBox->TabIndex = 17;
        // 
        // label11
        // 
        this->label11->AutoSize = true;
        this->label11->Location = System::Drawing::Point(6, 120);
        this->label11->Name = L"label11";
        this->label11->Size = System::Drawing::Size(75, 13);
        this->label11->TabIndex = 15;
        this->label11->Text = L"Evolvent type:";
        // 
        // max_it_num
        // 
        this->max_it_num->Location = System::Drawing::Point(210, 93);
        this->max_it_num->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
        this->max_it_num->Name = L"max_it_num";
        this->max_it_num->Size = System::Drawing::Size(47, 20);
        this->max_it_num->TabIndex = 14;
        this->max_it_num->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
        // 
        // label5
        // 
        this->label5->AutoSize = true;
        this->label5->Location = System::Drawing::Point(6, 99);
        this->label5->Name = L"label5";
        this->label5->Size = System::Drawing::Size(143, 13);
        this->label5->TabIndex = 13;
        this->label5->Text = L"Maximal number of iterations:";
        // 
        // prec_text
        // 
        this->prec_text->Location = System::Drawing::Point(210, 47);
        this->prec_text->Name = L"prec_text";
        this->prec_text->Size = System::Drawing::Size(47, 20);
        this->prec_text->TabIndex = 12;
        this->prec_text->Text = L"0.01";
        // 
        // map_tightness
        // 
        this->map_tightness->Location = System::Drawing::Point(210, 71);
        this->map_tightness->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
        this->map_tightness->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
        this->map_tightness->Name = L"map_tightness";
        this->map_tightness->Size = System::Drawing::Size(47, 20);
        this->map_tightness->TabIndex = 11;
        this->map_tightness->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
        // 
        // reliability_coeff
        // 
        this->reliability_coeff->DecimalPlaces = 1;
        this->reliability_coeff->Location = System::Drawing::Point(210, 24);
        this->reliability_coeff->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
        this->reliability_coeff->Name = L"reliability_coeff";
        this->reliability_coeff->Size = System::Drawing::Size(47, 20);
        this->reliability_coeff->TabIndex = 9;
        this->reliability_coeff->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
        // 
        // label3
        // 
        this->label3->AutoSize = true;
        this->label3->Location = System::Drawing::Point(6, 73);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(97, 13);
        this->label3->TabIndex = 8;
        this->label3->Text = L"Evolvent tightness:";
        // 
        // label4
        // 
        this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
        this->label4->AutoSize = true;
        this->label4->Location = System::Drawing::Point(3, 561);
        this->label4->Name = L"label4";
        this->label4->Size = System::Drawing::Size(51, 13);
        this->label4->TabIndex = 8;
        this->label4->Text = L"Progress:";
        // 
        // progressBar1
        // 
        this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
        this->progressBar1->Location = System::Drawing::Point(76, 563);
        this->progressBar1->Name = L"progressBar1";
        this->progressBar1->Size = System::Drawing::Size(193, 11);
        this->progressBar1->TabIndex = 10;
        // 
        // clear_button
        // 
        this->clear_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
        this->clear_button->Location = System::Drawing::Point(129, 589);
        this->clear_button->Name = L"clear_button";
        this->clear_button->Size = System::Drawing::Size(127, 23);
        this->clear_button->TabIndex = 11;
        this->clear_button->Text = L"Clear graph";
        this->clear_button->UseVisualStyleBackColor = true;
        this->clear_button->Click += gcnew System::EventHandler(this, &MainWindow::clear_button_Click);
        // 
        // drawIsolinesButton
        // 
        this->drawIsolinesButton->Location = System::Drawing::Point(9, 67);
        this->drawIsolinesButton->Name = L"drawIsolinesButton";
        this->drawIsolinesButton->Size = System::Drawing::Size(127, 23);
        this->drawIsolinesButton->TabIndex = 12;
        this->drawIsolinesButton->Text = L"Show isolines";
        this->drawIsolinesButton->UseVisualStyleBackColor = true;
        this->drawIsolinesButton->Click += gcnew System::EventHandler(this, &MainWindow::graph_button_Click);
        // 
        // solveTaskSerieBackgroundWorker
        // 
        this->solveTaskSerieBackgroundWorker->WorkerReportsProgress = true;
        this->solveTaskSerieBackgroundWorker->WorkerSupportsCancellation = true;
        this->solveTaskSerieBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainWindow::solveTaskSerieBackgroundWorker_DoWork);
        this->solveTaskSerieBackgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &MainWindow::backgroundWorker1_ProgressChanged);
        this->solveTaskSerieBackgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainWindow::backgroundWorker1_RunWorkerCompleted);
        // 
        // groupBox2
        // 
        this->groupBox2->Controls->Add(this->customProblemRadioButton);
        this->groupBox2->Controls->Add(this->gklsHardRadioButton);
        this->groupBox2->Controls->Add(this->gklsRadioButton2);
        this->groupBox2->Controls->Add(this->grishaginRadioButton);
        this->groupBox2->Controls->Add(this->label13);
        this->groupBox2->Controls->Add(this->OneDimGraphButton);
        this->groupBox2->Controls->Add(this->graph_checkBox);
        this->groupBox2->Controls->Add(this->solveSingleTaskButton);
        this->groupBox2->Controls->Add(this->task_number);
        this->groupBox2->Controls->Add(this->drawIsolinesButton);
        this->groupBox2->Controls->Add(this->label6);
        this->groupBox2->Controls->Add(this->solveSerieButton);
        this->groupBox2->Location = System::Drawing::Point(0, 209);
        this->groupBox2->Name = L"groupBox2";
        this->groupBox2->Size = System::Drawing::Size(275, 177);
        this->groupBox2->TabIndex = 13;
        this->groupBox2->TabStop = false;
        this->groupBox2->Text = L"Problem";
        // 
        // customProblemRadioButton
        // 
        this->customProblemRadioButton->AutoSize = true;
        this->customProblemRadioButton->Location = System::Drawing::Point(143, 158);
        this->customProblemRadioButton->Name = L"customProblemRadioButton";
        this->customProblemRadioButton->Size = System::Drawing::Size(60, 17);
        this->customProblemRadioButton->TabIndex = 23;
        this->customProblemRadioButton->Text = L"Custom";
        this->customProblemRadioButton->UseVisualStyleBackColor = true;
        // 
        // stopCheckBox
        // 
        this->stopCheckBox->AutoSize = true;
        this->stopCheckBox->Location = System::Drawing::Point(140, 173);
        this->stopCheckBox->Name = L"stopCheckBox";
        this->stopCheckBox->Size = System::Drawing::Size(109, 17);
        this->stopCheckBox->TabIndex = 22;
        this->stopCheckBox->Text = L"Stop by accuracy";
        this->stopCheckBox->UseVisualStyleBackColor = true;
        // 
        // gklsHardRadioButton
        // 
        this->gklsHardRadioButton->AutoSize = true;
        this->gklsHardRadioButton->Location = System::Drawing::Point(143, 135);
        this->gklsHardRadioButton->Name = L"gklsHardRadioButton";
        this->gklsHardRadioButton->Size = System::Drawing::Size(79, 17);
        this->gklsHardRadioButton->TabIndex = 21;
        this->gklsHardRadioButton->Text = L"GKLS Hard";
        this->gklsHardRadioButton->UseVisualStyleBackColor = true;
        // 
        // gklsRadioButton2
        // 
        this->gklsRadioButton2->AutoSize = true;
        this->gklsRadioButton2->Location = System::Drawing::Point(143, 112);
        this->gklsRadioButton2->Name = L"gklsRadioButton2";
        this->gklsRadioButton2->Size = System::Drawing::Size(87, 17);
        this->gklsRadioButton2->TabIndex = 20;
        this->gklsRadioButton2->Text = L"GKLS Simple";
        this->gklsRadioButton2->UseVisualStyleBackColor = true;
        // 
        // grishaginRadioButton
        // 
        this->grishaginRadioButton->AutoSize = true;
        this->grishaginRadioButton->Checked = true;
        this->grishaginRadioButton->Location = System::Drawing::Point(142, 89);
        this->grishaginRadioButton->Name = L"grishaginRadioButton";
        this->grishaginRadioButton->Size = System::Drawing::Size(115, 17);
        this->grishaginRadioButton->TabIndex = 19;
        this->grishaginRadioButton->TabStop = true;
        this->grishaginRadioButton->Text = L"Grishagin functions";
        this->grishaginRadioButton->UseVisualStyleBackColor = true;
        // 
        // label13
        // 
        this->label13->AutoSize = true;
        this->label13->Location = System::Drawing::Point(140, 70);
        this->label13->Name = L"label13";
        this->label13->Size = System::Drawing::Size(75, 13);
        this->label13->TabIndex = 16;
        this->label13->Text = L"Problem class:";
        // 
        // OneDimGraphButton
        // 
        this->OneDimGraphButton->Location = System::Drawing::Point(9, 91);
        this->OneDimGraphButton->Name = L"OneDimGraphButton";
        this->OneDimGraphButton->Size = System::Drawing::Size(127, 23);
        this->OneDimGraphButton->TabIndex = 18;
        this->OneDimGraphButton->Text = L"One dimensional graph";
        this->OneDimGraphButton->UseVisualStyleBackColor = true;
        this->OneDimGraphButton->Click += gcnew System::EventHandler(this, &MainWindow::OneDimGraphButton_Click);
        // 
        // graph_checkBox
        // 
        this->graph_checkBox->AutoSize = true;
        this->graph_checkBox->Location = System::Drawing::Point(9, 47);
        this->graph_checkBox->Name = L"graph_checkBox";
        this->graph_checkBox->Size = System::Drawing::Size(155, 17);
        this->graph_checkBox->TabIndex = 17;
        this->graph_checkBox->Text = L"Show trial points on isolines";
        this->graph_checkBox->UseVisualStyleBackColor = true;
        // 
        // solveSingleTaskButton
        // 
        this->solveSingleTaskButton->Location = System::Drawing::Point(141, 19);
        this->solveSingleTaskButton->Name = L"solveSingleTaskButton";
        this->solveSingleTaskButton->Size = System::Drawing::Size(76, 23);
        this->solveSingleTaskButton->TabIndex = 16;
        this->solveSingleTaskButton->Text = L"Solve";
        this->solveSingleTaskButton->UseVisualStyleBackColor = true;
        this->solveSingleTaskButton->Click += gcnew System::EventHandler(this, &MainWindow::button2_Click);
        // 
        // task_number
        // 
        this->task_number->Location = System::Drawing::Point(88, 21);
        this->task_number->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
        this->task_number->Name = L"task_number";
        this->task_number->Size = System::Drawing::Size(47, 20);
        this->task_number->TabIndex = 15;
        this->task_number->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
        // 
        // label6
        // 
        this->label6->AutoSize = true;
        this->label6->Location = System::Drawing::Point(6, 23);
        this->label6->Name = L"label6";
        this->label6->Size = System::Drawing::Size(76, 13);
        this->label6->TabIndex = 5;
        this->label6->Text = L"Problem index:";
        // 
        // groupBox3
        // 
        this->groupBox3->Controls->Add(this->lipConstLabel);
        this->groupBox3->Controls->Add(this->label17);
        this->groupBox3->Controls->Add(this->error_xy);
        this->groupBox3->Controls->Add(this->label12);
        this->groupBox3->Controls->Add(this->error_val);
        this->groupBox3->Controls->Add(this->label10);
        this->groupBox3->Controls->Add(this->it_count_lbl);
        this->groupBox3->Controls->Add(this->label9);
        this->groupBox3->Controls->Add(this->task_val_lbl);
        this->groupBox3->Controls->Add(this->task_answ_lbl);
        this->groupBox3->Controls->Add(this->label8);
        this->groupBox3->Controls->Add(this->label7);
        this->groupBox3->Location = System::Drawing::Point(0, 392);
        this->groupBox3->Name = L"groupBox3";
        this->groupBox3->Size = System::Drawing::Size(276, 162);
        this->groupBox3->TabIndex = 14;
        this->groupBox3->TabStop = false;
        this->groupBox3->Text = L"Results";
        // 
        // lipConstLabel
        // 
        this->lipConstLabel->AutoSize = true;
        this->lipConstLabel->Location = System::Drawing::Point(140, 140);
        this->lipConstLabel->Name = L"lipConstLabel";
        this->lipConstLabel->Size = System::Drawing::Size(10, 13);
        this->lipConstLabel->TabIndex = 17;
        this->lipConstLabel->Text = L"-";
        // 
        // label17
        // 
        this->label17->AutoSize = true;
        this->label17->Location = System::Drawing::Point(7, 140);
        this->label17->Name = L"label17";
        this->label17->Size = System::Drawing::Size(85, 13);
        this->label17->TabIndex = 16;
        this->label17->Text = L"Holder constant:";
        // 
        // error_xy
        // 
        this->error_xy->AutoSize = true;
        this->error_xy->Location = System::Drawing::Point(139, 116);
        this->error_xy->Name = L"error_xy";
        this->error_xy->Size = System::Drawing::Size(10, 13);
        this->error_xy->TabIndex = 15;
        this->error_xy->Text = L"-";
        // 
        // label12
        // 
        this->label12->AutoSize = true;
        this->label12->Location = System::Drawing::Point(6, 116);
        this->label12->Name = L"label12";
        this->label12->Size = System::Drawing::Size(104, 13);
        this->label12->TabIndex = 14;
        this->label12->Text = L"Error by coordinates:";
        // 
        // error_val
        // 
        this->error_val->AutoSize = true;
        this->error_val->Location = System::Drawing::Point(139, 93);
        this->error_val->Name = L"error_val";
        this->error_val->Size = System::Drawing::Size(10, 13);
        this->error_val->TabIndex = 13;
        this->error_val->Text = L"-";
        // 
        // label10
        // 
        this->label10->AutoSize = true;
        this->label10->Location = System::Drawing::Point(6, 93);
        this->label10->Name = L"label10";
        this->label10->Size = System::Drawing::Size(75, 13);
        this->label10->TabIndex = 12;
        this->label10->Text = L"Error by value:";
        // 
        // it_count_lbl
        // 
        this->it_count_lbl->AutoSize = true;
        this->it_count_lbl->Location = System::Drawing::Point(140, 69);
        this->it_count_lbl->Name = L"it_count_lbl";
        this->it_count_lbl->Size = System::Drawing::Size(10, 13);
        this->it_count_lbl->TabIndex = 11;
        this->it_count_lbl->Text = L"-";
        // 
        // label9
        // 
        this->label9->AutoSize = true;
        this->label9->Location = System::Drawing::Point(6, 69);
        this->label9->Name = L"label9";
        this->label9->Size = System::Drawing::Size(103, 13);
        this->label9->TabIndex = 10;
        this->label9->Text = L"Iteartions performed:";
        // 
        // task_val_lbl
        // 
        this->task_val_lbl->AutoSize = true;
        this->task_val_lbl->Location = System::Drawing::Point(139, 46);
        this->task_val_lbl->Name = L"task_val_lbl";
        this->task_val_lbl->Size = System::Drawing::Size(10, 13);
        this->task_val_lbl->TabIndex = 9;
        this->task_val_lbl->Text = L"-";
        // 
        // task_answ_lbl
        // 
        this->task_answ_lbl->AutoSize = true;
        this->task_answ_lbl->Location = System::Drawing::Point(139, 23);
        this->task_answ_lbl->Name = L"task_answ_lbl";
        this->task_answ_lbl->Size = System::Drawing::Size(10, 13);
        this->task_answ_lbl->TabIndex = 8;
        this->task_answ_lbl->Text = L"-";
        // 
        // label8
        // 
        this->label8->AutoSize = true;
        this->label8->Location = System::Drawing::Point(6, 46);
        this->label8->Name = L"label8";
        this->label8->Size = System::Drawing::Size(37, 13);
        this->label8->TabIndex = 7;
        this->label8->Text = L"Value:";
        // 
        // label7
        // 
        this->label7->AutoSize = true;
        this->label7->Location = System::Drawing::Point(6, 23);
        this->label7->Name = L"label7";
        this->label7->Size = System::Drawing::Size(66, 13);
        this->label7->TabIndex = 6;
        this->label7->Text = L"Coordinates:";
        // 
        // ShowLogButton
        // 
        this->ShowLogButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
        this->ShowLogButton->Location = System::Drawing::Point(2, 589);
        this->ShowLogButton->Name = L"ShowLogButton";
        this->ShowLogButton->Size = System::Drawing::Size(121, 23);
        this->ShowLogButton->TabIndex = 18;
        this->ShowLogButton->Text = L"Show log";
        this->ShowLogButton->UseVisualStyleBackColor = true;
        this->ShowLogButton->Click += gcnew System::EventHandler(this, &MainWindow::ShowLogButton_Click);
        // 
        // tableLayoutPanel1
        // 
        this->tableLayoutPanel1->ColumnCount = 2;
        this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
            290)));
        this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
            100)));
        this->tableLayoutPanel1->Controls->Add(this->panel1, 0, 0);
        this->tableLayoutPanel1->Controls->Add(this->panel2, 1, 0);
        this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
        this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
        this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
        this->tableLayoutPanel1->RowCount = 1;
        this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
        this->tableLayoutPanel1->Size = System::Drawing::Size(781, 621);
        this->tableLayoutPanel1->TabIndex = 19;
        // 
        // panel1
        // 
        this->panel1->Controls->Add(this->groupBox1);
        this->panel1->Controls->Add(this->ShowLogButton);
        this->panel1->Controls->Add(this->clear_button);
        this->panel1->Controls->Add(this->groupBox2);
        this->panel1->Controls->Add(this->groupBox3);
        this->panel1->Controls->Add(this->progressBar1);
        this->panel1->Controls->Add(this->label4);
        this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
        this->panel1->Location = System::Drawing::Point(3, 3);
        this->panel1->Name = L"panel1";
        this->panel1->Size = System::Drawing::Size(284, 615);
        this->panel1->TabIndex = 0;
        // 
        // panel2
        // 
        this->panel2->Controls->Add(this->chart1);
        this->panel2->Controls->Add(this->menuStrip1);
        this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
        this->panel2->Location = System::Drawing::Point(293, 3);
        this->panel2->Name = L"panel2";
        this->panel2->Size = System::Drawing::Size(485, 615);
        this->panel2->TabIndex = 1;
        // 
        // menuStrip1
        // 
        this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->saveToolStripMenuItem,
                this->advSettingsToolStripMenuItem, this->toolStripMenuItem1
        });
        this->menuStrip1->Location = System::Drawing::Point(0, 0);
        this->menuStrip1->Name = L"menuStrip1";
        this->menuStrip1->Size = System::Drawing::Size(485, 24);
        this->menuStrip1->TabIndex = 1;
        this->menuStrip1->Text = L"mainMenuStrip";
        // 
        // saveToolStripMenuItem
        // 
        this->saveToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->saveOPToolStripMenuItem,
                this->savePointsToolStripMenuItem, this->saveOPChartToolStripMenuItem
        });
        this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
        this->saveToolStripMenuItem->Size = System::Drawing::Size(43, 20);
        this->saveToolStripMenuItem->Text = L"Save";
        // 
        // saveOPToolStripMenuItem
        // 
        this->saveOPToolStripMenuItem->Name = L"saveOPToolStripMenuItem";
        this->saveOPToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
        this->saveOPToolStripMenuItem->Size = System::Drawing::Size(327, 22);
        this->saveOPToolStripMenuItem->Text = L"Operating characteristic";
        this->saveOPToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::saveOPToolStripMenuItem_Click);
        // 
        // savePointsToolStripMenuItem
        // 
        this->savePointsToolStripMenuItem->Name = L"savePointsToolStripMenuItem";
        this->savePointsToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
            | System::Windows::Forms::Keys::S));
        this->savePointsToolStripMenuItem->Size = System::Drawing::Size(327, 22);
        this->savePointsToolStripMenuItem->Text = L"Trial points";
        this->savePointsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::savePointsToolStripMenuItem_Click);
        // 
        // saveOPChartToolStripMenuItem
        // 
        this->saveOPChartToolStripMenuItem->Name = L"saveOPChartToolStripMenuItem";
        this->saveOPChartToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Alt)
            | System::Windows::Forms::Keys::S));
        this->saveOPChartToolStripMenuItem->Size = System::Drawing::Size(327, 22);
        this->saveOPChartToolStripMenuItem->Text = L"Save operating characteristics graph";
        this->saveOPChartToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::saveOPChartToolStripMenuItem_Click);
        // 
        // advSettingsToolStripMenuItem
        // 
        this->advSettingsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
            this->graphSettingsToolStripMenuItem,
                this->TaskGeneratorSettingsToolStripMenuItem, this->algSettingsToolStripMenuItem
        });
        this->advSettingsToolStripMenuItem->Name = L"advSettingsToolStripMenuItem";
        this->advSettingsToolStripMenuItem->Size = System::Drawing::Size(116, 20);
        this->advSettingsToolStripMenuItem->Text = L"Advanced settings";
        // 
        // graphSettingsToolStripMenuItem
        // 
        this->graphSettingsToolStripMenuItem->Name = L"graphSettingsToolStripMenuItem";
        this->graphSettingsToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::G));
        this->graphSettingsToolStripMenuItem->Size = System::Drawing::Size(257, 22);
        this->graphSettingsToolStripMenuItem->Text = L"Graph settings";
        this->graphSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::graphSettingsToolStripMenuItem_Click);
        // 
        // TaskGeneratorSettingsToolStripMenuItem
        // 
        this->TaskGeneratorSettingsToolStripMenuItem->Name = L"TaskGeneratorSettingsToolStripMenuItem";
        this->TaskGeneratorSettingsToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::T));
        this->TaskGeneratorSettingsToolStripMenuItem->Size = System::Drawing::Size(257, 22);
        this->TaskGeneratorSettingsToolStripMenuItem->Text = L"Problem generator settings";
        this->TaskGeneratorSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::TaskGeneratorSettingsToolStripMenuItem_Click);
        // 
        // algSettingsToolStripMenuItem
        // 
        this->algSettingsToolStripMenuItem->Name = L"algSettingsToolStripMenuItem";
        this->algSettingsToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
        this->algSettingsToolStripMenuItem->Size = System::Drawing::Size(257, 22);
        this->algSettingsToolStripMenuItem->Text = L"Algorithm settings";
        this->algSettingsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::algSettingsToolStripMenuItem_Click);
        // 
        // toolStripMenuItem1
        // 
        this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
        this->toolStripMenuItem1->Size = System::Drawing::Size(12, 20);
        // 
        // saveFileDialog
        // 
        this->saveFileDialog->DefaultExt = L"csv";
        // 
        // solveSingleTaskBackgroundWorker
        // 
        this->solveSingleTaskBackgroundWorker->WorkerSupportsCancellation = true;
        this->solveSingleTaskBackgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainWindow::solveSingleTaskBackgroundWorker_DoWork);
        this->solveSingleTaskBackgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MainWindow::solveSingleTaskBackgroundWorker_RunWorkerCompleted);
        // 
        // saveOPImgDialog
        // 
        this->saveOPImgDialog->DefaultExt = L"png";
        this->saveOPImgDialog->Filter = L"PNG|*.png";
        // 
        // MainWindow
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(781, 621);
        this->Controls->Add(this->tableLayoutPanel1);
        this->MinimumSize = System::Drawing::Size(797, 660);
        this->Name = L"MainWindow";
        this->ShowIcon = false;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        this->Text = L"Global search algorithm";
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
        this->groupBox1->ResumeLayout(false);
        this->groupBox1->PerformLayout();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threadsNumNumericUpDown))->EndInit();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->max_it_num))->EndInit();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->map_tightness))->EndInit();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->reliability_coeff))->EndInit();
        this->groupBox2->ResumeLayout(false);
        this->groupBox2->PerformLayout();
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->task_number))->EndInit();
        this->groupBox3->ResumeLayout(false);
        this->groupBox3->PerformLayout();
        this->tableLayoutPanel1->ResumeLayout(false);
        this->panel1->ResumeLayout(false);
        this->panel1->PerformLayout();
        this->panel2->ResumeLayout(false);
        this->panel2->PerformLayout();
        this->menuStrip1->ResumeLayout(false);
        this->menuStrip1->PerformLayout();
        this->ResumeLayout(false);

    }
#pragma endregion
  private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
    if (solveTaskSerieBackgroundWorker->IsBusy != true)
    {
      map_type = MapTypeComboBox->SelectedIndex + 1;
      ExperimentsLog += "Evolvent: " + MapTypeComboBox->SelectedItem;
      if (grishaginRadioButton->Checked)
        ExperimentsLog += "\nProblem class: Grishagin functions\n";
      else if (gklsRadioButton2->Checked)
        ExperimentsLog += "\nProblem class: GKLS Simple\n";
      else
        ExperimentsLog += "\nProblem class: GKLS Hard\n";
      if (isLocalCheckBox->Checked)
        ExperimentsLog += "Algorithm: local tuned\n";
      else
        ExperimentsLog += "Algorithm: global\n";
      ExperimentsLog += "Threads number: " + threadsNumNumericUpDown->Value.ToString() + "\n";
      solveTaskSerieBackgroundWorker->RunWorkerAsync();
      solveSerieButton->Enabled = false;
      solveSingleTaskButton->Enabled = false;
    }
  }
  private: System::Void clear_button_Click(System::Object^  sender, System::EventArgs^  e) {

    chart1->Series->Clear();
    chart1->Legends->Clear();
    series_count = 0;
  }
  private: System::Void solveTaskSerieBackgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
    readAlgorithmParameters();

    int currentDimention = 2;
    FunctionWrapperCommon *targetFunction;
    SharedVector leftBound, rightBound;
    String^ error_numbers = gcnew String("");
    mOperationCharacteristicData = gcnew array<int, 1>(100);
    double optimumCheckEps = mCurrentAlgParams->eps;
    if (stopCheckBox->Checked)
      optimumCheckEps *= 5;

    if (gklsHardRadioButton->Checked || gklsRadioButton2->Checked) {

      currentDimention = mTaskGeneratorSettings.GKLSDimention;
      leftBound = SharedVector(new double[currentDimention],
        utils::array_deleter<double>());
      rightBound = SharedVector(new double[currentDimention],
        utils::array_deleter<double>());

      for (int i = 0; i < currentDimention; i++) {
        leftBound.get()[i] = -1;
        rightBound.get()[i] = 1;
      }

      GKLSFunctionWrapper* g = new GKLSFunctionWrapper();
      if (gklsRadioButton2->Checked)
        g->SetClassType(gklsfunction::GKLSClass::Simple, mTaskGeneratorSettings.GKLSDimention);
      else if (gklsHardRadioButton->Checked)
        g->SetClassType(gklsfunction::GKLSClass::Hard, mTaskGeneratorSettings.GKLSDimention);

      targetFunction = g;
    }
    else if (grishaginRadioButton->Checked)  {
      leftBound = SharedVector(new double[2], utils::array_deleter<double>());
      rightBound = SharedVector(new double[2], utils::array_deleter<double>());
      leftBound.get()[0] = leftBound.get()[1] = 0;
      rightBound.get()[0] = rightBound.get()[1] = 1;
      targetFunction = new VAGRisFunctionWrapper();
    }
    else if (customProblemRadioButton->Checked) {
      return;
    }

    OptimizerFunctionPtr* taskFunctions = new OptimizerFunctionPtr[1];
    taskFunctions[0] = OptimizerFunctionPtr(targetFunction);
    optimizercore::OptimizerTask task(std::shared_ptr<OptimizerFunctionPtr>(taskFunctions,
      utils::array_deleter<OptimizerFunctionPtr>()), 0, currentDimention, leftBound, rightBound);

    //OptimizerAlgorithm ags;
    OptimizerAlgorithmUnconstrained ags;
    ags.SetParameters(*mCurrentAlgParams);
    ags.SetTask(taskFunctions[0], OptimizerSpaceTransformation(leftBound, rightBound, currentDimention));
    //agp.SetTask(task);

    double *x, *y = new double[mTaskGeneratorSettings.GKLSDimention];
    double meanIterationsCount = 0;
    int err_count = 0, max_count = 0;
    Stopwatch s_watch;
    s_watch.Start();
    for (int i = 1; i <= 100; i++)
    {
      targetFunction->SetFunctionNumber(i);
      targetFunction->GetMinPoint(y);

      auto expResult = ags.StartOptimization(y, static_cast<StopCriterionType>(stopCheckBox->Checked));
      auto taskSolution = expResult.GetSolution();
      x = taskSolution.GetOptimumPoint().get();

      if (utils::NormNDimMax(x, y, currentDimention) < optimumCheckEps) {
        meanIterationsCount += taskSolution.GetIterationsCount();
        mOperationCharacteristicData[i - 1] = taskSolution.GetIterationsCount();
      }
      else {
        err_count++;
        error_numbers += i.ToString() + ", ";
        mOperationCharacteristicData[i - 1] = mCurrentAlgParams->maxIterationsNumber * 2;
      }

      if (max_count < taskSolution.GetIterationsCount())
        max_count = taskSolution.GetIterationsCount();

      solveTaskSerieBackgroundWorker->ReportProgress(i);
    }
    s_watch.Stop();
    if (err_count>0)
      error_numbers = error_numbers->Remove(error_numbers->LastIndexOf(","));
    ExperimentsLog += "E=" + prec_text->Text + " R=" + reliability_coeff->Value.ToString("F1") + " M=" + map_tightness->Value.ToString("F0");
    ExperimentsLog += "\nTotal errors: " + err_count.ToString() + "\nIndexes of unsolved problems: " + error_numbers +
      "\nTime:" + s_watch.ElapsedMilliseconds.ToString() + " ms"
      "\nMean itrerations number: " + (meanIterationsCount / (100 - err_count)).ToString() +
      "\n-------------------\n";
    max_it_count = max_count;
    delete[] y;
  }
  private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
    progressBar1->Value = e->ProgressPercentage;
  }
  private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
    series_count++;
    String ^s_name = gcnew String(series_count.ToString() + ": E=" + prec_text->Text + " R=" + reliability_coeff->Value.ToString("F1") + " M=" + map_tightness->Value.ToString("F0"));
    if (grishaginRadioButton->Checked)
      s_name += " Gris";
    else if (gklsRadioButton2->Checked)
      s_name += " GE";
    else
      s_name += " GH";
    if (isLocalCheckBox->Checked)
      s_name += " Loc";
    else
      s_name += " Glob";
    s_name += " ThrNum=" + threadsNumNumericUpDown->Value.ToString();

    Series^  series1 = gcnew Series();

    if (series_count == 1) {
      Legend^  legend1 = gcnew Legend();
      legend1->Name = s_name;
      legend1->Alignment = System::Drawing::StringAlignment::Far;
      legend1->DockedToChartArea = L"ChartArea1";
      legend1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
      legend1->IsDockedInsideChartArea = false;
      legend1->LegendStyle = System::Windows::Forms::DataVisualization::Charting::LegendStyle::Table;
      series1->Legend = s_name;
      this->chart1->Legends->Add(legend1);
    }

    series1->Name = s_name;
    this->chart1->Series->Add(series1);
    chart1->Series[s_name]->ChartType = SeriesChartType::Point;

    int t_count = 0;
    for (int i = 10; i < max_it_count + 20; i += 10) {
      for (int j = 0; j < 100; j++)
        if (mOperationCharacteristicData[j]<i)
          t_count++;
      chart1->Series[s_name]->Points->AddXY(i, t_count / 100.0);
      t_count = 0;
    }
    solveSerieButton->Enabled = true;
    solveSingleTaskButton->Enabled = true;
  }

  private: System::Void graph_button_Click(System::Object^  sender, System::EventArgs^  e) {
    int task_num = Convert::ToInt32(task_number->Value);
    DrawIsolines(task_num, nullptr);
  }

  private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
    if (!solveSingleTaskBackgroundWorker->IsBusy)
    {
      solveSingleTaskBackgroundWorker->RunWorkerAsync();
      solveSingleTaskButton->Enabled = false;
      solveSerieButton->Enabled = false;
    }
  }

  private: void DrawIsolines(int task_num, OptimizerSearchSequence* points)
  {
    int n = 200, i, j, width = 800, height = 1100;
    float  fpi_x = 1, fpi_y = 1, step_x, step_y, zlev, x_left, y_min;
    double arg[2];
    String^ taskName;

    array<float, 1>^ xray = gcnew array<float, 1>(n);
    array<float, 1>^ yray = gcnew array<float, 1>(n);
    array<float, 2>^  zmat = gcnew array<float, 2>(n, n);

    FunctionWrapperCommon *f;
    TProblemManager manager;
    IProblem* problem = nullptr;

    if (grishaginRadioButton->Checked)
    {
      f = new VAGRisFunctionWrapper();

      x_left = y_min = 0;
      step_x = step_y = 1.f / (n - 1);
      fpi_x = fpi_y = 1;

      taskName += "Grishagin function #" + task_num.ToString();
    }
    else if (customProblemRadioButton->Checked)
    {
      std::string libPath = msclr::interop::marshal_as<std::string>(mTaskGeneratorSettings.dllPath->ToString());
      if (manager.LoadProblemLibrary(libPath) != TProblemManager::OK_)
      {
        MessageBox::Show("Failed to load custom problem");
        return;
      }
      problem = manager.GetProblem();
      if (problem->Initialize() != TProblemManager::OK_)
      {
        MessageBox::Show("Failed to initialize custom problem");
        return;
      }

      problem->SetDimension(mTaskGeneratorSettings.GKLSDimention);

      auto leftBound = SharedVector(new double[mTaskGeneratorSettings.GKLSDimention], utils::array_deleter<double>());
      auto rightBound = SharedVector(new double[mTaskGeneratorSettings.GKLSDimention], utils::array_deleter<double>());
      problem->GetBounds(leftBound.get(), rightBound.get());
      x_left = static_cast<float>(leftBound.get()[0]);
      y_min = static_cast<float>(leftBound.get()[1]);
      fpi_x = static_cast<float>(rightBound.get()[0]) - x_left;
      fpi_y = static_cast<float>(rightBound.get()[1]) - y_min;
      step_x = fpi_x / (n - 1);
      step_y = fpi_y / (n - 1);

      f = new CustomProblemWrapper(problem);
      taskName += "Custom problem";
    }
    else
    {
      if (gklsRadioButton2->Checked) {
        f = new GKLSFunctionWrapper(gklsfunction::GKLSClass::Simple, mTaskGeneratorSettings.GKLSDimention);
        taskName += "GKLS Simple function #" + task_num.ToString();
      }
      else if (gklsHardRadioButton->Checked) {
        f = new GKLSFunctionWrapper(gklsfunction::GKLSClass::Hard, mTaskGeneratorSettings.GKLSDimention);
        taskName += "GKLS Hard function #" + task_num.ToString();
      }
      x_left = y_min = -1;
      step_x = step_y = 2.f / (n - 1);
      fpi_x = fpi_y = 2;
    }

    f->SetFunctionNumber(task_num);
    for (i = 0; i < n; i++)
    {
      xray[i] = (float)(i * step_x + x_left);
      yray[i] = (float)(i * step_y + y_min);
    }
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
      {
        arg[0] = xray[i]; arg[1] = yray[j];
        zmat[i, j] = (float)f->Calculate(arg);
      }

    dislin::winsiz(width, height);
    dislin::page(2200, 2400);
    dislin::metafl("virt");
    dislin::scrmod("revers");
    dislin::disini();
    dislin::complx();
    dislin::wintit("Isolines");

    dislin::titlin(taskName, 3);

    dislin::name("X-axis", "x");
    dislin::name("Y-axis", "y");

    dislin::axspos(240, 2200);
    dislin::axslen(1900, 1900);

    dislin::graf(x_left, x_left + fpi_x, x_left, fpi_x / 4, y_min, y_min + fpi_y, y_min, fpi_y / 4);

    dislin::height(30);
    for (i = 0; i < 19; i++)
    {
      if (grishaginRadioButton->Checked == true)
        zlev = (float)(f->GetMinValue() + 0.1 + i);
      else
        zlev = (float)(f->GetMinValue() + 0.01 + i*0.3);
      if (mGraphSettings.isIsolinesColored)
        dislin::setclr((i + 1) * 25);
      if (mGraphSettings.numersOnIsolinesPlot)
      {
        if (i % 3 == 0)
          dislin::labels("float", "contur");
        else
          dislin::labels("none", "contur");
      }
      dislin::contur(xray, n, yray, n, zmat, zlev);
    }

    if (points != nullptr)
    {
      dislin::color("white");
      double y[2];
      dislin::hsymbl(15);
      int size = points->GetSize();
      for (int i = 0; i < size; i++)
      {
        points->GetPoint(i, y);
        dislin::rlsymb(21, (float)(y[0]), (float)(y[1]));
      }
      dislin::color("blue");
      dislin::hsymbl(30);
      f->GetMinPoint(y);
      dislin::rlsymb(21, (float)y[0], (float)y[1]);
    }

    dislin::height(50);
    dislin::color("fore");
    dislin::title();

    dislin::imgmod("rgb");
    dislin::imgini();
    array<unsigned char, 1>^ rawImage = gcnew array<unsigned char, 1>(3 * width * height);
    dislin::rpixls(rawImage, 0, 0, width, height);
    dislin::disfin();

    if (points != 0 && !mGraphSettings.isGraphAppearsInNewWindow && mIsolinesGraph)
      mIsolinesGraph->Close();

    mIsolinesGraph = gcnew IsolinesGraphWindow(rawImage, width, height);

    delete f;
    mIsolinesGraph->Show();
  }
  private: System::Void ShowLogButton_Click(System::Object^  sender, System::EventArgs^  e) {
    LogWindow^ Log = gcnew LogWindow(ExperimentsLog);
    Log->ShowDialog();
  }
  private: System::Void OneDimGraphButton_Click(System::Object^  sender, System::EventArgs^  e) {
    int task_num = Convert::ToInt32(task_number->Value);
    DrawOneDimGraph(task_num, nullptr);
  }

  private: System::Void DrawOneDimGraph(int task_num, OptimizerSearchSequence* points)
  {
    int n = 2000;
    double fpi = 1, step, *y = new double[mTaskGeneratorSettings.GKLSDimention];
    array<float, 1>^ xray = gcnew array<float, 1>(n + 1);
    array<float, 1>^ yray = gcnew array<float, 1>(n + 1);
    array<float, 2>^ searchSequence;
    String ^taskName;
    int map_t = Convert::ToInt32(map_tightness->Value);
    int currentDimention = 2;
    map_type = MapTypeComboBox->SelectedIndex + 1;
    TProblemManager manager;
    SharedVector leftBound, rightBound;
    
    FunctionWrapperCommon* f;

    if (grishaginRadioButton->Checked)
    {
      taskName = "Grishagin function # " + task_num.ToString();
      f = new VAGRisFunctionWrapper();
      leftBound = SharedVector(new double[2], utils::array_deleter<double>());
      rightBound = SharedVector(new double[2], utils::array_deleter<double>());
      leftBound.get()[0] = leftBound.get()[1] = 0;
      rightBound.get()[0] = rightBound.get()[1] = 1;
    }
    else if (customProblemRadioButton->Checked)
    {
      std::string libPath = msclr::interop::marshal_as<std::string>(mTaskGeneratorSettings.dllPath->ToString());
      if (manager.LoadProblemLibrary(libPath) != TProblemManager::OK_)
      {
        MessageBox::Show("Failed to load custom problem");
        return;
      }
      auto problem = manager.GetProblem();
      if (problem->Initialize() != TProblemManager::OK_)
      {
        MessageBox::Show("Failed to initialize custom problem");
        return;
      }

      problem->SetDimension(mTaskGeneratorSettings.GKLSDimention);
      leftBound = SharedVector(new double[mTaskGeneratorSettings.GKLSDimention], utils::array_deleter<double>());
      rightBound = SharedVector(new double[mTaskGeneratorSettings.GKLSDimention], utils::array_deleter<double>());
      problem->GetBounds(leftBound.get(), rightBound.get());

      taskName = "Custom function";
      f = new CustomProblemWrapper(problem);
    }
    else
    {
      if (gklsRadioButton2->Checked)
      {
        f = new GKLSFunctionWrapper(gklsfunction::GKLSClass::Simple, mTaskGeneratorSettings.GKLSDimention);
        taskName = "GKLS Simple function # " + task_num.ToString();
      }
      else if (gklsHardRadioButton->Checked)
      {
        f = new GKLSFunctionWrapper(gklsfunction::GKLSClass::Hard, mTaskGeneratorSettings.GKLSDimention);
        taskName = "GKLS Hard function # " + task_num.ToString();
      }
      currentDimention = mTaskGeneratorSettings.GKLSDimention;
      leftBound = SharedVector(new double[mTaskGeneratorSettings.GKLSDimention], utils::array_deleter<double>());
      rightBound = SharedVector(new double[mTaskGeneratorSettings.GKLSDimention], utils::array_deleter<double>());
      for (int i = 0; i < currentDimention; i++)
      {
        leftBound.get()[i] = -1;
        rightBound.get()[i] = 1;
      }
    }
    f->SetFunctionNumber(task_num);

    step = 1.0 / n;
    auto transform = OptimizerSpaceTransformation(leftBound, rightBound, currentDimention);

    for (int i = 0; i <= n; i++)
    {
      xray[i] = (float)(i * step);
      mapd(xray[i], map_t, y, currentDimention, map_type);
      transform.Transform(y, y);
      yray[i] = static_cast<float>(f->Calculate(y));
    }

    if (points != nullptr)
    {
      int size = points->GetSize();
      searchSequence = gcnew array<float, 2>(2, size);
      for (int i = 0; i < size; i++)
      {
        searchSequence[0, i] = (float)points->GetOneDimPoint(i);
        searchSequence[1, i] = (float)points->GetValue(i);
      }
    }

    if (!mGraphSettings.isGraphAppearsInNewWindow && mOneDimGraph && points != nullptr)
      mOneDimGraph->Close();

    mOneDimGraph = gcnew OneDimGraphWindow(xray, yray, taskName, searchSequence);
    mOneDimGraph->Show();
    delete[] y;
    delete f;
  }
  private: System::Void saveOPToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    if (series_count > 0)
    {
      if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
      {
        String^ outputString;
        int t_count = 0;
        for (int i = 10; i < max_it_count + 20; i += 10) {
          for (int j = 0; j < 100; j++)
            if (mOperationCharacteristicData[j]<i)
              t_count++;
          outputString += i.ToString() + "; " + (t_count / 100.0).ToString("F4") + "\n";
          t_count = 0;
        }
        System::IO::File::WriteAllText(saveFileDialog->FileName, outputString);
      }
    }
    else
      MessageBox::Show("No operating characteristic to save", "Error",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
  }
  private: System::Void savePointsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    if (currentSequence != nullptr)
    {
      if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
      {
        Thread^ fileWriteThread = gcnew Thread(gcnew ThreadStart(this, &MainWindow::savePoints));
        fileWriteThread->IsBackground = true;
        fileWriteThread->Start();
      }
    }
    else
      MessageBox::Show("No data to save", "Error",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
  }
  private: System::Void graphSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    GraphSettingsWindow ^settings = gcnew GraphSettingsWindow(mGraphSettings);
    settings->ShowDialog();
  }
  private: System::Void algSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    AlgorithmSettingsWindow ^settings = gcnew AlgorithmSettingsWindow(mAlgorithmSettings);
    settings->ShowDialog();
  }

  private: System::Void TaskGeneratorSettingsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    TaskGeneratorSettingsWindow ^settings = gcnew TaskGeneratorSettingsWindow(mTaskGeneratorSettings);
    settings->ShowDialog();
  }
  private: System::Void savePoints()
  {
    String^ outputString;

    int seqSize = currentSequence->GetSize();
    int seqDim = currentSequence->GetDimention();
    double *tmpPoint = new double[seqDim];
    OptimizerSearchSequence tmpSequence(*currentSequence);

    for (int i = 0; i < seqSize; i++) {
      tmpSequence.GetPoint(i, tmpPoint);
      for (int j = 0; j < seqDim; j++)
      {
        outputString += tmpPoint[j].ToString("F8");
        if (j != seqDim - 1)
          outputString += ";";
        else
          outputString += "\n";
      }
    }
    System::IO::File::WriteAllText(saveFileDialog->FileName, outputString);
    delete[] tmpPoint;
  }
  private: System::Void solveSingleTaskBackgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
    readAlgorithmParameters();
    int currentDimention = 2;
    FunctionWrapperCommon *targetFunction;
    SharedVector leftBound, rightBound;
    TProblemManager manager;
    IProblem* problem = nullptr;

    if (grishaginRadioButton->Checked)
    {
      leftBound = SharedVector(new double[2], utils::array_deleter<double>());
      rightBound = SharedVector(new double[2], utils::array_deleter<double>());
      leftBound.get()[0] = leftBound.get()[1] = 0;
      rightBound.get()[0] = rightBound.get()[1] = 1;

      targetFunction = new VAGRisFunctionWrapper();
    }
    else if (customProblemRadioButton->Checked)
    {
      std::string libPath = msclr::interop::marshal_as<std::string>(mTaskGeneratorSettings.dllPath->ToString());
      if (manager.LoadProblemLibrary(libPath) != TProblemManager::OK_)
      {
        MessageBox::Show("Failed to load custom problem");
        return;
      }
      problem = manager.GetProblem();
      if (problem->Initialize() != TProblemManager::OK_)
      {
        MessageBox::Show("Failed to initialize custom problem");
        return;
      }

      problem->SetDimension(mTaskGeneratorSettings.GKLSDimention);
      currentDimention = problem->GetDimension();

      leftBound = SharedVector(new double[currentDimention], utils::array_deleter<double>());
      rightBound = SharedVector(new double[currentDimention], utils::array_deleter<double>());

      problem->GetBounds(leftBound.get(), rightBound.get());

      targetFunction = new CustomProblemWrapper(problem);
    }
    else
    {
      currentDimention = mTaskGeneratorSettings.GKLSDimention;
      leftBound = SharedVector(new double[currentDimention],
        utils::array_deleter<double>());
      rightBound = SharedVector(new double[currentDimention],
        utils::array_deleter<double>());

      for (int i = 0; i < currentDimention; i++) {
        leftBound.get()[i] = -1;
        rightBound.get()[i] = 1;
      }

      if (gklsRadioButton2->Checked == true)
        targetFunction = new GKLSFunctionWrapper(gklsfunction::GKLSClass::Simple, mTaskGeneratorSettings.GKLSDimention);
      else if (gklsHardRadioButton->Checked == true)
        targetFunction = new GKLSFunctionWrapper(gklsfunction::GKLSClass::Hard, mTaskGeneratorSettings.GKLSDimention);
    }

    double* x, err_val, err_xy, * y = new double[currentDimention];

    targetFunction->SetFunctionNumber(mCurrentTaskNumber);
    targetFunction->GetMinPoint(y);
    err_val = targetFunction->Calculate(y);

    OptimizerFunctionPtr* taskFunctions = new OptimizerFunctionPtr[1];
    taskFunctions[0] = OptimizerFunctionPtr(targetFunction);
    optimizercore::OptimizerTask task(std::shared_ptr<OptimizerFunctionPtr>(taskFunctions,
      utils::array_deleter<OptimizerFunctionPtr>()), 0, currentDimention, leftBound, rightBound);

    OptimizerAlgorithmUnconstrained ags;
    ags.SetParameters(*mCurrentAlgParams);
    ags.SetTask(taskFunctions[0], OptimizerSpaceTransformation(leftBound, rightBound, currentDimention));

    auto expResult = ags.StartOptimization(y, static_cast<StopCriterionType>(stopCheckBox->Checked));
    if (currentSequence != nullptr)
      delete currentSequence;
    currentSequence = new auto(ags.GetSearchSequence());

    x = expResult.GetSolution().GetOptimumPoint().get();

    err_val = expResult.GetSolution().GetOptimumValue() - err_val;
    err_xy = utils::NormNDimMax(x, y, currentDimention);

    it_count_lbl->Text = expResult.GetSolution().GetIterationsCount().ToString();
    task_answ_lbl->Text = "(" + x[0].ToString("F4") + " ; " + x[1].ToString("F4") + ")";
    task_val_lbl->Text = expResult.GetSolution().GetOptimumValue().ToString("F6");
    error_val->Text = err_val.ToString("F6");
    error_xy->Text = err_xy.ToString("F6");
    mErrorValueString = err_xy.ToString("F6");
    //lipConstLabel->Text = ags.GetLipschitzConst(0).ToString("F5");
    lipConstLabel->Text = ags.GetLipschitzConst().ToString("F5");

    delete[] y;
  }

  private: System::Void solveSingleTaskBackgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
    solveSingleTaskButton->Enabled = true;
    int currentDimention = mCurrentAlgParams->algDimention;

    if (graph_checkBox->Checked && currentSequence)
    {
      if (mGraphSettings.showOneDimSolutionGraph)
        DrawOneDimGraph(mCurrentTaskNumber, currentSequence);
      if (currentDimention == 2)
        DrawIsolines(mCurrentTaskNumber, currentSequence);
    }
    solveSerieButton->Enabled = true;
  }

  private: System::Void readAlgorithmParameters()
  {
    mCurrentAlgParams->eps = Convert::ToDouble(prec_text->Text, nfi);
    *mCurrentAlgParams->r = Convert::ToDouble(reliability_coeff->Value);
    *mCurrentAlgParams->reserves = 0;
    mCurrentAlgParams->mapTightness = Convert::ToInt32(map_tightness->Value);
    mCurrentAlgParams->maxIterationsNumber = Convert::ToInt32(max_it_num->Value);
    mCurrentAlgParams->numberOfThreads = Convert::ToInt32(threadsNumNumericUpDown->Value);
    mCurrentAlgParams->mapType = static_cast<MapType>(MapTypeComboBox->SelectedIndex + 1);
    mCurrentAlgParams->localAlgStartIterationNumber = mAlgorithmSettings.localStartIteration;
    mCurrentAlgParams->localExponent = mAlgorithmSettings.alpha;
    if (isLocalCheckBox->Checked == true)
      mCurrentAlgParams->localMixParameter = mAlgorithmSettings.localMix;
    else
      mCurrentAlgParams->localMixParameter = 0;
    if (grishaginRadioButton->Checked)
      mCurrentAlgParams->algDimention = 2;
    else
      mCurrentAlgParams->algDimention = mTaskGeneratorSettings.GKLSDimention;
    mCurrentTaskNumber = Convert::ToInt32(task_number->Value);
    mCurrentAlgParams->localVerification = mAlgorithmSettings.localVerification;
    mCurrentAlgParams->localTuningMode = static_cast<LocalTuningMode>(mAlgorithmSettings.localAdaptationMode);
  }
  private: System::Void saveOPChartToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
    if (saveOPImgDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
      chart1->SaveImage(saveOPImgDialog->FileName, ChartImageFormat::Png);
    }
  }
};
}
