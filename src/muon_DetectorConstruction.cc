
#include "muon_DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

muon_DetectorConstruction::muon_DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

muon_DetectorConstruction::~muon_DetectorConstruction()
{ }

G4VPhysicalVolume* muon_DetectorConstruction::Construct()
{
    //Materials
    G4double a, z, density;
    G4String name, symbol;
    G4int ncomponents, natoms;
    a = 12.011*g/mole;
    G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
    a = 1.0079*g/mole;
    G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1., a);

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  // Plastic scintillator BC-408 (vinyltoluene based)
    density = 1.032*g/cm3;
    G4Material* BC408 = new G4Material(name="BC-408", density, ncomponents = 2);
    BC408->AddElement(elC, natoms = 1000);
    BC408->AddElement(elH, natoms = 1103);
    G4bool checkOverlaps = true;

    //Geometry
    G4double worldXY = 500*cm, worldZ = 500*cm;
    G4double detx = 40*cm, dety = 10*cm, detz = 10*cm;

    G4ThreeVector posL = G4ThreeVector(-1.*detx, 0, 0);
    G4ThreeVector posR = G4ThreeVector(1.*detx, 0, 0);

    //World
    G4Box* worldShape = new G4Box("World", worldXY, worldXY, worldZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(worldShape, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0, false, 0, checkOverlaps);

    //Detector
    G4Box* detectorShape = new G4Box("Detector", detx, dety, dety);
    G4LogicalVolume* logicDetector = new G4LogicalVolume(detectorShape, BC408, "DetectorL");
    G4PVPlacement *physDetectorL =  new G4PVPlacement(0, posL, logicDetector, "DetectorL", logicWorld, false, 0, checkOverlaps);
    G4PVPlacement *physDetectorR =  new G4PVPlacement(0, posR, logicDetector, "DetectorR", logicWorld, false, 0, checkOverlaps);

    fScoringVolume = logicDetector;
    return physWorld;
}
