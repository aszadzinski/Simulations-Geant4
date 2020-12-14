#include "pet_EventAction.hh"
#include "pet_RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include <fstream>
std::ofstream file;



pet_EventAction::pet_EventAction(pet_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  Edep(0.)
{
  file.open("./output.dat");
}

pet_EventAction::~pet_EventAction()
{
  file.close();
}

void pet_EventAction::BeginOfEventAction(const G4Event*)
{
  EdepA = 0.;
  posAX = 0.;
  posAY = 0.;
  posAZ = 0.;
  dFlagA = 0;
  EdepB = 0.;
  posBX = 0.;
  posBY = 0.;
  posBZ = 0.;
  dFlagB = 0;
  EntA = 0;
  EntB = 0;

}

void pet_EventAction::EndOfEventAction(const G4Event*)
{
  if (EntA == 1 || EntB == 1)
  {
    file<<Edep<<G4endl;
  }
  fRunAction->AddEdep(Edep);
  G4cout<<"Edep="<<Edep<<G4endl;
}
