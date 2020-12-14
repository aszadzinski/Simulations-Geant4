#ifndef pet_PrimaryGeneratorAction_h
#define pet_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4Event.hh"
class G4ParticleGun;
class G4Event;
class G4Box;

class pet_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    void SetHeight(G4double h) {fh = h;}
    G4double GetHeight() const {return fh;}
    pet_PrimaryGeneratorAction();
    virtual ~pet_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun1() const { return fParticleGun1; };
    const G4ParticleGun* GetParticleGun2() const { return fParticleGun2; };
  private:
    G4double sX, sY, sZ, gTh, gPhi;
    G4double gX, gY, gZ, R,sTh,sPhi;
    G4double Energy,E0;
    G4ParticleGun*  fParticleGun1;
    G4ParticleGun* fParticleGun2; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
    G4double fh;
    G4double R2 = 640000000.;
    G4double d = 600.;
    G4GenericMessenger* fMessenger;
    G4double eliminate();
    G4double petDist(G4double);
};
#endif
