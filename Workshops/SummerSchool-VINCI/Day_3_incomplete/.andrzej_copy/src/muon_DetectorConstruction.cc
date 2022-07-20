
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
#include "G4MaterialPropertiesTable.hh"
#include <vector>
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"


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
	//Optical Properties

    std::vector<G4double> l_Energy = {2.3721*eV,2.3836*eV,2.4055*eV,2.4277*eV,2.4503*eV,2.4735*eV,2.497*eV,2.521*eV,2.5447*eV,2.5641*eV,2.5776*eV,2.5979*eV,2.6127*eV,2.6294*eV,2.6424*eV,2.6535*eV,2.6609*eV,2.6708*eV,2.6795*eV,2.6901*eV,2.7024*eV,2.7108*eV,2.7253*eV,2.7351*eV,2.7488*eV,2.7596*eV,2.7705*eV,2.7797*eV,2.7875*eV,2.7949*eV,2.7994*eV,2.8029*eV,2.8083*eV,2.8133*eV,2.8168*eV,2.8211*eV,2.8218*eV,2.8236*eV,2.8287*eV,2.8325*eV,2.8408*eV,2.8495*eV,2.8593*eV,2.8808*eV,2.9035*eV,2.9131*eV,2.9236*eV,2.9326*eV,2.945*eV,2.9511*eV,2.9548*eV,2.9611*eV,2.97*eV,2.9757*eV,2.9797*eV,2.9861*eV,2.9933*eV,2.9976*eV,3.0022*eV,3.0108*eV,3.016*eV,3.0236*eV,3.0279*eV,3.0335*eV,3.0387*eV,3.047*eV,3.0534*eV,3.0616*eV,3.0659*eV,3.0794*eV,3.0908*eV,3.1033*eV,3.1105*eV,3.1296*eV,3.1499*eV,3.1743*eV,3.2113*eV,3.2511*eV,3.2919*eV,3.3337*eV,3.3766*eV,3.4206*eV};

    std::vector<G4double> l_Intensity = {0.022716,0.021981,0.030429,0.04076,0.05256,0.066518,0.083252,0.10139,0.12512,0.14411,0.15978,0.18771,0.21086,0.2373,0.26111,0.28602,0.30866,0.33413,0.35778,0.38281,0.41037,0.43405,0.46146,0.48255,0.50384,0.52919,0.55364,0.57926,0.60264,0.62942,0.65634,0.68397,0.7054,0.73127,0.75869,0.79616,0.82292,0.84278,0.86755,0.89382,0.92338,0.94836,0.97371,0.98912,0.96321,0.93861,0.91493,0.88674,0.8566,0.82742,0.79882,0.78013,0.75399,0.72797,0.7,0.67287,0.64558,0.62092,0.5879,0.55186,0.523,0.49073,0.46339,0.43586,0.40386,0.37712,0.35073,0.3214,0.29288,0.26175,0.23256,0.20328,0.18135,0.15706,0.1325,0.10604,0.088053,0.069016,0.053984,0.041725,0.033276,0.029208};

    G4MaterialPropertiesTable  *BC408_mt = new G4MaterialPropertiesTable();
	
    BC408_mt->AddProperty("SCINTILLATIONCOMPONENT1", l_Energy, l_Intensity);
    BC408_mt->AddConstProperty("RINDEX", 1.58);
    BC408_mt->AddConstProperty("ABSLENGTH", 210*cm); //Light Attenuation Length not Bulk Light Attenuation Length
    BC408_mt->AddConstProperty("SCINTILLATIONYIELD", 11136./MeV);
    BC408_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.1*ns);
    BC408_mt->AddConstProperty("RESOLUTIONSCALE", 1.0);
    BC408_mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

    BC408->SetMaterialPropertiesTable(BC408_mt);


    // Plastic scintillator BC-418
    G4Material* BC418 = new G4Material(name="BC-418", density, ncomponents = 2);
    BC418->AddElement(elC, natoms = 1000);
    BC418->AddElement(elH, natoms = 1100);

    //Geometry
    G4double worldXY = 500*cm, worldZ = 500*cm;
    G4double detx = 43.6*cm, dety = 10*cm, detz = 10*cm;

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
    G4Box* detectorShape = new G4Box("Detector", detx*0.5, dety*0.5, detz*0.5);
    G4Tubs* smallDetectorShape = new G4Tubs("SmallDetector", 0, smallDetR, smallDetDz, 0, 2*M_PI);
  
    G4LogicalVolume* logicDetector = new G4LogicalVolume(detectorShape, BC408, "LDetector");
    G4PVPlacement *physDetectorL =  new G4PVPlacement(0, posL, logicDetector, "LDetector", logicWorld, false, 0, checkOverlaps);
    G4PVPlacement *physDetectorR =  new G4PVPlacement(0, posR, logicDetector, "RDetector", logicWorld, false, 0, checkOverlaps);

    //Small Detectors
    G4LogicalVolume* logicSmallDetector = new G4LogicalVolume(smallDetectorShape, BC418,"SmallDetector");
    G4PVPlacement *physDetectorT = new G4PVPlacement(0, posT, logicSmallDetector, "TDetector", logicWorld, false, 0, checkOverlaps);
    G4PVPlacement *physDetectorB = new G4PVPlacement(0, posB, logicSmallDetector, "BDetector", logicWorld, false, 0, checkOverlaps);

	
    //Optical Surface
    G4OpticalSurface* opDetectorSurface = new G4OpticalSurface("DetectorSurface");
    opDetectorSurface->SetType(dielectric_dielectric);
    opDetectorSurface->SetFinish(polished);
    opDetectorSurface->SetModel(glisur);
    G4LogicalSkinSurface* detectorSurface = new G4LogicalSkinSurface("DetectorSurface", logicDetector, opDetectorSurface);
    //Border between two halfs
    G4LogicalBorderSurface* detectorInterface = new G4LogicalBorderSurface("DetectorInterface", physDetectorL, physDetectorR, opDetectorSurface);
    
    fScoringVolume = logicDetector;
    return physWorld;
}
