// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This file includes the implementation of all boson derived classes
// ie. Photon, Gluon, Higgs etc.
// All bosons functions are separated by spaces and comments
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<stdexcept>
#include<random>
#include"particle.h"
#include"boson.h"
#include"quark.h"
#include"lepton.h"
#include"decay.h"


//------------------------------------------------------------
//-----------------Boson Class Implementation-----------------
//------------------------------------------------------------

Boson::Boson(double energy_in, double px_in, double py_in, double pz_in, std::string name_in, double rest_mass_in, double charge_in, bool antiparticle_bool, int boson_type_in, double spin_in)
 : Particle(energy_in,px_in,py_in,pz_in,name_in,rest_mass_in,charge_in,antiparticle_bool)
{
  boson_type = boson_type_in;
  spin = spin_in;
}

void Boson::print_data()
{
  Particle::print_data();
  std::cout<<"Particle is a ";
  if(boson_type == 0)
  {
    std::cout<<"Gauge Boson"<<std::endl;
  }
  else
  {
    std::cout<<"Higgs Boson"<<std::endl;
  }
}


//-------------------------------------------------------------
//-----------------Photon Class Implementation-----------------
//-------------------------------------------------------------

Photon::Photon(double energy_in, double px_in, double py_in, double pz_in)
  : Boson(energy_in,px_in,py_in,pz_in,"Photon",0,0,false,0,1){}

void Photon::print_data()
{
  Boson::print_data();
  std::cout<<"--Photon has no Extra Information--"<<std::endl;
}



//-------------------------------------------------------------
//-----------------Gluon Class Implementation------------------
//-------------------------------------------------------------

Gluon::Gluon(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_in, ColourCharge colour_in)
  : Boson(energy_in,px_in,py_in,pz_in,"Gluon",0,0,antiparticle_in,0,1)
{
  if(antiparticle_in == false) //gluon antiparticle swaps the colour pairs
  {
    colour = colour_in;
    colour_pair = Quark::colour_swap(colour_in); //using static method from quark class
  }
  else
  {
    colour = Quark::colour_swap(colour_in);
    colour_pair = colour_in;
  }
}

void Gluon::print_data()
{
  Boson::print_data();
  std::cout<<"--Gluon Extra Information--"<<std::endl;
  std::cout<<"Colour pair: "<<Quark::colour_to_string(colour)<<", "<<Quark::colour_to_string(colour_pair)<<std::endl;
}



//--------------------------------------------------------------
//-----------------WBoson Class Implementation------------------
//--------------------------------------------------------------

std::string w_boson_name(double charge_in)
{
  if(charge_in == 1)
  {
    return "W+ Boson";
  }
  else if(charge_in == -1)
  {
    return "W- Boson";
  }
  else
  {
    return "Invalid Charge";
  }
}

WBoson::WBoson(double energy_in, double px_in, double py_in, double pz_in, double charge_in, int decay_type_in)
  : Boson(energy_in,px_in,py_in,pz_in,w_boson_name(charge_in), 80400, charge_in, false, 0, 1)
{
  decay_type = decay_type_in;
}

void WBoson::print_data()
{
  Boson::print_data();
  std::cout<<"--"<<w_boson_name(charge)<<" Extra Information--"<<std::endl;
  if(decay_type == 0) {std::cout<<"Decay type: Leptonic"<<std::endl;}
  else {std::cout<<"Decay type: Hadronic"<<std::endl;}
}

std::vector<std::shared_ptr<Particle>> WBoson::decay()
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

std::vector<std::shared_ptr<Particle>> WBoson::leptonic_decay()
{
  std::vector<std::shared_ptr<Particle>> decay_products;
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<> distr(0, 2); // Define the range
  int random_number{distr(gen)};

  if(charge == -1) //W- decays
  {
    if(random_number == 0)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{0.511,0});
      decay_products.push_back(std::make_shared<Electron>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,true,Neutrino::Flavour::Electron));
    }
    else if(random_number == 1)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{105.7,0.17});
      decay_products.push_back(std::make_shared<Muon>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false,false));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,true,Neutrino::Flavour::Muon));
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{1077,15.5});
      decay_products.push_back(std::make_shared<Tau>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false,0));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,true,Neutrino::Flavour::Tau));
    }
  }
  else
  {
    if(random_number == 0)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{0.511,0});
      decay_products.push_back(std::make_shared<Electron>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,false,Neutrino::Flavour::Electron));
    }
    else if(random_number == 1)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{105.7,0.17});
      decay_products.push_back(std::make_shared<Muon>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false,false));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,false,Neutrino::Flavour::Muon));
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{1077,15.5});
      decay_products.push_back(std::make_shared<Tau>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false,0));
      decay_products.push_back(std::make_shared<Neutrino>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,false,Neutrino::Flavour::Tau));
    }
  }
  return decay_products;
}

