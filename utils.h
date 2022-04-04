#ifndef EDITDISTANCE_UTILS_INCLUDE__
#define EDITDISTANCE_UTILS_INCLUDE__
#include <cstring>
#include <locale>
#include <codecvt>
#include <string>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

std::wstring to_wide_string(const std::string& input);
std::string to_byte_string(const std::wstring& input);
std::wstring findMaxSubString(std::wstring s1, std::wstring s2);
unsigned char ToHex(unsigned char x);

std::string UrlEncode(const std::string& str);

std::string StringToHex(const std::string& data);

std::string HexToStr(const std::string& str);

string HmacEncode(const std::string& key,const std::string& input);

std::string GetFileContent(const std::string& filename);

void parse_url(const std::string requset_url, std::string& post, std::string& path);

std::string get_rfc1123_time();

#ifdef __cplusplus
}
#endif

#endif