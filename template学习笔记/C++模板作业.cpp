#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

/* ============================================================
 *  Array 类模板定义
 *  泛型容器，支持任意数据类型（int, double, string 等）
 * ============================================================ */
template <typename T>
class Array {
private:
    T* data;        // 动态数组指针
    int size;       // 数组大小

public:
    // 构造函数：指定大小
    Array(int n);

    // 析构函数
    ~Array();

    // 设置元素（带边界检查）
    void set(int index, const T& value);

    // 获取元素（带边界检查）
    T get(int index) const;

    // 获取数组大小
    int getSize() const;

    // 打印所有元素
    void print() const;
};

/* ============================================================
 *  Array 类模板成员函数实现
 * ============================================================ */

template <typename T>
Array<T>::Array(int n) {
    if (n <= 0) {
        throw invalid_argument("Array size must be positive!");
    }
    size = n;
    data = new T[size];
    // 基本类型会自动初始化，这里不做额外处理
}

template <typename T>
Array<T>::~Array() {
    delete[] data;
}

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

template <typename T>
int Array<T>::getSize() const {
    return size;
}

template <typename T>
void Array<T>::print() const {
    cout << "[ ";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}

/* ============================================================
 *  函数模板实现（在类外部）
 * ============================================================ */

// findMax：返回数组中最大值（要求类型支持 operator>）
template <typename T>
T findMax(const Array<T>& arr) {
    if (arr.getSize() == 0) {
        throw runtime_error("Cannot find max of empty array!");
    }
    T maxVal = arr.get(0);
    for (int i = 1; i < arr.getSize(); i++) {
        if (arr.get(i) > maxVal) {
            maxVal = arr.get(i);
        }
    }
    return maxVal;
}

// reverse：反转数组元素顺序
template <typename T>
void reverse(Array<T>& arr) {
    int n = arr.getSize();
    for (int i = 0; i < n / 2; i++) {
        T temp = arr.get(i);
        arr.set(i, arr.get(n - 1 - i));
        arr.set(n - 1 - i, temp);
    }
}

// swapElements：交换指定下标的两个元素
template <typename T>
void swapElements(Array<T>& arr, int i, int j) {
    T temp = arr.get(i);
    arr.set(i, arr.get(j));
    arr.set(j, temp);
}

/* ============================================================
 *  测试程序
 * ============================================================ */

int main() {
    cout << "========================================" << endl;
    cout << "       Array Template 测试程序        " << endl;
    cout << "========================================" << endl;
    cout << endl;

    // ---------------- 测试 Array<int> ----------------
    cout << "--- 测试 Array<int> ---" << endl;
    Array<int> intArr(5);
    cout << "创建 Array<int>(5)" << endl;

    intArr.set(0, 10);
    intArr.set(1, 25);
    intArr.set(2, 7);
    intArr.set(3, 42);
    intArr.set(4, 15);
    cout << "填充元素: 10, 25, 7, 42, 15" << endl;

    cout << "数组内容: ";
    intArr.print();
    cout << "数组大小: " << intArr.getSize() << endl;
    cout << "下标 2 的元素: " << intArr.get(2) << endl;
    cout << "最大值: " << findMax(intArr) << endl;

    reverse(intArr);
    cout << "反转后: ";
    intArr.print();

    swapElements(intArr, 1, 3);
    cout << "交换下标 1 和 3 后: ";
    intArr.print();
    cout << endl;

    // ---------------- 测试 Array<double> ----------------
    cout << "--- 测试 Array<double> ---" << endl;
    Array<double> doubleArr(4);
    cout << "创建 Array<double>(4)" << endl;

    doubleArr.set(0, 3.14);
    doubleArr.set(1, 2.71);
    doubleArr.set(2, 1.41);
    doubleArr.set(3, 1.73);
    cout << "填充元素: 3.14, 2.71, 1.41, 1.73" << endl;

    cout << "数组内容: ";
    doubleArr.print();
    cout << "数组大小: " << doubleArr.getSize() << endl;
    cout << "下标 0 的元素: " << doubleArr.get(0) << endl;
    cout << "最大值: " << findMax(doubleArr) << endl;

    reverse(doubleArr);
    cout << "反转后: ";
    doubleArr.print();
    cout << endl;

    // ---------------- 测试边界检查 ----------------
    cout << "--- 测试边界检查 ---" << endl;
    try {
        intArr.set(10, 100);  // 越界访问
    } catch (const out_of_range& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    cout << endl;

    // ---------------- 测试 Array<string> ----------------
    cout << "--- 测试 Array<string> ---" << endl;
    Array<string> strArr(3);
    strArr.set(0, "Apple");
    strArr.set(1, "Banana");
    strArr.set(2, "Cherry");
    cout << "数组内容: ";
    strArr.print();
    cout << "字符串最大值: " << findMax(strArr) << endl;
    cout << endl;

    cout << "========================================" << endl;
    cout << "            测试全部通过！            " << endl;
    cout << "========================================" << endl;

    return 0;
}
