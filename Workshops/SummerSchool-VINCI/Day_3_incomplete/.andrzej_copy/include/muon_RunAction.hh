#ifndef muon_RunAction_h
#define muon_RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class muon_RunAction : public G4UserRunAction
{
  public:
    muon_RunAction();
    virtual ~muon_RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

 void AddE (G4double, G4double, G4double, G4double);

  private:
    G4double fELD;
    G4double fERD;
    G4double fETD;
    G4double fEBD;
};
#endif
