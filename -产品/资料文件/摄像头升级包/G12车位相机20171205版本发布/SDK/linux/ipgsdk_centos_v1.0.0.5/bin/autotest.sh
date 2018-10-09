#!/bin/sh

if [ $# -ne 1 ]; then
	echo -e "使用方法：\n./autotest.sh 设备IP（例如：192.168.55.100）\n"
	exit
fi

for test in [0-9][0-9][0-9]_*.tst
do
	if [ -x $test ];
	then
		echo -e "\e[36m[测试]\e[0m $test"
		./$test $1

		result=$?
		if [ $result = "1" ]; then
			echo -e "\e[32m[成功]\e[0m $test\n"
		else
			echo -e "\e[31m[失败]\e[0m $test\n"
		fi
	fi
done
