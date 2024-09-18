// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// Header file for FourMomentum Class
#ifndef FOURMOMENTUM_H
#define FOURMOMENTUM_H

#include<vector>
#include<iostream>
#include<iomanip>
#include<string>

class FourMomentum
{
private:
  double energy{0};
  double px{0};
  double py{0};
  double pz{0};

public:
  //constructors
  FourMomentum() = default;
  //Parameterized constructor
  FourMomentum(double energy_in, double px_in, double py_in, double pz_in, double rest_mass_in);
  // Assignment operator
  FourMomentum& operator=(const FourMomentum& copied_four_momentum);
  // Move constructor
  FourMomentum(FourMomentum&& moved_four_momentum);
  // Move assignment operator
  FourMomentum& operator=(FourMomentum&& moved_four_momentum);
  //Copy constructor
  FourMomentum(const FourMomentum& copied_four_momentum);
  //Destructor
  ~FourMomentum(){};

  //getters
  double get_energy() const {return energy;}
  double get_px() const {return px;}
  double get_py() const {return py;}
  double get_pz() const {return pz;}

  //setters
  void set_energy(const double energy_in, const double px_in, const double py_in, const double pz_in, const double rest_mass_in);
  void set_px(const double px_in) {px = px_in;}
  void set_py(const double py_in) {py = py_in;}
  void set_pz(const double pz_in) {pz = pz_in;}

  //Four momentum functions ie dot product, addition etc.
  friend std::vector<double> operator+(const FourMomentum& four_momentum_1, const FourMomentum& four_momentum_2);
  friend std::vector<double> operator-(const FourMomentum& four_momentum_1, const FourMomentum& four_momentum_2);
  friend double dotProduct(const FourMomentum& four_momentum_1, const FourMomentum& four_momentum_2);

  //return invariant mass
  double reutrn_invariant_mass();
};

#endif