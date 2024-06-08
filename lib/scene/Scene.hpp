#pragma once

#include <string>

class Scene {
 public:
  virtual void render() = 0;
  virtual std::string getName() const = 0;
};
