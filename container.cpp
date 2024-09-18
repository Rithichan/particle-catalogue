// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This file includes all the functionality of the container
// This file includes the implementation of the user interface
#include<iostream>
#include<unordered_map>
#include<string>
#include"container.h"
#include"particle.h"
#include"boson.h"
#include"quark.h"
#include"lepton.h"
#include"fourmomentum.h"

void Container::add(const std::string& key, std::shared_ptr<Particle> new_particle_ptr)
{
  map_of_particles[key] = new_particle_ptr;
  set_number_of_particles();

  //Whenever we add a new Particle it checks if the particle is of a specific type and adds it to the sub container
  std::shared_ptr<Lepton> lepton_ptr = std::dynamic_pointer_cast<Lepton>(new_particle_ptr);
  if(lepton_ptr) 
  {
    map_of_leptons[key] = lepton_ptr;
  }

  std::shared_ptr<Quark> quark_ptr = std::dynamic_pointer_cast<Quark>(new_particle_ptr);
  if(quark_ptr) 
  {
    map_of_quarks[key] = quark_ptr;
  }

  std::shared_ptr<Boson> boson_ptr = std::dynamic_pointer_cast<Boson>(new_particle_ptr);
  if(boson_ptr) 
  {
    map_of_bosons[key] = boson_ptr;
  }
}

bool Container::remove(const std::string& key) 
{
  auto it = map_of_particles.find(key);

  if(it != map_of_particles.end())
  {
    map_of_leptons.erase(key);
    map_of_bosons.erase(key);
    map_of_quarks.erase(key);
    map_of_particles.erase(it);
    set_number_of_particles();
    return true;
  }
  return false;
}

std::shared_ptr<Particle> Container::get(const std::string& key) 
{
  try
  {  
    if(map_of_particles.find(key) != map_of_particles.end()) 
    {
      return map_of_particles[key];
    }
    else
      throw std::invalid_argument("Cannot find particle");
  }
  catch(const std::exception& e)
  {
    std::cerr<<e.what()<<std::endl;
    return nullptr;
  }
}

bool Container::exists(const std::string& key) 
{
  return map_of_particles.find(key) != map_of_particles.end();
}

void Container::display_all()
{
  for(const auto& element : map_of_particles) 
  {
    (element.second)->print_data();
  }
}

void Container::display_specific(const std::string& key)
{
  map_of_particles[key]->print_data();
}

int Container::get_number_of_particles_per_type(std::string type)
{
  if(type == "Boson")
    return map_of_bosons.size();
  else if(type == "Quark")
    return map_of_quarks.size();
  else if(type == "Lepton")
    return map_of_leptons.size();
  else
    return 0;
}

void Container::display_type(std::string type)
{
  for(const auto& element : map_of_particles)
  {
    if(type == "Boson" && std::dynamic_pointer_cast<Boson>(element.second))
      (element.second)->print_data();
    else if(type == "Quark" && std::dynamic_pointer_cast<Quark>(element.second))
      (element.second)->print_data();
    else if(type == "Lepton" && std::dynamic_pointer_cast<Lepton>(element.second))
      (element.second)->print_data();
  }  
}

std::vector<double> Container::sum_of_four_momenta()
{
  std::vector<double> result{0,0,0,0};
  FourMomentum empty_four_momentum(0,0,0,0,0);
  for(const auto& element : map_of_particles)
  {
    auto temp = ((element.second)->get_four_momentum()) + empty_four_momentum;
    for(const auto& i : result)
    {
      result[0] = result[0] + temp[0];
      result[1] = result[1] + temp[1];
      result[2] = result[2] + temp[2];
      result[3] = result[3] + temp[3];
    }
  }
  return result;
}

//adds decay products to a sub container of decay products
void Container::add_decay_products(std::vector<std::shared_ptr<Particle>> decay_products)
{
  for (size_t i = 0; i < decay_products.size(); ++i) 
  {
    std::string key = decay_products[i]->get_particle_name() + "_product_" + std::to_string(i);
    map_of_decay_products[key] = decay_products[i];
  }
}

void Container::display_decay_products()
{
  for(const auto& element : map_of_decay_products)
  {
    (element.second)->print_data();
  }
}

