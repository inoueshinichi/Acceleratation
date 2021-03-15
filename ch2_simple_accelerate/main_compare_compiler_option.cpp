/**
 * @file main_compare_compiler_option.cpp
 * @author your name (you@domain.com)
 * @brief MSVCコンパイラ下で/Od(最適化無効)と/Ox(最大限の最適化)による実行速度の比較を行う.
 * @version 0.1
 * @date 2021-03-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <omp.h> // OpenMP

using namespace std::chrono;

int main(int, char**)
{
    /**
     * @brief y_i = a * x_i + b * x_i + c * x_iを計算する
     */

    // コンパイラオプションの違い
    {
        std::cout << "コンパイラオプションの違い" << std::endl;
        const int loop = 65536, n = 65536;
        volatile float a = (float)rand();
        volatile float b = (float)rand();
        volatile float c = (float)rand();
        float x[n], y[n];
        for (int i = 0; i < n; ++i) {
            x[i] = (float)rand();
        }

        auto start = high_resolution_clock::now();

        // 計測対象の処理
        #pragma omp parallel for
        for (int j = 0; j < loop; ++j) {
            for (int i = 0; i < n; ++i) {
                y[i] = a * x[i] + b * x[i] + c * x[i];
            }
        }

        auto end = high_resolution_clock::now();
        auto duration = end - start;
        double duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cout << duration_ms << "[ms]" << std::endl;
    }

    //////////////////
    // 初歩的な最適化
    //////////////////
    // 最適化オプションをつけていても、浮動小数点演算は最適化されない場合が多い.
    // プログラマが明示的に最適化すると良い.

    /**
     * @brief 1) 括弧でくくる
     * y_i = a * x_i + b * x_i + c * x_i を y_i = (a + b + c) * x_iと書き換え、
     * 乗算を減らす.
     */
    {
        std::cout << "括弧でくくる" << std::endl;
        const int loop = 65536, n = 65536;
        volatile float a = (float)rand();
        volatile float b = (float)rand();
        volatile float c = (float)rand();
        float x[n], y[n];
        for (int i = 0; i < n; ++i) {
            x[i] = (float)rand();
        }

        auto start = high_resolution_clock::now();

        // 計測対象の処理
        #pragma omp parallel for
        for (int j = 0; j < loop; ++j) {
            for (int i = 0; i < n; ++i) {
                y[i] = (a + b + c) * x[i];
            }
        }

        auto end = high_resolution_clock::now();
        auto duration = end - start;
        double duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        std::cout << duration_ms << "[ms]" << std::endl;
    }
    
    /**
     * @brief 2) 除算を避ける
     * y = x /z は、y = x * (1.0 / z)に書き換える.
     * y = x / 4.0 は、 y = x * 0.25にする.
     */
    {}






}