#ifndef DATA_TYPE_INCLUDE__
#define DATA_TYPE_INCLUDE__
#include <vector>
#include <string>
#include <memory>
using namespace std;

//通用ocr识别结果
typedef struct onlineOCRCoord_T{
	int x;
	int y;
}onlineOCRCoord;

typedef struct onlineOCRWordUntis_T{
	double conf;
	string content;
	onlineOCRCoord center_point;
	vector<onlineOCRCoord> coord;
}onlineOCRWordUntis;

typedef struct onlineOCRWords_T{
	double conf;
	string content;
	vector<onlineOCRCoord> coord;
}onlineOCRWords;

typedef struct onlineOCRLines_T{
	double angle;
	double conf;
	int exception;

	vector<onlineOCRCoord> coord;
	vector<onlineOCRWordUntis> word_units;
	vector<onlineOCRWords> words;
}onlineOCRLines;

typedef struct onlineOCRPages_T{
	double angle;
	int exception;
	int height;
	int width;

	vector<onlineOCRLines> lines;
}onlineOCRPages;

typedef struct onlineOCR_T{
	string category;
	string version;
	vector<onlineOCRPages> pages;

	bool h; // 0/1
	bool v; // 0/1
	int status; //状态  开始（0）、 进行中（1）和结束（2）  默认开始
}onlineOCR;


struct OCRConfig
{
	double thresd;//阈值
	string path; //图片路径
	string type;//图片类型
};

#endif