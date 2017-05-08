#include <SDKDDKVer.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <tchar.h>

#include "UnitNames.h"
#include "WeaponTypes.h"
#include "Includes/StormLib.h"

using namespace std;

static int ExtractFile(const TCHAR * szArchiveName, char * szArchivedFile, const TCHAR * szFileName)
{
	HANDLE hMpq = NULL;          // Open archive handle
	HANDLE hFile = NULL;          // Archived file handle
	HANDLE handle = NULL;          // Disk file handle
	int    nError = ERROR_SUCCESS; // Result value

								   // Open an archive, e.g. "d2music.mpq"
	if (nError == ERROR_SUCCESS)
	{
		if (!SFileOpenArchive(szArchiveName, 0, 0, &hMpq))
			nError = GetLastError();
	}

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if (nError == ERROR_SUCCESS)
	{
		if (!SFileOpenFileEx(hMpq, szArchivedFile, 0, &hFile))
			nError = GetLastError();
	}

	// Create the target file
	if (nError == ERROR_SUCCESS)
	{
		handle = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
		if (handle == INVALID_HANDLE_VALUE)
			nError = GetLastError();
	}

	// Read the file from the archive
	if (nError == ERROR_SUCCESS)
	{
		char  szBuffer[0x10000];
		DWORD dwBytes = 1;

		while (dwBytes > 0)
		{
			SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
			if (dwBytes > 0)
				WriteFile(handle, szBuffer, dwBytes, &dwBytes, NULL);
		}
	}

	// Cleanup and exit
	if (handle != NULL)
		CloseHandle(handle);
	if (hFile != NULL)
		SFileCloseFile(hFile);
	if (hMpq != NULL)
		SFileCloseArchive(hMpq);

	return nError;
}

static int InsertFile(const TCHAR * szArchiveName, const char * szArchivedFile, const TCHAR * szFileName)
{
	HANDLE hMpq = NULL;          // Open archive handle
	HANDLE hFile = NULL;          // Archived file handle
	HANDLE handle = NULL;          // Disk file handle
	int    nError = ERROR_SUCCESS; // Result value

								   // Open an archive, e.g. "d2music.mpq"
	if (nError == ERROR_SUCCESS)
	{
		if (!SFileOpenArchive(szArchiveName, 0, 0, &hMpq))
			nError = GetLastError();
	}

	cout << "ERROR open: " << nError << endl;

	if (nError == ERROR_SUCCESS)
	{
		if (!SFileRemoveFile(hMpq, szArchivedFile, 0))
			nError = GetLastError();
	}

	cout << "ERROR remove: " << nError << endl;
	if (nError == ERROR_SUCCESS)
	{
		if (!SFileAddFileEx(hMpq, szFileName, szArchivedFile, MPQ_FILE_REPLACEEXISTING, MPQ_COMPRESSION_ZLIB, 0))
			nError = GetLastError();
	}

	cout << "ERROR add file: " << nError << endl;

	if (handle != NULL)
		CloseHandle(handle);
	if (hFile != NULL)
		SFileCloseFile(hFile);
	if (hMpq != NULL)
		SFileCloseArchive(hMpq);

	return nError;
}

std::string hex_to_string(const std::string& in) {
	std::string output;

	if ((in.length() % 2) != 0) {
		throw std::runtime_error("String is not valid length ...");
	}

	size_t cnt = in.length() / 2;

	for (size_t i = 0; cnt > i; ++i) {
		uint32_t s = 0;
		std::stringstream ss;
		ss << std::hex << in.substr(i * 2, 2);
		ss >> s;

		output.push_back(static_cast<unsigned char>(s));
	}

	return output;
}

int hex_value(char in)
{
	if (in >= '0' && in <= '9')
		return in - '0';
	if (in >= 'a' && in <= 'f')
		return 10 + in - 'a';
	return -1;
}

