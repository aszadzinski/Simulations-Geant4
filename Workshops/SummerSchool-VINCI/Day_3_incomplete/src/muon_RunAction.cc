#include "muon_RunAction.hh"
#include "muon_PrimaryGeneratorAction.hh"
#include "muon_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>

muon_RunAction::muon_RunAction()
: G4UserRunAction(),
fELD(0.), 
fERD(0.), 
fEBD(0.), 
fETD(0.)
{
}

muon_RunAction::~muon_RunAction()
{}

void muon_RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4cout<<"--------------Begin of global run ------------"<<G4endl;;

}

void muon_RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4double eld  = fELD;
  G4double erd  = fERD;
  G4double etd  = fETD;
  G4double ebd  = fEBD;

  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------"
     << G4endl;
  }

  G4cout<<"TOTAL: LDet="<<eld<<" RDet="<<erd<<" TDet="<<etd<<" BDet="<<ebd<<G4endl;
}

void muon_RunAction::AddE(G4double eld, G4double erd, G4double etd, G4double ebd)
{
  fELD  += eld;
  fERD  += erd;
  fEBD  += ebd;
  fETD  += etd;
}
