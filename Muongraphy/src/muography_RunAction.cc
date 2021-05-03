#include "muography_RunAction.hh"
#include "muography_PrimaryGeneratorAction.hh"
#include "muography_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

muography_RunAction::muography_RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fEdep2(0.)
{
}

muography_RunAction::~muography_RunAction()
{}

void muography_RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed

}

void muography_RunAction::EndOfRunAction(const G4Run* run)
{

}

void muography_RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}
