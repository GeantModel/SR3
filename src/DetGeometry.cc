//Вариант 2
//Реализовать составную геометрию представленную на рисунке

#include <G4Tubs.hh>
#include <G4Orb.hh>
#include <G4Color.hh>
#include "DetGeometry.hh"
#include "G4VisAttributes.hh"

DetGeometry::DetGeometry() {
    world_sizeXYZ   = 50 * m;
    nist            = G4NistManager::Instance();
    world_mat       = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld      = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld      = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld       = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);
    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){
    G4Material * material       = nist->FindOrBuildMaterial("G4_Fe");
    G4Isotope *Na23 = new G4Isotope("Na23", 11, 23, 22.9898*g/mole);
    G4Isotope *I53 = new G4Isotope("I53", 53, 127, 126.9045*g/mole);
    G4Isotope *Tl81 = new G4Isotope("Tl81", 81, 204, 204.385*g/mole);

    G4Element *Na = new G4Element("Natrii","Na", 1);
    Na->AddIsotope(Na23, 1);
    G4Element *I = new G4Element("Iod","I", 1);
    I->AddIsotope(I53, 1);
    G4Element *Tl = new G4Element("Tallii","Tl", 1);
    Tl->AddIsotope(Tl81, 1);

    G4Material *NaITl = new G4Material("NaITl", 3.67*g/cm3, 3, kStateSolid, 293*kelvin, 1.5e7*pascal);
    NaITl->AddElement(Na, 59*perCent);
    NaITl->AddElement(I, 40*perCent);
    NaITl->AddElement(Tl, 1*perCent);

    G4Material *nistNaI = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4Material *nistTl = nist->FindOrBuildMaterial("G4_Tl");
    G4Material *nistNaITl = new G4Material("nistNaITl", 3.67*g/cm3, 2, kStateSolid, 293*kelvin, 1.5e7*pascal);
    nistNaITl->AddMaterial(nistNaI, 99*perCent);
    nistNaITl->AddMaterial(nistTl, 1*perCent);

    G4Element *nistFe = nist->FindOrBuildElement("Fe");
    G4Element *nistSi = nist->FindOrBuildElement("Si");
    G4Element *nistMn = nist->FindOrBuildElement("Mn");
    G4Element *nistTi = nist->FindOrBuildElement("Ti");
    G4Element *nistAl = nist->FindOrBuildElement("Al");
    G4Element *nistCu = nist->FindOrBuildElement("Cu");
    G4Element *nistBe = nist->FindOrBuildElement("Be");
    G4Element *nistMg = nist->FindOrBuildElement("Mg");
    G4Element *nistZn = nist->FindOrBuildElement("Zn");
    G4Material *nistAMG6 = new G4Material("nistAMG6", 3.67*g/cm3, 9, kStateSolid, 293*kelvin, 1.5e7*pascal);
    nistAMG6->AddElement(nistFe, 0.1*perCent);
    nistAMG6->AddElement(nistSi, 0.1*perCent);
    nistAMG6->AddElement(nistMn, 0.2*perCent);
    nistAMG6->AddElement(nistTi, 0.1*perCent);
    nistAMG6->AddElement(nistAl, 93.7*perCent);
    nistAMG6->AddElement(nistCu, 0.1*perCent);
    nistAMG6->AddElement(nistBe, 0.1*perCent);
    nistAMG6->AddElement(nistMg, 5.3*perCent);
    nistAMG6->AddElement(nistZn, 0.2*perCent);

    G4Box* box= new G4Box("box", 0.1*world_sizeXYZ , 0.1*world_sizeXYZ, 0.1*world_sizeXYZ);
    G4Orb* orb = new G4Orb("orb", 0.1*world_sizeXYZ);
    G4Tubs* tubs = new G4Tubs("tubs", 0, 0.1*world_sizeXYZ, 0.2*world_sizeXYZ, 0, 360*deg);

    G4LogicalVolume *box_log = new G4LogicalVolume(box, nistAMG6, "logic_world");
    box_log->SetVisAttributes(G4Colour::Yellow());
    G4LogicalVolume *orb_log = new G4LogicalVolume(orb, nistNaITl, "logic_world");
    orb_log->SetVisAttributes(G4Colour::Green());
    G4LogicalVolume *tubs_log = new G4LogicalVolume(tubs, NaITl, "logic_world");
    tubs_log->SetVisAttributes(G4Colour::Red());

    new G4PVPlacement(0, G4ThreeVector(0.1*world_sizeXYZ,0.1*world_sizeXYZ,0.1*world_sizeXYZ), box_log, "material_orb1", logicWorld, false, 0);
    new G4PVPlacement(0, G4ThreeVector(0.4*world_sizeXYZ,0.4*world_sizeXYZ,0.4*world_sizeXYZ), orb_log, "material_orb2", logicWorld, false, 0);
    new G4PVPlacement(0, G4ThreeVector(0.6*world_sizeXYZ,0.6*world_sizeXYZ,0.6*world_sizeXYZ), tubs_log, "material_orb3", logicWorld, false, 0);

    std::ofstream fout("/home/student/CLionProjects/M_FW_1/result.txt");
    //fout<<NaITl<<'\n';
   // fout<<nistNaITl<<'\n';
   // fout<<nistAMG6<<'\n'<<'\n'<<'\n'<<'\n'<<'\n';

    fout<<"Box mass = "<<box_log->GetMass()/g<<" surface = "<<box->GetSurfaceArea()<<box_log->GetMaterial()<<'\n';
    fout<<"Orb mass = "<<orb_log->GetMass()/g<<" surface = "<<orb->GetSurfaceArea()<<orb_log->GetMaterial()<<'\n';
    fout<<"Tubs mass ="<<tubs_log->GetMass()/g<<" surface = "<<tubs->GetSurfaceArea()<<tubs_log->GetMaterial()<<'\n';
    return physWorld;
}

