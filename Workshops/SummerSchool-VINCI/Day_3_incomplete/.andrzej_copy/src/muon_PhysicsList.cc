#include "muon_PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4OpticalPhysics.hh"


muon_PhysicsList::muon_PhysicsList()
:G4VModularPhysicsList()
{
  RegisterPhysics( new G4EmExtraPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4OpticalPhysics());
}

muon_PhysicsList::~muon_PhysicsList()
{
 }

void muon_PhysicsList::SetCuts()
{
  SetCutValue(7*m, "proton");
  SetCutValue(7*m, "e-");
  SetCutValue(7*m, "e+");
  SetCutValue(7*m, "mu-");
  SetCutValue(7*m, "gamma");
}
