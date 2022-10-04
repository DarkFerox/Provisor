#include <Windows.h>
#include <string>
#include <msclr\marshal.h>
#include <msclr/marshal_cppstd.h>

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "CoinBase.h"

using boost::property_tree::ptree;

System::String^ StringToSysString(std::string& from)
{
	wchar_t wstr[5000];													//This need for
	MultiByteToWideChar(CP_UTF8, 0, from.c_str(), -1, wstr, 5000);		//cirillian output
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

CoinBase::CoinBase()
{
	coins = gcnew System::Collections::Generic::List<Coin^>;
}

CoinBase::~CoinBase()
{
	delete coins;
}

void CoinBase::LoadCoins()
{
	ptree jsonTree;
	read_json("coins.json", jsonTree);
	for (auto child : jsonTree.get_child("coins"))
	{
		Coin^ coin = gcnew Coin;
		coin->name = StringToSysString(child.second.get<std::string>("name"));
		coin->symbol = StringToSysString(child.second.get<std::string>("sumbol"));
		coin->contract = StringToSysString(child.second.get<std::string>("contract"));
		if (!coins->Contains(coin)) coins->Add(coin);
	}
}

void CoinBase::SaveCoins() {
	ptree toJson;
    ptree ptCoins;
	for each (Coin ^ coin in coins)
	{
		ptree ptCoin;
		ptCoin.put("name", SysStringToString(coin->name));
		ptCoin.put("symbol", SysStringToString(coin->symbol));
		ptCoin.put("contract", SysStringToString(coin->contract));
		ptCoins.push_back(std::make_pair("", ptCoin));
	}
	toJson.add_child("coins", ptCoins);
	write_json("coins.json", toJson);
}