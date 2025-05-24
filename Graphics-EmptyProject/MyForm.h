#pragma once

#include"Model.h"
#include <msclr/marshal_cppstd.h>


namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			model = new Model();
			//
			//TODO: Add the constructor code here
			//
		}
	private: System::Windows::Forms::RichTextBox^ rtbTree;
	public:

	public:
	private: System::Windows::Forms::Button^ btnPrintTree;

	protected:

		Model* model;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			delete model;

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dgv;
	protected:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Key;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Value;
	private: System::Windows::Forms::RadioButton^ rbScan;
	private: System::Windows::Forms::RadioButton^ rbSort;
	private: System::Windows::Forms::RadioButton^ rbListHash;
	private: System::Windows::Forms::RadioButton^ rbArrayHash;
	private: System::Windows::Forms::RadioButton^ rbTree;
	private: System::Windows::Forms::RadioButton^ rbAVL;
	private: System::Windows::Forms::Label^ lblEff;

	private: System::Windows::Forms::TextBox^ tbAmount;
	private: System::Windows::Forms::TextBox^ tbMaxKey;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ btnCreate;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ tbSearchResult;

	private: System::Windows::Forms::TextBox^ tbKey;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ btnDelete;
	private: System::Windows::Forms::Button^ btnSearch;
	private: System::Windows::Forms::Button^ btnAdd;

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
			this->dgv = (gcnew System::Windows::Forms::DataGridView());
			this->Key = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Value = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->rbScan = (gcnew System::Windows::Forms::RadioButton());
			this->rbSort = (gcnew System::Windows::Forms::RadioButton());
			this->rbListHash = (gcnew System::Windows::Forms::RadioButton());
			this->rbArrayHash = (gcnew System::Windows::Forms::RadioButton());
			this->rbTree = (gcnew System::Windows::Forms::RadioButton());
			this->rbAVL = (gcnew System::Windows::Forms::RadioButton());
			this->lblEff = (gcnew System::Windows::Forms::Label());
			this->tbAmount = (gcnew System::Windows::Forms::TextBox());
			this->tbMaxKey = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btnCreate = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbSearchResult = (gcnew System::Windows::Forms::TextBox());
			this->tbKey = (gcnew System::Windows::Forms::TextBox());
			this->rtbTree = (gcnew System::Windows::Forms::RichTextBox());
			this->btnPrintTree = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// dgv
			// 
			this->dgv->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->Key, this->Value });
			this->dgv->Location = System::Drawing::Point(13, 13);
			this->dgv->Name = L"dgv";
			this->dgv->Size = System::Drawing::Size(240, 407);
			this->dgv->TabIndex = 0;
			// 
			// Key
			// 
			this->Key->HeaderText = L"Key";
			this->Key->Name = L"Key";
			// 
			// Value
			// 
			this->Value->HeaderText = L"Value";
			this->Value->Name = L"Value";
			// 
			// rbScan
			// 
			this->rbScan->AutoSize = true;
			this->rbScan->Checked = true;
			this->rbScan->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbScan->Location = System::Drawing::Point(14, 26);
			this->rbScan->Name = L"rbScan";
			this->rbScan->Size = System::Drawing::Size(98, 21);
			this->rbScan->TabIndex = 1;
			this->rbScan->TabStop = true;
			this->rbScan->Text = L"Scan Table";
			this->rbScan->UseVisualStyleBackColor = true;
			// 
			// rbSort
			// 
			this->rbSort->AutoSize = true;
			this->rbSort->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbSort->Location = System::Drawing::Point(14, 49);
			this->rbSort->Name = L"rbSort";
			this->rbSort->Size = System::Drawing::Size(92, 21);
			this->rbSort->TabIndex = 2;
			this->rbSort->Text = L"Sort Table";
			this->rbSort->UseVisualStyleBackColor = true;
			// 
			// rbListHash
			// 
			this->rbListHash->AutoSize = true;
			this->rbListHash->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbListHash->Location = System::Drawing::Point(14, 72);
			this->rbListHash->Name = L"rbListHash";
			this->rbListHash->Size = System::Drawing::Size(121, 21);
			this->rbListHash->TabIndex = 3;
			this->rbListHash->Text = L"ListHash Table";
			this->rbListHash->UseVisualStyleBackColor = true;
			// 
			// rbArrayHash
			// 
			this->rbArrayHash->AutoSize = true;
			this->rbArrayHash->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbArrayHash->Location = System::Drawing::Point(14, 95);
			this->rbArrayHash->Name = L"rbArrayHash";
			this->rbArrayHash->Size = System::Drawing::Size(133, 21);
			this->rbArrayHash->TabIndex = 4;
			this->rbArrayHash->Text = L"ArrayHash Table";
			this->rbArrayHash->UseVisualStyleBackColor = true;
			// 
			// rbTree
			// 
			this->rbTree->AutoSize = true;
			this->rbTree->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbTree->Location = System::Drawing::Point(14, 118);
			this->rbTree->Name = L"rbTree";
			this->rbTree->Size = System::Drawing::Size(96, 21);
			this->rbTree->TabIndex = 5;
			this->rbTree->Text = L"Tree Table";
			this->rbTree->UseVisualStyleBackColor = true;
			// 
			// rbAVL
			// 
			this->rbAVL->AutoSize = true;
			this->rbAVL->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbAVL->Location = System::Drawing::Point(14, 141);
			this->rbAVL->Name = L"rbAVL";
			this->rbAVL->Size = System::Drawing::Size(122, 21);
			this->rbAVL->TabIndex = 6;
			this->rbAVL->Text = L"AVLTree Table";
			this->rbAVL->UseVisualStyleBackColor = true;
			// 
			// lblEff
			// 
			this->lblEff->AutoSize = true;
			this->lblEff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->lblEff->Location = System::Drawing::Point(265, 378);
			this->lblEff->Name = L"lblEff";
			this->lblEff->Size = System::Drawing::Size(110, 24);
			this->lblEff->TabIndex = 7;
			this->lblEff->Text = L"Efficiecny: 0";
			// 
			// tbAmount
			// 
			this->tbAmount->Location = System::Drawing::Point(305, 27);
			this->tbAmount->Name = L"tbAmount";
			this->tbAmount->Size = System::Drawing::Size(100, 20);
			this->tbAmount->TabIndex = 8;
			this->tbAmount->Text = L"100";
			// 
			// tbMaxKey
			// 
			this->tbMaxKey->Location = System::Drawing::Point(305, 54);
			this->tbMaxKey->Name = L"tbMaxKey";
			this->tbMaxKey->Size = System::Drawing::Size(100, 20);
			this->tbMaxKey->TabIndex = 9;
			this->tbMaxKey->Text = L"100";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(203, 27);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 17);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Records amnt:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(236, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(63, 17);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Max key:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->btnCreate);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->tbMaxKey);
			this->groupBox1->Controls->Add(this->tbAmount);
			this->groupBox1->Controls->Add(this->rbAVL);
			this->groupBox1->Controls->Add(this->rbTree);
			this->groupBox1->Controls->Add(this->rbArrayHash);
			this->groupBox1->Controls->Add(this->rbListHash);
			this->groupBox1->Controls->Add(this->rbSort);
			this->groupBox1->Controls->Add(this->rbScan);
			this->groupBox1->Location = System::Drawing::Point(263, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(411, 179);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Table settings";
			// 
			// btnCreate
			// 
			this->btnCreate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnCreate->Location = System::Drawing::Point(250, 118);
			this->btnCreate->Name = L"btnCreate";
			this->btnCreate->Size = System::Drawing::Size(155, 44);
			this->btnCreate->TabIndex = 12;
			this->btnCreate->Text = L"Create table";
			this->btnCreate->UseVisualStyleBackColor = true;
			this->btnCreate->Click += gcnew System::EventHandler(this, &MyForm::btnCreate_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->btnDelete);
			this->groupBox2->Controls->Add(this->btnSearch);
			this->groupBox2->Controls->Add(this->btnAdd);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->tbSearchResult);
			this->groupBox2->Controls->Add(this->tbKey);
			this->groupBox2->Location = System::Drawing::Point(263, 197);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(410, 162);
			this->groupBox2->TabIndex = 13;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Records manip";
			// 
			// btnDelete
			// 
			this->btnDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnDelete->Location = System::Drawing::Point(168, 124);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(75, 32);
			this->btnDelete->TabIndex = 6;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &MyForm::btnDelete_Click);
			// 
			// btnSearch
			// 
			this->btnSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnSearch->Location = System::Drawing::Point(168, 71);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(75, 32);
			this->btnSearch->TabIndex = 5;
			this->btnSearch->Text = L"Search";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &MyForm::btnSearch_Click);
			// 
			// btnAdd
			// 
			this->btnAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnAdd->Location = System::Drawing::Point(168, 19);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(75, 32);
			this->btnAdd->TabIndex = 4;
			this->btnAdd->Text = L"Add";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &MyForm::btnAdd_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(302, 64);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(48, 17);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Result";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(64, 63);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 17);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Key";
			// 
			// tbSearchResult
			// 
			this->tbSearchResult->Location = System::Drawing::Point(289, 84);
			this->tbSearchResult->Name = L"tbSearchResult";
			this->tbSearchResult->Size = System::Drawing::Size(79, 20);
			this->tbSearchResult->TabIndex = 1;
			// 
			// tbKey
			// 
			this->tbKey->Location = System::Drawing::Point(43, 83);
			this->tbKey->Name = L"tbKey";
			this->tbKey->Size = System::Drawing::Size(79, 20);
			this->tbKey->TabIndex = 0;
			// 
			// rtbTree
			// 
			this->rtbTree->Location = System::Drawing::Point(13, 427);
			this->rtbTree->Name = L"rtbTree";
			this->rtbTree->Size = System::Drawing::Size(660, 380);
			this->rtbTree->TabIndex = 14;
			this->rtbTree->Text = L"";
			// 
			// btnPrintTree
			// 
			this->btnPrintTree->Location = System::Drawing::Point(573, 372);
			this->btnPrintTree->Name = L"btnPrintTree";
			this->btnPrintTree->Size = System::Drawing::Size(100, 41);
			this->btnPrintTree->TabIndex = 15;
			this->btnPrintTree->Text = L"Print tree";
			this->btnPrintTree->UseVisualStyleBackColor = true;
			this->btnPrintTree->Click += gcnew System::EventHandler(this, &MyForm::btnPrintTree_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(685, 819);
			this->Controls->Add(this->btnPrintTree);
			this->Controls->Add(this->rtbTree);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lblEff);
			this->Controls->Add(this->dgv);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgv))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



