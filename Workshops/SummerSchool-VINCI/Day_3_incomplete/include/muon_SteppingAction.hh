#ifndef muon_SteppingAction_h
#define muon_SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class muon_EventAction;

class G4LogicalVolume;

class muon_SteppingAction : public G4UserSteppingAction
{
  public:
    muon_SteppingAction(muon_EventAction* eventAction);
    virtual ~muon_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    muon_EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};
#endif
