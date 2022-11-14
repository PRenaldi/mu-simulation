#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *lime = nist->FindOrBuildMaterial("G4_CALCIUM_CARBONATE");
	//G4Trd *box = new G4Trd("PIRAMIDA",0.5*m,4*m,0.5*m,4*m,4*m);
	//G4Orb *orb = new G4Orb("solidOrb",0.25*m);
	//G4RotationMatrix identity;
	//rotationMatrix->rotateX(270.*deg);
	//G4VSolid *subs = new G4SubtractionSolid("box-orb",box,orb,&identity,G4ThreeVector(0,0,0));
	//G4LogicalVolume *logicbox = new G4LogicalVolume(subs,lime,"logicbox");

	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR"); //buat lingkungan udaranya
	G4Box *solidWorld = new G4Box("solidWorld",5*m,5*m,5*m);//definisikan bentuk dan ukuran lingkungan (10^3 Meter^3)
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");//material pembentuknya digabung dengan volume
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true); //penempatan dunia di geant4


	//G4VPhysicalVolume *physbox = new G4PVPlacement(0,G4ThreeVector(0,0,0),logicbox,"hole pyramid",logicWorld,false,0,true);

	//G4VSolid *subs = new G4SubtractionSolid("box-orb",box,orb,rotationMatrix,G4ThreeVector(0,0,0));

	//G4VPhysicalVolume *physbox = new G4PVPlacement (0,G4ThreeVector(0,0,0), subs, "physBOX", logicWorld, false, 0, true);

    G4VSolid* MenOrb2 =    new G4Sphere("MenOrb2", 0.*m,1*m, 0.*deg, 360.*deg, 0.*deg, 360.*deg);
    G4VSolid *box = new G4Trd("PIRAMIDA",0.3*m,4*m,0.3*m,4*m,4*m);
    G4RotationMatrix identity;
	G4ThreeVector positionMenOrb2(0,0,0);
	//G4VSolid* unipyr = new G4UnionSolid("unipyr",box,MenOrb2,&identity, positionMenOrb2);
	G4VSolid* Meniscus = new G4SubtractionSolid("Meniscus", box, MenOrb2,&identity, positionMenOrb2);

	G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
	rotationMatrix->rotateX(270.*deg);
                        
	G4LogicalVolume* logicball =
	new G4LogicalVolume(MenOrb2,
						worldMat,
						"chamber");

	new G4PVPlacement(rotationMatrix,
						G4ThreeVector(0,0,0),
						logicball,
						"realball",
						logicWorld,
						false,
						0,
						true);

    G4LogicalVolume* logicEnv2 =                         
    new G4LogicalVolume(Meniscus,            //its solid   //solidEvn2
                        lime,             //its material
                        "Meniscus2");         //its name

                    
 	new G4PVPlacement(rotationMatrix,                       //no rotation
                    G4ThreeVector(0,0,0),         //at (0,0,2.15) 2.15= 0.15*m+2*m
                    logicEnv2,                //its logical volume
                    "Meniscus",              //its name                      //Envelope2
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    true);          //overlaps checking
	



	// buat detektor
	G4Box *solidDetektor = new G4Box("solidDetektor",0.75*m,0.75*m,0.25*m); //def bentuk dan volume detektor
	G4Material *deteMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	logicDetekttor = new G4LogicalVolume(solidDetektor,deteMat,"logicDetektor");
	for(G4int i = 0;i<20;i++)
	{
		for (G4int j=0;j<20	;j++)
		{
			G4VPhysicalVolume *physDetektor = new G4PVPlacement(0,G4ThreeVector(-5*m+(i+0.5)*m/2,-5*m+(j+0.5)*m/2,4.75*m),logicDetekttor,"physDetektor",logicWorld,false,j+i*20,true);

		}
	}
	
	return physWorld;
}
