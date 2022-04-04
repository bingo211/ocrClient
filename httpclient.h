#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include <string>
#include <sstream>

const static std::string APPId = "984d4cb3";
const static std::string APIKey = "9868d2bcc3d1659dbdb5afe1099136b0";
const static std::string APISecret = "NTUzNjk5Zjg0ZDRkZjdkY2IyNjRjYWQz";
const static std::string _url = "http://api.xf-yun.com/v1/private/sf8e6aca1";
const static std::string _hostname = "api.xf-yun.com";

class httpclient {
public:
   httpclient() = default;
   ~httpclient() = default;
   int HttpPost(const std::string& filename, std::string &response);

};

#endif