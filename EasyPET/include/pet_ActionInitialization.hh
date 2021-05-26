#ifndef pet_ActionInitialization_h
#define pet_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "pet_DetectorConstruction.hh"

class pet_ActionInitialization : public G4VUserActionInitialization
{
  public:
    pet_ActionInitialization(pet_DetectorConstruction*);
    virtual ~pet_ActionInitialization();
    pet_DetectorConstruction* MyDC;

    virtual void BuildForMaster() const;
    virtual void Build() const;
};
#endif
