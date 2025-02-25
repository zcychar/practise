# 时间复杂度分析报告

注：该报告中分析关于自变量 n 的时间复杂度，m 视为常数

### 1. ADD
该部分时间复杂度由 `std::set.insert()` 及 `std::unordered_map.insert()` 决定， 为 $O(\log n)$
   
### 2.SUBMIT 
该部分时间复杂度由 `std::set.erase()` ，`std::unordered_map.find()`及 `std::set.insert()`决定，为 $O(\log n)$ 

- 调用函数`team.Submit()`更新了队伍的提交记录及排名相关信息两部分内容
  
    - 调用`RecordUpdate()`更新提交记录，时间复杂度 $O(1)$
    - 更新排名相关信息
  
        - 调用`buffer.insert()`在冻结状态下暂存排名相关信息,时间复杂度 $O(1)$
        - 调用`RankUpdate()`更新排名相关信息,时间复杂度 $O(1)$
  
### 3.FLUSH
该部分时间复杂度由对 `set<int>dynamic_rank` 的遍历决定  
由于使用了迭代器进行顺序遍历 时间复杂度为 $O(n)$

### 4.QUERY_RANKING
该部分时间复杂度由 `std::unordered_set.find()` 决定为 $O(\log n)$, 队伍当前排名由 `team.rank` 维护, 查询 $O(1)$.

### 5.QUERY_SUBMISSION
该部分时间复杂度由 `std::unordered_set.find()` 决定为 $O(\log n)$  
调用函数 `team.Query()`, 由于队伍提交信息及题目提交信息在 `SUBMIT` 中已更新, 查询复杂度 $O(1)$.

### 6.SCROLL 
该部分时间复杂度为 $O(n\log n)$   

- 调用 `FLUSH` 更新榜单, 时间复杂度 $O(n)$
- 打表 时间复杂度由遍历决定 $O(n)$
- **决定时间复杂度** 解冻 时间复杂度 $O(n\log n)$ 
  
    - 迭代器 `it` 指向满足  *排名最靠后且有冻结状态题目* 的队伍。每次更新有两种情况
  
         - 排名改变或冻结全部解除  `it` 改为指向原先位置前一个队伍
         - 排名未变且冻结未全部解除 `it` 不变
        
    - 由此可知，, `it` 指向队伍的排名是  *单调非增* 的, 遍历时间复杂度 $O(n)$
    - 每次解冻操作时间复杂度由`std::set.erase()` 及 `std::set. insert()`决定，为 $O(\log n)$ 
    - 整体时间复杂度 $O(n\log n)$ 

- 调用 `FLUSH` 更新榜单, 时间复杂度 $O(n)$
- 打表 时间复杂度由遍历决定 $O(n)$
  
    
