#pragma once
#include "HitableList.h"
namespace StellarTrace {
class Scene {
public :
  void Add(Hitable* hitable) { Objects.Add(hitable); }

  HitableList Objects;
};

}  // namespace StellarTrace
