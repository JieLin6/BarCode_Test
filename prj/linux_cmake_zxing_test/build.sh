#! /bin/bash

real_path=$(realpath $0)
dir_name=`dirname "${real_path}"`
echo "real_path: ${real_path}"
echo "dir_name: ${dir_name}"

data_dir="test_images"
if [[ ! -d ${dir_name}/${data_dir} ]]; then
	echo "data directory does not exist: ${data_dir}"
	ln -s ${dir_name}/./../../${data_dir} ${dir_name}
else
	echo "data directory already exists: ${data_dir}"
fi

new_dir_name=${dir_name}/build
mkdir -p ${new_dir_name}

# build zxing-cpp
#echo "########## start build zxing-cpp ##########"
#zxing_path=${dir_name}/../../src/zxing-cpp
#mkdir -p ${zxing_path}/build
#cd ${zxing_path}/build
#cmake ..
#make
#echo "########## finish build zxing-cpp ##########"

#cp -a ${zxing_path}/build/libzxing.a ${new_dir_name}

rc=$?
if [[ ${rc} != 0 ]]; then
	echo "##### Error: some of thess commands have errors above, please check"
	exit ${rc}
fi

#cd -

cd ${new_dir_name}
cmake ..
make

cd -

