#ifndef pet_ActionInitialization_h
#define pet_ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class pet_ActionInitialization : public G4VUserActionInitialization
{
  public:
    pet_ActionInitialization();
    virtual ~pet_ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};
#endif
