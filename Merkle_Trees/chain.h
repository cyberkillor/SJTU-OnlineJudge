//
// Created by 方志成 on 2019-06-09.
//

#ifndef MERKLE_TREES_CHAIN_H
#define MERKLE_TREES_CHAIN_H
#include <iostream>
#include "block.h"
#include <string>
#include <vector>
using namespace std;

class Chain
{
public:
    vector<Block> BlockChainTmp;
    Chain(); //添加创世区块
    ~Chain();
    void AddBlock(Block t); //添加新区快
    void Output(); //遍历输出链
};
#endif //MERKLE_TREES_CHAIN_H
