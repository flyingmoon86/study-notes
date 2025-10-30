# 🧩 Algorithms Notes

Welcome to my personal **Algorithm Study Notes** repository!  
This repo records everything I’ve learned about **data structures and algorithms** using Markdown.  
All notes are organized by topic and written for clarity and long-term review.

---

## 📘 Repository Overview

### 📗 1. Basic Concepts
> Understanding what algorithms are and how we evaluate them.
- [Algorithm Definition](01_Basic_Concepts/Algorithm_Definition.md)
- [Time Complexity](01_Basic_Concepts/Time_Complexity.md)
- [Space Complexity](01_Basic_Concepts/Space_Complexity.md)

### 🧮 2. Data Structures
> The foundation of algorithms — mastering how data is stored and accessed.
- [Array](02_Data_Structures/Array.md)
- [Linked List](02_Data_Structures/Linked_List.md)
- [Stack and Queue](02_Data_Structures/Stack_and_Queue.md)
- [Tree](02_Data_Structures/Tree.md)
- [Graph](02_Data_Structures/Graph.md)
- [Hash Table](02_Data_Structures/Hash_Table.md)

### 🔍 3. Sorting & Searching
> Sorting and searching are the heart of computer science efficiency.
- [Sorting Algorithms](03_Sorting_Searching/Sorting_Algorithms.md)
- [Searching Algorithms](03_Sorting_Searching/Searching_Algorithms.md)
- [Binary Search Tree](03_Sorting_Searching/Binary_Search_Tree.md)

### ⚙️ 4. Divide and Conquer
> Break problems down into smaller ones and conquer them recursively.
- [Merge Sort](04_Divide_and_Conquer/Merge_Sort.md)
- [Quick Sort](04_Divide_and_Conquer/Quick_Sort.md)
- [Binary Search](04_Divide_and_Conquer/Binary_Search.md)

### 💡 5. Dynamic Programming
> Reuse results, avoid repetition — make solutions efficient.
- [DP Basics](05_Dynamic_Programming/DP_Basics.md)
- [Knapsack Problem](05_Dynamic_Programming/Knapsack_Problem.md)
- [Longest Common Subsequence](05_Dynamic_Programming/Longest_Common_Subsequence.md)
- [Matrix Path Sum](05_Dynamic_Programming/Matrix_Path_Sum.md)

### ⚡ 6. Greedy Algorithms
> Make the best choice at each step and hope for the global optimum.
- [Greedy Introduction](06_Greedy_Algorithms/Greedy_Introduction.md)
- [Huffman Coding](06_Greedy_Algorithms/Huffman_Coding.md)
- [Interval Scheduling](06_Greedy_Algorithms/Interval_Scheduling.md)

### 🕸️ 7. Graph Algorithms
> Explore connections — BFS, DFS, shortest paths, and spanning trees.
- [BFS and DFS](07_Graph_Algorithms/BFS_and_DFS.md)
- [Dijkstra’s Algorithm](07_Graph_Algorithms/Dijkstra.md)
- [Floyd–Warshall](07_Graph_Algorithms/Floyd_Warshall.md)
- [Minimum Spanning Tree](07_Graph_Algorithms/Minimum_Spanning_Tree.md)
- [Topological Sort](07_Graph_Algorithms/Topological_Sort.md)

### 📝 8. Practice and Notes
> My reflections and problem-solving records.
- [LeetCode Tips](08_Practice_and_Notes/LeetCode_Tips.md)
- [Classic Problems](08_Practice_and_Notes/Classic_Problems.md)
- [My Learning Notes](08_Practice_and_Notes/My_Learning_Notes.md)

---

## ✨ Why Markdown
- Simple and clean syntax — focus on learning, not formatting.  
- Easy to read on GitHub or VSCode.  
- Perfect for long-term version control and knowledge accumulation.

---
## 🔗 GitHub 访问方式对比（HTTPS vs SSH）

在管理 GitHub 仓库时，有两种常用访问方式：**HTTPS** 和 **SSH**。了解区别能帮助你选择最适合自己的方式。

| 特性 | HTTPS | SSH |
|------|-------|-----|
| URL 格式 | `https://github.com/用户名/仓库名.git` | `git@github.com:用户名/仓库名.git` |
| 认证方式 | 用户名 + 密码 / Personal Access Token | SSH Key（公钥/私钥） |
| 网络依赖 | 对防火墙、代理敏感 | 更稳定，不易被网络阻断 |
| 安全性 | 数据加密，但密码/Token可能泄露 | 高安全性，私钥保存在本地，公钥在 GitHub |
| 配置难度 | 零配置，克隆快速 | 初次需要生成 SSH key 并添加到 GitHub |
| 使用体验 | 每次 push/pull 可能要求输入 Token | 配置好后长期无密码，操作更顺畅 |
| 适合场景 | 临时拉取公共仓库、小项目 | 长期项目、频繁 push/pull、网络不稳定环境 |

### 💡 建议
- **HTTPS**：适合临时下载、少量操作、网络稳定的情况。  
- **SSH**：适合持续开发、频繁同步代码，尤其是在网络可能不稳定的环境下。  

> ⚡ Tip：我们在本仓库已将远程仓库改为 **SSH** 方式，保证长期 push/pull 的稳定性。
