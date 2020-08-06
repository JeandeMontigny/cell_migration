// -----------------------------------------------------------------------------
//
// Copyright (C) Jean de Montigny.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef BIOLOGY_MODULE_H_
#define BIOLOGY_MODULE_H_

#include "biodynamo.h"
#include "core/biology_module/biology_module.h"
#include "my_cell.h"

namespace bdm {

  // enumerate substances in simulation
  enum Substances { dg_0_ };

  // ---------------------------------------------------------------------------
  // define behaviour for ganglion cells
  struct GanglionBM : public BaseBiologyModule {
    BDM_STATELESS_BM_HEADER(GanglionBM, BaseBiologyModule, 1);

    GanglionBM() : BaseBiologyModule(gAllEventIds) {}

    void Run(SimObject* so) override {
      auto* sim = Simulation::GetActive();
      auto* rm = sim->GetResourceManager();
      auto* cell = bdm_static_cast<MyCell*>(so);

      DiffusionGrid* dg = nullptr;
      dg = rm->GetDiffusionGrid("rgc_guide");
      const auto& position = cell->GetPosition();

      dg->IncreaseConcentrationBy(position, 1);

    } // end Run
  }; // end GanglionBM

  // ---------------------------------------------------------------------------
  // define behaviour for amacrine cells
  struct AmacrineBM : public BaseBiologyModule {
    BDM_STATELESS_BM_HEADER(AmacrineBM, BaseBiologyModule, 1);

    AmacrineBM() : BaseBiologyModule(gAllEventIds) {}

    void Run(SimObject* so) override {
      auto* sim = Simulation::GetActive();
      auto* rm = sim->GetResourceManager();
      auto* random = sim->GetRandom();
      auto* cell = bdm_static_cast<MyCell*>(so);

      DiffusionGrid* dg = nullptr;
      dg = rm->GetDiffusionGrid("rgc_guide");
      const auto& position = cell->GetPosition();
      double concentration = dg->GetConcentration(position);

      auto movement = random->UniformArray<3>(-0.2, 0.2).Normalize();
      movement[2] = -1;

      if (concentration < 0.001) {
        cell->SetPosition(position + movement);
      }
      else {
        cell->RemoveBiologyModule(this);
      }

    } // end Run
  }; // end AmacrineBM

}  // namespace bdm

#endif  // BIOLOGY_MODULE_H_
