#pragma once
#include "stdafx.h"
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
#include "live_testing.h"
#include "Start_Page.h"

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
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button2;







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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(573, 422);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 440);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(145, 37);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(258, 450);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 17);
			this->label1->TabIndex = 2;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(458, 440);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(116, 37);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Close";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(597, 487);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Tutorial";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		static array<String^>^ vehical_list = {"","","","","","","","","","","","","","","","","","","","","","","","","","","",""};

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //initObjects();

			 pictureBox1->ImageLocation = "";
			 StreamReader^ DataIn = File::OpenText(VEHICAL_IMAGE_MAPPING);
			 String^ DataStr;
           int count = 0;
           while ((DataStr = DataIn->ReadLine()) != nullptr) 
           {
			   vehical_list[count] = DataStr;
               count++;   
           }

		   

			 FILE *log = fopen("log.txt","w+");
			 long double codebook[KC][P]={0};
			 readCodeBook(codebook,LBG_CODE_BOOK_PATH);
			 /*Initialize TDW vector*/
			 getTokhuraDistanceWeight();
			 int index = doLiveTesting(codebook);
			 fprintf(log, "%d\n", index);

			 if(index > -1){
				 pictureBox1->ImageLocation = vehical_list[index];
				 label1->Text = (gcnew String(OBJECTS[index]))->ToUpper();
			 }else{
				 pictureBox1->ImageLocation = "files/images/oops.jpeg";
				 label1->Text = "TRY AGAIN !!!!";
			 }
			 fclose(log);
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Hide();
		 }

private: System::Void Form1_Page_Load(System::Object^  sender, System::EventArgs^  e) {
			 button1->Enabled = false;
			 button2->Enabled = false;
		 }
};
}

