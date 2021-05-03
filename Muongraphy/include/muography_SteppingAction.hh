#ifndef muography_SteppingAction_h
#define muography_SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class muography_EventAction;

class G4LogicalVolume;

class muography_SteppingAction : public G4UserSteppingAction
{
  public:
    muography_SteppingAction(muography_EventAction* eventAction);
    virtual ~muography_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    muography_EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};
#endif
