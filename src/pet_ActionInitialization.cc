#include "pet_ActionInitialization.hh"
#include "pet_PrimaryGeneratorAction.hh"
#include "pet_RunAction.hh"
#include "pet_EventAction.hh"
#include "pet_SteppingAction.hh"

pet_ActionInitialization::pet_ActionInitialization(pet_DetectorConstruction* MDC)
 : G4VUserActionInitialization()
{
MyDC = MDC;

}
pet_ActionInitialization::~pet_ActionInitialization()
{}

void pet_ActionInitialization::BuildForMaster() const
{
  pet_RunAction* runAction = new pet_RunAction;
  SetUserAction(runAction);
}

void pet_ActionInitialization::Build() const
{
  SetUserAction(new pet_PrimaryGeneratorAction(MyDC));

  pet_RunAction* runAction = new pet_RunAction;
  SetUserAction(runAction);

  pet_EventAction* eventAction = new pet_EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new pet_SteppingAction(eventAction));
}
