#ifndef muon_EventAction_h
#define muon_EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class muon_RunAction;

class muon_EventAction : public G4UserEventAction
{
  public:
    muon_EventAction(muon_RunAction* runAction);
    virtual ~muon_EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    muon_RunAction* fRunAction;
    G4double     fEdep;
};

#endif
