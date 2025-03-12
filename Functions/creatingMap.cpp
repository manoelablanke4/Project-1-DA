// Created by cosme on 10/03/2025.
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "/Users/cosme/CLionProjects/Project-1-DA/data_structures/Graph.h"
typedef struct {
std::string name;
int id;
std::string code;
bool parking;
}Location;

bool operator==(const Location& a,const Location& other)  {
  return a.id == other.id;
}

Graph<Location> createMap(){
Graph<Location> map;
std::ifstream LocationsFile("/Users/cosme/CLionProjects/Project-1-DA/for_Students/Locations.csv");

if(!LocationsFile.is_open()){
  std::cerr << "Error opening file" << std::endl;
  exit(1);
}

std::unordered_map<std::string, Location> locations;

std::string line;
std::getline(LocationsFile, line);

while(std::getline(LocationsFile, line)){
  std::istringstream iss(line);
  std::string name,id,code, parking;
  if(std::getline(iss, name, ',') && std::getline(iss, id, ',') && std::getline(iss, code,',') && std::getline(iss, parking,',')){
    Location location;
    location.name = name;
    location.id = std::stoi(id);
    location.code = code;
    location.parking = (parking == "1");
    map.addVertex(location);
    locations[code]= location;
  }
}
  LocationsFile.close();

  std::ifstream DistancesFile("/Users/cosme/CLionProjects/Project-1-DA/for_Students/Distances.csv");

  if(!DistancesFile.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    exit(1);
  }

  std::getline(DistancesFile, line);
  while(std::getline(DistancesFile, line)) {
    std::istringstream iss(line);
    std::string source,destination,driving,walking;
    if (std::getline(iss, source, ',') && std::getline(iss, destination, ',') && std::getline(iss, driving,',') && std::getline(iss, walking,',')) {
      double d,w;
      Location s,de;
      s=locations[source];
      de=locations[destination];
      if (driving=="X") {
        d=-1;
      }
      else {
        d=std::stod(driving);
      }
      w=stod(walking);
      map.addBidirectionalEdge(s,de,d,w);
    }
  }

  DistancesFile.close();


return map;
}

