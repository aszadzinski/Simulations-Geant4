#include "muography_SteppingAction.hh"
#include "muography_EventAction.hh"
#include "muography_DetectorConstruction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "muography_PrimaryGeneratorAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


muography_SteppingAction::muography_SteppingAction(muography_EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

muography_SteppingAction::~muography_SteppingAction()
{}

void muography_SteppingAction::UserSteppingAction(const G4Step* theStep)
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
  fEventAction->SetHeight(muography_PrimaryGeneratorAction::GetHeight());
  fEventAction->SetZ(muography_PrimaryGeneratorAction::GetZ());
  fEventAction->SetDist(muography_PrimaryGeneratorAction::GetDist());


  if (thePrePVname(0,9)=="ADetector")
  {

    fEventAction->SetEdepA(theStep->GetTotalEnergyDeposit());
    fEventAction->SetEntA(1);
    fEventAction->SetPosA(theTrack->GetPosition().x(),
                          theTrack->GetPosition().y(),
                          theTrack->GetPosition().z());
    fEventAction->SetdFlagA(1);

  }
    if (thePrePVname(0,9)=="BDetector")
    {

      fEventAction->SetEdepB(theStep->GetTotalEnergyDeposit());
      fEventAction->SetEntB(1);
      fEventAction->SetPosB(theTrack->GetPosition().x(),
                            theTrack->GetPosition().y(),
                            theTrack->GetPosition().z());
      fEventAction->SetdFlagB(1);

    }
  return;

}
