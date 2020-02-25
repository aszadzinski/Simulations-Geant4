#include "muon_PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"


muon_PhysicsList::muon_PhysicsList()
:G4VModularPhysicsList()
{
  RegisterPhysics( new G4EmExtraPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
}

muon_PhysicsList::~muon_PhysicsList()
{
 }

void muon_PhysicsList::SetCuts()
{
  SetCutValue(0.07*mm, "proton");
  SetCutValue(0.07*mm, "e-");
  SetCutValue(0.07*mm, "e+");
  SetCutValue(0.07*mm, "mu-");
  SetCutValue(0.07*mm, "gamma");
}
