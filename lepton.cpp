// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This file includes all implementation of functions for all Lepton class
// Includes function for tau decay, specialised data members for different leptons
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<random>
#include<stdexcept>
#include"particle.h"
#include"lepton.h"
#include"decay.h"
#include"quark.h"

//----------------------------
//Lepton Class implementations
//----------------------------

Lepton::Lepton(double energy_in, double px_in, double py_in, double pz_in, std::string name_in, double rest_mass_in, double charge_in, bool antiparticle_bool)
 : Particle(energy_in,px_in,py_in,pz_in,name_in,rest_mass_in,charge_in,antiparticle_bool)
{
  spin = 0.5;

  if(antiparticle_bool == false)
  {
    lepton_number = 1;
  }
  else
  {
    lepton_number = -1;
  }
}

void Lepton::print_data()
{
  Particle::print_data();
  std::cout<<"Particle is a Lepton with "; //Lepton number specific to each lepton
}

//------------------------------
//Electron Class Implementations
//------------------------------

void Electron::set_energy_deposit(double EM_1, double EM_2, double HAD_1, double HAD_2)
{
  if(EM_1 + EM_2 + HAD_1 + HAD_2 == four_momentum->get_energy())
  {
    energy_deposit[0] = EM_1;
    energy_deposit[1] = EM_2;
    energy_deposit[2] = HAD_1;
    energy_deposit[3] = HAD_2;
  }
  else
  {
    std::cout<<"Error: Energy Deposited not equal to total energy"<<std::endl;
  }
}

Electron::Electron(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_bool)
 : Lepton(energy_in,px_in,py_in,pz_in,"Electron",0.511,-1,antiparticle_bool)
{
  double EM_1 = energy_in/2;
  double EM_2 = energy_in/2;
  double HAD_1{0};
  double HAD_2{0};

  if(EM_1 + EM_2 + HAD_1 + HAD_2 == four_momentum->get_energy())
  {
    set_energy_deposit(EM_1, EM_2, HAD_1, HAD_2);
  }
  else
  {
    std::cout<<"Error: Energy Deposited not equal to total energy"<<std::endl;
  }
}

void Electron::print_data()
{
  Lepton::print_data();
  std::cout<<"Electron lepton number : "<<get_lepton_number()<<std::endl;
  std::cout<<"--Electron Extra Information--"<<std::endl;
  std::cout<<"Energy Deposited: "<<" EM_1 = "<<energy_deposit[0]<<"MeV, EM_2 = "<<energy_deposit[1]<<"MeV, HAD_1 = "<<energy_deposit[2]<<"MeV, HAD_2 = "<<energy_deposit[3]<<"MeV"<<std::endl;
}

//------------------------
//Functions for Muon Class
//------------------------

Muon::Muon(double energy_in, double px_in, double py_in, double pz_in, bool isolation_in, bool antiparticle_bool)
  : Lepton(energy_in,px_in,py_in,pz_in,"Muon",105.7,-1,antiparticle_bool)
{
  set_isolation(isolation_in);
}

void Muon::print_data()
{
  Lepton::print_data();
  std::cout<<"Muon lepton number: "<<get_lepton_number()<<std::endl;
  auto printBool = [](bool input) 
  {
    if (input == false) {std::cout << "Isolation: false" << std::endl;} 
    else {std::cout << "Isolation: true" << std::endl;}
  };
  std::cout<<"--Muon Extra Information--"<<std::endl;
  printBool(isolation);
}

//-----------------------
//Functions for Tau Class
//-----------------------

Tau::Tau(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_bool, int decay_type_in)
  : Lepton(energy_in,px_in,py_in,pz_in,"Tau",1077,-1,antiparticle_bool)
{
  decay_type = decay_type_in;
}

