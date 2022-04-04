#include "ucrresult.h"
#include "picojson.h"
#include "base64.h"

using namespace std;


inline onlineOCR* parseUcrResult(const std::string& res){
    onlineOCR *result = new onlineOCR;
    
    picojson::value v;
    std::string err =picojson::parse(v,res);
    if (!err.empty()){
        return NULL;
    }

    if (!v.is<picojson::object>()){
        return NULL;
    }
    if (v.contains("category")){
        result->category = v.get("category").get<string>();
    }
    
    if (v.contains("version")){
        result->version = v.get("version").get<string>();
    }

    if (v.contains("pages")){
        picojson::value _pages = v.get("pages");
        if (_pages.is<picojson::array>()){
            picojson::array pageList = _pages.get<picojson::array>();
            for (picojson::array::iterator iter = pageList.begin(); iter != pageList.end(); ++iter){
                onlineOCRPages pageItem;

                if ((*iter).contains("exception"))
                  pageItem.exception = (*iter).get("exception").get<double>();

                if ((*iter).contains("angle"))
                  pageItem.angle = (*iter).get("angle").get<double>();
                
                if ((*iter).contains("height"))
                  pageItem.height = (*iter).get("height").get<double>();

                if ((*iter).contains("width"))
                  pageItem.width = (*iter).get("width").get<double>();

                if ((*iter).contains("lines")){

                    picojson::value _lines = (*iter).get("lines");
                    if (_lines.is<picojson::array>()){
                        picojson::array _linesItem = _lines.get<picojson::array>();
                        for(picojson::array::iterator _line_iter = _linesItem.begin(); _line_iter != _linesItem.end(); ++_line_iter){
                            onlineOCRLines olines;
                            picojson::value li = (*_line_iter);
                            if (li.contains("coord")){
                                picojson::value coord = li.get("coord");
                                if (coord.is<picojson::array>()){
                                    picojson::array __coord = coord.get<picojson::array>();
                                    for (picojson::array::iterator co = __coord.begin(); co != __coord.end(); ++co){
                                        onlineOCRCoord xy;

                                        picojson::value x = (*co);
                                        if (x.contains("x")){
                                            xy.x = x.get("x").get<double>();
                                        }

                                        if (x.contains("y")){
                                            xy.y= x.get("y").get<double>();
                                        }
                                        olines.coord.push_back(xy);
                                    }
                                }
                            }

                            if (li.contains("exception")){
                                olines.exception = li.get("exception").get<double>();
                            }

                            if (li.contains("words")){
                                 picojson::value words = li.get("words");
                                 if (words.is<picojson::array>()){
                                     picojson::array _words = words.get<picojson::array>();
                                     for (picojson::array::iterator wd = _words.begin(); wd != _words.end(); ++wd){
                                        onlineOCRWords owords;
                                         picojson::value __wordsItem = (*wd);
                                        
                                         if (__wordsItem.contains("content")){
                                             owords.content = __wordsItem.get("content").get<string>();
                                         }

                                         if (__wordsItem.contains("conf")){
                                             owords.conf = __wordsItem.get("conf").get<double>();
                                         }

                                         if (__wordsItem.contains("coord")){
                                             picojson::value _coord = __wordsItem.get("coord");
                                             if (_coord.is<picojson::array>()){
                                                picojson::array __coord = _coord.get<picojson::array>();
                                                for (picojson::array::iterator co = __coord.begin(); co != __coord.end(); ++co){
                                                    onlineOCRCoord xy;
                                                    picojson::value x = (*co);
                                                    if (x.contains("x")){
                                                        xy.x = x.get("x").get<double>();
                                                    }

                                                    if (x.contains("y")){
                                                        xy.y= x.get("y").get<double>();
                                                    }
                                                    owords.coord.push_back(xy);
                                                }

                                             }
                                         }
                                         
                                         olines.words.push_back(owords);
                                     }
                                    
                                 }
                            }

                            if (li.contains("conf")){
                                olines.conf = li.get("conf").get<double>();
                            }

                            if (li.contains("word_units")){
                                picojson::value _word_units = li.get("word_units");
                                if (_word_units.is<picojson::array>()){
                                    picojson::array __wn = _word_units.get<picojson::array>();
                                    for (picojson::array::iterator witer = __wn.begin(); witer != __wn.end(); ++witer){
                                        picojson::value wordItem = (*witer);
                                        onlineOCRWordUntis_T word_unit_t;
                                        if (wordItem.contains("content")){
                                            word_unit_t.content = wordItem.get("content").get<string>();
                                        }

                                        if (wordItem.contains("conf")){
                                            word_unit_t.conf = wordItem.get("conf").get<double>();
                                        }

                                        if (wordItem.contains("coord")){
                                            picojson::value __coord = wordItem.get("coord");
                                            if (__coord.is<picojson::array>()){
                                                picojson::array crarr = __coord.get<picojson::array>();
                                                for (picojson::array::iterator criter = crarr.begin(); criter != crarr.end() ; ++criter){
                                                    onlineOCRCoord xy;
                                                    picojson::value x = (*criter);
                                                    if (x.contains("x")){
                                                        xy.x = x.get("x").get<double>();
                                                    }
                                                    if (x.contains("y")){
                                                        xy.y= x.get("y").get<double>();
                                                    }
                                                    word_unit_t.coord.push_back(xy);
                                                }
                                            }
                                        }

                                        if (wordItem.contains("center_point")){
                                            picojson::value cp = wordItem.get("center_point");
                                            if (cp.is<picojson::object>()){
                                                onlineOCRCoord xy;
                                                picojson::object x = cp.get<picojson::object>();
                                                if (x.find("x") != x.end()){
                                                    xy.x = x["x"].get<double>();
                                                }

                                                if (x.find("y") != x.end()){
                                                    xy.y= x["y"].get<double>();
                                                }
                                                word_unit_t.center_point = xy;
                                            }
                                        }

                                        olines.word_units.push_back(word_unit_t);
                                    }
                                }
                            }

                            if (li.contains("angle")){
                                olines.angle = li.get("angle").get<double>();
                            }

                            pageItem.lines.push_back(olines);
                        }
                    }
                }
             
                result->pages.push_back(pageItem);
            }
        }
    }

    return result;
}