uint32_t string_to_int(const string& input, bool LittleEndian = false)
{
	uint32_t res = 0;
	int len = input.length();
	if (LittleEndian)
	{
		for (int i = 0; i < len; i++)
		{
			if (input[len - i - 1] >= 0)
				res = res + pow(16, i * 2) * input[len - i - 1];
			else
				res = res + pow(16, i * 2) * (256 + input[len - i - 1]);
		}
	}
	else {
		for (int i = 0; i < len; i++)
		{
			if (input[i] >= 0)
				res = res + pow(16, i * 2) * input[i];
			else
				res = res + pow(16, i * 2) * (256 + input[i]);
		}
	}

	return res;
}

const char* int_to_string(const uint32_t input, int bytes, bool LittleEndian = false)
{
	char* res = new char[bytes];

	//string res2 = "";
	int value = input;

	if (LittleEndian)
	{
		for (int i = bytes - 1; i >= 0; i = i - 1)
		{
			//res[i] = value / pow(256, i);
			char val = value / pow(256, i);
			res[i] = val;
			if (value > 0)
				value = value % (int)pow(256, i);
		}
	}
	else {
		for (int i = bytes - 1; i >= 0; i = i - 1)
		{
			//res[bytes - i + 1] = value / pow(256, i);
			char val = value / pow(256, i);
			res[bytes - i - 1] = val;
			if (value > 0)
				value = value % (int)pow(256, i);
		}
	}

	return res;
}

std::string string_to_hex(const std::string& input)
{
	static const char* const lut = "0123456789abcdef";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);

	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

uint32_t hex_to_int(const std::string& in, int bits) {
	uint32_t res = 0;

	if (bits != 16)
	{

		for (int i = 0; i < in.length(); i++)
		{

			if (i % 2 == 0)
				res += pow(16, i) * hex_value(in[i + 1]);
			else
				res += pow(16, i) * hex_value(in[i - 1]);
		}


	}

	else {
		for (int i = in.length() - 1; i >= 0; i = i - 1)
		{
			res += pow(16, in.length() - i - 1) * hex_value(in[i]);
		}
	}

	return res;
}

/*const int ImportantUnits[40] =
{
0, 1, 2, 3, 5, 7, 8, 12, 32, 34, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62,
63, 64, 65, 66, 67, 68, 71, 72, 73, 83, 85, 103
};

const int ImportantWeapons[70] =
{
1, 3, 5, 7, 8, 9, 12, 14, 16, 17, 20, 21,
26, 28, 30, 31, 36, 39, 41, 43, 44, 47, 49,
53, 54, 61, 63, 65, 67, 70, 71, 74, 75, 78,
80, 83, 85, 110, 112
};*/

/*const int ImportantUnits[40] =
{
0, 7, 37
};

const int ImportantWeapons[70] =
{
0, 13, 35
};

const int ImportantCount = 3;*/

struct UnitData
{
	bool UseDef;
	string Name;
	uint32_t HP;
	uint16_t Shield;
	uint8_t Armor;
	uint16_t BuildTime;
	uint16_t MineralCost;
	uint16_t GasCost;
	uint16_t StringNr;
	//uint16_t WeaponDamage;
	//uint16_t UpgradeBonusWeaponDamage;
};

struct WeaponData
{
	string Name;
	uint16_t Damage;
};

