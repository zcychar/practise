#ifndef SRC_HPP
#define SRC_HPP
#include <chrono>
/**
 * 枚举类，用于枚举可能的置换策略
 */
enum class ReplacementPolicy { kDEFAULT = 0, kFIFO, kLRU, kMRU, kLRU_K };

inline int k_ = 0;
/**
 * @brief 该类用于维护每一个页对应的信息以及其访问历史，用于在尝试置换时查询需要的信息。
 */
class PageNode {
public:
  int get_id() {
    return page_id_;
  }

  void clear() {
      free(history);
  }

  void change(int id, int time) {
    page_id_ = id;
    length = 1;
    history[length - 1] = time;
    first = time;
  }

  void refresh(int time) {
    length++;
    history[(length - 1) % k_] = time;
  }

  int get_time(int identifier) {
    if (identifier == -1) {
      return first;
    }
    if (identifier == 0) {
      return history[(length - 1) % k_];
    }
    if (length < k_)return -1;
    return history[(length) % k_];
  }
  void build() {
    history=(int*)calloc(k_,sizeof(int));
  }
private:
  int page_id_{};
  int *history = nullptr;
  int first = 0;
  int length = 0;
};

class ReplacementManager {
public:
  constexpr static size_t npos = -1;

  ReplacementManager() = delete;

  /**
   * @brief 初始化整个类
   * @param max_size 缓存池可以容纳的页数量的上限
   * @param k LRU-K所基于的常数k，在类销毁前不会变更
   * @param default_policy 在置换时，如果没有显式指示，则默认使用default_policy作为策略
   * @note 我们将保证default_policy的值不是ReplacementPolicy::kDEFAULT。
   */
  ReplacementManager(int max_size, int k, ReplacementPolicy default_policy) {
    max_size_ = max_size;
    k_ = k;
    default_policy_ = default_policy;
    pool = (PageNode *) calloc(max_size_, sizeof(PageNode));
    for(int i=0;i<max_size_;++i) {
      pool[i].build();
    }
    filled = (bool *) calloc(max_size_, sizeof(bool));
  }

  /**
   * @brief 析构函数
   * @note 我们将对代码进行Valgrind Memcheck，请保证你的代码不发生内存泄漏
   */
  ~ReplacementManager() {
    for (int i = 0; i < max_size_; ++i) {
      pool[i].clear();
    }
    free(pool);
    free(filled);
  }

  /**
   * @brief 重设当前默认的缓存置换政策
   * @param default_policy 新的默认政策，保证default_policy不是ReplacementPolicy::kDEFAULT
   */
  void SwitchDefaultPolicy(ReplacementPolicy default_policy) {
    default_policy_ = default_policy;
  }

