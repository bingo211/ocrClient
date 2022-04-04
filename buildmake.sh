#!/bin/bash
g++ test_http.cpp ../utils.cpp ../httpclient.cpp ../base64.cpp  ../ucrresult.cpp -I ../include/ -I ../  -I ../third_party/include  -L ../libs/ -L ../third_party/lib -lcrypto -lssl  -lcurl -std=c++11 -fpermissive
