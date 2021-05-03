
#include "muography_DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "muography_DetectorMessenger.hh"
#include "G4Orb.hh"
#include "G4Box.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "cmath"

muography_DetectorConstruction::muography_DetectorConstruction()
: G4VUserDetectorConstruction(),
  fEdA(0), fEdB(0), fEdR(0), fEdTC(0), fEdT(0)
{ fMessenger = new muography_DetectorMessenger(this);}

muography_DetectorConstruction::~muography_DetectorConstruction()
{
delete fMessenger;}

G4VPhysicalVolume* muography_DetectorConstruction::Construct()
{  G4NistManager* man = G4NistManager::Instance();

    //Materials
    G4double da, daz, dadensity;
    G4double db, dbz, dbdensity;
    G4String name, symbol;
    G4int ncomponents, natoms;
    da = 12.011*g/mole;

    G4Element* elC = new G4Element(name="Carbon", symbol="C", daz=6., da);
    da = 1.0079*g/mole;
    G4Element* elH = new G4Element(name="Hydrogen", symbol="H", daz=1.,da);

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    // Plastic scintillator BC-408 (vinyltoluene based)
    dadensity = 1.032*g/cm3;
    G4Material* BC408 = new G4Material(name="BC-408", dadensity, ncomponents = 2);
    BC408->AddElement(elC, natoms = 1000);
    BC408->AddElement(elH, natoms = 1103);
    G4bool checkOverlaps = true;
    G4Material* cryst_mat   = nist->FindOrBuildMaterial("Lu2SiO5");

    G4double zAu, aAu, densityAu;
    densityAu = 19.3*g/cm3;
    aAu = 197*g/mole;
    G4Material* Au = new G4Material(name="Au", zAu=79, aAu, densityAu); 

    G4double zC, zO, zMg, zCa, zFe, zAuu;
    G4double aC, aO, aMg, aCa, aFe, aAuu;
    G4Element* C = new G4Element("C",          "C",  zC=6.,  aC= 12.01   *g/mole);
    G4Element* O = new G4Element("Oxygen",     "O",  zO=8.,  aO= 15.9994 *g/mole);
    G4Element* Mg = new G4Element("Magnesium", "Mg", zMg=12., aMg= 24.3050 *g/mole);
    G4Element* Ca = new G4Element("Calcium",   "Ca", zCa=20., aCa= 40.0784*g/mole);
    G4Element* Fe = new G4Element("Ferrum",   "Fe", zFe=26., aFe= 55.845*g/mole);
    G4Element* Auu = new G4Element("Calcium",   "Au", zAuu=79., aAuu= 196.966*g/mole);

    G4double densityTrain;
    G4Material* GoldTrain = new G4Material("GoldTrain",densityTrain=13.3*g/cm3,2);
    GoldTrain->AddElement(Fe,  50.*perCent);
    GoldTrain->AddElement(Auu, 50*perCent);

    G4double densityRock;
    G4Material* StdRock = new G4Material("StdRock",densityRock=1.65*g/cm3,4);
    StdRock->AddElement(O,  52.*perCent);
    StdRock->AddElement(Ca, 2.*perCent);
    StdRock->AddElement(C,  39.*perCent);
    StdRock->AddElement(Mg,  9.*perCent);

    //Geometry
    G4double worldXY = 3100*m, worldZ = 3100*m;

    G4ThreeVector posDA = G4ThreeVector(-fDetX-fRockX/2, 0, 0);
    G4ThreeVector posDB = G4ThreeVector(fDetX+fRockX/2, 0, 0);
    G4ThreeVector posTC = G4ThreeVector(fTrainX, fTrainY, fTrainZ);

    //G4RotationMatrix* rotS = new G4RotationMatrix;
    //rotS->rotateY(M_PI/2*rad);

    //World
    G4Box* worldShape = new G4Box("World", worldXY, worldXY, worldZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(worldShape, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0, false, 0, checkOverlaps);


    //Rock
    G4Box* rockShape = new G4Box("Rock", fRockX/2, fRockYZ/2, fRockYZ/2);
    G4LogicalVolume* logicRock = new G4LogicalVolume(rockShape, StdRock, "Rock");
    G4VPhysicalVolume* physRock = new G4PVPlacement(0, G4ThreeVector(), logicRock,  "Rock", logicWorld, false, 0, checkOverlaps);
    fEdR = logicRock;

    //Train chamber
    G4double tubePhi = 2.*M_PI;
    G4Orb* tchamberShape = new G4Orb("TChamber",fTChamberR);
    G4LogicalVolume* logicTChamber = new G4LogicalVolume(tchamberShape, air, "TChamber");
    G4PVPlacement* physTChamber =  new G4PVPlacement(0, posTC, logicTChamber, "TChamber", logicRock, false, 0, checkOverlaps);
    fEdTC = logicTChamber;

    //Train
    G4Orb* trainShape = new G4Orb("Train",fTrainR);
    G4LogicalVolume* logicTrain = new G4LogicalVolume(trainShape, Au, "Train");
    G4PVPlacement* physTrain =  new G4PVPlacement(0, posTC, logicTrain, "Train", logicRock, false, 0, checkOverlaps);
    fEdT = logicTrain;

    //Detectors
    G4Box* detectorShapeA = new G4Box("DetectorA", fDetX/2, fDetYZ/2, fDetYZ/2);
    G4LogicalVolume* logicDetectorA = new G4LogicalVolume(detectorShapeA, BC408, "ADetector");
    G4PVPlacement *physDetectorA =  new G4PVPlacement(0, posDA, logicDetectorA, "ADetector", logicWorld, false, 0, checkOverlaps);
    fEdA = logicDetectorA;

    G4Box* detectorShapeB = new G4Box("DetectorA", fDetX/2, fDetYZ/2, fDetYZ/2);
    G4LogicalVolume* logicDetectorB = new G4LogicalVolume(detectorShapeB, BC408, "BDetector");
    G4PVPlacement *physDetectorB =  new G4PVPlacement(0, posDB, logicDetectorB, "BDetector", logicWorld, false, 0, checkOverlaps);
    fEdB = logicDetectorB;

    return physWorld;
}
