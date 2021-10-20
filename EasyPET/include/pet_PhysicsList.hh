#ifndef pet_PhysicsList_h
#define pet_PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class pet_PhysicsList: public G4VModularPhysicsList
{
  public:
    pet_PhysicsList();
   ~pet_PhysicsList();
   void SetCuts();
};

#endif