std::vector<std::shared_ptr<Particle>> Tau::leptonic_decay() 
{
  std::vector<std::shared_ptr<Particle>> decay_products;
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<> distr(0, 1); // Define the range
  int random_number{distr(gen)};

  if(antiparticle == true)
  {
    if(random_number == 0) //Decay with different probabilities
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{0.511,0,15.5});
      decay_products.push_back(std::make_shared<Electron>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,false,Neutrino::Flavour::Electron));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,true,Neutrino::Flavour::Tau));
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{105.7,0.17,15.5});
      decay_products.push_back(std::make_shared<Muon>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true,true));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,false,Neutrino::Flavour::Muon));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,true,Neutrino::Flavour::Tau));
    }
  }
  else
  {
    if(random_number == 0) //Decay with different probabilities
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{105.7,0.17,15.5});
      decay_products.push_back(std::make_shared<Muon>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true,false));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,true,Neutrino::Flavour::Muon));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,false,Neutrino::Flavour::Tau));
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{0.511,0,15.5});
      decay_products.push_back(std::make_shared<Electron>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,true,Neutrino::Flavour::Electron));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,false,Neutrino::Flavour::Tau));
    }
  }
  return decay_products;
}

std::vector<std::shared_ptr<Particle>> Tau::hadronic_decay() 
{
  std::vector<std::shared_ptr<Particle>> decay_products;
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<> distr(0, 1); // Define the range
  int random_number{distr(gen)};
  if(antiparticle == false)
  {
    if(random_number == 0)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(QuarkType::Up),Quark::mass_of_type(QuarkType::Down),15.5});
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true, ColourCharge::AntiRed, QuarkType::Up));
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false,ColourCharge::Red,QuarkType::Down));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,false,Neutrino::Flavour::Tau));
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(QuarkType::Charm),Quark::mass_of_type(QuarkType::Strange),15.5});
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true, ColourCharge::AntiRed, QuarkType::Charm));
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false,ColourCharge::Red,QuarkType::Strange));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,false,Neutrino::Flavour::Tau));
    }
  }
  else
  {
    if(random_number == 0)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(QuarkType::Up),Quark::mass_of_type(QuarkType::Down),15.5});
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false, ColourCharge::Red, QuarkType::Up));
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,ColourCharge::AntiRed,QuarkType::Down));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,true,Neutrino::Flavour::Tau)); 
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(QuarkType::Charm),Quark::mass_of_type(QuarkType::Strange),15.5});
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false, ColourCharge::AntiRed, QuarkType::Charm));
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,ColourCharge::Red,QuarkType::Strange));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[4],decay_parameters[5],decay_parameters[5],decay_parameters[5],true,true,Neutrino::Flavour::Tau));
    }
  }
  return decay_products;
}

std::vector<std::shared_ptr<Particle>> Tau::decay() 
{
  if(decay_type == 0)
  {
    return leptonic_decay();
  }
  else
  {
    return hadronic_decay();
  }
}

void Tau::print_data()
{
  Lepton::print_data();
  std::cout<<"Tau lepton number: "<<get_lepton_number()<<std::endl;
  std::cout<<"--Tau Extra Information--"<<std::endl;
  if(decay_type == 0) {std::cout<<"Decay type: Leptonic"<<std::endl;}
  else {std::cout<<"Decay type: Hadronic"<<std::endl;}
}