private: System::Void btnCreate_Click(System::Object^ sender, System::EventArgs^ e) {
	int amount = Convert::ToInt32(tbAmount->Text);
	int maxKey = Convert::ToInt32(tbMaxKey->Text);

	if (rbScan->Checked)        model->initScanTable(amount);
	else if (rbSort->Checked)   model->initSortTable(amount);
	else if (rbListHash->Checked) model->initListHashTable(amount);
	else if (rbArrayHash->Checked) model->initArrayHashTable(amount);
	else if (rbTree->Checked)   model->initTreeTable();
	else if (rbAVL->Checked)    model->initAVLTreeTable();

	model->generateRecords(amount, maxKey);

	updDataGridView();

	lblEff->Text = "Efficiency: " + model->getEfficiency().ToString();
}
private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
	int key = Convert::ToInt32(tbKey->Text);
	double value = (rand() % 1000) / 10.0;

	model->insertRecord(Record<int, double>{key, value});

	updDataGridView();
	lblEff->Text = "Efficiency: " + model->getEfficiency().ToString();
}
private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
	int key = Convert::ToInt32(tbKey->Text);
	bool found = model->findRecord(key);

	tbSearchResult->Text = found ? "Found" : "Not Found";
	lblEff->Text = "Efficiency: " + model->getEfficiency().ToString();
}
private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
	int key = Convert::ToInt32(tbKey->Text);
	model->deleteRecord(key);

	updDataGridView();

	lblEff->Text = "Efficiency: " + model->getEfficiency().ToString();
}
private: System::Void updDataGridView() {
	dgv->Rows->Clear();

	auto records = model->getAllRecords();
	for (auto& rec : records) {
		dgv->Rows->Add(rec.key, rec.val);
	}

	PrintTreeToRichText();
}

private: System::Void btnPrintTree_Click(System::Object^ sender, System::EventArgs^ e) {
	PrintTreeToRichText();
}

	   private: System::Void PrintTreeToRichText() {
		   // Получаем std::string
		   std::string tree = model->getTreeAsString();
		   // Конвертим в System::String^
		   msclr::interop::marshal_context ctx;
		   String^ managed = ctx.marshal_as<String^>(tree);
		   // Выводим
		   rtbTree->Clear();
		   rtbTree->AppendText(managed);
	   }

};
}