std::vector<std::shared_ptr<Particle>> WBoson::hadronic_decay()
{
  std::vector<std::shared_ptr<Particle>> decay_products;
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<> distr(0, 2); // Define the range
  int random_number{distr(gen)};

  auto get_random_up_type_flavour = [random_number]() 
  {
    switch(random_number)
    {
      case 0:
        return QuarkType::Up;
      case 1:
        return QuarkType::Charm;
      case 2:
        return QuarkType::Top;
      default:
        return QuarkType::Up;
    }
  };

  auto get_random_down_type_flavour = [random_number]() 
  {
    switch(random_number)
    {
      case 0:
        return QuarkType::Down;
      case 1:
        return QuarkType::Strange;
      case 2:
        return QuarkType::Bottom;
      default:
        return QuarkType::Down;
    }
  };

  if(charge == -1) //W- decays (anti-up_type q=-2/3 and down type q = -1/3)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(get_random_up_type_flavour()),Quark::mass_of_type(get_random_down_type_flavour())});
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true,ColourCharge::AntiRed,get_random_up_type_flavour()));
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false,ColourCharge::Red,get_random_down_type_flavour()));
    }
    else //W+ decays (up_type q=2/3 and anti-down type q = 1/3)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(get_random_up_type_flavour()),Quark::mass_of_type(get_random_down_type_flavour())});
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false,ColourCharge::Red,get_random_up_type_flavour()));
      decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,ColourCharge::AntiRed,get_random_down_type_flavour()));
    }

  return decay_products;
}

std::vector<std::shared_ptr<Particle>> WBoson::decay(std::initializer_list<std::string> particle_names)
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
        std::cout<<"WBoson Does Not Decay into those particles";
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



//--------------------------------------------------------------
//-----------------ZBoson Class Implementation------------------
//--------------------------------------------------------------

ZBoson::ZBoson(double energy_in, double px_in, double py_in, double pz_in, int decay_type_in)
  : Boson(energy_in,px_in,py_in,pz_in,"Z Boson", 91200, 0, false, 0, 1)
{
  decay_type = decay_type_in;
}

void ZBoson::print_data()
{
  Boson::print_data();
  std::cout<<"--Z Boson Extra Information--"<<std::endl;
  if(decay_type == 0) {std::cout<<"Decay type: Leptonic"<<std::endl;}
  else {std::cout<<"Decay type: Hadronic"<<std::endl;}
}

std::vector<std::shared_ptr<Particle>> ZBoson::leptonic_decay()
{
  std::vector<std::shared_ptr<Particle>> decay_products;
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<> distr(0, 2); // Define the range
  int random_number{distr(gen)};

  if(random_number == 0)
  {
    std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{0.511,0.511});
    decay_products.push_back(std::make_shared<Electron>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true));
    decay_products.push_back(std::make_shared<Electron>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false));
  }
  else if(random_number == 1)
  {
    std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{105.7,105.7});
    decay_products.push_back(std::make_shared<Muon>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true,true));
    decay_products.push_back(std::make_shared<Muon>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false,false));
  }
  else
  {
    std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{1077,1077});
    decay_products.push_back(std::make_shared<Tau>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true,0));
    decay_products.push_back(std::make_shared<Tau>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false,1));
  }
  return decay_products;
}

