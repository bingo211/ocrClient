#ifndef __BASE64_H_0EVGAWXSPPAX__
#define __BASE64_H_0EVGAWXSPPAX__
#include <string>
using namespace std;

class base64
{
public:
    base64() = default;
    virtual ~base64() = default; 

    static string base64Encode(const char *buffer, int length, bool newLine = false);
    static string base64Decode(char *input, int length, bool newLine = false);
};

#endif  // __BASE64_H_0EVGAWXSPPAX__
