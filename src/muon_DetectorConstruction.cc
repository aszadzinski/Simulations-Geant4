
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

  G4NistManager* nist = G4NistManager::Instance();

  G4double env_sizeXY = 100*cm, env_sizeZ = 100*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4bool checkOverlaps = true;

  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking


  G4Box* solidEnv =
    new G4Box("Envelope",                    //its name
        env_sizeXY, env_sizeXY, env_sizeZ); //its size

  G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4double a, z, density;
  G4String name, symbol;
  G4int ncomponents, natoms;

  a = 12.011*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
  a = 1.0079*g/mole;
  G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1., a);

// Plastic scintillator BC-408 (vinyltoluene based)
  density = 1.032*g/cm3;
  G4Material* BC408 = new G4Material(name="BC-408", density, ncomponents = 2);
  BC408->AddElement(elC, natoms = 1000);
  BC408->AddElement(elH, natoms = 1103);
  G4double detx = 10*cm, dety=10*cm, detz=40*cm;
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");

  G4ThreeVector pos1 = G4ThreeVector(1.*detz, 0, 0);
  G4ThreeVector pos2 = G4ThreeVector(-1.*detz, 0, 0);

  G4Box* solidShape1 =
    new G4Box("Shape1", detz, detx, dety );     //its size

  G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,         //its solid
                        BC408,          //its material
                        "Shape1");           //its name

  G4LogicalVolume* logicShape2 =
    new G4LogicalVolume(solidShape1,         //its solid
                        BC408,          //its material
                        "Shape3");           //its name


  G4PVPlacement *Phys1 =  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  G4PVPlacement *Phys2 =  new G4PVPlacement(0,
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape3",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  fScoringVolume = logicShape2;

  return physWorld;
}
