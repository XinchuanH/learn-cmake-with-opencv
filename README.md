# learn-cmake-with-opencv

> 用一个 OpenCV 项目，从最小工程一步步演化到多模块工程，把常用 CMake 知识点串成一条递进链。

每一步都是一个独立分支，分支之间是递进关系：后一个分支基于前一个，只引入该步要讲的新东西。
你可以**切到任一步看实际代码**，或**对比相邻两步的 diff**——两步之间的差异，就是那一步要讲的内容。

---

## 分支索引

| 分支 | Tag | 这一步在讲 |
|---|---|---|
| [`step-0-hello-opencv`](../../tree/step-0-hello-opencv)         | `v0` | 最小工程：一个 `CMakeLists.txt` + 一个 `main.cpp`，跑通 `find_package(OpenCV)` |
| [`step-1-multi-file`](../../tree/step-1-multi-file)             | `v1` | 拆成多文件，区分**编译**（看到声明）和**链接**（连入实现） |
| [`step-2-subdirectory`](../../tree/step-2-subdirectory)         | `v2` | `add_subdirectory` + 把 `vision` 抽成自己的库，顶层只做组织 |
| [`step-3-visibility`](../../tree/step-3-visibility)             | `v3` | `PUBLIC` / `PRIVATE` / `INTERFACE`：依赖到底传不传给下游 |
| [`step-4-shared-vs-static`](../../tree/step-4-shared-vs-static) | `v4` | 静态库 vs 动态库；运行期找不到 `.dll/.so` 的典型坑与修法 |
| [`step-5-modern-cmake`](../../tree/step-5-modern-cmake)         | `v5` | Modern CMake：连 C++ 标准都挂在 target 上，外加 `compile_commands.json` |

`main` 分支是把 step-0 → step-5 全部合并后的「最终版」，长这样：

```text
demo/
├─ CMakeLists.txt
├─ app/
│  └─ main.cpp
└─ vision/
   ├─ CMakeLists.txt
   ├─ include/vision/vision.hpp     # 公开 API（PUBLIC include 路径）
   ├─ src/vision.cpp
   └─ src/internal_log.hpp          # 内部头文件（PRIVATE include 路径）
```

---

## 怎么读这个仓库

```bash
# 切到某一步看代码
git switch step-2-subdirectory

# 看相邻两步的 diff = 那一步在讲的内容
git diff v1..v2

# 看从最简到最终的所有改动
git diff v0..v5

# 不切换分支，直接看某 tag 上某文件的内容
git show v3:demo/vision/CMakeLists.txt
```

也可以直接在 GitHub 网页上用左上角分支下拉切换，或访问：

- 全部分支：[/branches](../../branches)
- 全部 tag： [/tags](../../tags)
- 跨步骤对比：[v1...v2](../../compare/v1...v2)

---

## 怎么编

每个分支顶部都有一个 `demo/CMakeLists.txt`，构建方式统一：

```bash
# 推荐用 Ninja（这样 step-5 的 compile_commands.json 才会真的生成）
cmake -S demo -B build -G Ninja
cmake --build build

# 没装 Ninja 也行（默认生成器）
cmake -S demo -B build
cmake --build build
```

可执行文件落在：

- `step-0` ~ `step-3`：`build/`（或 `build/Debug/`，取决于生成器）
- `step-4` ~ `step-5`：`build/bin/`（顶层 `CMakeLists.txt` 设置了输出目录，`vision.dll` 与 `demo.exe` 共处一室，运行时不再找不到 DLL）

运行：

```bash
./build/bin/demo        # 需要当前目录有 test.jpg
```

---

## 前置条件

- **CMake** ≥ 3.15
- **OpenCV**（4.x），`find_package(OpenCV REQUIRED)` 能找到。如果找不到，配置时显式指定路径：
  ```bash
  cmake -S demo -B build -DCMAKE_PREFIX_PATH=/path/to/opencv/build
  ```
- 任意 C++17 编译器（MSVC / clang / gcc 都行）

---

## 看任何 `CMakeLists.txt` 都能问的三个问题

1. 这个 **target** 是什么？（可执行 / 静态库 / 动态库）
2. 它**依赖谁**？（哪些库、哪些头文件路径）
3. 这些依赖**要不要继续往下传**？（`PUBLIC` / `PRIVATE` / `INTERFACE`）

把这三件事想清楚，CMake 就不再玄学。