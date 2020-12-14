#ifndef pet_DetectorConstruction_h
#define pet_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class pet_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        pet_DetectorConstruction();
        virtual ~pet_DetectorConstruction();
        virtual G4VPhysicalVolume* Construct();

        G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    protected:
        G4LogicalVolume*  fScoringVolume;
        G4LogicalVolume*  fEdA;
        G4LogicalVolume*  fEdB;
};
#endif