void Container::user_interface()
{
  std::cout<<"-------------------------------------------------------"<<std::endl;
  std::cout<<"-----------Welcome to the Particle Catalouge-----------"<<std::endl;
  while(true)
  {
    int user_input{0};
    auto total_four_momentum = sum_of_four_momenta();
    std::cout<<"-------------------------------------------------------"<<std::endl;
    std::cout<<"There are currently "<<get_number_of_particles()<<" particles in the catalogue."<<std::endl;
    std::cout<<"Number of Leptons: "<<get_number_of_particles_per_type("Lepton")<<std::endl;
    std::cout<<"Number of Bosons: "<<get_number_of_particles_per_type("Boson")<<std::endl;
    std::cout<<"Number of Quarks: "<<get_number_of_particles_per_type("Quark")<<std::endl;
    std::cout<<"Number of decay products: "<<map_of_decay_products.size()<<std::endl;
    std::cout<<"Sum of four momentum in catalouge: "<<"("<<total_four_momentum[0]<<", "<<total_four_momentum[1];
    std::cout<<", "<<total_four_momentum[2]<<", "<<total_four_momentum[3]<<" )"<<std::endl;
    std::cout<<"Please select the following options:"<<std::endl;
    std::cout<<"Press 1 to display all particles, Press 2 to display specific particle types"<<std::endl;
    std::cout<<"Press 3 to display specific particle, Press 4 to initiate a decay"<<std::endl;
    std::cout<<"Press 5 to see all decay products, Press 6 to test input checking"<<std::endl;
    std::cout<<"Press 7 to exit"<<std::endl;
    std::cout<<"-------------------------------------------------------"<<std::endl;
    std::cout<<"Please select an option to continue: ";
    std::cin>>user_input;
    while(true)
    {
    if(user_input == 1 or user_input == 2 or user_input ==3 or user_input == 4 or user_input == 5 or user_input == 6 or user_input == 7)
      break;
    std::cout<<"Please enter a number from 1 to 7: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin>>user_input;
    }

    if(user_input == 1) //display all
    {
      display_all();
    }
    else if(user_input == 2) //display specific type
    {
      std::string input_type;
      std::cout<<"Please enter the type of particle you want to see"<<std::endl;
      std::cout<<"Particle Types are: Boson, Quark, Lepton (Captialisation matters)"<<std::endl;
      std::cout<<"Input:";
      std::cin>>input_type;
      while(true)
      {
        if(input_type == "Boson" or input_type == "Quark" or input_type == "Lepton")
          break;
        std::cout<<"Please enter Boson, Lepton or Quark:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin>>input_type;
      }
      display_type(input_type);
    }
    else if(user_input == 3) //display specific particle
    {
      std::string input_name{"Null"};
      std::cout<<"Please enter the particle you wish to see"<<std::endl;
      std::cout<<"Example of particle names: Tau, Gluon, AntiElectron, AntiTauNeutrino, WPlusBoson"<<std::endl;
      std::cout<<"Follow the syntax above or you wont find anything."<<std::endl;
      std::cout<<"Input:";
      std::cin>>input_name;
      if(exists(input_name))
        display_specific(input_name);
      else
        std::cout<<"Unable to find particle."<<std::endl;
    }
    else if(user_input == 4) //initiate decay
    {
      std::string input_name{"Null"};
      std::cout<<"Please enter the particle you wish to decay"<<std::endl;
      std::cout<<"Only Tau, AntiTau, ZBoson, WPlusBoson, WMinusBoson and Higgs decay in this catalouge."<<std::endl;
      std::cout<<"Input:";
      std::cin>>input_name;
      if(exists(input_name))
      {
        std::shared_ptr<Particle> decaying_particle = get(input_name);
        auto decay_products = decaying_particle->decay();
        if(decay_products.empty())
          std::cout<<"Particle does not decay"<<std::endl;
        else
          add_decay_products(decay_products); //add decay products to the sub container, no need to remove the parent
          for(const auto element: decay_products)
          {
            element->print_data();
          }
          std::cout<<"Decay Complete"<<std::endl;
      }
      else
      {
        std::cout<<"Unable to find particle."<<std::endl;
      }
    }
    else if(user_input == 5) //display decay products
    {
      display_decay_products();
    }
    else if(user_input == 6) //test input checking
    {
      std::cout<<"Attempting to add an Electron with mass of 10 MeV and 0 momentum."<<std::endl;
      add("ElectronBad",std::make_shared<Electron>(10,0,0,0,false));
    }
    else //end code
    {
      std::cout<<"Thank you for using particle catalouge."<<std::endl;
      break;
    }

    //clear everything at end of loop
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}