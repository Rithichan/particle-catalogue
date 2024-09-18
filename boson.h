// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This file is the header file for all the boson derived classes
#ifndef BOSON_H
#define BOSON_H

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<stdexcept>
#include"particle.h"
#include"quark.h"

//Boson Intermediate Class
class Boson: public Particle
{
private:
  int boson_type{0}; //0 is for Gauge bosons and 1 is for Higgs
public:
  Boson() = default;
  Boson(double energy_in, double px_in, double py_in, double pz_in, std::string name_in, double rest_mass_in, double charge_in, bool antiparticle_bool, int boson_type_in, double spin_in);
  virtual ~Boson(){};

  //Getter
  int get_boson_type() const {return boson_type;}

  virtual void print_data();
  virtual std::vector<std::shared_ptr<Particle>> decay(){return {};}
  virtual std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names){return {};}
};

//Photon Derived Class
class Photon: public Boson
{
public:
  Photon() = default;
  Photon(double energy_in, double px_in, double py_in, double pz_in);
  ~Photon(){};

  //Print Data
  void print_data();
};

//Gluon Derived Class
class Gluon: public Boson
{
private:
  ColourCharge colour;
  ColourCharge colour_pair;
public:
  Gluon() = default;
  Gluon(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_in, ColourCharge colour_in);
  ~Gluon(){};

  //Getter
  ColourCharge get_colour_1() const {return colour;}
  ColourCharge get_colour_2() const {return colour_pair;}

  //Print Data
  void print_data();
};


//W Boson Derived Class
class WBoson: public Boson
{
private:
  int decay_type{0};
public:
  WBoson() = default;
  WBoson(double energy_in, double px_in, double py_in, double pz_in, double charge_in, int decay_type_in);
  ~WBoson(){};

  //Getter
  int get_decay_type() const {return decay_type;}

  //Decay Functions
  std::vector<std::shared_ptr<Particle>> decay();
  std::vector<std::shared_ptr<Particle>> leptonic_decay();
  std::vector<std::shared_ptr<Particle>> hadronic_decay();
  std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names);

  //Print Data Function
  void print_data();
};

//Z Boson Derived Class
class ZBoson: public Boson
{
private:
  int decay_type{0};
public:
  ZBoson() = default;
  ZBoson(double energy_in, double px_in, double py_in, double pz_in, int decay_type_in);
  ~ZBoson(){};

  //Getter
  int get_decay_type() const {return decay_type;}

  //Decay Functions
  std::vector<std::shared_ptr<Particle>> decay();
  std::vector<std::shared_ptr<Particle>> leptonic_decay();
  std::vector<std::shared_ptr<Particle>> hadronic_decay();
  std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names);

  //Print Data Function
  void print_data();
};

//Higgs Boson Derived Class
class Higgs: public Boson
{
private:
  int decay_type{0};
public:
  Higgs() = default;
  Higgs(double energy_in, double px_in, double py_in, double pz_in, int decay_type_in);
  ~Higgs(){};

  //Getter
  int get_decay_type() const {return decay_type;}

  //Decay Functions
  std::vector<std::shared_ptr<Particle>> decay();
  std::vector<std::shared_ptr<Particle>> bosonic_decay();
  std::vector<std::shared_ptr<Particle>> hadronic_decay();
  std::vector<std::shared_ptr<Particle>> decay(std::initializer_list<std::string> particle_names);

  //Print Data Function
  void print_data();
};

#endif