#include "muography_ActionInitialization.hh"
#include "muography_PrimaryGeneratorAction.hh"
#include "muography_RunAction.hh"
#include "muography_EventAction.hh"
#include "muography_SteppingAction.hh"

muography_ActionInitialization::muography_ActionInitialization(muography_DetectorConstruction* MDC)
 : G4VUserActionInitialization()
{
MyDC = MDC;

}
muography_ActionInitialization::~muography_ActionInitialization()
{}

void muography_ActionInitialization::BuildForMaster() const
{
  muography_RunAction* runAction = new muography_RunAction;
  SetUserAction(runAction);
}

void muography_ActionInitialization::Build() const
{
  SetUserAction(new muography_PrimaryGeneratorAction(MyDC));

  muography_RunAction* runAction = new muography_RunAction;
  SetUserAction(runAction);

  muography_EventAction* eventAction = new muography_EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new muography_SteppingAction(eventAction));
}
