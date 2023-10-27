#define CURL_STATICLIB
#include <iostream>
#include <string>
#include "curl/curl.h"
#include <map>
#include <vector>
//#include <any>
using namespace std;
/////////////////////////////////////stringX/////////////////////////////////
namespace stringX {
	void replace_all(string& mainString, string stringToReplace, string stringToReplaceWith) {
		for (int i = mainString.find(stringToReplace); i != string::npos; i = mainString.find(stringToReplace)) {
			mainString.replace(i, stringToReplace.size(), stringToReplaceWith);
		}
	}
	void replace(string& mainString, string stringToReplace, string stringToReplaceWith, int findNthOccurrence) { //if 4th param is null (0), will replace first instance of string
		mainString.replace(mainString.find(stringToReplace, findNthOccurrence), stringToReplace.size(), stringToReplaceWith);
	}
	void splitString(string mainString, vector<string>& vec, string stringToSplitWith) {
		int fPos = 0;
		int lPos = mainString.find(stringToSplitWith);
		while (lPos != string::npos) {
			vec.push_back(mainString.substr(fPos, lPos - fPos));
			fPos = lPos + stringToSplitWith.size();
			lPos = mainString.find(stringToSplitWith, fPos);
		}
		vec.push_back(mainString.substr(fPos));
	}
	int numOfStr(string mainString, string strToCount) {
		int amount = 0;
		string tempMain = mainString;
		while (tempMain.find(strToCount) != string::npos) {
			//cout << mainString;
			if (string(1, tempMain[0]) == strToCount) {
				tempMain = tempMain.substr(1);
				amount++;
			}
			else {
				tempMain = tempMain.substr(1);
			}
		}
		return amount;
	}
	bool isnum(string mainString) {
		return mainString.find_first_not_of("0123456789") == string::npos;
	}
	void removeNonInt(string& mainString) {
		int pos = 0;
		string tempMain = "";
		while (pos != mainString.size()) {
			if (isnum(string(1, mainString[pos]))) {
				tempMain.append(string(1,mainString[pos]));
			}
			pos++;
		}
		mainString = tempMain;
	}
}
namespace json {
	map<string, string> parse(string str) {
		map<string, string> json;
		stringX::replace_all(str, "{", "");
		stringX::replace_all(str, "}", "");
		string name = "";
		string data = "";
		int fqNamePos = 0;
		int lqNamePos = 0;
		int fqDataPos = 0;
		int lqDataPos = 0;
		bool invalid = false;
		//		int pos = str.find('"');
		vector <string> com;
		vector <string> col;
		//int qnum = 0;
		if (str.find(',') != string::npos) {
			stringX::splitString(str, com, ",");
		}
		if ((com.size()) != 0) {
			for (string& data : com) {
				//cout << data << endl;
				if (data.find(':') != string::npos) {
					stringX::splitString(data, col, ":");
				}
				else {
					cout << "invalid json syntax. missing \":\"." << endl;
					invalid = true;
				}
			}
		}
		else {
			if (stringX::numOfStr(str, ":") > 1) {
				cout << "invalid syntax. missing \",\".";
			}
			else {
				stringX::splitString(data, col, ":");
			}
		}
		if (((col.size()) != 0) && (invalid == false)) {
			for (string& data : col) {
				if (data.find('"') != string::npos) {
					data = data.substr(1, data.size() - 2) + "\0";
				}
			}
			string prevData = "";
			int inc = 1;
			for (string& data : col) {
				if (inc % 2 == 1) {
					prevData = data;
					inc++;
				}
				else {
					json[prevData] = data;
					inc++;
				}
			}
		}
		return json;
	}
}
//////////////////////////////////////input//////////////////////////////////
#include <conio.h>
#define ANY_ARROW 224
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define UP_ARROW 72
#define DOWN_ARROW 80
string startInput(string preMessage)
{
	string input;
	int rowPos = 0;
	cout << preMessage;
	for (int i = 0; i != 13;) {
		i = _getch();
		if (i == 8) {
			cout << "\b \b";
			input.pop_back();
			if (rowPos > 0) {
				rowPos = rowPos - 1;
			}
		}
		else {
			switch (i) {
			case ANY_ARROW:
				i = _getch();
				switch (i) {
				case LEFT_ARROW:
					cout << "\b";
					if (rowPos > 0) {
						rowPos = rowPos - 1;
					}
					break;
				case RIGHT_ARROW:
					if (rowPos < input.length()) {
						cout << "\033[C"; //idk how tf this works whoever's reading this pls explain!11
						rowPos = rowPos + 1;
					}
					break;
				case UP_ARROW:
					break;
				case DOWN_ARROW:
					break;
				}
				break;
			default:
				cout << (char)i;
				rowPos = rowPos + 1;
				input = input + (char)i;

			}
		}
	}
	return input;
}
/////////////////////////////////////////////////////////////////////////////

static size_t iForgor(void* result, size_t size, size_t size2, void* f)
{
	int totalsize = size * size2;
	string& ligma = *static_cast<string*>(f);
	ligma.append(static_cast<char*>(result), totalsize);
	return totalsize;
}

int main()
{
	curl_global_init(CURL_GLOBAL_ALL);
	string input = startInput("type in any userid: ");
	string webRes;
	stringX::removeNonInt(input);
	string url = "https://users.roblox.com/v1/users/";
	url.append(input);
	CURL* init = curl_easy_init();
	curl_easy_setopt(init, CURLOPT_URL, url.c_str());
	curl_easy_setopt(init, CURLOPT_WRITEFUNCTION, iForgor);
	curl_easy_setopt(init, CURLOPT_WRITEDATA, &webRes);
	CURLcode s = curl_easy_perform(init);
	curl_easy_cleanup(init);
	if (s != CURLE_OK) {
		std::cout << "CURL error: " << curl_easy_strerror(s) << endl;
	}
	else {
		//stringX::replace_all(webRes, ",", "\n");
		cout << endl;
		json::parse(webRes);
		cout << webRes;
	}
	return 0;
}
