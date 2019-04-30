#include "funset.hpp"
#include <string.h>
#include <string>
#include <fstream>
#include <Windows.h>

#include <zxing/LuminanceSource.h>
#include <zxing/common/Counted.h>
#include <zxing/Reader.h>
#include <zxing/aztec/AztecReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/DecodeHints.h>
#include <zxing/datamatrix/DataMatrixReader.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/pdf417/PDF417Reader.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/oned/CodaBarReader.h>
#include <zxing/oned/Code39Reader.h>
#include <zxing/oned/Code93Reader.h>
#include <zxing/oned/Code128Reader.h>
#include <zxing/oned/EAN8Reader.h>
#include <zxing/oned/EAN13Reader.h>
#include <zxing/oned/ITFReader.h>
#include <zxing/oned/UPCAReader.h>
#include <zxing/oned/UPCEReader.h>

#include <opencv2/opencv.hpp>

#include "zxing/MatSource.h"

int test_UPC_E_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54647142
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/UPC_E.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::UPCEReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::UPC_E_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/UPC_E.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_UPC_A_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54647101
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/UPC_A.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::UPCAReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::UPC_A_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/UPC_A.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_RSS_Expanded_decode()
{
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/RSS_Expanded.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::MultiFormatReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	//zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::RSS_EXPANDED_HINT)));

	//std::string txt = "E:/GitCode/BarCode_Test/test_images/RSS_Expanded.txt";
	//std::ifstream in(txt);
	//if (!in.is_open()) {
	//	fprintf(stderr, "fail to open file: %s\n", txt.c_str());
	//	return -1;
	//}

	//std::string str1;
	//std::getline(in, str1);
	//fprintf(stderr, "actual        result: %s\n", str1.c_str());
	//std::string str2 = result->getText()->getText();
	//fprintf(stdout, "recognization result: %s\n", str2.c_str());

	//if (str1.compare(str2) == 0) {
	//	fprintf(stderr, "=====  recognition is correct  =====\n");
	//}
	//else {
	//	fprintf(stderr, "=====  recognition is wrong =====\n");
	//	return -1;
	//}

	//in.close();

	return -1;
}

int test_RSS14_decode()
{
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/RSS14.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::MultiFormatReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	//zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::RSS_14_HINT)));

	//std::string txt = "E:/GitCode/BarCode_Test/test_images/RSS14.txt";
	//std::ifstream in(txt);
	//if (!in.is_open()) {
	//	fprintf(stderr, "fail to open file: %s\n", txt.c_str());
	//	return -1;
	//}

	//std::string str1;
	//std::getline(in, str1);
	//fprintf(stderr, "actual        result: %s\n", str1.c_str());
	//std::string str2 = result->getText()->getText();
	//fprintf(stdout, "recognization result: %s\n", str2.c_str());

	//if (str1.compare(str2) == 0) {
	//	fprintf(stderr, "=====  recognition is correct  =====\n");
	//}
	//else {
	//	fprintf(stderr, "=====  recognition is wrong =====\n");
	//	return -1;
	//}

	//in.close();

	return -1;
}

int test_ITF25_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54619699
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/ITF25.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::ITFReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::ITF_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/ITF25.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_EAN13_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54619624
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/EAN13.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::EAN13Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::EAN_13_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/EAN13.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_EAN8_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54619482
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/EAN8.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::EAN8Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::EAN_8_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/EAN8.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_Code128_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54604786
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/Code128.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::Code128Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::CODE_128_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/Code128.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_Code93_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54604651
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/Code93.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::Code93Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::CODE_93_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/Code93.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;

}

