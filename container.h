// PHYS 30762 Programming in C++
// Rithichan Chhorn 06/05/2024
// Final Project: Particle Catalogue
// This is the header file for the particle container
#ifndef CONTAINER_H
#define CONTAINER_H

#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include"particle.h"
#include"quark.h"
#include"lepton.h"
#include"boson.h"

class Container
{
private:
  std::unordered_map<std::string, std::shared_ptr<Particle>> map_of_particles;
  std::unordered_map<std::string, std::shared_ptr<Lepton>> map_of_leptons; 
  std::unordered_map<std::string, std::shared_ptr<Quark>> map_of_quarks;
  std::unordered_map<std::string, std::shared_ptr<Boson>> map_of_bosons;
  std::unordered_map<std::string, std::shared_ptr<Particle>> map_of_decay_products;
  int number_of_entries{0};
public:
    //Some utility functions
    //add remove functions
    void add(const std::string& key, std::shared_ptr<Particle> new_particle_ptr);
    bool remove(const std::string& key);

    //get particle
    std::shared_ptr<Particle> get(const std::string& key);

    //check for existence
    bool exists(const std::string& key);

    //display functions
    void display_all();
    void display_specific(const std::string& key); //displays specific particles
    void display_type(const std::string type); //displays particles of the same type
    void display_decay_products();

    //number of total particles
    void set_number_of_particles() {number_of_entries = map_of_particles.size();}
    int get_number_of_particles() const {return number_of_entries;}
    int get_number_of_particles_per_type(std::string type);
    int get_number_of_decay_products() const {return map_of_decay_products.size();}

    //sum four momentum of all particles
    std::vector<double> sum_of_four_momenta();

    //adds decay products to the container
    void add_decay_products(std::vector<std::shared_ptr<Particle>> decay_products);

    //user interface to allow for streamlined and easy access to catalouge
    void user_interface();
};

#endif