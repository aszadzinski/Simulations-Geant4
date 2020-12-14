#include "pet_RunAction.hh"
#include "pet_PrimaryGeneratorAction.hh"
#include "pet_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

pet_RunAction::pet_RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{
}

pet_RunAction::~pet_RunAction()
{}

void pet_RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed

}

void pet_RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl;
  }

  G4cout
     << "->Sum Edep ="
     << edep
     <<"MeV?"
     << G4endl;
}

void pet_RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}
