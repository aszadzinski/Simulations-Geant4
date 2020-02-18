#include "muon_EventAction.hh"
#include "muon_RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

muon_EventAction::muon_EventAction(muon_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{}

muon_EventAction::~muon_EventAction()
{}

void muon_EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
}

void muon_EventAction::EndOfEventAction(const G4Event*)
{
  fRunAction->AddEdep(fEdep);
}
