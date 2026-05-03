#pragma once
#include <iostream>

// 仅供 vision 模块内部使用的小工具：
// 放在 src/ 而不是 include/，并通过 CMake 把 src/ 标成 PRIVATE 的 include 路径，
// 下游（如 demo 可执行）就不会、也不应该看到这个头文件。
namespace vision_internal {
    inline void log(const char* msg) {
        std::cerr << "[vision] " << msg << "\n";
    }
}
