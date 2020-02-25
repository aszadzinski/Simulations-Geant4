#include "muon_SteppingAction.hh"
#include "muon_EventAction.hh"
#include "muon_DetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

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

void muon_SteppingAction::UserSteppingAction(const G4Step* theStep)
{
	G4Track *theTrack = theStep->GetTrack();

  G4int ParticleType = theTrack->GetDefinition()->GetPDGEncoding();
  G4StepPoint * thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume * thePrePV = thePrePoint->GetPhysicalVolume();
  G4StepPoint * thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume();
  G4String thePrePVname = thePrePV->GetName();
  G4String thePostPVname="nnnnn";
  G4int lastParticle = 0;
  if(thePostPV !=0 ){ thePostPVname = thePostPV->GetName(); }
  if (theStep->GetTotalEnergyDeposit()==0) {return;}

  if (thePrePVname(0,4)=="LDet")
  {
    fEventAction->SetEdep(theStep->GetTotalEnergyDeposit());
    fEventAction->SetPos(theTrack->GetPosition().x(),
                          theTrack->GetPosition().y(),
                          theTrack->GetPosition().z());
    fEventAction->SetdFlag(0.);

  }
  return;

}
