#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1); //jumlah sumber tembakan particle
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	//generate ukuran maks untuk random
	G4double size = 5;
	//random seed - random seed karena gk tau cara buat seed minus
	G4double rand1 = G4UniformRand();
	G4double rand2 = G4UniformRand();
	//seed untuk pilihan partikel
	G4int val = 2;
	G4int rand3 = val*G4UniformRand();
	G4cout <<rand3<<std::endl;
	G4double x0 = size*(G4UniformRand()-rand1);
	G4double y0 = size*(G4UniformRand()-rand2);
	G4cout << "posisi x,y partikel" <<std::endl;
	G4cout << x0 <<","<< y0 <<std::endl;
	
	//G4ThreeVector pos(x0*m,y0*m,-5*m); //posisi awal partikel
	G4ThreeVector pos(0*m,0*m,-5*m);
	//sumbu z dibuat statik sebagai penanda area tembak
	G4ThreeVector mom(0,0,100); //momentum partikel
	
	fParticleGun->SetParticlePosition(pos); //posisi awal partikel
	fParticleGun->SetParticleMomentumDirection(mom); //arah momentum 
	fParticleGun->SetParticleMomentum(100*GeV); //besar momentum
	if(rand3 == 0)
	{
		fParticleGun->SetParticleDefinition(G4MuonPlus::Definition()); //partikel yang dipakai
	};
	if(rand3 == 1)
	{
		fParticleGun->SetParticleDefinition(G4MuonMinus::Definition()); //partikel yang dipakai
	};
	

	
	fParticleGun->GeneratePrimaryVertex(anEvent);
}
