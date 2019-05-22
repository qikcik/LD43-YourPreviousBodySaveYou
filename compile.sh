#bin/bash

cd make
	
echo -e "\e[39m -------- \e[31mBUILDING \e[39m--------"
cmake -G "Ninja"
ninja

cd ..