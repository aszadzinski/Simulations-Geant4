
#include "muon_DetectorConstruction.hh"

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

    //Optical Properties
    BC408->AddProperty("SCINTILLATIONCOMPONENT1", l_Energy, l_Intensity);
    BC408->AddProperty("RINDEX", 1.58);

    G4bool checkOverlaps = true;

    // Plastic scintillator BC-418
    G4Material* BC418 = new G4Material(name="BC-418", density, ncomponents = 2);
    BC418->AddElement(elC, natoms = 1000);
    BC418->AddElement(elH, natoms = 1100);

    //Geometry
    G4double worldXY = 500*cm, worldZ = 500*cm;
    G4double detx = 40*cm, dety = 10*cm, detz = 10*cm;

    G4double detTx = 0*cm;
    G4double detBx= 0*cm;
    G4double gap= 9.2*cm;	

    G4double smallDetR= 1.9*cm, smallDetDz= 1.29*cm;

    G4ThreeVector posL = G4ThreeVector(-1.*detx, 0, 0);
    G4ThreeVector posR = G4ThreeVector(1.*detx, 0, 0);

    G4ThreeVector posT = G4ThreeVector(detTx, 0, detz+smallDetDz);
    G4ThreeVector posB = G4ThreeVector(detBx, 0, -(detz+gap+smallDetDz) );

    //World
    G4Box* worldShape = new G4Box("World", worldXY, worldXY, worldZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(worldShape, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0, false, 0, checkOverlaps);

    //Detector
    G4Box* detectorShape = new G4Box("Detector", detx, dety, dety);
    G4Tubs* smallDetectorShape = new G4Tubs("SmallDetector", 0, smallDetR, smallDetDz, 0, 2*M_PI);
  
    G4LogicalVolume* logicDetector = new G4LogicalVolume(detectorShape, BC408, "LDetector");
    G4PVPlacement *physDetectorL =  new G4PVPlacement(0, posL, logicDetector, "LDetector", logicWorld, false, 0, checkOverlaps);
    G4PVPlacement *physDetectorR =  new G4PVPlacement(0, posR, logicDetector, "RDetector", logicWorld, false, 0, checkOverlaps);

    //Small Detectors
    G4LogicalVolume* logicSmallDetector = new G4LogicalVolume(smallDetectorShape, BC418,"SmallDetector");
    G4PVPlacement *physDetectorT = new G4PVPlacement(0, posT, logicSmallDetector, "TDetector", logicWorld, false, 0, checkOverlaps);
    G4PVPlacement *physDetectorB = new G4PVPlacement(0, posB, logicSmallDetector, "BDetector", logicWorld, false, 0, checkOverlaps);


    fScoringVolume = logicDetector;
    return physWorld;
}
