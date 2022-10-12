#pragma once

#include "CoinBase.h"

#include <Windows.h>
#include <iostream>
#include <cstdlib>

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
	private: System::Windows::Forms::ListView^ listViewCoins;

	private: System::Windows::Forms::ColumnHeader^ ch_coin;

	private: System::Windows::Forms::ColumnHeader^ ch_currentPrice;
	private: System::Windows::Forms::ColumnHeader^ ch_priceChange;
	private: System::Windows::Forms::ColumnHeader^ ch_buyPrice;
	private: System::Windows::Forms::ColumnHeader^ ch_profit;

	private:
		
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->buttonAddCoin = (gcnew System::Windows::Forms::Button());
			this->smartContractTextBox = (gcnew System::Windows::Forms::TextBox());
			this->listViewCoins = (gcnew System::Windows::Forms::ListView());
			this->ch_coin = (gcnew System::Windows::Forms::ColumnHeader());
			this->ch_currentPrice = (gcnew System::Windows::Forms::ColumnHeader());
			this->ch_priceChange = (gcnew System::Windows::Forms::ColumnHeader());
			this->ch_buyPrice = (gcnew System::Windows::Forms::ColumnHeader());
			this->ch_profit = (gcnew System::Windows::Forms::ColumnHeader());
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
			this->buttonAddCoin->Click += gcnew System::EventHandler(this, &MainForm::buttonAddCoin_Click);
			// 
			// smartContractTextBox
			// 
			this->smartContractTextBox->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->smartContractTextBox->Location = System::Drawing::Point(105, 15);
			this->smartContractTextBox->Name = L"smartContractTextBox";
			this->smartContractTextBox->Size = System::Drawing::Size(514, 20);
			this->smartContractTextBox->TabIndex = 1;
			// 
			// listViewCoins
			// 
			this->listViewCoins->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->ch_coin, this->ch_currentPrice,
					this->ch_priceChange, this->ch_buyPrice, this->ch_profit
			});
			this->listViewCoins->HideSelection = false;
			this->listViewCoins->Location = System::Drawing::Point(105, 52);
			this->listViewCoins->MultiSelect = false;
			this->listViewCoins->Name = L"listViewCoins";
			this->listViewCoins->Size = System::Drawing::Size(515, 300);
			this->listViewCoins->TabIndex = 2;
			this->listViewCoins->UseCompatibleStateImageBehavior = false;
			this->listViewCoins->View = System::Windows::Forms::View::Details;
			// 
			// ch_coin
			// 
			this->ch_coin->Text = L"Coin";
			// 
			// ch_currentPrice
			// 
			this->ch_currentPrice->Text = L"Current Price";
			this->ch_currentPrice->Width = 138;
			// 
			// ch_priceChange
			// 
			this->ch_priceChange->Text = L"Price change";
			this->ch_priceChange->Width = 88;
			// 
			// ch_buyPrice
			// 
			this->ch_buyPrice->Text = L"Buy price";
			// 
			// ch_profit
			// 
			this->ch_profit->Text = L"Profit";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 509);
			this->Controls->Add(this->listViewCoins);
			this->Controls->Add(this->smartContractTextBox);
			this->Controls->Add(this->buttonAddCoin);
			this->Name = L"MainForm";
			this->Text = L"Provisor";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public: System::Void RefreshCoins();

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	
	private: System::Void buttonAddCoin_Click(System::Object^ sender, System::EventArgs^ e) {
		
	}
	
	};
}