#pragma once

#include <cliext/map>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <msclr\marshal.h>
#include <msclr/marshal_cppstd.h>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

System::String^ StringToSysString(std::string& from)
{
	wchar_t wstr[5000];
	MultiByteToWideChar(CP_UTF8, 0, from.c_str(), -1, wstr, 5000);		//This need for cirillian output
	System::String^ sysString = gcnew System::String(wstr);
	return sysString;
}

std::string SysStringToString(System::String^ from)
{
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(from)).ToPointer();
	std::string result = chars;
	System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)chars));
	return result;
}

ref struct Coin
{
	System::String^ name = "";
	System::String^ symbol = "";
	System::String^ contract = "";

	bool operator <(const Coin^ other)
	{
		return this->name < other->name;
	}
};

ref class CoinBase
{
	typedef cliext::map<Coin^, System::Collections::Generic::List<int>^> coinsMap;
private:
	coinsMap^ coins;

public:
	CoinBase()
	{
		coins = gcnew coinsMap;
		LoadCoins();
	}
	~CoinBase()
	{
		delete coins;
	}
	
	coinsMap^ GetCoins()
	{
		return coins;
	}

	void LoadCoins()
	{
		using boost::property_tree::ptree;
		std::ifstream inputFile{ "coins.json" };
		try
		{
			if (!inputFile.is_open()) throw std::runtime_error{ "Unable to open file" };
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what();
		}
		ptree jsonTree;
		read_json(inputFile, jsonTree);
		for (auto child : jsonTree.get_child("coins"))
		{
			Coin^ coin = gcnew Coin;
			coin->name = StringToSysString(child.second.get<std::string>("name"));
			coin->symbol = StringToSysString(child.second.get<std::string>("symbol"));
			coin->contract = StringToSysString(child.second.get<std::string>("contract"));
			if (coins->count(coin) == 0) coins[coin] = gcnew System::Collections::Generic::List<int>;			
		}
	}

	void SaveCoins()
	{
		using boost::property_tree::ptree;
		ptree toJson;
		ptree ptCoins;
		for each (auto coin in coins)
		{
			ptree ptCoin;
			ptCoin.put("name", SysStringToString(coin->first->name));
			ptCoin.put("symbol", SysStringToString(coin->first->symbol));
			ptCoin.put("contract", SysStringToString(coin->first->contract));
			ptCoins.push_back(std::make_pair("", ptCoin));
		}
		toJson.add_child("coins", ptCoins);
		write_json("coins.json", toJson);
	}
};