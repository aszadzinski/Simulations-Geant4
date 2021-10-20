#ifndef pet_SteppingAction_h
#define pet_SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class pet_EventAction;

class G4LogicalVolume;

class pet_SteppingAction : public G4UserSteppingAction
{
  public:
    pet_SteppingAction(pet_EventAction* eventAction);
    virtual ~pet_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    pet_EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};
#endif
