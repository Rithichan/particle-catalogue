// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// The main function of the Particle Catalogue
// This code is a catalogue for all particles in the Standard Model
// It shows information about each particle and their four momentum
// This catalogue allows for some decays and can be initiated via the user interface
// This catalogue allows for searching of particles via type or particle name
// It also shows total number of particles, total four momentum, total number of quarks etc.
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<memory>
#include"particle.h"
#include"fourmomentum.h"
#include"lepton.h"
#include"quark.h"
#include"boson.h"
#include"decay.h"
#include"container.h"

// Template function to print particles in any container
template<typename T>
void print_container(const T& items) 
{
  for(const auto& item : items) 
  {
    item->print_data();
  }
}

int main()
{
  //Interface in main
  //user is free to change parameters
  //All keys are written as the name of the particle
  //Many functions use the key to get a specific particle
  //Example of a key: "Up", "WPlusBoson", "Higgs" ... etc

  //initialse catalouge with all particles and antiparticles
  Container particle_container;
  //Quarks
  particle_container.add("Up",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Up),0,0,0,false,ColourCharge::Red,QuarkType::Up));
  particle_container.add("Down",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Down),0,0,0,false,ColourCharge::Blue,QuarkType::Down));
  particle_container.add("Charm",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Charm),0,0,0,false,ColourCharge::Green,QuarkType::Charm));
  particle_container.add("Strange",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Strange),0,0,0,false,ColourCharge::Red,QuarkType::Strange));
  particle_container.add("Top",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Top),0,0,0,false,ColourCharge::Blue,QuarkType::Top));
  particle_container.add("Bottom",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Bottom),0,0,0,false,ColourCharge::Green,QuarkType::Bottom));
  //AntiQuarks
  particle_container.add("AntiUp",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Up),0,0,0,true,ColourCharge::Red,QuarkType::Up));
  particle_container.add("AntiDown",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Down),0,0,0,true,ColourCharge::Blue,QuarkType::Down));
  particle_container.add("AntiCharm",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Charm),0,0,0,true,ColourCharge::Green,QuarkType::Charm));
  particle_container.add("AntiStrange",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Strange),0,0,0,true,ColourCharge::Red,QuarkType::Strange));
  particle_container.add("AntiTop",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Top),0,0,0,true,ColourCharge::Blue,QuarkType::Top));
  particle_container.add("AntiBottom",std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Bottom),0,0,0,true,ColourCharge::Green,QuarkType::Bottom));
  //Leptons
  particle_container.add("Electron",std::make_shared<Electron>(0.511,0,0,0,false));
  particle_container.add("Muon",std::make_shared<Muon>(105.7,0,0,0,false,false));
  particle_container.add("Tau",std::make_shared<Tau>(2000,1685.25102,0,0,false,1));
  particle_container.add("ElectronNeutrino",std::make_shared<Neutrino>(1,1,0,0,true,false,Neutrino::Flavour::Electron));
  particle_container.add("MuonNeutrino",std::make_shared<Neutrino>(Neutrino::mass_for_flavour(Neutrino::Flavour::Muon),0,0,0,true,false,Neutrino::Flavour::Muon));
  particle_container.add("TauNeutrino",std::make_shared<Neutrino>(Neutrino::mass_for_flavour(Neutrino::Flavour::Tau),0,0,0,true,false,Neutrino::Flavour::Tau));
  //AntiLeptons
  particle_container.add("AntiElectron",std::make_shared<Electron>(0.511,0,0,0,true));
  particle_container.add("AntiMuon",std::make_shared<Muon>(105.7,0,0,0,true,true));
  particle_container.add("AntiTau",std::make_shared<Tau>(1077,0,0,0,true,1));
  particle_container.add("AntiElectronNeutrino",std::make_shared<Neutrino>(1,1,0,0,true,true,Neutrino::Flavour::Electron));
  particle_container.add("AntiMuonNeutrino",std::make_shared<Neutrino>(Neutrino::mass_for_flavour(Neutrino::Flavour::Muon),0,0,0,true,true,Neutrino::Flavour::Muon));
  particle_container.add("AntiTauNeutrino",std::make_shared<Neutrino>(Neutrino::mass_for_flavour(Neutrino::Flavour::Tau),0,0,0,true,true,Neutrino::Flavour::Tau));
  //Bosons
  particle_container.add("Photon",std::make_shared<Photon>(5,5,0,0));
  particle_container.add("ZBoson",std::make_shared<ZBoson>(91200,0,0,0,0));
  particle_container.add("WPlusBoson",std::make_shared<WBoson>(80400,0,0,0,1,1)); //W+
  particle_container.add("WMinusBoson",std::make_shared<WBoson>(80400,0,0,0,-1,1)); //W-
  particle_container.add("Gluon",std::make_shared<Gluon>(1,1,0,0,false,ColourCharge::Red));
  particle_container.add("AntiGluon",std::make_shared<Gluon>(1,1,0,0,true,ColourCharge::Blue)); //antigluon
  particle_container.add("Higgs",std::make_shared<Higgs>(126000,0,0,0,0));

  // Since I already made an interface, the user can use the console interface as well.
  int input{0};
  std::cout<<"Would you like to use a user interface or see the functions in main?"<<std::endl;
  std::cout<<"Press 1 for functions in main, 2 for interface: ";
  std::cin>>input;
  while(true)
  {
    if(input == 1 or input == 2)
      break;
    std::cout<<"Please enter 1 or 2:";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin>>input;
  }

  if(input == 1)
  {
    //Streamlined function demonstrations
    std::cout<<"--Printing Particle Information--"<<std::endl;
    particle_container.display_all(); //displays all particles
    std::cout<<" "<<std::endl;
    particle_container.display_type("Boson"); //displays a specific type of particle i.e. Bosons
    std::cout<<" "<<std::endl;
    particle_container.display_specific("Tau"); //displays a specific particle i.e. Tau
    std::cout<<" "<<std::endl;

    std::cout<<"--Displaying information about catalogue--"<<std::endl; //Information about the catalogue
    std::cout<<"There are currently "<<particle_container.get_number_of_particles()<<" particles in the catalogue."<<std::endl;
    std::cout<<"Number of Leptons: "<<particle_container.get_number_of_particles_per_type("Lepton")<<std::endl;
    std::cout<<"Number of Bosons: "<<particle_container.get_number_of_particles_per_type("Boson")<<std::endl;
    std::cout<<"Number of Quarks: "<<particle_container.get_number_of_particles_per_type("Quark")<<std::endl;
    std::cout<<"Number of decay products: "<<particle_container.get_number_of_decay_products()<<std::endl;
    auto total_four_momentum = particle_container.sum_of_four_momenta();
    std::cout<<"Sum of four momentum in catalouge: "<<"("<<total_four_momentum[0]<<", "<<total_four_momentum[1];
    std::cout<<", "<<total_four_momentum[2]<<", "<<total_four_momentum[3]<<" )"<<std::endl;
    std::cout<<" "<<std::endl;

    std::cout<<"--Showcasing Default Random Decays--"<<std::endl;
    std::cout<<"Tau Decays into"<<std::endl;
    auto decay_products_tau = particle_container.get("Tau")->decay();
    print_container(decay_products_tau);
    std::cout<<"AntiTau Decays into"<<std::endl;
    auto decay_products_antitau = particle_container.get("AntiTau")->decay();
    print_container(decay_products_antitau);
    std::cout<<"ZBoson Decays into"<<std::endl;
    auto decay_products_z = particle_container.get("ZBoson")->decay();
    print_container(decay_products_z);
    std::cout<<"W+ Boson Decays into"<<std::endl;
    auto decay_products_wp = particle_container.get("WPlusBoson")->decay();
    print_container(decay_products_wp);
    std::cout<<"W- Boson Decays into"<<std::endl;
    auto decay_products_wm = particle_container.get("WMinusBoson")->decay();
    print_container(decay_products_wm);
    std::cout<<"Higgs Decays into"<<std::endl;
    auto decay_products_higgs = particle_container.get("Higgs")->decay();
    print_container(decay_products_higgs);
    std::cout<<" "<<std::endl;

    std::cout<<"--Showcasing Input checking--"<<std::endl;
    //Trying to add an electron with 10MeV energy and 0 momentum
    //will give error, user can try with other energies and momentum
    particle_container.add("InputCheck",std::make_shared<Electron>(10,0,0,0,false));
    std::cout<<" "<<std::endl;

    //Test Custom Decays (Feel free to test different decays)
    //Tests check for charge conservation
    auto custom_decay_tau = particle_container.get("Tau")->decay({"TauNeutrino","Electron","AntiElectronNeutrino"});
    std::cout<<"Custom Tau Decay"<<std::endl;
    print_container(custom_decay_tau);
    auto custom_decay_z = particle_container.get("ZBoson")->decay({"Charm","AntiCharm"});
    std::cout<<"Custom ZBoson Decay"<<std::endl;
    print_container(custom_decay_z);
    auto custom_decay_w = particle_container.get("WPlusBoson")->decay({"Up","AntiDown"});
    std::cout<<"Custom WBoson Decay"<<std::endl;
    print_container(custom_decay_w);
    std::cout<<"Custom Higgs Decay"<<std::endl;
    auto custom_decay_higgs = particle_container.get("Higgs")->decay({"Bottom","AntiBottom"});
    print_container(custom_decay_higgs);
    std::cout<<"Invalid Decay Demonstration"<<std::endl;
    auto invalid_decay = particle_container.get("WMinusBoson")->decay({"Up","Up"});
  }
  else
  {
    //run the terminal interface
    particle_container.user_interface();
  }

  return 0;
}