  /**
   * @brief 访问某个页面。
   * @param page_id 访问页的编号
   * @param evict_id 需要被置换的页编号，如果不需要置换请将其设置为npos
   * @param policy 如果需要置换，那么置换所基于的策略
   * (a) 若访问的页已经在缓存池中，那么直接记录其访问信息。
   * (b) 若访问的页不在缓存池中，那么：
   *    1. 若缓存池已满，就从中依照policy置换一个页（彻底删除其对应节点），并将新访问的页加入缓存池，记录其访问
   *    2. 若缓存池未满，则直接将其加入缓存池并记录其访问
   * @note 我们不保证page_id在调用间连续，也不保证page_id的范围，只保证page_id在int内
   */
  void Visit(int page_id, size_t &evict_id, ReplacementPolicy policy = ReplacementPolicy::kDEFAULT) {
    time_++;
    for (int i = 0; i < maxm_size; ++i) {
      if (filled[i] && pool[i].get_id() == page_id) {
        pool[i].refresh(time_);
        evict_id = npos;
        return;
      }
    }
    if(!Full()) {
      for(int i=0;i<max_size_;++i) {
        if(!filled[i]) {
          size_++;
          maxm_size=std::max(maxm_size,size_);
          pool[i].change(page_id,time_);
          filled[i]=true;
          evict_id=npos;
          return;
        }
      }

    }
    if (policy == ReplacementPolicy::kDEFAULT) {
      policy = default_policy_;
    }
    switch (policy) {
      case ReplacementPolicy::kFIFO: {
        int first_time = 1e9;
        int remove_p=-1;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(-1);
          if (t < first_time) {
            remove_p=i;
            first_time = t;
          }
        }
        evict_id=pool[remove_p].get_id();
        pool[remove_p].change(page_id,time_);
        return;
      }
      case ReplacementPolicy::kLRU: {
        int first_time = 1e9;
        int remove_p=-1;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(0);
          if (t < first_time) {
            remove_p=i;
            first_time = t;
          }
        }
        evict_id=pool[remove_p].get_id();
        pool[remove_p].change(page_id,time_);
        return;
      }
      case ReplacementPolicy::kMRU: {
        int first_time = 0;
        int remove_id = 0,remove_p=-1;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(0);
          if (t > first_time) {
            remove_p=i;
            first_time = t;
          }
        }
        evict_id=pool[remove_p].get_id();
        pool[remove_p].change(page_id,time_);
        return;
      }
      case ReplacementPolicy::kLRU_K: {
        int first_time = 1e9, last_time = 1e9;
        int remove_p=-1;
        bool haveless = false;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(1);
          if (t == npos) {
            haveless = true;
            int tmp = pool[i].get_time(-1);
            if (last_time > tmp) {
              last_time = tmp;
              remove_p=i;
            }
          } else if (t < first_time && !haveless) {
            remove_p=i;
            first_time = t;
          }
        }
        evict_id=pool[remove_p].get_id();
        pool[remove_p].change(page_id,time_);
        return;
      }
      default: {
        return;
      }
    }
  }

  /**
   * @brief 强制地删除特定的页（无论缓存池是否已满）
   * @param page_id 被删除页的编号
   * @return 如果成功删除，则返回true; 如果该页不存在于缓存池中，则返回false
   * 如果page_id存在于缓存池中，则删除它；否则，直接返回false
   */
  bool RemovePage(int page_id) {
    for (int i = 0; i < max_size_; ++i) {
      if (filled[i] && pool[i].get_id() == page_id) {
        filled[i] = false;
        size_--;
        return true;
      }
    }
    return false;
  }

  /**
   * @brief 查询特定策略下首先被置换的页
   * @param policy 置换策略
   * @return 当前策略下会被置换的页的编号。若缓存池没满，则返回npos
   * 不对缓存池做任何修改，只查询在需要置换的情况下，基于给定的政策，应该置换哪个页。
   * @note 如果缓存池没有满，请直接返回npos
   */
  [[nodiscard]] int TryEvict(ReplacementPolicy policy = ReplacementPolicy::kDEFAULT) const {
    if (!Full())return npos;
    if (policy == ReplacementPolicy::kDEFAULT) {
      policy = default_policy_;
    }
    switch (policy) {
      case ReplacementPolicy::kFIFO: {
        int first_time = 2e9;
        int remove_id = 0;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(-1);
          if (t < first_time) {
            remove_id = pool[i].get_id();
            first_time = t;
          }
        }
        return remove_id;
      }
      case ReplacementPolicy::kLRU: {
        int first_time = 2e9;
        int remove_id = 0;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(0);
          if (t < first_time) {
            remove_id = pool[i].get_id();
            first_time = t;
          }
        }
        return remove_id;
      }
      case ReplacementPolicy::kMRU: {
        int first_time = 0;
        int remove_id = 0;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(0);
          if (t > first_time) {
            remove_id = pool[i].get_id();
            first_time = t;
          }
        }
        return remove_id;
      }
      case ReplacementPolicy::kLRU_K: {
        int first_time = 2e9, last_time = 2e9;
        int remove_id = 0;
        bool haveless = false;
        for (int i = 0; i < max_size_; ++i) {
          int t = pool[i].get_time(1);
          if (t == npos) {
            haveless = true;
            int tmp = pool[i].get_time(-1);
            if (last_time > tmp) {
              last_time = tmp;
              remove_id = pool[i].get_id();
            }
          } else if (t < first_time && !haveless) {
            remove_id = pool[i].get_id();
            first_time = t;
          }
        }
        return remove_id;
      }
      default: {
        return npos;
      }
    }
  }

  /**
   * @brief 返回当前缓存管理器是否为空。
   */
  [[nodiscard]] bool Empty() const {
    if (size_ == 0)return true;
    return false;
  }

  /**
   * @brief 返回当前缓存管理器是否已满（即是否页数量已经达到上限）
   */
  [[nodiscard]] bool Full() const {
    if (size_ == max_size_)return true;
    return false;
  }

  /**
   * @brief 返回当前缓存管理器中页的数量
   */
  [[nodiscard]] int Size() const {
    return size_;
  }

private:
  int max_size_;
  ReplacementPolicy default_policy_;
  PageNode *pool = nullptr;
  bool *filled = nullptr;
  int size_ = 0;
  int time_ = 0;
  int maxm_size=0;
};
#endif