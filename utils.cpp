#include "utils.h"
#include <vector>
#include <bits/stdc++.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/hmac.h>
#include <sstream>
#include "http_time.h"

using namespace std;

std::wstring to_wide_string(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}
 
std::string to_byte_string(const std::wstring& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
}

std::wstring findMaxSubString(std::wstring s1, std::wstring s2)
{
    if (s1.length() > s2.length()){
        swap(s1, s2);
    }

    int len1 = s1.length(), len2 = s2.length();
    int maxLen = 0, start = 0;
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1,0));

    for (int i = 1; i <= len1; i++){
        for (size_t j = 1; j <= len2; j++)
        {
            if (s1[i -1] == s2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen){
                    maxLen = dp[i][j];
                    start = i - maxLen;
                }
            }
        }
        
    }
    return s1.substr(start, maxLen);
}


unsigned char ToHex(unsigned char x)   
{   
    return  x > 9 ? x + 55 : x + 48;   
}  

std::string UrlEncode(const std::string& str)  
{  
    std::string strTemp = "";  
    size_t length = str.length();  
    for (size_t i = 0; i < length; i++)  
    {  
        if (isalnum((unsigned char)str[i]) ||   
            (str[i] == '-') ||  
            (str[i] == '_') ||   
            (str[i] == '.') ||   
            (str[i] == '~'))  
            strTemp += str[i];  
        else if (str[i] == ' ')  
            strTemp += "+";  
        else  
        {  
            strTemp += '%';  
            strTemp += ToHex((unsigned char)str[i] >> 4);  
            strTemp += ToHex((unsigned char)str[i] % 16);  
        }  
    }  
    return strTemp;  
}


std::string StringToHex(const std::string& data)
{
    const std::string hex = "0123456789ABCDEF";
    std::stringstream ss;

    for (std::string::size_type i = 0; i < data.size(); ++i)
        ss << hex[(unsigned char)data[i] >> 4] << hex[(unsigned char)data[i] & 0xf];
    return ss.str();
}

std::string HexToStr(const std::string& str)
{
    std::string result;
    for (size_t i = 0; i < str.length(); i += 2)
    {
        std::string byte = str.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
        result.push_back(chr);
    }
    return result;
}

string HmacEncode(const std::string& key,const std::string& input){
    const EVP_MD * engine = EVP_sha256();
    string output;
    unsigned int len;
    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_CTX_reset(ctx);
    
    HMAC_Init_ex(ctx, key.data(), key.size(), engine, NULL);
    HMAC_Update(ctx, (unsigned char*)input.data(), input.size());
    output.resize(EVP_MAX_MD_SIZE);

    HMAC_Final(ctx, (unsigned char*)output.c_str(), &len);
    HMAC_CTX_free(ctx);

    output.resize(len);
    return output;
}


std::string GetFileContent(const std::string& filename)
{
    std::ostringstream oss;
	std::fstream input(filename);
    if (input.is_open()){
        oss << input.rdbuf();
        input.close();
    }
    return oss.str();
}

void parse_url(const std::string requset_url, std::string& post, std::string& path){
    int stidx1 = requset_url.find("://"); //5
    int stidx2 = requset_url.find("/", stidx1+3); //22

    post = requset_url.substr(stidx1+3, stidx2-(stidx1+3));
    path = requset_url.substr(stidx2);
}

std::string get_rfc1123_time(){
    int buf_len = 100;
    char buf[buf_len] = {0};
    time_t t;
    time(&t);
    make_http_time(t, buf, buf_len);

    return  std::string(buf);
}