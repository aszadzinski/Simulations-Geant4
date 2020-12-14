
#include "pet_DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "cmath"

pet_DetectorConstruction::pet_DetectorConstruction()
: G4VUserDetectorConstruction(),
  fEdA(0), fEdB(0)
{ }

pet_DetectorConstruction::~pet_DetectorConstruction()
{ }

G4VPhysicalVolume* pet_DetectorConstruction::Construct()
{  G4NistManager* man = G4NistManager::Instance();
    //Materials
    //G4double a, z, density;
    G4double da, daz, dadensity;
    G4double db, dbz, dbdensity;
    G4String name, symbol;
    G4int ncomponents, natoms;
    da = 12.011*g/mole;
      G4bool isotopes = false;
    G4Element*  O = man->FindOrBuildElement("O" , isotopes);
G4Element* Si = man->FindOrBuildElement("Si", isotopes);
G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);
G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
LSO->AddElement(Lu, 2);
LSO->AddElement(Si, 1);
LSO->AddElement(O , 5);


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
    //Geometry
    G4double worldXY = 500*cm, worldZ = 500*cm;
    G4double detAz = 50.8*mm, detAr = 50.8*mm;
    G4double detBz = 50.8*mm, detBr = 50.8*mm;
    G4double sourcez = 4*mm, sourcer = 20*mm;
    G4double distAB = 14*cm;


    G4ThreeVector posA = G4ThreeVector(0, 0, -0.5*detAz-distAB);
    G4ThreeVector posB = G4ThreeVector(0, 0, 0.5*detBz+distAB);

    G4RotationMatrix* rotS = new G4RotationMatrix;
    rotS->rotateY(M_PI/2*rad);
    G4ThreeVector posS = G4ThreeVector(0, 0, 0);

    //World
    G4Box* worldShape = new G4Box("World", worldXY, worldXY, worldZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(worldShape, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0, false, 0, checkOverlaps);

    //Source
    G4double tubePhi = 2.*M_PI;
    G4Tubs* detectorShapeSource = new G4Tubs("Source", 0, sourcer/2, sourcez/2, 0., tubePhi);
    G4LogicalVolume* logicSource = new G4LogicalVolume(detectorShapeSource, BC408, "Source");
    G4PVPlacement *physSource =  new G4PVPlacement(rotS, posS, logicSource, "Source", logicWorld, false, 0, checkOverlaps);

    //Detector
    G4Tubs* detectorShapeA = new G4Tubs("DetectorA", 0, detAr/2, detAz/2, 0., tubePhi);
    G4LogicalVolume* logicDetectorA = new G4LogicalVolume(detectorShapeA, cryst_mat, "ADetector");
    G4PVPlacement *physDetectorA =  new G4PVPlacement(0, posA, logicDetectorA, "ADetector", logicWorld, false, 0, checkOverlaps);
    fEdA = logicDetectorA;

    G4Tubs* detectorShapeB = new G4Tubs("DetectorA", 0, detBr/2, detBz/2, 0., tubePhi);
    G4LogicalVolume* logicDetectorB = new G4LogicalVolume(detectorShapeB, cryst_mat, "BDetector");
    G4PVPlacement *physDetectorB =  new G4PVPlacement(0, posB, logicDetectorB, "BDetector", logicWorld, false, 0, checkOverlaps);
    fEdB = logicDetectorB;

    return physWorld;
}
