#include <iostream>
#include "httpclient.h"
#include <string>
#include "ucrresult.h"
using namespace std;

int main(int argc, char const *argv[])
{
    httpclient cli;
    string response;

    cli.HttpPost("1.jpg",response);
    onlineOCR* result = ucrresult::Parse(response);

    for (int mt = 0; mt < result->pages.size(); mt++)
    {
        for (int j = 0 ; j < result->pages[mt].lines.size();j++){
            onlineOCRLines lines = result->pages[mt].lines[j];
            for(int k =0 ; k < lines.words.size(); k++){
                cout << "recog result = " << lines.words[k].content << endl;
            }        
        }
    }
    delete result;

    return 0;
}
