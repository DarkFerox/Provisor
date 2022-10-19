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
	private: System::Windows::Forms::Label^ uncorrectContractLabel;
	private: System::Windows::Forms::Label^ testLabel;


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
			this->uncorrectContractLabel = (gcnew System::Windows::Forms::Label());
			this->testLabel = (gcnew System::Windows::Forms::Label());
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
			this->listViewCoins->Location = System::Drawing::Point(105, 58);
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
			this->ch_currentPrice->Width = 140;
			// 
			// ch_priceChange
			// 
			this->ch_priceChange->Text = L"Price change";
			this->ch_priceChange->Width = 88;
			// 
			// ch_buyPrice
			// 
			this->ch_buyPrice->Text = L"Buy price";
			this->ch_buyPrice->Width = 163;
			// 
			// ch_profit
			// 
			this->ch_profit->Text = L"Profit";
			// 
			// uncorrectContractLabel
			// 
			this->uncorrectContractLabel->AutoSize = true;
			this->uncorrectContractLabel->ForeColor = System::Drawing::Color::Red;
			this->uncorrectContractLabel->Location = System::Drawing::Point(102, 38);
			this->uncorrectContractLabel->Name = L"uncorrectContractLabel";
			this->uncorrectContractLabel->Size = System::Drawing::Size(0, 13);
			this->uncorrectContractLabel->TabIndex = 3;
			// 
			// testLabel
			// 
			this->testLabel->AutoSize = true;
			this->testLabel->Location = System::Drawing::Point(105, 365);
			this->testLabel->MaximumSize = System::Drawing::Size(500, 100);
			this->testLabel->MinimumSize = System::Drawing::Size(500, 100);
			this->testLabel->Name = L"testLabel";
			this->testLabel->Size = System::Drawing::Size(500, 100);
			this->testLabel->TabIndex = 4;
			this->testLabel->Text = L"TestLabel";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 509);
			this->Controls->Add(this->testLabel);
			this->Controls->Add(this->uncorrectContractLabel);
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

	public: System::Void RefreshCoins()
	{
		this->listViewCoins->Items->Clear();
		for each (auto coin in coinBase->GetCoins())
		{
			System::Windows::Forms::ListViewItem^ listViewItem = gcnew Windows::Forms::ListViewItem(coin->second->symbol);
			if (!coin->second->price.empty())
			{
				listViewItem->SubItems->Add(System::Convert::ToString(coin->second->price.back()));
				listViewItem->SubItems->Add(System::Convert::ToString(coin->second->price.front() - coin->second->price.back()));
			}
			this->listViewCoins->Items->Add(listViewItem);
		}		
	}

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		RefreshCoins();
	}

	private: System::String^ CheckResponse(std::string response)
	{
		if (response.find("error") == std::string::npos) return L"OK";
		boost::property_tree::ptree tree;
		std::stringstream stream(response);
		boost::property_tree::read_json(stream, tree);
		boost::property_tree::ptree root = tree.get_child("error");
		return StringToSysString(root.get<std::string>("message"));
	}
	
	private: System::Void buttonAddCoin_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!coinBase->ContractIsValid(smartContractTextBox->Text))
		{
			uncorrectContractLabel->Text = L"Uncorrect smart-contract";
			uncorrectContractLabel->ForeColor = System::Drawing::Color::Red;
			return;
		}
		std::string response = coinBase->GetResponseByContract(smartContractTextBox->Text);
		testLabel->Text = StringToSysString(response);
		if (CheckResponse(response) != "OK") return;
		testLabel->Text += L"\n" + CheckResponse(response);
		auto responsePt = coinBase->JsonToPtree(response);
		if (coinBase->GetCoins()->count(StringToSysString(responsePt.get_child("data").get<std::string>("name"))) != 0)
		{
			uncorrectContractLabel->Text = L"This smart-contract already added";
			uncorrectContractLabel->ForeColor = System::Drawing::Color::Red;
			return;
		}
		Coin^ coin = gcnew Coin;
		coin->name = StringToSysString(responsePt.get_child("data").get<std::string>("name"));
		coin->symbol = StringToSysString(responsePt.get_child("data").get<std::string>("symbol"));
		coin->contract = smartContractTextBox->Text;
		coinBase->GetCoins()[coin->name] = coin;
		uncorrectContractLabel->Text = L"Coin added to database";
		uncorrectContractLabel->ForeColor = System::Drawing::Color::Green;
		RefreshCoins();
	}
};
}