#ifndef muography_ActionInitialization_h
#define muography_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "muography_DetectorConstruction.hh"

class muography_ActionInitialization : public G4VUserActionInitialization
{
  public:
    muography_ActionInitialization(muography_DetectorConstruction*);
    virtual ~muography_ActionInitialization();
    muography_DetectorConstruction* MyDC;

    virtual void BuildForMaster() const;
    virtual void Build() const;
};
#endif
