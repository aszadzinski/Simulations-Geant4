#include "muography_PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4RadioactiveDecayPhysics.hh"

muography_PhysicsList::muography_PhysicsList()
:G4VModularPhysicsList()
{
 //RegisterPhysics( new G4EmExtraPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
  RegisterPhysics(new G4DecayPhysics());
 // RegisterPhysics(new G4RadioactiveDecayPhysics());

}

muography_PhysicsList::~muography_PhysicsList()
{
 }
void muography_PhysicsList::SetCuts()
{
  SetCutValue(7*mm, "proton");
  SetCutValue(7*mm, "e-");
  SetCutValue(7*mm, "e+");
  SetCutValue(7*mm, "mu-");
  SetCutValue(7*mm, "gamma");
}
