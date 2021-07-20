#ifndef muon_ActionInitialization_h
#define muon_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class muon_ActionInitialization : public G4VUserActionInitialization
{
  public:
    muon_ActionInitialization();
    virtual ~muon_ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};
#endif
