# C++ Template 技术学习笔记

> 姓名：黄宗凯  
> 学号：（填写你的学号）  
> 日期：2026年6月  
> 课程：C++面向对象编程

---

## 一、模板技术概述

### 1.1 什么是模板（Template）

模板是 C++ 实现**泛型编程（Generic Programming）**的核心机制。它允许程序员编写与具体数据类型无关的代码，在编译时由编译器根据实际使用的类型自动生成对应的代码。这种"代码复用"思想极大地提高了程序的灵活性和可维护性。

C++ 模板分为两大类：
- **函数模板（Function Template）**：编写与类型无关的函数
- **类模板（Class Template）**：编写与类型无关的类

### 1.2 模板的作用

| 作用 | 说明 |
|------|------|
| 代码复用 | 同一套逻辑适用于多种数据类型，无需重复编写 |
| 类型安全 | 编译期进行类型检查，避免运行时类型错误 |
| 性能优化 | 模板实例化在编译期完成，无运行时开销 |
| 容器设计 | 标准库中 `vector`、`stack` 等均基于模板实现 |

### 1.3 语法要点

```cpp
// 函数模板
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

// 类模板
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() { return value; }
};
```

---

## 二、Array 类模板设计与实现

### 2.1 UML 类图

```
+------------------------------------------+
|               Array<T>                     |
+------------------------------------------+
| - data : T*                                |
| - size : int                               |
+------------------------------------------+
| + Array(n : int)                           |
| + ~Array()                                 |
| + set(index : int, value : const T&)       |
| + get(index : int) : T                     |
| + getSize() : int                          |
| + print() : void                           |
+------------------------------------------+
```

**说明**：
- `T` 为模板参数，代表数组元素的数据类型
- `data` 为动态分配的数组指针
- `size` 记录数组长度
- 所有成员函数均带有边界检查，防止越界访问

### 2.2 核心代码实现

#### 构造函数与析构函数

```cpp
template <typename T>
Array<T>::Array(int n) {
    if (n <= 0) {
        throw invalid_argument("Array size must be positive!");
    }
    size = n;
    data = new T[size];
}

template <typename T>
Array<T>::~Array() {
    delete[] data;  // 释放动态内存
}
```

**分析**：构造函数在堆上分配 `n` 个 `T` 类型的元素，析构函数负责释放内存，防止内存泄漏。

#### 带边界检查的索引访问

```cpp
template <typename T>
void Array<T>::set(int index, const T& value) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds!");
    }
    data[index] = value;
}

template <typename T>
T Array<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds!");
    }
    return data[index];
}
```

**分析**：通过 `out_of_range` 异常处理越界访问，比返回错误码更安全，符合 C++ 异常处理规范。

---

## 三、函数模板实现

### 3.1 findMax — 查找最大值

```cpp
template <typename T>
T findMax(const Array<T>& arr) {
    T maxVal = arr.get(0);
    for (int i = 1; i < arr.getSize(); i++) {
        if (arr.get(i) > maxVal) {
            maxVal = arr.get(i);
        }
    }
    return maxVal;
}
```

**约束条件**：类型 `T` 必须支持 `operator>` 比较操作。对于 `int`、`double`、`string` 均满足此条件。

### 3.2 reverse — 反转数组

```cpp
template <typename T>
void reverse(Array<T>& arr) {
    int n = arr.getSize();
    for (int i = 0; i < n / 2; i++) {
        T temp = arr.get(i);
        arr.set(i, arr.get(n - 1 - i));
        arr.set(n - 1 - i, temp);
    }
}
```

**分析**：使用首尾交换法，只需遍历一半元素，时间复杂度为 O(n/2)，即 O(n)。

### 3.3 swapElements — 交换指定元素

```cpp
template <typename T>
void swapElements(Array<T>& arr, int i, int j) {
    T temp = arr.get(i);
    arr.set(i, arr.get(j));
    arr.set(j, temp);
}
```

---

## 四、运行环境说明

| 项目 | 说明 |
|------|------|
| 操作系统 | Windows 11 |
| 编译器 | Microsoft Visual Studio 2022 (MSVC) / g++ 13.2 |
| C++ 标准 | C++17 |
| 编译命令 | `g++ -std=c++17 -o ArrayTemplate ArrayTemplate.cpp` |
| 运行方式 | 命令行执行生成的 `.exe` 文件 |

