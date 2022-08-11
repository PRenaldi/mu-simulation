#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	G4Material *lime = nist->FindOrBuildMaterial("G4_CALCIUM_CARBONATE");
	
	G4Trd *box = new G4Trd("PIRAMIDA",0.5*m,4*m,0.5*m,4*m,4*m);
	
	G4LogicalVolume *logicbox = new G4LogicalVolume(box,lime,"logicbox");
	
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR"); //buat lingkungan udaranya
	
	G4Box *solidWorld = new G4Box("solidWorld",5*m,5*m,5*m);//definisikan bentuk dan ukuran lingkungan (10^3 Meter^3)
	
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");//material pembentuknya digabung dengan volume
	
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true); //penempatan dunia di geant4
	
	G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
	rotationMatrix->rotateX(270.*deg);
	
	G4VPhysicalVolume *physbox = new G4PVPlacement (rotationMatrix,G4ThreeVector(0,0,0), logicbox, "physBOX", logicWorld, false, 0, true);
	
	// buat detektor
	G4Box *solidDetektor = new G4Box("solidDetektor",0.5*m,0.5*m,0.05*m); //def bentuk dan volume detektor

	G4Material *deteMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

	logicDetekttor = new G4LogicalVolume(solidDetektor,deteMat,"logicDetektor");

	for(G4int i = 0;i<50;i++)
	{
		for (G4int j=0;j<50;j++)
		{
			G4VPhysicalVolume *physDetektor = new G4PVPlacement(0,G4ThreeVector(-5*m+(i+0.5)*m/5,-5*m+(j+0.5)*m/5,4.95*m),logicDetekttor,"physDetektor",logicWorld,false,j+i*50,true);

		}
	}
	
	return physWorld;
}
