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
fParticleGun(0)
{
  G4int n_particle = 1;
  E0 = 300*MeV;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(E0);
}

muon_PrimaryGeneratorAction::~muon_PrimaryGeneratorAction()
{
  delete fParticleGun;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void muon_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  // from spherical coord. Generate point on the sphere [th[0,90], phi[0,360]]
  R = 80*cm;
  gTh = eliminate(); 					// theta angle from real muon distribution (von Neumann method/elimination method)
  gPhi = G4UniformRand()*2*M_PI; 			// random phi ang.

  sX = R*sin(gTh)*cos(gPhi);				// random position on sphere surrounding detector
  sY = R*sin(gTh)*sin(gPhi);
  sZ = R*cos(gTh);

  // solved z=sqrt(r^2-x^2-y^2), eq of surface z-z0 = df(x0,y0)/dx*(x-x0) + df(x0,y0)/dy*(y-y0)  
  // //partial derivative
  gX = G4UniformRand()*2*R-R;				
  gY = G4UniformRand()*2*20*cm-20*cm;
  gZ = sZ + sX*(gX-sX)/sZ + sY*(gY-sY)/sZ;

  //Energy = G4RandGauss::shoot(E0,10); 				// Random energy (from specyfic distribution)
  Energy = E0*muonDist(gTh); 				// Random energy (from specyfic distribution)


  fParticleGun->SetParticlePosition(G4ThreeVector(sX+gX,sY+gY,sZ));		// Setting particlegun position
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-sX,-sY,-sZ));	// Setting direction
  fParticleGun->SetParticleEnergy(Energy);					// Setting Energy
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

G4double muon_PrimaryGeneratorAction::muonDist(G4double theta)
{
  // Angular cosmic ray distribution https://doi.org/10.1142/S0217751X18501750

  G4double D;
  D = (sqrt(R2*R2/(d*d)*cos(theta)*cos(theta)+2*R2/d +1)-R2/d * cos(theta));
  return 1/(D*D);
}

G4double muon_PrimaryGeneratorAction::eliminate()
{
  // von Neumann method. Drawing variable from muonDist()
  G4double random1, random2;
  do
  {
    random1 = G4UniformRand()*M_PI/2;
    random2 = G4UniformRand();
  }while (muonDist(random1)/M_PI *2 <= random2);
  return random1;
}
