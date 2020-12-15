#include "pet_DetectorMessenger.hh"

#include "pet_DetectorConstruction.hh"

#include "G4UIdirectory.hh"

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"


pet_DetectorMessenger::pet_DetectorMessenger(pet_DetectorConstruction* Det):G4UImessenger(),
myDetector(Det)
{


//////////////////////////////
// Directory
//////////////////////////////

  petDir = new G4UIdirectory("/pet/");
  petDir->SetGuidance("Detector control.");

//////////////////////////////
// Generation Parameters


  height = new G4UIcmdWithADoubleAndUnit("/pet/h",this);
  height->SetGuidance("alpha ang. [deg]");
  height->SetDefaultUnit("cm");
  zz = new G4UIcmdWithADoubleAndUnit("/pet/z",this);
  zz->SetGuidance("alpha ang. [deg]");
  zz->SetDefaultUnit("cm");
}

pet_DetectorMessenger::~pet_DetectorMessenger()
{
//////////////////////////////
// Generation Parameters
//////////////////////////////
  delete height;

}
void pet_DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{

//////////////////////////////
// Generation Parameters
//////////////////////////////
   if(command==height)
    myDetector->SetHeight(height->GetNewDoubleValue(newValues));

    else if(command==zz)
      myDetector->SetZ(zz->GetNewDoubleValue(newValues));

}
