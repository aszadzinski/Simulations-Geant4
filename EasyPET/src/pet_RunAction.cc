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

}

void pet_RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}
