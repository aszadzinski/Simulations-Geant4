#include "muon_EventAction.hh"
#include "muon_RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
std::ofstream file;



muon_EventAction::muon_EventAction(muon_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  Edep(0.)
{
  file.open("./output.dat");
}

muon_EventAction::~muon_EventAction()
{
  file.close();
}

void muon_EventAction::BeginOfEventAction(const G4Event*)
{
  Edep = 0.;
  posX = 0.;
  posY = 0.;
  posZ = 0.;
  dFlag = 0;

}

void muon_EventAction::EndOfEventAction(const G4Event*)
{
  if (Edep > 10.)
  {
    file<<Edep<<G4endl;
  }
  fRunAction->AddEdep(Edep);
  G4cout<<"Edep="<<Edep<<G4endl;
}
