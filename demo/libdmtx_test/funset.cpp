#include "funset.hpp"
#include <assert.h>
#include <iostream>
#include <string>
#include "dmtx.h"
#include <opencv2/opencv.hpp>

int test_data_matrix_base()
{
	std::string str = "中国_abc_DEF_123_@#$！";

	/* 1) ENCODE a new Data Matrix barcode image (in memory only) */
	DmtxEncode* enc = dmtxEncodeCreate();
	assert(enc != NULL);
	int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());
	assert(ret == 1);

	/* 2) COPY the new image data before releasing encoding memory */
	int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
	int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
	int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);

	unsigned char* pxl = (unsigned char *)malloc(width * height * bytesPerPixel);
	assert(pxl != NULL);
	memcpy(pxl, enc->image->pxl, width * height * bytesPerPixel);

	dmtxEncodeDestroy(&enc);

	/* 3) DECODE the Data Matrix barcode from the copied image */
	DmtxImage* img = dmtxImageCreate(pxl, width, height, DmtxPack24bppRGB);
	assert(img != NULL);

	DmtxDecode* dec = dmtxDecodeCreate(img, 1);
	assert(dec != NULL);

	std::string dst;
	DmtxRegion* reg = dmtxRegionFindNext(dec, NULL);
	if (reg != NULL) {
		DmtxMessage* msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
		if (msg != NULL) {
			/*fputs("output: \"", stdout);
			fwrite(msg->output, sizeof(unsigned char), msg->outputIdx, stdout);
			fputs("\"\n", stdout);*/
			dst = std::string(reinterpret_cast<const char*>(msg->output));
			dmtxMessageDestroy(&msg);
		}
		dmtxRegionDestroy(&reg);
	}

	std::cout << "source string : " << str << std::endl;
	std::cout << "dst    string : " << dst << std::endl;

	dmtxDecodeDestroy(&dec);
	dmtxImageDestroy(&img);
	free(pxl);

	return 0;
}

int test_data_matrix_encode()
{
	std::string str = "中国_abc_DEF_123_@#$！HTTP://WWW.LIBDMTX.ORG";

	DmtxEncode* enc = dmtxEncodeCreate();
	assert(enc != NULL);
	int ret = dmtxEncodeDataMatrix(enc, strlen(str.c_str()), (unsigned char*)str.c_str());
	assert(ret == 1);

	int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
	int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
	int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
	fprintf(stderr, "image width: %d, image height: %d, channels: %d\n", width, height, bytesPerPixel);
	assert(bytesPerPixel == 1 || bytesPerPixel == 3 || bytesPerPixel == 4);

	cv::Mat mat;
	if (bytesPerPixel == 1)
		mat = cv::Mat(height, width, CV_8UC1);
	else if (bytesPerPixel == 3)
		mat = cv::Mat(height, width, CV_8UC3);
	else
		mat = cv::Mat(height, width, CV_8UC4);

	mat.data = enc->image->pxl;

	std::string image_name = "E:/GitCode/BarCode_Test/test_images/data_matrix_encode.jpg";
	cv::imwrite(image_name, mat);

	dmtxEncodeDestroy(&enc);

	return 0;
}

int test_data_matrix_decode()
{
	std::string image_name = "E:/GitCode/BarCode_Test/test_images/data_matrix_encode.jpg";
	cv::Mat mat = cv::imread(image_name, 1);
	if (!mat.data) {
		fprintf(stderr, "read image error\n");
		return -1;
	}

	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	DmtxImage* img = dmtxImageCreate(mat.data, width, height, DmtxPack24bppRGB);
	if (!img) {
		fprintf(stderr, "dmtx image create fail\n");
		return -1;
	}

	DmtxDecode* dec = dmtxDecodeCreate(img, 1);
	if (!dec) {
		fprintf(stderr, "dmtx decode create fail\n");
		return -1;
	}

	DmtxRegion* reg = dmtxRegionFindNext(dec, nullptr);
	if (!reg) {
		fprintf(stderr, "dmtx region fail\n");
		return -1;
	}

	DmtxMessage* msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
	if (!msg) {
		fprintf(stderr, "dmtx decode matrix region fail\n");
		return -1;
	}

	std::string str(reinterpret_cast<char*>(msg->output));
	fprintf(stderr, "decode result: %s\n", str.c_str());

	dmtxMessageDestroy(&msg);
	dmtxRegionDestroy(&reg);
	dmtxDecodeDestroy(&dec);
	dmtxImageDestroy(&img);

	return 0;
}
