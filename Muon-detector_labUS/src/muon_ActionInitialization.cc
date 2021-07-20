#include "muon_ActionInitialization.hh"
#include "muon_PrimaryGeneratorAction.hh"
#include "muon_RunAction.hh"
#include "muon_EventAction.hh"
#include "muon_SteppingAction.hh"

muon_ActionInitialization::muon_ActionInitialization()
 : G4VUserActionInitialization()
{}
muon_ActionInitialization::~muon_ActionInitialization()
{}

void muon_ActionInitialization::BuildForMaster() const
{
  muon_RunAction* runAction = new muon_RunAction;
  SetUserAction(runAction);
}

void muon_ActionInitialization::Build() const
{
  SetUserAction(new muon_PrimaryGeneratorAction);

  muon_RunAction* runAction = new muon_RunAction;
  SetUserAction(runAction);

  muon_EventAction* eventAction = new muon_EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new muon_SteppingAction(eventAction));
}