int main(int argc, char* argv[])
{
	cout << "Starting map generation" << endl;
	UnitData* units = new UnitData[230]();
	WeaponData* weapons = new WeaponData[131];

	const size_t newsize = 512;
	size_t convertedChars = 0;
	wchar_t arg1[512];
	mbstowcs_s(&convertedChars, arg1, strlen(argv[2]) + 1, argv[2], _TRUNCATE);
	//mbstowcs_s(argv[2], arg1, (arg1, argv[2], 512);

	std::wstring InputMap(arg1);// = L"../maps/GPMaps/(2)Astral Balance OG.scx";

								//mbstowcs(arg1, argv[3], 512);
	mbstowcs_s(&convertedChars, arg1, strlen(argv[3]) + 1, argv[3], _TRUNCATE);

	std::wstring OutputMap(arg1);

	mbstowcs_s(&convertedChars, arg1, strlen(argv[1]) + 1, argv[1], _TRUNCATE);

	cout << "Converted inputs to wstrings" << endl;

	wchar_t ExtractedPath[80];
	wcscpy_s(ExtractedPath, L"Temp/Extracted");
	wcscat_s(ExtractedPath, arg1);
	wcscat_s(ExtractedPath, L".chk");

	ExtractFile(InputMap.c_str(), "staredit/scenario.chk", ExtractedPath);

	cout << "Extracted files" << endl;

	ifstream f(ExtractedPath, ios::in | ios::binary);

	std::string str;

	f.seekg(0, std::ios::end);
	str.reserve(f.tellg());
	f.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());

	//Test.erase(std::remove(Test.begin(), Test.end(), ' '), Test.end());

	//str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	//str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

	//cout << hex_to_string(Test) << endl;

	/*int offset = str.find("55 4e49 78");

	if (offset == string::npos)
	{
	offset = str.find("554e 4978");
	}*/


	int offset = str.find("UNIx");

	offset += 8;

	string before = str.substr(0, offset);

	string Chunk = "";

	for (int unit = 0; unit < 229; unit++)
	{
		Chunk = str.substr(offset, 1);
		units[unit].UseDef = hex_to_int(string_to_hex(Chunk), 8);

		//cout << units[unit].HP << endl;

		offset += 1;
	}

	//HPs
	for (int unit = 0; unit < 227; unit++)
	{
		units[unit].Name = DefaultUnitDisplayName[unit];
		Chunk = str.substr(offset, 4);

		//units[unit].HP = hex_to_int(string_to_hex(Chunk), 32);
		units[unit].HP = string_to_int(Chunk);

		//cout << units[unit].HP << endl;

		offset += 4;
	}

	offset += 2;

	//Shields
	for (int unit = 0; unit < 228; unit++)
	{

		Chunk = str.substr(offset, 2);

		units[unit].Shield = string_to_int(Chunk, true);

		offset += 2;

		string_to_int(Chunk, true);
	}

	offset += 1;

	//Armor
	for (int unit = 0; unit < 228; unit++)
	{

		Chunk = str.substr(offset, 1);

		units[unit].Armor = string_to_int(Chunk, true);

		//cout << units[unit].Name << ": " << (int)units[unit].Armor << endl;

		offset += 1;
	}

	//offset -= 6;

	//offset += 1;

	//Buildtime
	for (int unit = 0; unit < 228; unit++)
	{

		Chunk = str.substr(offset, 2);

		units[unit].BuildTime = string_to_int(Chunk, false);

		//cout << units[unit].Name << ": " << (int)units[unit].BuildTime << endl;

		offset += 2;
	}

	//Minerals
	for (int unit = 0; unit < 228; unit++)
	{

		Chunk = str.substr(offset, 2);

		units[unit].MineralCost = string_to_int(Chunk, false);

		//cout << units[unit].Name << ": " << (int)units[unit].MineralCost << endl;

		offset += 2;
	}

	//Gas Cost
	for (int unit = 0; unit < 228; unit++)
	{

		Chunk = str.substr(offset, 2);

		units[unit].GasCost = string_to_int(Chunk, true);

		//cout << units[unit].Name << ": " << (int)units[unit].GasCost << endl;

		offset += 2;
	}

	//StringNr
	for (int unit = 0; unit < 228; unit++)
	{

		Chunk = str.substr(offset, 2);

		units[unit].StringNr = string_to_int(Chunk, false);

		offset += 2;
	}

	//BaseWp
	for (int unit = 0; unit < 130; unit++)
	{

		Chunk = str.substr(offset, 2);

		weapons[unit].Name = WeaponTypes[unit];
		weapons[unit].Damage = string_to_int(Chunk, false);

		//cout << weapons[unit].Name << ": " << (int)weapons[unit].Damage << endl;

		offset += 2;
	}

	//offset = str.find("UPGx");

	string after = str.substr(offset);

	f.close();

	cout << "Reading new values" << endl;

	ifstream Input("Temp/Instance" + string(argv[1]) + ".txt");

	int ImportantCount = 0;
	Input >> ImportantCount;

	vector<int> ImportantUnits;
	vector<int> ImportantWeapons;

	int nr;
	for (int i = 0; i < ImportantCount; i++)
	{
		Input >> nr;
		ImportantUnits.push_back(nr);
	}

	for (int i = 0; i < ImportantCount; i++)
	{
		Input >> nr;
		ImportantWeapons.push_back(nr);
	}

	vector<int> values;
	while (Input >> nr)
	{
		values.push_back(nr);
	}


	cout << "Read new values" << endl;

	for (int i = 0; i < ImportantCount; i++)
	{
		units[ImportantUnits[i]].UseDef = false;


		cout << weapons[ImportantWeapons[i]].Name << " Attack: " << (int)weapons[ImportantWeapons[i]].Damage << " to " << values[i] << endl;

		cout << units[ImportantUnits[i]].Name << " HP: " << (int)units[ImportantUnits[i]].HP << " to " << values[ImportantCount + i] << endl;

		units[ImportantUnits[i]].HP = values[ImportantCount + i];

		weapons[ImportantWeapons[i]].Damage = values[i];
	}

	//Rewrite it now
	wchar_t ResultPath[250];
	wcscpy_s(ResultPath, L"Temp/result");
	wcscat_s(ResultPath, arg1);
	wcscat_s(ResultPath, L".chk");

	ofstream f2(ResultPath, ios::out | ios::binary);

	f2 << before;



	for (int unit = 0; unit < 229; unit++)
	{
		//const char* towrite = int_to_string(units[unit].UseDef, 1, true);
		const char* towrite = int_to_string(false, 1, true);
		for (int i = 0; i < 1; i++)
		{

			f2 << std::hex << towrite[i];
		}
	}

	//HPs
	for (int unit = 0; unit < 227; unit++)
	{
		const char* towrite = int_to_string(units[unit].HP, 4, true);
		for (int i = 0; i < 4; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	f2 << std::hex << ' ' << ' ' << ' ';

	//Shields
	for (int unit = 0; unit < 228; unit++)
	{

		const char* towrite = int_to_string(units[unit].Shield, 2, true);
		for (int i = 0; i < 2; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	/*f2 << std::hex << ' '; */

	//Armor
	for (int unit = 0; unit < 228; unit++)
	{

		const char* towrite = int_to_string(units[unit].Armor, 1, true);
		for (int i = 0; i < 1; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	//offset -= 6;

	//offset += 1;

	//Buildtime
	for (int unit = 0; unit < 228; unit++)
	{
		const char* towrite = int_to_string(units[unit].BuildTime, 2, true);
		for (int i = 0; i < 2; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	//Minerals
	for (int unit = 0; unit < 228; unit++)
	{
		const char* towrite = int_to_string(units[unit].MineralCost, 2, true);
		for (int i = 0; i < 2; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	//Gas Cost
	for (int unit = 0; unit < 228; unit++)
	{
		const char* towrite = int_to_string(units[unit].GasCost, 2, false);
		for (int i = 0; i < 2; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	//StringNr
	for (int unit = 0; unit < 228; unit++)
	{
		const char* towrite = int_to_string(units[unit].StringNr, 2, false);
		for (int i = 0; i < 2; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	//BaseWp
	for (int unit = 0; unit < 130; unit++)
	{
		const char* towrite = int_to_string(weapons[unit].Damage, 2, true);
		for (int i = 0; i < 2; i++)
		{
			f2 << std::hex << towrite[i];
		}
	}

	f2 << after;

	f2.close();


	cout << InsertFile(OutputMap.c_str(), "staredit\\scenario.chk", ResultPath) << endl;

	//char x;
	//cin >> x;

	return 0;
}

