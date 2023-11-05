#define CURL_STATICLIB
#include <iostream>
#include <string>
#include "curl/curl.h"
#include <map>
#include <vector>
//#include <any>
using namespace std;
//insert stringX namespace here
//insert json namespace here
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
	int linePos = 0;

	for (int i = 0;;) {
		i = _getch();
		if (i == 8) {
			if (rowPos > 0) {
				rowPos = rowPos - 1;
				cout << "\b \b";
				input.pop_back();
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
				if (rowPos == input.size()) {
					input = input + (char)i;
					cout << "\r" << input;
					rowPos = rowPos + 1;
				}
				else {
					input = input.substr(0, rowPos) + (char)i + input.substr(rowPos);
					cout << "\r" << input;
					for (int i = 0; i < input.size() - rowPos; i++) {
						cout << "\b";
					}
					rowPos = rowPos + 1;
				}
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
