#include "muon_PrimaryGeneratorAction.hh"

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

muon_PrimaryGeneratorAction::muon_PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0),
fEnvelopeBox(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(1.*GeV);
}

muon_PrimaryGeneratorAction::~muon_PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void muon_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume("DetectorL");
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

  // from spherical coord. Generate point on the sphere [th[0,90], phi[0,360]]
  R = 80*cm;
  gTh = G4UniformRand()*M_PI/2;
  gPhi = G4UniformRand()*2*M_PI;
  sX = R*sin(gTh)*cos(gPhi);
  sY = R*sin(gTh)*sin(gPhi);
  sZ = R*cos(gTh);
  // solve z=sqrt(r^2-x^2-y^2), eq of surface z-z0 = df(x0,y0)/dx*(x-x0) + df(x0,y0)/dy*(y-y0)
  //partial derivative
  gX = G4UniformRand()*2*R-R;
  gY = G4UniformRand()*2*20*cm-20*cm;
  gZ = sZ + sX*(gX-sX)/sZ + sY*(gY-sY)/sZ;

  Energy = cos(gTh)*G4RandGauss::shoot(1000,400)*MeV;
  G4double size = 0.8;
  G4double x0 = size * 20*cm * (G4UniformRand()-0.5);
  G4double y0 = size * 20*cm * (G4UniformRand()-0.5);
  G4double z0 = -0.5 * 40*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(sX+gX,sY+gY,sZ));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-sX,-sY,-sZ));
  fParticleGun->SetParticleEnergy(Energy);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
