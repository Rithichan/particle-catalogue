// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This is the header file for all Lepton classes
#ifndef LEPTON_H
#define LEPTON_H

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<stdexcept>
#include"particle.h"

//Lepton Intermediate Class
class Lepton: public Particle
{
private:
  int lepton_number{1};
public:
  //Constructor
  Lepton() = default;
  //Parameterised Constructor
  Lepton(double energy_in, double px_in, double py_in, double pz_in, std::string name_in, double rest_mass_in, double charge_in, bool antiparticle_bool);
  //Virtual Destructor
  virtual ~Lepton(){};

  //Print data for leptons
  virtual void print_data();

  //Getter
  int get_lepton_number() const {return lepton_number;}

  //decay
  virtual std::vector<std::shared_ptr<Particle>> decay(){return {};}
  virtual std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names){return {};}
};

//Electron Derived Class
class Electron: public Lepton
{
private:
  std::vector<double> energy_deposit{0,0,0,0};

public:
  //Default constructor
  Electron() = default;
  //Parameterised constructor
  Electron(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_bool);
  //Destructor
  ~Electron(){}

  //getters
  std::vector<double> get_energy_deposit() const {return energy_deposit;}

  //setters
  void set_energy_deposit(double EM_1, double EM_2, double HAD_1, double HAD_2);

  //print data
  void print_data();
};

//Muon Derived Class
class Muon: public Lepton
{
private:
  bool isolation{false};
public:
  //Default constructor
  Muon() = default;
  //Parameterised constructor
  Muon(double energy_in, double px_in, double py_in, double pz_in, bool isolation_in, bool antiparticle_bool);
  //Destructor
  ~Muon(){}

  //getters
  bool get_isolation() const {return isolation;}

  //setters
  void set_isolation(bool isolation_in){isolation = isolation_in;}

  //print data
  void print_data();
};

//Tau Derived Class
class Tau: public Lepton
{
private:
  int decay_type{0}; //0 for leptonic, 1 for hadronic
public:
  //Default Constructor
  Tau() = default;
  //Parameterised Constructor
  Tau(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_bool, int decay_type_in);
  //Destructor
  ~Tau(){};

  //Getter
  int get_decay_type() {return decay_type;}

  //Setter
  void set_decay_type(int decay_type_in) {decay_type = decay_type_in;}

  //Decay Functions
  std::vector<std::shared_ptr<Particle>> decay();
  std::vector<std::shared_ptr<Particle>> leptonic_decay();
  std::vector<std::shared_ptr<Particle>> hadronic_decay();
  std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names);

  //print data
  void print_data();
};

//Neutrino Derived Class
class Neutrino: public Lepton
{
public:
  enum class Flavour { Electron, Muon, Tau };
private:
  bool has_interacted{false};
  Flavour flavour;
public:
  //Default Constructor
  Neutrino() = default;
  //Parameterised Constructor
  Neutrino(double energy_in, double px_in, double py_in, double pz_in, bool has_interacted_in, bool antiparticle_bool, Flavour flavour_in);
  //Destructor
  ~Neutrino(){};

  //static functions
  static double mass_for_flavour(Flavour flavour_in);
  static std::string flavour_to_string(Flavour flavour_in); 

  //Getters
  bool get_interation() const {return has_interacted;}
  Flavour get_flavour() const {return flavour;}

  //Setters
  void set_interaction(bool has_interacted_in) {has_interacted = has_interacted_in;}
  void set_flavour(Flavour flavour_in) {flavour = flavour_in;}

  //print data
  void print_data();
};

#endif