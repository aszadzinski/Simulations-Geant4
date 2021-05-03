#ifndef muography_DetectorMessenger_h
#define muography_DetectorMessenger_h 1

class muography_DetectorConstruction;
class G4UIcmdWithoutParameter;

#include "globals.hh"
#include "G4UImessenger.hh"


class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
class muography_DetectorConstruction;

class muography_DetectorMessenger: public G4UImessenger
{

  public:
    muography_DetectorMessenger(muography_DetectorConstruction*);
   virtual ~muography_DetectorMessenger();

virtual   void SetNewValue(G4UIcommand * command, G4String newValues);

  private:
    muography_DetectorConstruction* myDetector;

    G4UIdirectory*  muographyDir;

    G4UIcmdWithADoubleAndUnit* fTrainX;
    G4UIcmdWithADoubleAndUnit* fTrainY;
    G4UIcmdWithADoubleAndUnit* fTrainZ;

    G4UIcmdWithADoubleAndUnit* fDetX;
    G4UIcmdWithADoubleAndUnit* fDetYZ;

    G4UIcmdWithADoubleAndUnit* fRockX;
    G4UIcmdWithADoubleAndUnit* fRockYZ;

    G4UIcmdWithADoubleAndUnit* fTChamberR;
    G4UIcmdWithADoubleAndUnit* fTrainR;

    G4UIcmdWithAnInteger* fGunChoice;

    G4UIcmdWithADoubleAndUnit* fGunPosX;
    G4UIcmdWithADoubleAndUnit* fGunPosY;
    G4UIcmdWithADoubleAndUnit* fGunPosZ;

    G4UIcmdWithADoubleAndUnit* fGunE0;

};

#endif
