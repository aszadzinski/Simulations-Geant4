#ifndef muon_DetectorConstruction_h
#define muon_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class muon_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        muon_DetectorConstruction();
        virtual ~muon_DetectorConstruction();
        virtual G4VPhysicalVolume* Construct();

        G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    protected:
        G4LogicalVolume*  fScoringVolume;
};
#endif
