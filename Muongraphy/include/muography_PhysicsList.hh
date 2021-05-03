#ifndef muography_PhysicsList_h
#define muography_PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class muography_PhysicsList: public G4VModularPhysicsList
{
  public:
    muography_PhysicsList();
   ~muography_PhysicsList();
   void SetCuts();
};

#endif
