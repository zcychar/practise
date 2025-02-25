#ifndef SRC_HPP
#define SRC_HPP
/**
 * 枚举类，用于枚举可能的置换策略
 */
enum class ReplacementPolicy { kDEFAULT = 0, kFIFO, kLRU, kMRU, kLRU_K };

/**
 * @brief 该类用于维护每一个页对应的信息以及其访问历史，用于在尝试置换时查询需要的信息。
 */
class PageNode {
public:
  // TODO: Add your code here.

private:
  std::size_t page_id_{};
  // TODO: Add your variables here.
};

class ReplacementManager {
public:
  constexpr static std::size_t npos = -1;

  ReplacementManager() = delete;

  /**
   * @brief 初始化整个类
   * @param max_size 缓存池可以容纳的页数量的上限
   * @param k LRU-K所基于的常数k，在类销毁前不会变更
   * @param default_policy 在置换时，如果没有显式指示，则默认使用default_policy作为策略
   * @note 我们将保证default_policy的值不是ReplacementPolicy::kDEFAULT。
   */
  ReplacementManager(std::size_t max_size, std::size_t k, ReplacementPolicy default_policy) {
    // TODO: Code here
  }

  /**
   * @brief 析构函数
   * @note 我们将对代码进行Valgrind Memcheck，请保证你的代码不发生内存泄漏
   */
  ~ReplacementManager() {
    // TODO: Code here
  }

  /**
   * @brief 重设当前默认的缓存置换政策
   * @param default_policy 新的默认政策，保证default_policy不是ReplacementPolicy::kDEFAULT
   */
  void SwitchDefaultPolicy(ReplacementPolicy default_policy) {
    // TODO: Code here
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
   * @note 我们不保证page_id在调用间连续，也不保证page_id的范围，只保证page_id在std::size_t内
   */
  void Visit(std::size_t page_id, std::size_t &evict_id, ReplacementPolicy policy = ReplacementPolicy::kDEFAULT) {
    // TODO: Code here
  }

  /**
   * @brief 强制地删除特定的页（无论缓存池是否已满）
   * @param page_id 被删除页的编号
   * @return 如果成功删除，则返回true; 如果该页不存在于缓存池中，则返回false
   * 如果page_id存在于缓存池中，则删除它；否则，直接返回false
   */
  bool RemovePage(std::size_t page_id) {
    // TODO: Code here
  }

  /**
   * @brief 查询特定策略下首先被置换的页
   * @param policy 置换策略
   * @return 当前策略下会被置换的页的编号。若缓存池没满，则返回npos
   * 不对缓存池做任何修改，只查询在需要置换的情况下，基于给定的政策，应该置换哪个页。
   * @note 如果缓存池没有满，请直接返回npos
   */
  [[nodiscard]] std::size_t TryEvict(ReplacementPolicy policy = ReplacementPolicy::kDEFAULT) const {
    // TODO: Code here
  }

  /**
   * @brief 返回当前缓存管理器是否为空。
   */
  [[nodiscard]] bool Empty() const {
    // TODO: Code here
  }

  /**
   * @brief 返回当前缓存管理器是否已满（即是否页数量已经达到上限）
   */
  [[nodiscard]] bool Full() const {
    // TODO: Code here
  }

  /**
   * @brief 返回当前缓存管理器中页的数量
   */
  [[nodiscard]] std::size_t Size() const {
    // TODO: Code here
  }

private:
  // TODO: Add your variables here.
};
#endif