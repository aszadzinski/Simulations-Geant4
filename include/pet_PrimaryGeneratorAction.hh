#ifndef pet_PrimaryGeneratorAction_h
#define pet_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "pet_DetectorConstruction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4Event.hh"
class G4ParticleGun;
class G4Event;
class G4Box;

class G4GenericMessenger;
class pet_DetectorConstruction;
class pet_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    void SetHeight(G4double h) {fh = h;}
    void SetZ(G4double z) {zz = z;}

    inline static G4double GetHeight(G4double num=99)  {
      static double temp;
      if (num!=99) temp = num;
      return temp;
    }
    inline static G4double GetDist(G4double num=99)  {
      static double temp;
      if (num!=99) temp = num;
      return temp;
    }
    inline static G4double GetZ(G4double num=99)  {
      static double temp;
      if (num!=99) temp = num;
      return temp;
    }
    pet_PrimaryGeneratorAction(pet_DetectorConstruction*);
    virtual ~pet_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun1() const { return fParticleGun1; };
  private:
    pet_DetectorConstruction* myDetector;
    void DefineCommands();
    G4double sX, sY, sZ, gTh, gPhi;
    G4double gX, gY, gZ, R,sTh,sPhi;
    G4double Energy,E0;
    G4ParticleGun*  fParticleGun1;
// pointer a to G4 gun class
    G4Box* fEnvelopeBox;
    G4double fh,zz,dist,ffh,zzz,zz0;
    G4double R2 = 640000000.;
    G4double d = 600.;
    G4GenericMessenger* fMessenger;
    G4double eliminate();
    G4double petDist(G4double);
};
#endif
