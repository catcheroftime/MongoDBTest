# MongoDB C++库使用说明

## mongoDBlib 文件夹

- 此文件夹主要包含了mongodb C++ driver 驱动需要的头文件和编译生成的库（包括依赖的mongoc，bson, bsoncxx）。 
- 其中bsoncxx  主要是用来编写查询的语句，和结果的解析。

## MongoTest 文件夹

- 简单测试mongodb 连接池和基于我们human表参数的增删改查

## package 文件夹

- bson mongo-c-driver mongo-cxx-driver 等库的源码
- 编译库的步骤阅读其中的readme
