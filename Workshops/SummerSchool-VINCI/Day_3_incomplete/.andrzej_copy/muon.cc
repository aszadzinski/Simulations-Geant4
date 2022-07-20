#include "muon_DetectorConstruction.hh"
#include "muon_ActionInitialization.hh"
#include "muon_PhysicsList.hh"


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

#include <iostream>

int main(int argc,char** argv)
{
    G4UIExecutive* ui = 0;
    if ( argc == 1 )
    {
        ui = new G4UIExecutive(argc, argv);
    }

  #ifdef G4MULTITHREADED
      G4MTRunManager* runManager = new G4MTRunManager;
      runManager->SetNumberOfThreads(3);
	std::cout<<"USING MTHREADING"<<std::endl;
  #else
      G4RunManager* runManager = new G4RunManager;
  #endif

    runManager->SetUserInitialization(new muon_DetectorConstruction());
    runManager->SetUserInitialization(new muon_PhysicsList());
    runManager->SetUserInitialization(new muon_ActionInitialization());

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( ! ui )
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
    else
    {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
}
