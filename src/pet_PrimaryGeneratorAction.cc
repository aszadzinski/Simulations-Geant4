#include "pet_PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "cmath"
#include "G4GenericMessenger.hh"

pet_PrimaryGeneratorAction::pet_PrimaryGeneratorAction(pet_DetectorConstruction* MyDC)
:myDetector(MyDC)

{
  G4int n_particle = 1;
  E0 = 1*keV;
  fParticleGun1  = new G4ParticleGun(n_particle);
  fh = MyDC->GetHeight();
  zz = MyDC->GetZ();
  dist = MyDC->GetDist();

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e+");
  fParticleGun1->SetParticleDefinition(particle);
  fParticleGun1->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun1->SetParticleEnergy(E0);
}

pet_PrimaryGeneratorAction::~pet_PrimaryGeneratorAction()
{
  delete fParticleGun1;
  delete fMessenger;

}

void pet_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume("DetectorA");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if ( fEnvelopeBox )
  {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }
  else
  {
  }
  R = G4UniformRand()*5*mm;
  sTh = G4UniformRand()*2*M_PI;
  sPhi = G4UniformRand()*M_PI;
  sX = R*sin(sTh)*cos(sPhi);
  sY = R*sin(sTh)*sin(sPhi);
  sZ = R*cos(sTh);

  gTh = G4UniformRand()*2*M_PI;
  gPhi = G4UniformRand()*M_PI;
  gX = R*sin(gTh)*cos(gPhi);
  gY = R*sin(gTh)*sin(gPhi);
  gZ = R*cos(gTh);

  Energy = E0;
  G4cout<<"En k"<<fh<<G4endl;
  GetHeight(fh);
  GetZ(zz);
  GetDist(dist);

  fParticleGun1->SetParticlePosition(G4ThreeVector(gX,gY+fh,gZ+zz));
  fParticleGun1->SetParticleMomentumDirection(G4ThreeVector(-sX,-sY,-sZ));
  fParticleGun1->SetParticleEnergy(Energy);
  fParticleGun1->GeneratePrimaryVertex(anEvent);

}
