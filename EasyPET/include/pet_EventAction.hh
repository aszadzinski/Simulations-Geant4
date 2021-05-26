#ifndef pet_EventAction_h
#define pet_EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class pet_RunAction;

class pet_EventAction : public G4UserEventAction
{
  public:
    pet_EventAction(pet_RunAction* runAction);
    virtual ~pet_EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void SetEdepA(G4double edep) { EdepA += edep; }

    void SetEdepB(G4double edep) { EdepB += edep; }
    void SetPosA(G4double x,G4double y, G4double z) { posAX=x;posAY=y;posAZ=z;}
    void SetPosB(G4double x,G4double y, G4double z) { posBX=x;posBY=y;posBZ=z;}
    void SetdFlagA(G4int flag) { dFlagA=flag; }
    void SetdFlagB(G4int flag) { dFlagB=flag; }
    void SetEntA(G4int enta) { EntA=enta; }
    void SetEntB(G4int entb) { EntB=entb; }
    void SetHeight(G4double h){hei = h;}
    void SetZ(G4double z){zz = z;}
    void SetDist(G4double z){dist = z;}


  private:
    pet_RunAction* fRunAction;
    G4double        EdepA, EdepB, posAX,posAY,posAZ, posBX,posBY,posBZ,hei,zz,dist;
    G4int           dFlagA=0;
    G4int           dFlagB=0;
    G4int  EntA, EntB;
};

#endif
