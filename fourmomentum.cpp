// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// Functions of FourMomentum Class
// Includes dotproduct, overloaded + and - operators, return rest mass
// consistentcy checks for energy and momentum
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<stdexcept>
#include<fstream>
#include<memory>
#include<exception>
#include"particle.h"
#include"fourmomentum.h"

std::ofstream logFile("error.log");

void FourMomentum::set_energy(const double energy_in, const double px_in, const double py_in, const double pz_in, const double rest_mass_in)
{
  try
  {
    if(energy_in < 0)
    {
      throw std::invalid_argument("Energy must not be negative.");
    }
    else if(std::abs(energy_in*energy_in - (rest_mass_in*rest_mass_in + px_in*px_in + py_in*py_in + pz_in*pz_in)) > 0.1) //some tolerance for floating point arithemetic
    {
      throw std::invalid_argument("Energy must obey invariant mass equation. Default value assumed.");
    }
    else
    {
      energy = energy_in;
    }
  }
  catch(const std::exception& e)
  {
    logFile<<"Error with FourMomentum"<<"("<<energy_in<<", "<<px_in<<", "<<py_in<<", "<<pz_in<<")"<<std::endl;
    energy = sqrt(px_in*px_in + py_in*py_in + pz_in*pz_in + rest_mass_in*rest_mass_in);
    std::cerr<<e.what()<<std::endl;
  }
}

//Parameterised constructor
FourMomentum::FourMomentum(double energy_in, double px_in, double py_in, double pz_in, double rest_mass_in)
{
  set_energy(energy_in, px_in, py_in, pz_in, rest_mass_in);
  set_px(px_in);
  set_py(py_in);
  set_pz(pz_in);
}

//Copy constructor
FourMomentum::FourMomentum(const FourMomentum& copied_four_momentum)
{
  energy = copied_four_momentum.get_energy();
  px = copied_four_momentum.get_px();
  py = copied_four_momentum.get_py();
  pz = copied_four_momentum.get_pz();
}

//Assignment operator
FourMomentum& FourMomentum::operator=(const FourMomentum& copied_four_momentum)
{
  if(this != &copied_four_momentum) //avoids self assignment
  {
    energy = copied_four_momentum.get_energy();
    px = copied_four_momentum.get_px();
    py = copied_four_momentum.get_py();
    pz = copied_four_momentum.get_pz();
  }
  else
  {
    throw("Error: Self-assignment");
  }
  return *this;
}

//Move constructor
FourMomentum::FourMomentum(FourMomentum&& moved_four_momentum): energy{moved_four_momentum.energy}, px{moved_four_momentum.px}, py{moved_four_momentum.py}, pz{moved_four_momentum.pz}
{
  moved_four_momentum.energy = 0;
  moved_four_momentum.px  = 0;
  moved_four_momentum.py = 0;
  moved_four_momentum.pz = 0;
}

//Move assignment operator
FourMomentum& FourMomentum::operator=(FourMomentum&& moved_four_momentum)
{
  if(this != &moved_four_momentum) //avoids self assignment
  {
    energy = moved_four_momentum.get_energy();
    px = moved_four_momentum.get_px();
    py = moved_four_momentum.get_py();
    pz = moved_four_momentum.get_pz();
    //for safe deletion of the moved four momentum
    moved_four_momentum.energy = 0;
    moved_four_momentum.px  = 0;
    moved_four_momentum.py = 0;
    moved_four_momentum.pz = 0;
  }
  else
  {
    throw("Error: Self-assignment");
  }
  return *this;
}

//4 momentum addition function
std::vector<double> operator+(const FourMomentum& four_momentum_1, const FourMomentum& four_momentum_2)
{
    std::vector<double> result;
    result.push_back(four_momentum_1.get_energy() + four_momentum_2.get_energy());
    result.push_back(four_momentum_1.get_px() + four_momentum_2.get_px());
    result.push_back(four_momentum_1.get_py() + four_momentum_2.get_py());
    result.push_back(four_momentum_1.get_pz() + four_momentum_2.get_pz());
    return result;
}

//4 momentum addition function
std::vector<double> operator-(const FourMomentum& four_momentum_1, const FourMomentum& four_momentum_2)
{
    std::vector<double> result;
    result.push_back(four_momentum_1.get_energy() - four_momentum_2.get_energy());
    result.push_back(four_momentum_1.get_px() - four_momentum_2.get_px());
    result.push_back(four_momentum_1.get_py() - four_momentum_2.get_py());
    result.push_back(four_momentum_1.get_pz() - four_momentum_2.get_pz());
    return result;
}

//Dot product function
double dotProduct(const FourMomentum& four_momentum_1, const FourMomentum& four_momentum_2)
{
  return four_momentum_1.get_energy()*four_momentum_2.get_energy()
  - four_momentum_1.get_px()*four_momentum_2.get_px()
  - four_momentum_1.get_py()*four_momentum_2.get_py()
  - four_momentum_1.get_pz()*four_momentum_2.get_pz();
}

double FourMomentum::reutrn_invariant_mass()
{
  return this->energy*this->energy - (this->px*this->px + this->py*this->py + this->pz*this->pz);
}