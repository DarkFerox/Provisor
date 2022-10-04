#pragma once

#include "CoinBase.h"

namespace Provisor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		CoinBase^ coinBase;
	public:
		MainForm(void)
		{
			InitializeComponent();
			coinBase = gcnew CoinBase;
		}

	protected:
		
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
			delete coinBase;
		}
	private: System::Windows::Forms::Button^ buttonAddCoin;
	private: System::Windows::Forms::TextBox^ smartContractTextBox;

	private:
		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->buttonAddCoin = (gcnew System::Windows::Forms::Button());
			this->smartContractTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// buttonAddCoin
			// 
			this->buttonAddCoin->Location = System::Drawing::Point(13, 13);
			this->buttonAddCoin->Name = L"buttonAddCoin";
			this->buttonAddCoin->Size = System::Drawing::Size(75, 23);
			this->buttonAddCoin->TabIndex = 0;
			this->buttonAddCoin->Text = L"Add coin";
			this->buttonAddCoin->UseVisualStyleBackColor = true;
			// 
			// smartContractTextBox
			// 
			this->smartContractTextBox->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->smartContractTextBox->Location = System::Drawing::Point(105, 15);
			this->smartContractTextBox->Name = L"smartContractTextBox";
			this->smartContractTextBox->Size = System::Drawing::Size(514, 20);
			this->smartContractTextBox->TabIndex = 1;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 509);
			this->Controls->Add(this->smartContractTextBox);
			this->Controls->Add(this->buttonAddCoin);
			this->Name = L"MainForm";
			this->Text = L"Provisor";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
};
}
