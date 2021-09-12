#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "newcpp.h"
#include "BasicSource.h"
#include "md5.h"

#include <filesystem> //#include <experimental/filesystem> 
namespace fs = std::filesystem; //namespace fs = std::experimental::filesystem;

const int virusDatabaseSize = 10000;
const string defenceProtocollName = "DefenceProtocoll.bat";

int virusCount = 0;

class virus {
public:
	string name;
	string signature;

	void Declare(string name, string sig) {
		this->name = name;
		this->signature = sig;
	}
};

virus database[virusDatabaseSize];

void AddVirus(string location, string name) {
	//Start opening your file
	ifstream inBigArrayfile;
	inBigArrayfile.open(location, std::ios::binary | std::ios::in);

	//Find length of file
	inBigArrayfile.seekg(0, std::ios::end);
	long Length = inBigArrayfile.tellg();
	inBigArrayfile.seekg(0, std::ios::beg);

	//Read in the data from your file
	char* InFileData = new char[Length];
	inBigArrayfile.read(InFileData, Length);

	string sig = md5(InFileData); //, Length).c_str();

	inBigArrayfile.close();
	delete[] InFileData;

	database[virusCount].Declare(name, sig);
	virusCount++;
}

//#include <iostream>
//#include <string>
//#include <fstream>
//#include <Urlmon.h>
//
//#include "newcpp.h"
//
//#include "BasicSource.h"
//
//string database = "Virus database";
//const int maxVirDBSize = 1000; //Maximum virus database size.
//const string defaultURL = "";
//const string defenceProtocollFileName = "DefenceProtocoll.bat"; //Defence macros file name. \
//																Note: to change to name with spaces, \
//																needed to change source of react function.
//
//#include <filesystem> //#include <experimental/filesystem> 
////namespace fs = std::experimental::filesystem;
//namespace fs = std::filesystem;
//
////WARNING: May be slow.
////WARNING: Checking by uppercasing and something not. Danger.
//string GetTypeBySignature(string sig) {
//	if (UpperString(sig.substr(0, 2)) == "MZ")
//		return "exe";
//	else if (UpperString(sig.substr(0, 2)) == "PK")
//		return "zip";
//	else if (UpperString(sig.substr(0, 3)) == "RAR")
//		return "rar";
//	else if (UpperString(sig.substr(0, 3)) == "%PDF") //?
//		return "pdf";
//	else if (UpperString(sig.substr(0, 4)) == "%!PS")
//		return "ps";
//	else if (UpperString(sig.substr(0, 8)) == "$SDI0001")
//		return "System Deployment Image";
//	else if (UpperString(sig.substr(0, 4)) == "8BPS")
//		return "psd";
//	else if (UpperString(sig.substr(0, 4)) == ".PNG")
//		return "png";
//	else if (UpperString(sig.substr(0, 4)) == ".ELF")
//		return "UNIX executable";
//	else if (UpperString(sig.substr(0, 8)) == "........")
//		return "Mach-O binary";
//	else if (UpperString(sig.substr(0, 2)) == "ÿû" || UpperString(sig.substr(0, 2)) == "ID3" || sig.substr(0, 2) == "ÿû" || sig.substr(0, 2) == "ID3")
//		return "mp3";
//	else if (UpperString(sig.substr(0, 2)) == "BM")
//		return "bmp"; //WARNING: Or dib.
//	else if (UpperString(sig.substr(0, 3)) == "KDM")
//		return "vmdk";
//	else if (UpperString(sig.substr(0, 4)) == "CR24")
//		return "crx";
//	else if (UpperString(sig.substr(0, 4)) == "AGD3")
//		return "fh8";
//	else if (UpperString(sig.substr(0, 4)) == "XAR!")
//		return "xar";
//	else if (UpperString(sig.substr(0, 8)) == "PMOCCMOC")
//		return "dat";
//	else if (UpperString(sig.substr(0, 3)) == "NES")
//		return "nes";
//	else if (UpperString(sig.substr(0, 3)) == "TOX")
//		return "tox";
//	else if (UpperString(sig.substr(0, 4)) == "MLVI")
//		return "mlv";
//	else if (sig.substr(0, 7) == "x.s.bb`")
//		return "dmg";
//	else if (UpperString(sig.substr(0, 4)) == "SZDD")
//		return "undetected"; //WARNING
//	else if (UpperString(sig.substr(0, 4)) == "MSCF")
//		return "cab";
//	else if (sig.substr(0, 4) == ".Eß£")
//		return "mkv"; //WARNING: May be also mka, mks, mk3d, webm.
//	else if (UpperString(sig.substr(0, 3)) == "MIL")
//		return "stg";
//	else if (sig.substr(0, 5) == "<?xml")
//		return "xml";
//	else if (sig.substr(0, 4) == ".asm")
//		return "wasm";
//	else if (sig.substr(0, 9) == "....G....")
//		return "mpg"; //WARNING: Or mpeg
//	else if (sig.substr(0, 4) == ".Lua")
//		return "luac";
//	else if (Contains(sig, "CD001"))
//		return "iso";
//	return sig; //"unknown"; //sig;
//}
//
//class virus {
//protected:
//	string name;
//
//	string signature;
//	string type;
//
//	string reaction = "None";
//public:
//	virus() {
//		name = "";
//		signature = "";
//		type = "";
//	}
//
//	virus(string mainName, string aliases, string signature, string reaction = "None") {
//		this->name = mainName;
//		this->signature = signature;
//		this->type = GetTypeBySignature(signature);
//		this->reaction = reaction;
//	}
//
//	virus(string mainName, string aliases, string signature, string type, string reaction = "None") {
//		this->name = mainName;
//		this->signature = signature;
//		this->type = type;
//		this->reaction = reaction;
//	}
//
//	void SetName(string name) {
//		this->name = name;
//	}
//	void SetSignature(string sig) {
//		this->signature = sig;
//	}
//	void SetType(string t) {
//		this->type = t;
//	}
//	void SetReaction(string reaction) {
//		this->reaction = reaction;
//	}
//
//	string Name() {
//		return name;
//	}
//	string Signature() {
//		return signature;
//	}
//	string Type() {
//		return type;
//	}
//	string Reaction() {
//		return reaction;
//	}
//};
//
//virus viruses[maxVirDBSize]; //Virus database.
//int virusesLoaded = 0; //How many viruses loaded to the database.
//
//void SaveDatabase() {
//	//WARNING: Data can be not saved. Can be optimization here.
//	ofstream databaseFile(database);
//	for (int i = 0; i < virusesLoaded; i++) {
//		databaseFile << "NAME" << endl;
//		databaseFile << viruses[i].Name() << endl;
//		databaseFile << "SIGNATURE" << endl;
//		databaseFile << viruses[i].Signature() << endl;
//		databaseFile << "STOP" << endl;
//		databaseFile << "END" << endl;
//	}
//	databaseFile.close();
//}
//
//#include <sstream>
//#include <vector>
//vector<string> SplitStr(const string& str, char symbol) {
//	auto result = std::vector<std::string>{};
//	auto ss = std::stringstream{ str };
//
//	for (std::string line; std::getline(ss, line, symbol);)
//		result.push_back(line);
//
//	return result;
//}
//
//void React(int virusID, string path) {
//	if (viruses[virusID].Reaction() == "None") {
//		//If so, seems like no reaction in database for delete this virus. So then it can be just deleted.
//		remove(path.c_str());
//	}
//	//Split commands to vector
//	vector<string> commands = SplitStr(viruses[virusID].Reaction(), '\n');
//
//	bool fullCmd = false; //Does macros use cmd.
//
//	ofstream defenceProtocol(defenceProtocollFileName);
//	//Execute every command.
//	for (string command : commands) {
//		//cout << "Command: " << command << endl;
//		if (fullCmd)
//			defenceProtocol << command << endl;
//		if (command == "$Full cmd" || command == "$Full cmd ")
//			fullCmd = true;
//
//		/*if(command.length() > 0)
//			if(command[command.length() - 1] == ' ')
//				system(command.c_str());*/
//	}
//	if (fullCmd) {
//		defenceProtocol << endl << "exit";
//		Sleep(1000);
//		//ShellExecute(NULL, s2ws("open"), s2ws(defenceProtocollFileName), NULL, NULL, SW_SHOWDEFAULT);
//
//		//system(("start " + defenceProtocollFileName + " " + path).c_str()); //system("start DefenceProtocol");
//		//Sleep(3000);
//
//		//Slower mode:
//		system((defenceProtocollFileName + " \"" + path + "\"").c_str()); //system("start DefenceProtocol");
//
//		//remove(defenceProtocollFileName.c_str()); //system(("del \"" + defenceProtocollFileName + "\"").c_str());
//	}
//	defenceProtocol.close();
//
//	int index = 0;
//	while (remove(defenceProtocollFileName.c_str()) && index < 500) {
//		Sleep(500);
//		index++;
//	}
//
//	if (FileExists(defenceProtocollFileName)) {
//		system(("taskkill /IM \"" + defenceProtocollFileName + "\" /F").c_str());
//		remove(defenceProtocollFileName.c_str());
//	}
//}
//
//void Initialize() {
//	if (!FileExists(database)) return;
//	virusesLoaded = 0; //WARNING: Volunerbillity
//
//	ifstream databaseFile(database);
//	string s;
//	//int *lastVirus = &virusesLoaded;
//
//	while (getline(databaseFile, s) && virusesLoaded < maxVirDBSize) {
//		if (s == "NAME") {
//			getline(databaseFile, s);
//			viruses[virusesLoaded].SetName(s);
//		}
//		else if (s == "ALIASES")
//			while (s != "STOP") {
//				getline(databaseFile, s);
//				//viruses[virusesLoaded].AddAlias(s); WARNING
//			}
//		else if (s == "SIGNATURE") {
//			string sig = "";
//			getline(databaseFile, s);
//			while (s != "STOP") {
//				//WARNING: Can be slow.
//				if (sig != "")
//					sig += "\n";
//
//				sig += s;
//				getline(databaseFile, s);
//			}
//			viruses[virusesLoaded].SetSignature(sig);
//			//WARNING: Doesent save and load type, but calculating it by itself.
//			viruses[virusesLoaded].SetType(GetTypeBySignature(sig));
//		}
//		else if (s == "REACTION") {
//			string r = "";
//			getline(databaseFile, s);
//			while (s != "STOP") {
//				//WARNING: Can be slow.
//				if (r != "")
//					r += "\n";
//
//				r += s;
//				getline(databaseFile, s);
//			}
//			viruses[virusesLoaded].SetReaction(r);
//		}
//		else if (s == "END") {
//			//viruses[lastVirus] = ;
//			virusesLoaded++;
//		}
//	}
//	databaseFile.close();
//	cout << "Initialization compliete. " << virusesLoaded << " virus(es) got." << endl;
//}
//
//void Scan(string s) {
//	//if (scanType == "fast" && FileSize(s) > TOOBIGSCANSIZE)
//		//return; //WARNING: Volunerbillity.
//	string buff;
//	bool v = false;
//	string source = ReadSource(s);
//	for (int i = 0; i < virusesLoaded; i++)
//		if (source == viruses[i].Signature()) {
//			buff = '"' + viruses[i].Name() + '"';
//			//MakeInfoWithDeskription(i);//MakeInfo(i);
//			v = true;
//
//			//Virus detected, start deleting protocol, execute protecting macros:
//			React(i, s);
//
//			//WARNING: Volunerbillity.
//			break;
//		}
//	//filesScanned++;
//	if (v)
//		cout << "Virus detected: " << buff << endl;
//	else
//		cout << "Virus not found." << endl;
//}
//
//void ScanDir(string path) {
//	for (const auto& entry : fs::directory_iterator(path)) {
//		if (DirExists(entry.path().string())) //(DirExists(path.c_str()))
//			ScanDir(entry.path().string());
//		else
//			Scan(entry.path().string());
//	}
//}
//
//void Update(const string url = defaultURL) {
//	HRESULT hr; //HANDLE hr; L"http://www.example.com/myfile.html"
//	hr = URLDownloadToFile(NULL, (wstring(url.begin(), url.end())).c_str(), L"result.exe", BINDF_GETNEWESTVERSION, NULL);
//}
//
////Returns 1 if success, 9 if not enough place.
//int AddVirus(string name, string signature, string type = "") {
//	if (virusesLoaded >= maxVirDBSize - 1)
//		return 9;
//
//	viruses[virusesLoaded].SetName(name);
//	viruses[virusesLoaded].SetSignature(signature);
//	viruses[virusesLoaded].SetType((type == "") ? GetTypeBySignature(signature) : type);
//
//	virusesLoaded++;
//	return 1;
//}

/*
	Example of writing virus database:

		NAME
		Virus name
		SIGNATURE
		asdaskbfdhabkfoqlwc ckan;claefcj lajf
		ashfg  kg haskdh k kaf
		asfajk   fkahdf
		 fd adfjbf
		STOP
		REACTION
		info...
		$Full cmd
		cmd del $path
		setx ABS=""
		STOP
		END
*/