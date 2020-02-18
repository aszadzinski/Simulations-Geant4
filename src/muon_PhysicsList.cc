#include "muon_PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"

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
