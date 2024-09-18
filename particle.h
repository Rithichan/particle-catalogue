// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This is the header file for the Particle Base Class
#ifndef PARTICLE_H
#define PARTICLE_H

#include<vector>
#include<iostream>
#include<iomanip>
#include<string>
#include<memory>
#include"fourmomentum.h"

//Particle Abstract Base Class
class Particle
{
protected:
  std::string particle_name{"Null"};
  std::unique_ptr<FourMomentum> four_momentum{nullptr};
  double rest_mass{0};
  double charge{0};
  bool antiparticle{false};
  double spin{0};

public:

  //Most things are tied to particle type and dont need setters
  //Default Copy,Move constructors/operators are good enough as the derived classses dont have pointers or anything of the sort.
  //The Particle Base Class has customised copy and move constructors/operators as four_momentum is a unique_ptr

  // Constructors
  //Default constructor
  Particle() = default;
  //Paramerterized constructor
  Particle(double energy_in, double px_in, double py_in, double pz_in, std::string name_in, double rest_mass_in, double charge_in, bool antiparticle_bool);
  //Copy Constructor
  Particle(const Particle& copied_particle);
  //Assignment copy operator
  Particle& operator=(const Particle& copied_particle);
  //Move constructor
  Particle(Particle&& moved_particle);
  //move assignment operator
  Particle& operator=(Particle&& moved_particle);

  //Virtual Destructor
  virtual ~Particle(){};

  // Getter functions
  std::string get_particle_name() const {return particle_name;}
  double get_rest_mass() const {return rest_mass;}
  double get_charge() const {return charge;}
  bool get_antiparticle() const {return antiparticle;}
  double get_spin() const {return spin;}
  double get_energy() const {return four_momentum->get_energy();}
  double get_px() const {return four_momentum->get_px();}
  double get_py() const {return four_momentum->get_py();}
  double get_pz() const {return four_momentum->get_pz();}
  FourMomentum get_four_momentum() const {return *four_momentum;}

  // Setter functions
  void set_particle_name(const std::string particle_name_in) {particle_name = particle_name_in;}
  void set_rest_mass(const double rest_mass_in) {rest_mass = rest_mass_in;}
  void set_charge(const double charge_in) {charge = charge_in;}
  void set_four_momentum(const double energy_in, const double px_in, const double py_in, const double pz_in);

  //print data function
  virtual void print_data();

  //decay
  virtual std::vector<std::shared_ptr<Particle>> decay(){return {};}
  virtual std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names){return {};}
};

#endif