#ifndef muon_PrimaryGeneratorAction_h
#define muon_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class muon_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    muon_PrimaryGeneratorAction();
    virtual ~muon_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4double sX, sY, sZ, gTh, gPhi;
    G4double gX, gY, gZ, R;
    G4double Energy;
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
};
#endif
