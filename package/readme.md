# 编译MongoDB C++ 的驱动

## 编译环境

- Ubuntu 16.04
- GCC，G++版本 5.4
- cmake 版本 cmake-3.12.0.tar.gz（cmake官网自行下载）
- mongo-c-driver 版本 1.12.0（其中自带 bson）
- mongo-cxx-driver 版本 3.3.0 (其中自带bsoncxx)

## 安装 cmake (如果有忽略此版本)

    tar -zxvf cmake-3.12.0.tar.gz 
    cd ./cmake-3.12.0
    sudo ./bootstrap
    sudo make
    sudo make install 

## 安装 mongo-c-driver

    git clone https://github.com/mongodb/mongo-c-driver.git
    cd mongo-c-driver
    git checkout 1.12.0
    sudo mkdir ./cmake-build
    cd cmake-build
    sudo cmake ..
    sudo make && sudo make install

## 安装 mongo-cxx-driver

    git clone https://github.com/mongodb/mongo-cxx-driver
    cd mongo-cxx
    git checkout r3.3.0
    sudo cmake ..
    sudo make && sudo make install

## 总结 

由于全程基本都是默认安装最后编译完成的include和lib位置

### mongoc 和  bson

- 头文件 /usr/local/include
- 库文件 /usr/local/lib     (8个)

### mongocxx 和 bsoncxx

编译输出在git工程目录（mongo-cxx-driver）里面

- 头文件 mongo-cxx-driver/build/install/include
- 库文件 mongo-cxx-driver/build/install/lib  (6个)
  