std::vector<std::shared_ptr<Particle>> ZBoson::hadronic_decay()
{
  std::vector<std::shared_ptr<Particle>> decay_products;
  std::random_device rd;  // Obtain a random number from hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<> distr(0, 5); // Define the range
  int random_number{distr(gen)};

  //To save me from writing 20 if-else statements
  auto get_random_flavour = [random_number]() 
  {
    switch(random_number)
    {
      case 0:
      return QuarkType::Up;
      case 1:
      return QuarkType::Down;
      case 2:
      return QuarkType::Charm;
      case 3:
      return QuarkType::Strange;
      case 4:
      return QuarkType::Bottom;
      case 5:
      return QuarkType::Top;
      default:
      return QuarkType::Up;
    }
  };

  std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{Quark::mass_of_type(get_random_flavour()),Quark::mass_of_type(get_random_flavour())});
  decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],true,ColourCharge::AntiRed,get_random_flavour()));
  decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],false,ColourCharge::Red,get_random_flavour()));

  return decay_products;
}

std::vector<std::shared_ptr<Particle>> ZBoson::decay()
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

std::vector<std::shared_ptr<Particle>> ZBoson::decay(std::initializer_list<std::string> particle_names)
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
        std::cout<<"ZBoson Does Not Decay into those particles";
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



//--------------------------------------------------------------
//-----------------Higgs Class Implementation-------------------
//--------------------------------------------------------------

Higgs::Higgs(double energy_in, double px_in, double py_in, double pz_in, int decay_type_in)
  : Boson(energy_in,px_in,py_in,pz_in,"Higgs Boson",126000,0,false,1,0){}

void Higgs::print_data()
{
  Boson::print_data();
  std::cout<<"--Higgs Boson Extra Information--"<<std::endl;
  if(decay_type == 0) {std::cout<<"Decay type: Bosons"<<std::endl;}
  else {std::cout<<"Decay type: Bottom"<<std::endl;}
}

  std::vector<std::shared_ptr<Particle>> Higgs::decay()
  {
    if(decay_type == 0)
      return bosonic_decay();
    else
      return hadronic_decay();
  }

  std::vector<std::shared_ptr<Particle>> Higgs::bosonic_decay()
  {
    std::vector<std::shared_ptr<Particle>> decay_products;
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, 2); // Define the range
    int random_number{distr(gen)};

    if(random_number == 0)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{91200,91200});
      decay_products.push_back(std::make_shared<ZBoson>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],0));
      decay_products.push_back(std::make_shared<ZBoson>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],0)); 
    }
    else if(random_number == 1)
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{80400,80400});
      decay_products.push_back(std::make_shared<WBoson>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],1,1));
      decay_products.push_back(std::make_shared<WBoson>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],-1,1)); 
    }
    else
    {
      std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{0,0});
      decay_products.push_back(std::make_shared<Photon>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1]));
      decay_products.push_back(std::make_shared<Photon>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3]));
    }
    return decay_products;
  }

  std::vector<std::shared_ptr<Particle>> Higgs::hadronic_decay()
  {
    std::vector<std::shared_ptr<Particle>> decay_products; //one hadronic decay
    std::vector<double> decay_parameters = Decay::decay_logic(get_energy(),get_px(),get_py(),get_pz(),{4180,4180});
    decay_products.push_back(std::make_shared<Quark>(decay_parameters[0],decay_parameters[1],decay_parameters[1],decay_parameters[1],false,ColourCharge::Red,QuarkType::Bottom));
    decay_products.push_back(std::make_shared<Quark>(decay_parameters[2],decay_parameters[3],decay_parameters[3],decay_parameters[3],true,ColourCharge::AntiRed,QuarkType::Bottom));
    return decay_products;
  }

std::vector<std::shared_ptr<Particle>> Higgs::decay(std::initializer_list<std::string> particle_names)
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
      else if(element == "Photon")
        decay_products.push_back(std::make_shared<Photon>(0,0,0,0));
      else if(element == "WPlusBoson")
        decay_products.push_back(std::make_shared<WBoson>(80400,0,0,0,1,1));
      else if(element == "WMinusBoson")
        decay_products.push_back(std::make_shared<WBoson>(80400,0,0,0,-1,1));
      else if(element == "ZBoson")
        decay_products.push_back(std::make_shared<ZBoson>(91200,0,0,0,1));
      else
      {
        std::cout<<"Higgs Does Not Decay into those particles";
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