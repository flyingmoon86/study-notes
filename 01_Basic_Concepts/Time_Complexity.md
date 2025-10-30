# 算法时间复杂度（Time Complexity）

时间复杂度是用来衡量算法运行时间随输入规模增长的变化趋势。我们通常使用大O符号（Big O notation）来表示时间复杂度。

## 常见的时间复杂度

### 1. O(1) - 常数时间
表示算法的执行时间与输入规模无关，始终是固定的时间。

示例：
```python
def get_first_element(arr):
    return arr[0]  # 无论数组多大，只访问第一个元素
```

### 2. O(log n) - 对数时间
算法的执行时间与输入规模的对数成正比。常见于二分查找等算法。

示例：
```python
def binary_search(arr, target):
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1
```

### 3. O(n) - 线性时间
算法的执行时间与输入规模成正比。

示例：
```python
def find_max(arr):
    max_val = arr[0]
    for num in arr:  # 遍历一次数组
        if num > max_val:
            max_val = num
    return max_val
```

### 4. O(n log n) - 线性对数时间
常见于高效的排序算法，如归并排序和快速排序。

示例（归并排序）：
```python
def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return merge(left, right)
```

### 5. O(n²) - 平方时间
常见于嵌套循环的算法。

示例：
```python
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):  # 两层嵌套循环
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr
```

### 6. O(2ⁿ) - 指数时间
算法的执行时间随输入规模呈指数增长。常见于递归实现的斐波那契数列。

示例：
```python
def fibonacci(n):
    if n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)  # 每个函数调用产生两个递归调用
```

## 如何分析时间复杂度

1. **计算基本操作次数**：确定算法中的基本操作（如比较、赋值等）
2. **找出最高阶项**：在复杂度表达式中，只保留最高阶项
3. **去除常数项**：去除表达式中的常数系数

## 常见算法的时间复杂度比较

从快到慢排序：
- O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ) < O(n!)

## 实际应用中的考虑因素

1. **输入规模**：小规模数据下，O(n²)的算法可能比O(n log n)的算法更快
2. **常数因子**：虽然在渐进分析中忽略常数，但在实际应用中要考虑
3. **硬件限制**：不同硬件平台可能导致实际运行时间有所差异

## 优化建议

1. 避免不必要的嵌套循环
2. 使用适当的数据结构（如哈希表可以将某些操作从O(n)降至O(1)）
3. 考虑使用更高效的算法（如将冒泡排序改为快速排序）
4. 在可能的情况下，使用空间换时间的策略
