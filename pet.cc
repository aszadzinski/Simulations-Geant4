#include "pet_DetectorConstruction.hh"
#include "pet_ActionInitialization.hh"
#include "pet_PhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

int main(int argc,char** argv)
{
    G4UIExecutive* ui = 0;
    if ( argc == 1 )
    {
        ui = new G4UIExecutive(argc, argv);
    }

  #ifdef G4MULTITHREADED
      G4MTRunManager* runManager = new G4MTRunManager;
  #else
      G4RunManager* runManager = new G4RunManager;
  #endif

    runManager->SetUserInitialization(new pet_DetectorConstruction());
    runManager->SetUserInitialization(new pet_PhysicsList());
    runManager->SetUserInitialization(new pet_ActionInitialization());

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
