#ifndef __UCRRESULT_H_XJXW7WI7IKO0__
#define __UCRRESULT_H_XJXW7WI7IKO0__

#include <string>
#include "datatype.h"

class ucrresult final
{
public:
    ucrresult() = default;
    virtual ~ucrresult() = default;
    static onlineOCR* Parse(const std::string& res);
};

#endif  // __UCRRESULT_H_XJXW7WI7IKO0__
