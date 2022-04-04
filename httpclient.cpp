#include "httpclient.h"
#include <sstream>
#include <iostream>
#include <curl/curl.h>
#include "utils.h"
#include "base64.h"
#include "picojson.h"

using namespace  std;

string get_signature_origin(const char* host, const char* date, const char *path){
    stringstream ss;
    ss <<"host: "<< host << "\n" << "date: " << date << "\n" << "POST " << path << " HTTP/1.1";
    return ss.str();
}

inline string assemble_ws_auth_url(const std::string requset_url, const std::string method, const std::string api_key, const std::string api_secret){
    string host, path, finalRequset_url;
    parse_url(requset_url, host, path);
    std::string date = get_rfc1123_time();
    std::string signature_origin = get_signature_origin(host.c_str(), date.c_str(), path.c_str());
    std::string signature_sha = HmacEncode(api_secret.c_str(),signature_origin.c_str());
	string signature = base64::base64Encode(signature_sha.c_str(),signature_sha.length(),false);
    char authorization_origin[512];
    memset(authorization_origin, 0, 512);
    snprintf(authorization_origin, 512, "api_key=\"%s\", algorithm=\"hmac-sha256\", headers=\"host date request-line\", signature=\"%s\"", api_key.c_str(), signature.data());
    int authorization_origin_len = strlen(authorization_origin);
    string authorization =  base64::base64Encode(authorization_origin, authorization_origin_len, false);
    finalRequset_url = requset_url + "?" + "host=" + UrlEncode(host) + "&" + "date=" + UrlEncode(date) + "&" + "authorization=" + UrlEncode(authorization);
    return finalRequset_url;
}


std::string constructBody(const std::string& filename)
{
	picojson::value json;
	json.set<picojson::object>(picojson::object());
	json.get<picojson::object>()["header"].set<picojson::object>(picojson::object());
	json.get<picojson::object>()["header"].get<picojson::object>()["app_id"] =  picojson::value(APPId);
	json.get<picojson::object>()["header"].get<picojson::object>()["status"] =  picojson::value(double(3));

	json.get<picojson::object>()["parameter"].set<picojson::object>(picojson::object());
	json.get<picojson::object>()["parameter"].get<picojson::object>()["sf8e6aca1"].set<picojson::object>(picojson::object());
	json.get<picojson::object>()["parameter"].get<picojson::object>()["sf8e6aca1"].get<picojson::object>()["category"] = picojson::value("ch_en_public_cloud");

	json.get<picojson::object>()["parameter"].get<picojson::object>()["sf8e6aca1"].get<picojson::object>()["result"].set<picojson::object>(picojson::object());
	json.get<picojson::object>()["parameter"].get<picojson::object>()["sf8e6aca1"].get<picojson::object>()["result"].get<picojson::object>()["encoding"] = picojson::value("utf8");
	json.get<picojson::object>()["parameter"].get<picojson::object>()["sf8e6aca1"].get<picojson::object>()["result"].get<picojson::object>()["compress"] = picojson::value("raw");
	json.get<picojson::object>()["parameter"].get<picojson::object>()["sf8e6aca1"].get<picojson::object>()["result"].get<picojson::object>()["format"] = picojson::value("json");

	string picData = GetFileContent(filename);//图像数据
	string body = base64::base64Encode(picData.data(), picData.length());

	json.get<picojson::object>()["payload"].set<picojson::object>(picojson::object());
	json.get<picojson::object>()["payload"].get<picojson::object>()["sf8e6aca1_data_1"].set<picojson::object>(picojson::object());
	json.get<picojson::object>()["payload"].get<picojson::object>()["sf8e6aca1_data_1"].get<picojson::object>()["encoding"] = picojson::value("jpg");
	json.get<picojson::object>()["payload"].get<picojson::object>()["sf8e6aca1_data_1"].get<picojson::object>()["image"] = picojson::value(body);
	json.get<picojson::object>()["payload"].get<picojson::object>()["sf8e6aca1_data_1"].get<picojson::object>()["status"] = picojson::value(double(3));
	return json.serialize();
}

size_t write_callback(char *pData, size_t size, size_t nmemb, void* lpVoid)
{
   std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
    if( NULL == str || NULL == pData )
    {
        return -1;
    }
    str->append(pData, size * nmemb);
    return size * nmemb;
}


int httpclient::HttpPost(const std::string& filename, std::string &response)
{
	string request_url = assemble_ws_auth_url(_url, "POST",APIKey,APISecret);
	string body = constructBody(filename);
	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL,request_url.data());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "content-type: application/json");
		headers = curl_slist_append(headers, "host: api.xf-yun.com");

		string appidH = "app_id" + APPId;
		headers = curl_slist_append(headers, appidH.data());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
		res = curl_easy_perform(curl);

		if (res != CURLE_OK){
			const char* szErr = curl_easy_strerror(res);
			fprintf(stderr, "curl_easy_perform() failed: %s\n", szErr);
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			return -1;
		}
	}

	curl_easy_cleanup(curl);
	curl_global_cleanup();
	return 0;
}
