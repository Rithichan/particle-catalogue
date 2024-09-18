// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This file includes the implementations of the functions for all quark classes
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<random>
#include<stdexcept>
#include"particle.h"
#include"quark.h"

//---------------------
//Quark Class Functions
//---------------------

Quark::Quark(double energy_in, double px_in, double py_in, double pz_in, bool antiparticle_bool, ColourCharge colour_in, QuarkType type_in)
 : Particle(energy_in,px_in,py_in,pz_in,type_to_string(type_in),mass_of_type(type_in),charge_of_type(type_in),antiparticle_bool)
{
  spin = 0.5;
  quark_type = type_in;

  if(antiparticle_bool == false)
  {
    baryon_number = 0.33;

    //Consistentcy Check for Quark Colour
    if(colour_in == ColourCharge::Blue or colour_in == ColourCharge::Red or colour_in == ColourCharge::Green)
    {
      colour = colour_in;
    }
    else
    {
      colour = colour_swap(colour_in);
    }
  }
  else
  {
    baryon_number = -0.33;

    //Same here check for quark colour
    if(colour_in == ColourCharge::Blue or colour_in == ColourCharge::Red or colour_in == ColourCharge::Green)
    {
      colour = colour_swap(colour_in);
    }
    else
    {
      colour = colour_in;
    }
  }
}


void Quark::print_data()
{
  Particle::print_data();
  std::cout<<"Particle is a Quark with Baryon Number: "<<baryon_number<<std::endl;
  std::cout<<"--"<<type_to_string(quark_type)<<" Extra Information--"<<std::endl;
  std::cout<<"Colour: "<<colour_to_string(colour)<<std::endl;
}

std::string Quark::colour_to_string(ColourCharge colour_in)
{
  switch (colour_in) 
  {
    case ColourCharge::Red: 
      return "Red";
    case ColourCharge::Blue:
      return "Blue";
    case ColourCharge::Green:
      return "Green";
    case ColourCharge::AntiRed: 
      return "AntiRed";
    case ColourCharge::AntiBlue:
      return "AntiBlue";
    case ColourCharge::AntiGreen:
      return "AntiGreen";
    default:
      return "No colour";
  }
}

std::string Quark::type_to_string(QuarkType type_in)
{
  switch (type_in) 
  {
    case QuarkType::Up: 
      return "Up quark";
    case QuarkType::Down: 
      return "Down quark";
    case QuarkType::Charm: 
      return "Charm quark";
    case QuarkType::Strange: 
      return "Strange quark";
    case QuarkType::Top: 
      return "Top quark";
    case QuarkType::Bottom: 
      return "Bottom quark";
    default:
      return "None";
  }
}

double Quark::mass_of_type(QuarkType type_in)
{
  switch (type_in) 
  {
    case QuarkType::Up:
      return 2.3;  
    case QuarkType::Down:
      return 4.8;  
    case QuarkType::Charm:
      return 1275; 
    case QuarkType::Strange:
      return 95;   
    case QuarkType::Top:
      return 173100; 
    case QuarkType::Bottom:
      return 4180; 
    default:
      return 0;
  }
}

double Quark::charge_of_type(QuarkType type_in)
{
  if(type_in == QuarkType::Up or type_in == QuarkType::Charm or type_in == QuarkType::Top)
  {
    return 0.66;
    }
  else
  {
    return -0.33;
  }
}

ColourCharge Quark::colour_swap(ColourCharge colour_in)
{
  switch (colour_in) 
  {
    case ColourCharge::Red: 
      return ColourCharge::AntiRed;
    case ColourCharge::Blue:
      return ColourCharge::AntiBlue;
    case ColourCharge::Green:
      return ColourCharge::AntiGreen;
    case ColourCharge::AntiRed: 
      return ColourCharge::Red;
    case ColourCharge::AntiBlue:
      return ColourCharge::Blue;
    case ColourCharge::AntiGreen:
      return ColourCharge::Green;
    default:
      return ColourCharge::Red;
  }
}