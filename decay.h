// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// Header file for the decay methods class
#ifndef DECAY_H
#define DECAY_H

#include<iostream>
#include<iomanip>
#include<string>
#include<memory>
#include"particle.h"
#include"lepton.h"

class Decay
{
public:
  ~Decay(){};
  //decay methods
  static std::vector<std::shared_ptr<Particle>> decay_method(Particle& decaying_particle);
  static std::vector<double> decay_logic(double energy, double px, double py, double pz, std::initializer_list<double> decay_masses);
  static bool check_charge_cons(double charge, std::vector<std::shared_ptr<Particle>> particles_in_decay_process);
};

#endif