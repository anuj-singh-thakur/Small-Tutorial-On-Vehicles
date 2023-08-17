#pragma once
#include<stdlib.h>
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include "pre_define.h"
#include "generate_codebook.h"
#include "generate_universe.h"
#include "generate_models.h"
#include "utility.h"
#include "testing.h"
namespace SecondModel {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for Live_training
	/// </summary>
	public ref class Live_training : public System::Windows::Forms::Form
	{
	public:
		Live_training(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Live_training()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Label^  label2;



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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Live_training::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(272, 23);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter the Vehicle type to add ->";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(300, 68);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(121, 22);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(31, 235);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(130, 39);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Start Recording";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Live_training::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(265, 235);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(156, 39);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Training";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Live_training::button2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(31, 110);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(293, 34);
			this->textBox2->TabIndex = 4;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(330, 110);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(91, 34);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Browse";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Live_training::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(176, 173);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(96, 34);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Upload";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Live_training::button4_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(48, 354);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(344, 17);
			this->label2->TabIndex = 7;
			this->label2->Text = L"** Make Sure to Upload the file before Start recording";
			// 
			// Live_training
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(468, 380);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"Live_training";
			this->Text = L"Live Training";
			this->Load += gcnew System::EventHandler(this, &Live_training::Live_training_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		static String^ ext = "";

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 char vehicalName[FILE_NAME_SIZE] ={'\0'}; 
				 sprintf(vehicalName,"%s",textBox1->Text);
				 
				 char txtFileName[FILE_NAME_SIZE] ={'\0'}; 
			     char wavFileName[FILE_NAME_SIZE] ={'\0'}; 
				 char commandFormation[2*FILE_NAME_SIZE] = {'\0'};
				 char liveTrainingFileName[FILE_NAME_SIZE] ={'\0'}; 

				 
				 FILE *ptr = fopen(OBJECT_MAPPING_PATH,APPEND_MODE);
				 
				 fprintf(ptr,"\n%s",vehicalName);
				 fclose(ptr);
				 
				 for(int i = 1; i <=MAX_FILE_COUNT ; i++){
					getLiveTrainingFileName(txtFileName,vehicalName,i,FILE_FORMAT_TXT);
					getLiveTrainingFileName(wavFileName,vehicalName,i,FILE_FORMAT_WAV);
					
					getLiveTrainingFilePath(liveTrainingFileName,vehicalName,i,FILE_FORMAT_TXT);

					getLiveTrainingCommand(commandFormation,wavFileName,txtFileName);
					system(commandFormation);
					removeSilenceUsingMax(txtFileName,liveTrainingFileName);
				 }
							 
				 
			 }

	private: System::Void Live_training_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 startTraining();
			 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Browse
			 Stream^ myStream;
			 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

			 openFileDialog1->InitialDirectory = "c:\\";
			 openFileDialog1->Filter = "Files|*.jpg;*.jpeg;*.png";
			 openFileDialog1->FilterIndex = 2;
			 openFileDialog1->RestoreDirectory = true;

			 if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK){
				 if((myStream = openFileDialog1->OpenFile()) != nullptr){
					 textBox2->Text = openFileDialog1->FileName->ToString();
					 ext = System::IO::Path::GetExtension(openFileDialog1->FileName);
					 myStream->Close();
				 }
			 }
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Upload
			 if(textBox2->Text != "" && textBox1->Text != ""){
				 char imageFileName[FILE_NAME_SIZE] ={'\0'};
				 char vehicalFileName[FILE_NAME_SIZE] ={'\0'};
				 sprintf(vehicalFileName, "%s%s%s",IMAGE_PATH,textBox1->Text->ToString(),ext);
				 sprintf(imageFileName, "COPY \"%s\" %s", textBox2->Text->ToString(), vehicalFileName);
				 system(imageFileName);

				 FILE *ptr = fopen(VEHICAL_IMAGE_MAPPING, APPEND_MODE);
				 fprintf(ptr, "\n%s", vehicalFileName);
				 fclose(ptr);

			 }
		 }
};
}
