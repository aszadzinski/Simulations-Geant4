#ifndef pet_DetectorMessenger_h
#define pet_DetectorMessenger_h 1

class pet_DetectorConstruction;
class G4UIcmdWithoutParameter;

#include "globals.hh"
#include "G4UImessenger.hh"


class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
class pet_DetectorConstruction;

class pet_DetectorMessenger: public G4UImessenger
{

  public:
    pet_DetectorMessenger(pet_DetectorConstruction*);
   virtual ~pet_DetectorMessenger();

virtual   void SetNewValue(G4UIcommand * command, G4String newValues);

  private:
    pet_DetectorConstruction* myDetector;

  G4UIdirectory*  petDir;


  G4UIcmdWithADoubleAndUnit* height;
  G4UIcmdWithADoubleAndUnit* height0;
    G4UIcmdWithADoubleAndUnit* deta;
    G4UIcmdWithADoubleAndUnit* detb;
    G4UIcmdWithADoubleAndUnit* zz;
    G4UIcmdWithADoubleAndUnit* zz0;
    G4UIcmdWithADoubleAndUnit* dist;

};

#endif
