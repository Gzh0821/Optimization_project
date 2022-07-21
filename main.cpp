#include "Optimization.h"
#include <iostream>
#include <thread>
#include <chrono>
//主函数
using namespace std;
using namespace chrono;

int cal_func(Solution &&s,int compare_ans) {
    auto startTime = system_clock::now();
    int ans = s.SA(make_tuple(250, 5, 0.95, 25));//SA算法,参数设置分别为起始温度,温度阈值,退火速度和允许相同数
    //int ans = s.HCS();//HCS算法
    auto endTime = system_clock::now();
    if(ans <= compare_ans){//若结果比上一次优，输出
        cout << ans << endl;
        for(auto& i:s.next_order)
            cout << i << ',';
        cout << endl << "Time:" << duration_cast<milliseconds>(endTime - startTime).count() << endl;//时间
    }
    return min(ans,compare_ans);
}

int main(int argc,char* argv[]) {
    int id,last_ans = INT_MAX;
    if(argc==1)
        cin >> id;
    else
        id = strtol(argv[1],nullptr,10);
    Solution sol;
    sol.setup(id);//设置id
    auto startTime = system_clock::now();
    for (int i = 0; i < 20; ++i) {
        Solution s(sol);//复制构造Solution对象
        last_ans = cal_func(move(s),last_ans);//计算
    }
    auto endTime = system_clock::now();
    cout << endl << "TotalTime:" << duration_cast<milliseconds>(endTime - startTime).count() << endl;//输出总时间
}
