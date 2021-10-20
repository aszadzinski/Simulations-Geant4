#ifndef pet_RunAction_h
#define pet_RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

class pet_RunAction : public G4UserRunAction
{
  public:
    pet_RunAction();
    virtual ~pet_RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep);

  private:
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fEdep2;
};
#endif
