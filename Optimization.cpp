#include "Optimization.h"
#include <fstream>
#include <algorithm>
//最优化实现
using namespace std;

void Solution::setup(int id) //预处理数据读入
{
    string line;
    int id_now;
    ifstream fin("../flowshop-test-10-student.txt");
    if (!fin.is_open()) {
        throw ios_base::failure("unable to open file!");
    }
    while (getline(fin, line)) {
        if(line.front()!='+')
            continue;
        fin >> line >> id_now;
        if (id_now == id)
        {
            fin >> workpieces >> machines;//存入工件与机器数量
            cost_table.resize(workpieces);
            int _;
            for (auto &&i: cost_table) {
                i.resize(machines);
                for (int &j: i)
                    fin >> _ >> j;//写入工件耗时表
            }
            fin.close();
            return;
        }
    }
}

void Solution::change_random_order() {
    int a = get_random_num(workpieces), b = get_random_num(workpieces);
    swap(order[a], order[b]);//随机交换
}

void Solution::change_adjacent_order(int wa) {
    if (wa < workpieces - 1 && wa >= 0) {
        swap(order[wa], order[wa + 1]);//交换相邻两项
    } else
        throw out_of_range("Out of range in order!");
}


int Solution::calc_order_time() {
    vector<int> order_time_dp(workpieces); //记录每个工件在当前步骤机器上加工结束时的时间
    order_time_dp.front() = cost_table[order.front()].front();
    for (int i = 1; i < workpieces; ++i)
        order_time_dp[i] = order_time_dp[i - 1] + cost_table[order[i]][0];
    for (int i = 1; i < machines; ++i) {
        order_time_dp[0] += cost_table[order[0]][i];
        for (int j = 1; j < workpieces; ++j) {
            int res = max(order_time_dp[j - 1], order_time_dp[j]);
            order_time_dp[j] = res + cost_table[order[j]][i]; //动态规划计算当前序列耗时
        }
    }
    return order_time_dp[workpieces - 1];
}

[[maybe_unused]] int Solution::HCS() {
    int last = INT_MAX; //上一次计算结果
    next_order.reserve(workpieces);
    order.reserve(workpieces);
    last_order.reserve(workpieces);//预分配空间
    for (int i = 0; i < workpieces; ++i)
        order.emplace_back(i);
    for (int i = 0; i < workpieces; ++i) //随机化初始顺序
        change_random_order();
    int res = calc_order_time();
    next_order = order;
    while (last > res) //邻域内所有解均小于上次迭代解则结束迭代
    {
        int now_min = res;
        last = res;
        last_order = order;
        for (int i = 0; i < workpieces - 1; i++) //计算邻域，即交换相邻位置，并取最小值
        {
            change_adjacent_order(i);
            res = calc_order_time();
            if (res < now_min) {
                now_min = res;
                next_order = order;
            }
            order = last_order; //还原初始序列，继续迭代
        }
        res = now_min;//存储结果
        order = next_order;
    }
    return res;
}

[[maybe_unused]] int Solution::SA(para_format input_para) //模拟退火算法
{
    auto &&[T, T_ed, velocity, same_threshold] = input_para;//参数元组，分别为起始温度,温度阈值,退火速度和允许相同数
    next_order.reserve(workpieces);
    order.reserve(workpieces);
    last_order.reserve(workpieces);
    int last = INT_MAX, res; //last用于记录上次迭代结果
    for (int i = 0; i < workpieces; ++i)
        order.emplace_back(i);
    for (int i = 0; i < workpieces; ++i)
        change_random_order();
    last_order = order;
    while (T > T_ed) //温度低于阈值时推出
    {
        int count_same = 0, count_cycle = 1; //记录循环次数和相同解重复次数
        T *= velocity; //降温
        do {
            res = calc_order_time();
            if (res < last) {
                last = res;
                count_same = 0;
                next_order = order;
            } else if (res == last)
                ++count_same;
            else
            {
                double randtmp = get_random_num(), threshold = pow(e_v, ((last - res) / T)); // log(count_cycle+2)用于规避临近值反复
                if (randtmp < threshold) {
                    last = res;
                    count_same = 0;
                    next_order = order;
                } else {
                    ++count_same;
                    order = last_order;
                }//使用Metropolis准则判断是否接受
            }
            order_record->emplace(order);//记录当前序列
            last_order = order;
            do {
                change_random_order();//获得从未出现的序列
            } while (order_record->count(order));

            ++count_cycle;
        } while (count_same < same_threshold &&
                 count_cycle < workpieces * 250); //结束迭代,count_cycle为了防止出现循环跳跃
    }
    order_record->clear();//清除集合内的序列
    return last;
}

