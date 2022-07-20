#include "muon_EventAction.hh"
#include "muon_RunAction.hh"


#include "G4Threading.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include <string>
#include <vector>
#include <fstream>
std::vector<std::ofstream> streams;



muon_EventAction::muon_EventAction(muon_RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction), ERD(0.), ELD(0.), ETD(0.), EBD(0.)
{
	G4int threadID =  G4Threading::G4GetThreadId();
	//std::ofstream file;
	std::string s = "output-"+std::to_string(threadID)+".dat";
	//file.open(s);
	    streams.emplace_back(std::ofstream{ s });
	G4cout<<"Creating file for thread: "<<s<<G4endl;
}

muon_EventAction::~muon_EventAction()
{
  G4int threadID =  G4Threading::G4GetThreadId();
  streams[threadID].close();
}

void muon_EventAction::BeginOfEventAction(const G4Event*)
{
  ERD = 0;
  ELD = 0;
  ETD = 0;
  EBD = 0;

}

void muon_EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int nevt = evt->GetEventID();
  G4int threadID =  G4Threading::G4GetThreadId();
  if (!(nevt%200000)) G4cout<<"\n-> Begin of event: "<<nevt<<" Worker "<<threadID<<G4endl;
  if (ELD > 0 || ERD > 0 || ETD > 0 || EBD > 0)
  {
   streams[threadID]<<ELD<<" "<<ERD<<" "<<ETD<<" "<<EBD<<G4endl;
  }
  fRunAction->AddE(ELD, ERD, ETD, EBD);
  //G4cout<<"LDet="<<ELD<<" RDet="<<ERD<<" TDet="<<ETD<<" BDet="<<EBD<<G4endl;
}
