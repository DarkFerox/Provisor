#pragma once

#include <cliext/map>
#include <cliext/queue>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <msclr\marshal.h>
#include <msclr/marshal_cppstd.h>
#include "Client.h"

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
	System::String^ name;
	System::String^ symbol;
	System::String^ contract;
	cliext::queue<System::UInt32> time;
	cliext::queue<System::Double> price;
	
	bool operator <(const Coin^ other)
	{
		return this->name < other->name;
	}
};

ref class CoinBase
{
	typedef cliext::map<System::String^, Coin^> coinsMap;
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

	bool ContractIsValid(System::String^ contract)
	{
		if (contract->Length < 42) return false;
		if (contract[0] != '0' && contract[1] != 'x') return false;
		return true;
	}

	void LoadCoins()
	{
		std::ifstream inputFile{ "coins.json" };
		try
		{
			if (!inputFile.is_open()) throw std::runtime_error{ "Unable to open file" };
		}
		catch (std::exception& ex)
		{
			std::cerr << ex.what();
		}
		boost::property_tree::ptree jsonTree;
		read_json(inputFile, jsonTree);
		for (auto child : jsonTree.get_child("coins"))
		{
			Coin^ coin = gcnew Coin;
			coin->name = StringToSysString(child.second.get<std::string>("name"));
			coin->symbol = StringToSysString(child.second.get<std::string>("symbol"));
			coin->contract = StringToSysString(child.second.get<std::string>("contract"));
			if (coins->count(coin->name) == 0) coins[coin->name] = coin;			
		}
	}

	void SaveCoins()
	{
		boost::property_tree::ptree toJson;
		boost::property_tree::ptree ptCoins;
		for each (auto coin in coins)
		{
			boost::property_tree::ptree ptCoin;
			ptCoin.put("name", SysStringToString(coin->second->name));
			ptCoin.put("symbol", SysStringToString(coin->second->symbol));
			ptCoin.put("contract", SysStringToString(coin->second->contract));
			ptCoins.push_back(std::make_pair("", ptCoin));
		}
		toJson.add_child("coins", ptCoins);
		write_json("coins.json", toJson);
	}

	std::string GetResponseByContract(System::String^ contract)
	{
		std::string response = GetResponse(SysStringToString(contract));
		return response;
	}

	boost::property_tree::ptree JsonToPtree(std::string& json)
	{
		std::stringstream fromJson(json);
		boost::property_tree::ptree response;
		boost::property_tree::read_json(fromJson, response);
		return response;
	}

	void ResponseToCoin(boost::property_tree::ptree& response)
	{
		Coin^ coin = coins[StringToSysString(response.get_child("data").get<std::string>("name"))];
		coin->time.push(response.get<System::UInt32>("updated_at"));
		coin->price.push(response.get<System::Double>("price_BNB"));
		const System::UInt32 HOUR = 3600;
		System::UInt32 period = coin->time.back() - coin->time.front();
		while (period > HOUR)
		{
			coin->time.pop();
			coin->price.pop();
			period = coin->time.back() - coin->time.front();
		}
	}
};