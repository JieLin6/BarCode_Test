#include <iostream>
#include "funset.hpp"

int main(int argc, char* argv[])
{
	// Blog: http://blog.csdn.net/fengbingchun/article/details/53889293
	// Note: windows10 vs2013 will crash, windows7 vs2013 is normal
	int ret = test_data_matrix_decode();

	if (ret == 0) fprintf(stderr, "test success\n");
	else fprintf(stderr, "test fail: %d\n", ret);

	return 0;
}

