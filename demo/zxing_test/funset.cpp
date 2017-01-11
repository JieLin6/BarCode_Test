#include "funset.hpp"
#include <string>
#include <fstream>

#include <zxing/LuminanceSource.h>
#include <zxing/common/Counted.h>
#include <zxing/Reader.h>
#include <zxing/aztec/AztecReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/DecodeHints.h>
#include <opencv2/opencv.hpp>

#include "zxing/MatSource.h"

int test_Aztec_decode()
{
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
