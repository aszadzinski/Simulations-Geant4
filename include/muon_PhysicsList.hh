#ifndef muon_PhysicsList_h
#define muon_PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class muon_PhysicsList: public G4VModularPhysicsList
{
  public:
    muon_PhysicsList();
   ~muon_PhysicsList();
   void SetCuts();
};

#endif
