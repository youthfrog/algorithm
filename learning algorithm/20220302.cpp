//
//  2.cpp
//  learning algorithm
//
//  Created by 沈琚伟 on 2022/3/2.
//  Copyright © 2022 sheldon. All rights reserved.
//

/*
 有一个甜甜圈商店，每批次都烤 batchSize 个甜甜圈。
 这个店铺有个规则，就是在烤一批新的甜甜圈时，之前所有甜甜圈都必须已经全部销售完毕。
 给你一个整数 batchSize 和一个整数数组groups，
 数组中的每个整数都代表一批前来购买甜甜圈的顾客，其中groups[i]表示这一批顾客的人数。
 每一位顾客都恰好只要一个甜甜圈。
 
 当有一批顾客来到商店时，他们所有人都必须在下一批顾客来之前购买完甜甜圈。
 如果一批顾客中第一位顾客得到的甜甜圈不是上一组剩下的，那么这一组人都会很开心。
 
 你可以随意安排每批顾客到来的顺序。请你返回在此前提下，最多有多少组人会感到开心。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/maximum-number-of-groups-getting-fresh-donuts
 */

/*
 1 <= batchSize <= 9
 1 <= groups.length <= 30
 1 <= groups[i] <= 10^9
 */

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution1{
private:
    struct hashNode{
        size_t operator()(const vector<int>& nums) const{
            size_t hashValue = 0;
            for(int num:nums) hashValue = hashValue*5 + num;
            return hashValue;
        }
    };
    unordered_map<vector<int>, int, hashNode> hashmap;
    int dfs(vector<int>& u, int& n){
        if(hashmap.count(u)) return hashmap[u];
        int res = 0;
        for(int i = 1; i < n; i++ ){
            if (u[i]) {
                auto v = u;
                v[i]--, v[0] = (v[0]+i)%n;
                res = max(res, (!u[0]) + dfs(v, n));
            }
        }
        return hashmap[u] = res;
    }
public:
    int maxHappyGroups(int batchSize, vector<int>& groups){
        int ans = 0;
        vector<int> counter(batchSize, 0);
        for(int &group:groups) counter[group%=batchSize]++;
        ans = counter[0], counter[0] = 0;
        for(int i = 1; i <= (batchSize - 1)/2; i++){
            int minValue;
            ans += minValue = min(counter[i], counter[batchSize - i]);
            counter[batchSize - i] -= minValue;
            counter[i] -= minValue;
        }
        return ans + dfs(counter, batchSize);
    }
};