---

## 五、运行结果与分析

### 5.1 完整运行输出

```
========================================
       Array Template 测试程序
========================================

--- 测试 Array<int> ---
创建 Array<int>(5)
填充元素: 10, 25, 7, 42, 15
数组内容: [ 10, 25, 7, 42, 15 ]
数组大小: 5
下标 2 的元素: 7
最大值: 42
反转后: [ 15, 42, 7, 25, 10 ]
交换下标 1 和 3 后: [ 15, 25, 7, 42, 10 ]

--- 测试 Array<double> ---
创建 Array<double>(4)
填充元素: 3.14, 2.71, 1.41, 1.73
数组内容: [ 3.14, 2.71, 1.41, 1.73 ]
数组大小: 4
下标 0 的元素: 3.14
最大值: 3.14
反转后: [ 1.73, 1.41, 2.71, 3.14 ]

--- 测试边界检查 ---
捕获异常: Index out of bounds!

--- 测试 Array<string> ---
数组内容: [ Apple, Banana, Cherry ]
字符串最大值: Cherry

========================================
            测试全部通过！
========================================
```

### 5.2 结果分析

| 测试项 | 结果 | 说明 |
|--------|------|------|
| `Array<int>` 创建与访问 | 通过 | 正确创建大小为 5 的整型数组，set/get 正常 |
| `findMax` | 通过 | 返回 42，为数组中最大值 |
| `reverse` | 通过 | 数组顺序完全反转，首尾元素对调 |
| `swapElements` | 通过 | 下标 1（42）与下标 3（25）交换正确 |
| `Array<double>` | 通过 | 同一套模板代码适用于 double 类型，无修改 |
| 边界检查 | 通过 | 越界访问抛出 `out_of_range` 异常，程序安全 |
| `Array<string>` | 通过 | 模板对 `string` 同样有效，`findMax` 按字典序返回 "Cherry" |

---

## 六、学习心得体会

通过本次 C++ Template 技术的学习与实践，我对泛型编程有了更加深入的理解。

在理论学习阶段，我系统掌握了函数模板和类模板的基本语法，认识到模板的核心价值在于"将类型参数化"。这意味着我们可以编写一次代码，却能让它适用于多种数据类型，极大提高了代码的复用性。这让我理解了为什么 C++ 标准模板库（STL）中的 `vector`、`stack`、`queue` 等容器都是基于模板实现的——它们无需为每种类型单独重写，却能保证类型安全。

在编程实践阶段，我设计并实现了一个泛型 `Array` 类模板。过程中最大的挑战在于理解**模板成员函数在类外定义**时的语法：不仅需要给每个函数加上 `template <typename T>` 前缀，还要在类名后加上 `<T>`，如 `Array<T>::set(...)`。刚开始时经常遗漏 `<T>` 导致编译错误，通过反复查阅资料和调试，逐渐熟练掌握了这一写法。

另一个重要收获是**异常处理**的应用。在 `set` 和 `get` 函数中加入 `out_of_range` 检查，让我意识到编写健壮代码的重要性。越界访问是数组操作中最常见的错误之一，通过抛出异常而非静默失败，可以让程序更安全、更容易调试。

在函数模板的实现中，`findMax` 要求类型支持 `operator>` 这一约束条件让我体会到**模板并非万能**。虽然模板提供了泛型能力，但它仍然依赖于类型本身的语义。例如 `string` 类型之所以能使用 `findMax`，是因为 C++ 为 `string` 重载了 `>` 运算符，使其按字典序比较。这提醒我在设计泛型代码时，必须明确类型需要满足的前置条件。

最后，通过测试 `Array<int>`、`Array<double>` 和 `Array<string>`，我亲眼验证了"同一份代码适用于不同数据类型"这一泛型编程的核心思想。当看到 `reverse` 和 `swapElements` 无需任何修改就能同时处理整数、浮点数和字符串时，我深刻感受到了模板机制的强大之处。这次作业不仅让我掌握了 C++ 模板技术，更培养了我从"具体问题"中抽象出"通用解决方案"的编程思维，这对我后续学习 STL 以及更高级的泛型编程技术奠定了坚实的基础。

---

## 七、附录：完整源代码

见同目录下 `C++模板作业.cpp` 文件。

