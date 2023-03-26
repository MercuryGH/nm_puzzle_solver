# 数字华容道求解器

这个求解器使用IDA-star算法求解$n \times m$数字华容道问题（puzzle）。

## 使用方法

直接编译运行即可，修改源代码以配置合适的问题。

## 数学原理

> [UVa 10181 15-Puzzle Problem 题解《挑战程序设计竞赛》-码农场 (hankcs.com)](http://www.hankcs.com/program/algorithm/uva-10181-15-puzzle-problem.html)

> [POJ - 2893 M × N Puzzle(n*m数码问题+逆序对结论)_Frozen_Guardian的博客-CSDN博客](https://blog.csdn.net/qq_45458915/article/details/103313671)

## 改进？

现在的IDA-star算法在问题规模变大时会很慢，因为它总是试图寻找最优解。是否有一种方法能够找到$n \times m$数字华容道问题的可行解，但效率比在指数空间中搜索更高呢？
