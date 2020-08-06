// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef MY_CELL_H_
#define MY_CELL_H_

#include "core/sim_object/cell.h"
#include "core/biology_module/biology_module.h"

namespace bdm {

/// Possible states
enum Type { kGanglion, kAmacrine };

class MyCell : public Cell {
  BDM_SIM_OBJECT_HEADER(MyCell, Cell, 1, type_);

 public:
  MyCell() {}
  MyCell(const Event& event, SimObject* other, uint64_t new_oid = 0)
      : Base(event, other, new_oid) {}
  explicit MyCell(const Double3& position) : Base(position) {}

  /// This data member stores the cell type.
  int type_ = Type::kGanglion;
};

}  // namespace bdm

#endif // MY_CELL_H_
