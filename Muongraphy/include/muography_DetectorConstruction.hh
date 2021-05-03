#ifndef muography_DetectorConstruction_h
#define muography_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class muography_DetectorMessenger;

class muography_DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        G4double GetTChamberR() {return fTChamberR;}
        void SetTChamberR(G4double tmp) {fTChamberR=tmp;}
        G4double GetTrainR() {return fTrainR;}
        void SetTrainR(G4double tmp) {fTrainR=tmp;}

        void SetDetX(G4double tmp) {fDetX=tmp;}
        G4double GetDetYZ() {return fDetYZ;}
        void SetDetYZ(G4double tmp) {fDetYZ=tmp;}
        G4double GetDetX() {return fDetX;}

        G4double GetRockYZ() {return fRockYZ;}
        void SetRockYZ(G4double tmp) {fRockYZ=tmp;}
        G4double GetRockX() {return fRockX;}
        void SetRockX(G4double tmp) {fRockX=tmp;}

        G4double GetTrainX() {return fTrainX;}
        void SetTrainX(G4double tmp) {fTrainX=tmp;}
        G4double GetTrainY() {return fTrainY;}
        void SetTrainY(G4double tmp) {fTrainY=tmp;}
        G4double GetTrainZ() {return fTrainZ;}
        void SetTrainZ(G4double tmp) {fTrainZ=tmp;}

        G4double GetGunChoice() {return fGunChoice;}
        void SetGunChoice(G4double tmp) {fGunChoice=tmp;}
        G4double GetGunPosX() {return fGunPosX;}
        void SetGunPosX(G4double tmp) {fGunPosX=tmp;}
        G4double GetGunPosY() {return fGunPosY;}
        void SetGunPosY(G4double tmp) {fGunPosY=tmp;}
        G4double GetGunPosZ() {return fGunPosZ;}
        void SetGunPosZ(G4double tmp) {fGunPosZ=tmp;}
        G4double GetGunE0() {return fGunE0;}
        void SetGunE0(G4double tmp) {fGunE0=tmp;}

        muography_DetectorConstruction();

        virtual ~muography_DetectorConstruction();
        virtual G4VPhysicalVolume* Construct();

        G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
        muography_DetectorMessenger* fMessenger;

    protected:
        G4LogicalVolume*  fScoringVolume;
        G4LogicalVolume*  fEdA;
        G4LogicalVolume*  fEdB;
        G4LogicalVolume*  fEdR;
        G4LogicalVolume*  fEdTC;
        G4LogicalVolume*  fEdT;

        G4double fTrainX, fTrainY, fTrainZ;
	G4double fRockX, fRockYZ;
	G4double fDetX, fDetYZ;
	G4double fTChamberR, fTrainR;

	G4double fGunPosX, fGunPosY, fGunPosZ, fGunE0;
	G4int fGunChoice;

};
#endif
