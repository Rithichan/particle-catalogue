// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This is implementation of the functions in the Particle Base Class
// It includes the copy, move, assignment operators and constructors
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<stdexcept>
#include"particle.h"
#include"fourmomentum.h"

//Functions for Particle Base Class
//Parameterized constructor
Particle::Particle(double energy_in, double px_in, double py_in, double pz_in, std::string name_in, double rest_mass_in, double charge_in, bool antiparticle_bool)
{
  rest_mass = rest_mass_in;
  antiparticle = antiparticle_bool;

  if(antiparticle_bool == false)
  {
    charge = charge_in;
    particle_name = name_in;
  }
  else
  {
    charge = -1*charge_in;
    particle_name = "Anti" + name_in;
  }

  four_momentum = std::make_unique<FourMomentum>(energy_in, px_in, py_in, pz_in, rest_mass_in);
}

//print_data function
void Particle::print_data()
{ 
  std::cout<<" "<<std::endl;
  std::cout<<"---Particle information---"<<std::endl;
  std::cout<<"Four momentum: ( "<<four_momentum->get_energy()<<", "<<four_momentum->get_px()<<", "<<four_momentum->get_py()<<", "<<four_momentum->get_pz()<<" )"<<std::endl;
  std::cout<<"Particle name: "<<particle_name<<std::endl;
  std::cout<<"Rest Mass: "<<rest_mass<<" Mev, ";
  std::cout<<"Charge: "<<charge<<" e, ";
  std::cout<<"Spin: "<<spin<<std::endl;
}

//Deep copy constructor
Particle::Particle(const Particle& copied_particle)
{
  four_momentum = std::make_unique<FourMomentum>(*copied_particle.four_momentum);
  particle_name = copied_particle.get_particle_name();
  charge = copied_particle.get_charge();
  rest_mass = copied_particle.get_rest_mass();
  antiparticle = copied_particle.get_antiparticle();
  spin = copied_particle.get_spin();
}

//Assignment copy operator
Particle& Particle::operator=(const Particle& copied_particle)
{
  if(this != &copied_particle) //avoids self assignment
  {
    four_momentum = std::make_unique<FourMomentum>(*copied_particle.four_momentum);
    particle_name = copied_particle.get_particle_name();
    charge = copied_particle.get_charge();
    rest_mass = copied_particle.get_rest_mass();
    antiparticle = copied_particle.get_antiparticle();
    spin = copied_particle.get_spin();
  }
  else
  {
    throw("Error: Self-assignment");
  }
  return *this;
}

// Move constructor
Particle::Particle(Particle&& moved_particle)
    : particle_name(moved_particle.particle_name),
      four_momentum(std::move(moved_particle.four_momentum)),  
      rest_mass(moved_particle.rest_mass),
      charge(moved_particle.charge),
      antiparticle(moved_particle.antiparticle),
      spin(moved_particle.spin)
{
    moved_particle.charge = 0;
    moved_particle.rest_mass = 0;
    moved_particle.antiparticle = false;
    moved_particle.spin = 0;
    moved_particle.particle_name = "Moved";
}

// Move assignment operator
Particle& Particle::operator=(Particle&& moved_particle)
{
    if (this != &moved_particle) // Avoid self-assignment
    {
        four_momentum = std::move(moved_particle.four_momentum);
        particle_name = moved_particle.particle_name;
        charge = moved_particle.charge;
        rest_mass = moved_particle.rest_mass;
        antiparticle = moved_particle.antiparticle;
        spin = moved_particle.spin;

        moved_particle.charge = 0;
        moved_particle.rest_mass = 0;
        moved_particle.antiparticle = false;
        moved_particle.spin = 0;
        moved_particle.particle_name = "Moved";
    }
    return *this;
}

void Particle::set_four_momentum(const double energy_in, const double px_in, const double py_in, const double pz_in)
{
  four_momentum->set_energy(energy_in,px_in,py_in,pz_in,rest_mass);
  four_momentum->set_px(px_in);
  four_momentum->set_py(py_in);
  four_momentum->set_pz(pz_in);
}