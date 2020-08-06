// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef CELL_CREATION_
#define CELL_CREATION_

#include "my_cell.h"
#include "biology_module.h"

namespace bdm {

  // define cell creator
  static void CellCreator(double min, double max,
                          int num_cell, Type type) {

    auto* sim = Simulation::GetActive();
    auto* rm = sim->GetResourceManager();
    auto* random = sim->GetRandom();

    double x, y;
    double z = 0;
    if (type == Type::kAmacrine) {
      z = 100;
    }
    for (int i = 0; i < num_cell; i++) {
      x = random->Uniform(min, max);
      y = random->Uniform(min, max);

      MyCell* cell = new MyCell({x, y, z});
      cell->SetDiameter(10);
      cell->type_ = type;
      if (type == Type::kAmacrine) {
        cell->AddBiologyModule(new AmacrineBM());
      }
      if (type == Type::kGanglion) {
        cell->AddBiologyModule(new GanglionBM());
      }

      rm->push_back(cell);
    }
  }  // end CellCreator

}

#endif // CELL_CREATION_
