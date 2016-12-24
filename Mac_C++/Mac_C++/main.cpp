//
//  main.cpp
//  Mac_C++
//
//  Created by John on 2016/12/18.
//  Copyright © 2016年 John. All rights reserved.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>

#define CHINESE_CHAR_LENGTH_UTF8 3  // 根据编码格式定义一个中文字符占几个字节(默认为UTF-8,三个字节)

using namespace std;

/*
 brief 截取字符串
 param start 起始下标，从1开始
 param end   结束下标
 param isNeedPoint 是否需要在末尾添加“...”
 return 截取之后的字符串
 */
string subNickName(string str,int start, int end, bool isNeedPoint)
{
    vector<string> result;   // 存储解析之后的字符串
    int i = 0;
    while (i < str.length()){
        if (~(str.at(i) >> 8) == 0){
            //代表不是汉字
            result.push_back(str.substr(i, CHINESE_CHAR_LENGTH_UTF8));  // 一个汉字三个字节
            i = i + CHINESE_CHAR_LENGTH_UTF8;
        }else{
            result.push_back(str.substr(i, 1));  // 一个英文一个字节
            i = i + 1;
        }
    }
    
    // 容错处理，如果end大于字符串长度，则舍弃多余部分
    end = (result.size()) >= end ? end : (result.size());
    
    string temp = "";
    //直接从_result里取即可
    for (int i = start; i <= end; i++){
        temp += result[i - 1];
    }
    
    // 如果字符串太长，在末尾添加“...”
    if (isNeedPoint){
        if ((result.size()) > end){
            temp += "..";
        }
    }
    
    return temp;
}

/**
 *  求差集
 *
 *  @param subArr 子集数组
 *  @param subNum 子集数组大小
 *  @param parArr 父集数组
 *  @param parNum 父集数组大小
 *  @param outArr 接收数组  保证足够大小，不能小于父集数组大小
 */
void getChaJi(int *subArr, int subNum, int *parArr, int parNum, int *outArr)
{
    if(nullptr == subArr || nullptr == parArr || nullptr == outArr ){
        return;
    }
    
    int iOutNum = 0;
    for (int i = 0; i < parNum; i++) {
        bool isEqual = false;
        for (int j = 0; j < subNum; j++) {
            if (subArr[j] == parArr[i] ) {
                isEqual = true;
            }
        }
        
        if (!isEqual) {
            outArr[iOutNum] = parArr[i];
            iOutNum++;
        }
    }
}



int main(int argc, const char* argv[]) {
    //排序
    double result[4] = {63,345,34,897};
    //自动排序：升序
    map<double,int> mapResult;
    mapResult.clear();
    for (int i = 0; i < 4; i++) {
        mapResult.insert(pair<double, int>(result[i],i));
    }
   
    map<double,int>::iterator iter;
    for (iter = mapResult.begin(); iter != mapResult.end(); iter++) {
        printf("%f = %d\n",iter->first,iter->second);
    }
    
    iter = mapResult.end(); //end()指向最后一个元素的后面
    iter--;
    int iMaxValue = iter->second;
    printf("iMaxValue = %d\n", iMaxValue);
    
    string str  ="最好放不是你法案是sadfasgfaqw";
    
    string temp = subNickName(str,1,4,true);
    cout << temp << endl;
    
    int subArray[6] = {3,3,3,4,4,4};
    int parArray[18] = {12,3,3,67,4,12,4,67,4,4,7812,3,334,5345,654634,765,548,854};
    int getArr[18]  ={0};
    getChaJi(subArray,6,parArray,18,getArr);
    
    for (int i = 0; i < 18; i++) {
        cout << getArr[i] << endl;
    }
    
    return 0;
}
