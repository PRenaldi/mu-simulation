#include <iostream>


#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"


//PR buat area detektornya
//install root setelah detektor selesai dibuat (done)

// before run, jalankan command 
//". software/geant4/geant4-v11.0.2-install/share/Geant4-11.0.2/geant4make/geant4make.sh"

//masuk dir sim/build
//run make
//run ./TOMOGRAFI


int main(int argc, char** argv)
{
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	//menampilkan Graphical Simulation
	
	UImanager-> ApplyCommand("/vis/open OGL");
	//UImanager-> ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
	
	
	// menampilan world yang sudah dibuat
	
	UImanager->ApplyCommand("/vis/drawVolume");
	
	// menampilkan partikel di GUI
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate"); //akumulasi event
	//UImanager->ApplyCommand("vis/geometry/set/visibility logicWorld 0 false");
	//UImanager->ApplyCommand("/vis/geometry/set/colour Meniscus2 0 0 0 1 .25");
	//UImanager->ApplyCommand("/vis/geometry/set/colour chamber 0 0.5 1 0.5 .25");

	
	ui->SessionStart();
	
	return 0;
}