onlineOCR* ucrresult::Parse(const std::string& res)
{
    if (res.length() == 0)
    {
        return NULL;
    }

    picojson::value v;
    std::string err =picojson::parse(v,res);
    if (!err.empty()){
        return NULL;
    }

    if (!v.is<picojson::object>()){
        return NULL;
    }

    picojson::value _header = v.get("header");
    if (_header.is<picojson::object>()){
        picojson::object _headerItem = _header.get<picojson::object>();
        int code;
        if (_headerItem.find("code") != _headerItem.end()){
            code = _headerItem["code"].get<double>();
        }

        if (code == 0){
            picojson::value _payload = v.get("payload");
            if (_payload.is<picojson::object>()){
                picojson::object _payloadItem = _payload.get<picojson::object>();
                if (_payloadItem.find("result") != _payloadItem.end()){
                    picojson::object _result = _payloadItem["result"].get<picojson::object>();
                    string compress, encoding, format, ucrResText;
                    if (_result.find("compress") != _result.end()){
                        compress = _result["compress"].get<string>();
                    }

                    if (_result.find("encoding") != _result.end()){
                        encoding = _result["encoding"].get<string>();
                    }

                    if (_result.find("format") != _result.end()){
                        format = _result["format"].get<string>();
                    }

                    if (_result.find("text") != _result.end()){
                        ucrResText = _result["text"].get<string>();
                    }

                    if (compress == "raw" && encoding == "utf8" && format == "json"){
                        if (!ucrResText.empty()){
                            string decodeResult = base64::base64Decode(ucrResText.data(),ucrResText.length());
                            return parseUcrResult(decodeResult);
                        }
                    }
                }
            }
        }

    }
    return NULL;    
}