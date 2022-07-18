#include "muon_EventAction.hh"
#include "muon_RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
std::ofstream file;



muon_EventAction::muon_EventAction(muon_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction), ERD(0.), ELD(0.), ETD(0.), EBD(0.)
{
  file.open("./output.dat");
}

muon_EventAction::~muon_EventAction()
{
  file.close();
}

void muon_EventAction::BeginOfEventAction(const G4Event*)
{
  ERD = 0;
  ELD = 0;
  ETD = 0;
  EBD = 0;

}

void muon_EventAction::EndOfEventAction(const G4Event*)
{
  if (ELD > 1. || ERD > 1. || ETD > 1. || EBD > 1.)
  {
   file<<ELD<<" "<<ERD<<" "<<ETD<<" "<<EBD<<G4endl;
  }
  fRunAction->AddE(ELD, ERD, ETD, EBD);
  G4cout<<"LDet="<<ELD<<" RDet="<<ERD<<" TDet="<<ETD<<" BDet="<<EBD<<G4endl;
}
