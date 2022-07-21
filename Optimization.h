#pragma once
//最优化头文件
#include <vector>
#include <tuple>
#include <random>
#include <set>
#include <memory>

using para_format = std::tuple<double, double, double, int>;//SA参数格式

class random_num_engine {//随机数生成引擎
    std::random_device rand_source;//随机熵源
    std::mt19937_64 rand_eng;//64位梅森环绕生成器
public:
    random_num_engine() : rand_source(), rand_eng(time(nullptr) + rand_source()) {};
    //下为函数对象定义
    int operator()(int max) {//生成0-max的随机整数
        rand_eng.seed(rand_eng() ^ time(nullptr) + rand_source());
        return std::uniform_int_distribution<>(0, max - 1)(rand_eng);
    }

    double operator()(double start = 0.0, double end = 1.0) {//生成start-end的随机浮点数
        rand_eng.seed(rand_eng() ^ time(nullptr) + rand_source());
        return std::uniform_real_distribution<>(start, end)(rand_eng);
    }

};

class Solution {//解决方案类
public:
    static constexpr double e_v = 2.71828;//编译常量e

    Solution() : order_record(std::make_unique<std::set<std::vector<int>>>()), machines(0), workpieces(0) {}

    Solution(const Solution &other) : machines(other.machines), workpieces(other.workpieces),
                                      cost_table(other.cost_table),
                                      order_record(std::make_unique<std::set<std::vector<int>>>()) {}

    ~Solution() {
        order_record.reset();
    }

    void setup(int id);

    [[maybe_unused, nodiscard]] int HCS();

    [[maybe_unused, nodiscard]] int SA(para_format input_para);

    friend int cal_func(Solution &&,int);
private:
    random_num_engine get_random_num;//随机数模块
    int machines, workpieces;     //机器数量和工件数量
    std::vector<int> last_order, order, next_order;//当前序列
    std::vector<std::vector<int>> cost_table;//工件耗时表
    std::unique_ptr<std::set<std::vector<int>>> order_record;//独占指针指向存储序列的红黑树


    inline void change_random_order();//随机换序

    inline void change_adjacent_order(int wa);//相邻两点调换

    int calc_order_time();//计算函数模块
};