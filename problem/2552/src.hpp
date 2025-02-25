#pragma once
#ifndef SRC_HPP
#define SRC_HPP

#include <type_traits>

namespace sjtu {

  class Throwable {
  public:
    virtual std::string what() const noexcept = 0;
    virtual ~Throwable() = default;
  };

  class NonThrowableException : public Throwable {
  public:
    std::string what() const noexcept override {
      return "Cannot Throw a non-Throwable Exception";
    }
  };

  void handle_exception() {

  }

  template <typename T>
  void my_throw(T &&e) {

  }

}

#endif //SRC_HPP