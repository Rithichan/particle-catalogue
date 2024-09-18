// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This is the header file for the quark class
#ifndef QUARK_H
#define QUARK_H

#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<stdexcept>
#include"particle.h"

//Enum Classes for types and colour
enum class ColourCharge { Red, Blue, Green, AntiRed, AntiBlue, AntiGreen };
enum class QuarkType {Up, Down, Charm, Strange, Top, Bottom};

//Quark Derived class
class Quark: public Particle
{
private:
  double baryon_number{0.33};
  ColourCharge colour;
  QuarkType quark_type;
public:
  Quark() = default;
  //Parameterised Constructor
  Quark(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_bool, ColourCharge colour_in, QuarkType type_in);
  //Destructor
  virtual ~Quark(){};

  //Getters
  double get_baryon_number() const {return baryon_number;}
  std::string get_colour() const {return colour_to_string(colour);}
  std::string get_quark_type() const {return type_to_string(quark_type);}

  //Print Function
  virtual void print_data();

  //Static Functions
  static std::string colour_to_string(ColourCharge colour_in);
  static std::string type_to_string(QuarkType type_in);
  static double mass_of_type(QuarkType type_in);
  static double charge_of_type(QuarkType type_in);
  static ColourCharge colour_swap(ColourCharge type_in);
};

#endif