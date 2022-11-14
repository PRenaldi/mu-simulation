#include "physics.hh"

MyPhysicsList :: MyPhysicsList()
{
	RegisterPhysics(new G4EmStandardPhysics_option3());
	RegisterPhysics(new G4OpticalPhysics());
	RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
	//RegisterPhysics(new G4MuIonisation());
	//RegisterPhysics(new G4MuBremsstrahlung());
	//RegisterPhysics(new G4MuPairProduction());
	
}

MyPhysicsList::~MyPhysicsList()
{}

//void MyPhysicsList_1:: ConstructionProcess()
//{
	//RegisterProcess(new G4MuIonisation,G4MuonPlus::Definition());
	//RegisterProcess(new G4MuBremsstrahlung,G4MuonPlus::Definition());
	//RegisterProcess(new G4MuPairProduction,G4MuonPlus::Definition());
	//RegisterProcess(new G4MuIonisation,G4MuonMinus::Definition());
	//RegisterProcess(new G4MuBremsstrahlung,G4MuonMinus::Definition());
	//RegisterProcess(new G4MuPairProduction,G4MuonMinus::Definition());
//}
