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

    void SetEdep(G4double edep) { Edep += edep; }
    void SetPos(G4double x,G4double y, G4double z) { posX=x;posY=y;posZ=z;}
    void SetdFlag(G4int flag) { dFlag=flag; }

  private:
    muon_RunAction* fRunAction;
    G4double        Edep, posX,posY,posZ;
    G4int           dFlag;
};

#endif
