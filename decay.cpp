// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalouge
// The decay logic and calculations for four momentum of decay products
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<random>
#include<initializer_list>
#include<cmath>
#include"particle.h"
#include"decay.h"
#include"lepton.h"

  std::vector<std::shared_ptr<Particle>> Decay::decay_method(Particle& decaying_particle)
  {
    if((decaying_particle.decay()).empty())
    {
      std::cout<<"Particle Does not decay in this catalogue"<<std::endl;
    }
    return decaying_particle.decay();
  }

//Not exactly correct
std::vector<double> Decay::decay_logic(double energy, double px, double py, double pz, std::initializer_list<double> decay_masses)
{
  double remaining_energy{energy};
  for(double mass_of_particle: decay_masses)
  {
    remaining_energy = remaining_energy - mass_of_particle;
    if(remaining_energy < 0)
    {
      std::cout<<"Not enough energy to perform decay"<<std::endl;
      return {0,0,0,0,0,0};
    }
  }

  std::vector<double> decay_parameters;
  for(double mass_of_particle: decay_masses)
  {
    double energy_imparted = (remaining_energy/(decay_masses.size()) + mass_of_particle);
    double p_squared = energy_imparted*energy_imparted - mass_of_particle*mass_of_particle;
    //Keeps momentum consistent with the energy of the particle, but still not consistent with total energy of decay
    decay_parameters.push_back(energy_imparted);
    double momentum = sqrt(0.33333333333333333 * p_squared); 
    decay_parameters.push_back(momentum);
  }
  return decay_parameters;
}

bool Decay::check_charge_cons(double charge,std::vector<std::shared_ptr<Particle>> particles_in_decay_process)
{
  std::shared_ptr<Particle> daughter1 = particles_in_decay_process[0];
  std::shared_ptr<Particle> daughter2 = particles_in_decay_process[1];

  if(particles_in_decay_process.size() == 3) //check if 3 body decay
  {
    std::shared_ptr<Particle> daughter3 = particles_in_decay_process[2];
    
    //Check charge conservation
    if(std::abs(charge - (daughter1->get_charge() + daughter2->get_charge() + daughter3->get_charge())) > 0.1)
    {
      std::cout<<"Charge Not Conserved"<<std::endl;
      return false;
    }
    else
      return true;
  }
  else if(particles_in_decay_process.size() == 2)
  {
    //Check charge conservation
    if(std::abs(charge - (daughter1->get_charge() + daughter2->get_charge())) > 0.1)
    {
      std::cout<<"Charge Not Conserved"<<std::endl;
      return false;
    }
    else
      return true;
  }
  else if(particles_in_decay_process.size() == 1)
  {
    std::cout<<"One particle decays not allowed"<<std::endl;
    return false;
  }
  else
  {
    std::cout<<"This catalogue does not deal with more than 3 body decays"<<std::endl;
    return false;
  }
}