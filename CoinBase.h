#pragma once

ref struct Coin
{
	System::String^ name;
	System::String^ symbol;
	System::String^ contract;
};

ref class CoinBase
{
private:
	System::Collections::Generic::List<Coin^>^ coins;
public:
	CoinBase();
	~CoinBase();

	void LoadCoins();
	void SaveCoins();
};