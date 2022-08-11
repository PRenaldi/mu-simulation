#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4MuonMinus.hh" 
#include "G4MuonPlus.hh" 
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4ParticleTable.hh" 
class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public :
	MyPrimaryGenerator();
	~MyPrimaryGenerator();
	
	virtual void GeneratePrimaries(G4Event*);
private:
	//generate particle gun
	G4ParticleGun *fParticleGun; //pembuatan definsi partikel gun
	
};

#endif
