// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef CELL_MIGRATION_H_
#define CELL_MIGRATION_H_

#include "biodynamo.h"
#include "my_cell.h"
#include "biology_module.h"
#include "population_creation.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {

    auto set_param = [&](Param* param) {
      // Create an artificial bounds for the simulation space
      param->bound_space_ = true;
      param->min_bound_ = 0;
      param->max_bound_ = 250;
    };

  Simulation simulation(argc, argv, set_param);

  auto* param = simulation.GetParam();
  simulation.GetRandom()->SetSeed(8563); // rand() % 10000

  int max_step = 200;
  int nb_cells = 400;

  int grid_spacing = 2; // 4
  int resolution = param->max_bound_/grid_spacing;
  // ratio diffusion_coef/spacing/spacing = 0.125
  double diffusion_coef = 0.125*grid_spacing*grid_spacing;
  double decay_const = 0;

  CellCreator(param->min_bound_, param->max_bound_, nb_cells, Type::kGanglion);
  CellCreator(param->min_bound_, param->max_bound_, nb_cells, Type::kAmacrine);

  ModelInitializer::DefineSubstance(dg_0_, "rgc_guide", diffusion_coef,
                                    decay_const, resolution);

  std::cout << "cells created and substances initialised" << std::endl;

  // Run simulation for one timestep
  std::cout << "simulating.." << std::endl;
  for (int i = 0; i < max_step; i++) {
    simulation.GetScheduler()->Simulate(1);
  }

  std::cout << "done" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // CELL_MIGRATION_H_
