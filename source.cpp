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
	cout << preMessage;
	//insert type-test repository code here (the code inside the main function)
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
