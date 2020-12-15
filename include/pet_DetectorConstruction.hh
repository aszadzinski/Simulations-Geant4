#ifndef pet_DetectorConstruction_h
#define pet_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class pet_DetectorMessenger;

class pet_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        G4double GetHeight() {return fh;}
        void SetHeight(G4double h) {fh=h;}
        G4double GetDist() {return dist;}
        void SetDist(G4double h) {dist=h;}
        G4double GetZ() {return fz;}
        void SetZ(G4double h) {fz=h;}
        pet_DetectorConstruction();
        virtual ~pet_DetectorConstruction();
        virtual G4VPhysicalVolume* Construct();

        G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
        pet_DetectorMessenger* fMessenger;
    protected:
        G4LogicalVolume*  fScoringVolume;
        G4LogicalVolume*  fEdA;
        G4LogicalVolume*  fEdB;
        G4double fh,fz,dist;
};
#endif
