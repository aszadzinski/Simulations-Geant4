#include "muon_SteppingAction.hh"
#include "muon_EventAction.hh"
#include "muon_DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

muon_SteppingAction::muon_SteppingAction(muon_EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

muon_SteppingAction::~muon_SteppingAction()
{}

void muon_SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const muon_DetectorConstruction* detectorConstruction
      = static_cast<const muon_DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;

  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);
}