std::vector<std::shared_ptr<Particle>> Tau::decay(std::initializer_list<std::string> particle_names)
{
  std::vector<std::shared_ptr<Particle>> decay_products;

  //Decay Table
  for(auto element: particle_names)
    {
      if(element == "TauNeutrino")
        decay_products.push_back(std::make_shared<Neutrino>(15.5,0,0,0,true,false,Neutrino::Flavour::Tau));
      else if(element == "AntiTauNeutrino")
        decay_products.push_back(std::make_shared<Neutrino>(15.5,0,0,0,true,true,Neutrino::Flavour::Tau));
      else if(element == "AntiElectronNeutrino")
        decay_products.push_back(std::make_shared<Neutrino>(0,0,0,0,true,true,Neutrino::Flavour::Electron));
      else if(element == "ElectronNeutrino")
        decay_products.push_back(std::make_shared<Neutrino>(0,0,0,0,false,false,Neutrino::Flavour::Electron));
      else if(element == "AntiMuonNeutrino")
        decay_products.push_back(std::make_shared<Neutrino>(0.17,0,0,0,true,true,Neutrino::Flavour::Muon));
      else if(element == "MuonNeutrino")
        decay_products.push_back(std::make_shared<Neutrino>(0.17,0,0,0,true,false,Neutrino::Flavour::Muon));      
      else if(element == "Electron")
        decay_products.push_back(std::make_shared<Electron>(0.511,0,0,0,false));
      else if(element == "AntiElectron")
        decay_products.push_back(std::make_shared<Electron>(0.511,0,0,0,true));
      else if(element == "Muon")
        decay_products.push_back(std::make_shared<Muon>(105.7,0,0,0,true,false));
      else if(element == "AntiMuon")
        decay_products.push_back(std::make_shared<Muon>(105.7,0,0,0,true,true));
      else if(element == "Up")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Up),0,0,0,false, ColourCharge::Red, QuarkType::Up));
      else if(element == "AntiUp")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Up),0,0,0,true, ColourCharge::AntiRed, QuarkType::Up));
      else if(element == "Down")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Down),0,0,0,false,ColourCharge::Red,QuarkType::Down));
      else if(element == "AntiDown")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Down),0,0,0,true,ColourCharge::AntiRed,QuarkType::Down));
      else if(element == "Strange")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Strange),0,0,0,false,ColourCharge::Red,QuarkType::Strange));
      else if(element == "AntiStrange")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Strange),0,0,0,true,ColourCharge::AntiRed,QuarkType::Strange));
      else if(element == "Charm")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Charm),0,0,0,false,ColourCharge::Red,QuarkType::Charm));
      else if(element == "AntiCharm")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Charm),0,0,0,true,ColourCharge::AntiRed,QuarkType::Charm));
      else if(element == "Top")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Top),0,0,0,false,ColourCharge::Red,QuarkType::Top));
      else if(element == "AntiTop")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Top),0,0,0,true,ColourCharge::AntiRed,QuarkType::Top));
      else if(element == "Bottom")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Bottom),0,0,0,false,ColourCharge::Red,QuarkType::Bottom));
      else if(element == "AntiBottom")
        decay_products.push_back(std::make_shared<Quark>(Quark::mass_of_type(QuarkType::Bottom),0,0,0,true,ColourCharge::AntiRed,QuarkType::Bottom));
      else
      {
        std::cout<<"Tau Does Not Decay into those particles";
        return {};
      }
    }

  if(Decay::check_charge_cons(get_charge(),decay_products))
  {
    return decay_products;
  }
  else
  {
    return {};
  }
}

//-----------------------------
//Neutrino Class implementation
//-----------------------------

double Neutrino::mass_for_flavour(Flavour flavour_in)
{
  switch (flavour_in)
  {
    case Flavour::Electron:
      return 0; 
    case Flavour::Muon:
      return 0.17; 
    case Flavour::Tau:
      return 15.5; 
    default:
      return 0;
  }
}

std::string Neutrino::flavour_to_string(Flavour flavour_in)
{
  switch (flavour_in) 
  {
    case Flavour::Electron: 
      return "Electron Neutrino";
    case Flavour::Muon: 
      return "Muon Neutrino";
    case Flavour::Tau: 
      return "Tau Neutrino";
    default:
      return "Unknown Neutrino";
  }
}

Neutrino::Neutrino(double energy_in, double px_in, double py_in, double pz_in, bool has_interacted_in, bool antiparticle_bool, Flavour flavour_in)
  : Lepton(energy_in, px_in, py_in, pz_in, flavour_to_string(flavour_in), mass_for_flavour(flavour_in), 0, antiparticle_bool)
{
  set_interaction(has_interacted_in);
  set_flavour(flavour_in);
}

void Neutrino::print_data()
{
  Lepton::print_data();

  std::string lepton_number_type;
  if(flavour == Flavour::Electron)
    lepton_number_type = "Electron";
  else if(flavour == Flavour::Muon)
    lepton_number_type = "Muon";
  else
    lepton_number_type = "Tau";

  std::cout<<lepton_number_type<<" lepton number: "<<get_lepton_number()<<std::endl;
  std::cout<<"--Neutrino Extra Information--"<<std::endl;
  if(has_interacted == true) {std::cout<<"Detected: True"<<std::endl;}
  else {std::cout<<"Detected: False"<<std::endl;}
}