int test_Code39_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54587385
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/Code39.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::Code39Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::CODE_39_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/Code39.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_Codabar_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54577605
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/Codabar.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::oned::CodaBarReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::CODABAR_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/Codabar.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_QRCode_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54577456
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/QRCode.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::qrcode::QRCodeReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::QR_CODE_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/QRCode.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1); // utf-8
	str1 = utf8_to_gbk(str1.c_str());
	fprintf(stderr, "actual        result: %s\n", str1.c_str());

	std::string str2 = result->getText()->getText(); // if it include chinese, then it's format is utf-8 bom
	const char bom[] = { 0xEF, 0xBB, 0xBF }; //'0xEF', '0xBB', '0xBF';
	if (strncmp(str2.data(), (const char*)bom, 3) == 0)
		str2 = str2.substr(3, str2.length()); // utf-8, remove first three bytes: 0xEF, 0xBB, 0xBF
	str2 = utf8_to_gbk(str2.c_str());
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_PDF417_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54432986
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/PDF417.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::pdf417::PDF417Reader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::PDF_417_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/PDF417.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}

int test_Maxicode_decode()
{
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/Maxicode.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::MultiFormatReader);

	/*zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::MAXICODE_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/Maxicode.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();*/

	return -1;
}

static void utf8_to_gbk(const char* utf8, char* gbk) {
	const int maxlen = 128;
	wchar_t unicode_str[maxlen];
	int outlen = MultiByteToWideChar(CP_UTF8, 0, utf8, strlen(utf8), unicode_str, maxlen);
	outlen = WideCharToMultiByte(CP_ACP, 0, unicode_str, outlen, gbk, 128, NULL, NULL);
	gbk[outlen] = '\0';
}

int test_DataMatrix_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54429722
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/data_matrix_encode.jpg";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}
	
	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);
	
	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);
	
	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::datamatrix::DataMatrixReader);
	
	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::DATA_MATRIX_HINT)));
	
	std::string txt = "E:/GitCode/BarCode_Test/test_images/data_matrix_encode.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	char tmp[128];
	utf8_to_gbk(str1.c_str(), tmp);
	std::string ret = std::string(tmp);
	fprintf(stderr, "actual        result: %s\n", ret.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());
	
	if (ret.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	}
	else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}
	
	in.close();
	
	return 0;
}

int test_Aztec_decode()
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/54347391
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/Aztec_tableShifts.png";
	cv::Mat matSrc = cv::imread(image_name, 1);
	if (!matSrc.data) {
		fprintf(stderr, "read image error: %s", image_name.c_str());
		return -1;
	}

	cv::Mat matGray;
	cv::cvtColor(matSrc, matGray, CV_BGR2GRAY);

	zxing::Ref<zxing::LuminanceSource> source = MatSource::create(matGray);
	int width = source->getWidth();
	int height = source->getHeight();
	fprintf(stderr, "image width: %d, height: %d\n", width, height);

	zxing::Ref<zxing::Reader> reader;
	reader.reset(new zxing::aztec::AztecReader);

	zxing::Ref<zxing::Binarizer> binarizer(new zxing::GlobalHistogramBinarizer(source));
	zxing::Ref<zxing::BinaryBitmap> bitmap(new zxing::BinaryBitmap(binarizer));
	zxing::Ref<zxing::Result> result(reader->decode(bitmap, zxing::DecodeHints(zxing::DecodeHints::AZTEC_HINT)));

	std::string txt = "E:/GitCode/BarCode_Test/test_images/Aztec_tableShifts.txt";
	std::ifstream in(txt);
	if (!in.is_open()) {
		fprintf(stderr, "fail to open file: %s\n", txt.c_str());
		return -1;
	}

	std::string str1;
	std::getline(in, str1);
	fprintf(stderr, "actual        result: %s\n", str1.c_str());
	std::string str2 = result->getText()->getText();
	fprintf(stdout, "recognization result: %s\n", str2.c_str());

	if (str1.compare(str2) == 0) {
		fprintf(stderr, "=====  recognition is correct  =====\n");
	} else {
		fprintf(stderr, "=====  recognition is wrong =====\n");
		return -1;
	}

	in.close();

	return 0;
}
