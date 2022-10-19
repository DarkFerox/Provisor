#pragma once

#ifdef CLIENTLIBRARY_EXPORTS
#define CLIENTLIBRARY_API __declspec(dllexport)
#else
#define CLIENTLIBRARY_API __declspec(dllimport)
#endif

#include <string>

extern "C" CLIENTLIBRARY_API std::string GetResponse(std::string contract);