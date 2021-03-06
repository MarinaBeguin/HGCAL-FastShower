
#include <iostream>
#ifdef STANDALONE
#include "Parameters.h"
#else
#include "HGCalSimulation/FastShower/interface/Parameters.h"
#endif


using namespace boost;

Parameters::General::
General():
  events(0),
  part_type(0),
  debug(false),
  output_file("")
{
}

const std::map<std::string, Parameters::Geometry::Type>
Parameters::Geometry::type_map_ = {
  {"Hexagons", Parameters::Geometry::Type::Hexagons},
  {"Triangles", Parameters::Geometry::Type::Triangles},
  {"External", Parameters::Geometry::Type::External}
};
const std::map<std::string, Parameters::Generation::GenType>
Parameters::Generation::calib_type_map_ = {
  {"External", Parameters::Generation::GenType::External},
  {"Personnal", Parameters::Generation::GenType::Personnal},
};

Parameters::Geometry::
Geometry():
  type(Type::Undefined),
  layer(-1),
  layers_z(0),
  small_cell_side(0),
  large_cell_side(0),
  EE_limit_layer(0),
  FH_limit_layer(0),
  BH_limit_layer(0),
  limit_first_zone(0),
  limit_second_zone(0),
  eta_min(0.),
  eta_max(0.),
  phi_min(0.),
  phi_max(0.),
  file("")
{
}

Parameters::Shower::
Shower():
  moliere_radius(0.),
  transverse_parameters_electro(),
  transverse_parameters_hadro(),
  map_layers_energy(),
  map_alpha(),
  a_halo(0.),
  b_halo(0.),
  a_core(0.),
  b_core(0.)
{
}

Parameters::Generation::
Generation():
  gentype(GenType::Undefined),
  fluctuation(false),
  fluctuation_energy(false),
  gun_type(""),
  energy(0.),
  E_range_min(0.),
  E_range_max(0.),
  sampling(0.),
  number_of_hits_per_gev(0),
  noise(false),
  noise_sigma(0.),
  incident_eta(0.),
  incident_phi(0.),
  eta_fluctuation(false),
  phi_fluctuation(false),
  eta_range_max(0.),
  eta_range_min(0.),
  phi_range_max(0.),
  phi_range_min(0.),
  calib_file("")
{
}

Parameters::Display::
Display():
  events(0),
  layer(0)
{
}

Parameters::
Parameters()
{
}

void
Parameters::
read(const std::string& file)
{
  Py_Initialize();
  python::object main_module = python::import("__main__");
  python::dict main_namespace = python::extract<python::dict>(main_module.attr("__dict__"));
  python::object py_module = python::exec_file(file.c_str(), main_namespace);
  fillGeneral(main_namespace);
  fillGeometry(main_namespace);
  fillShower(main_namespace);
  fillGeneration(main_namespace);
  fillDisplay(main_namespace);
}

void
Parameters::
fillGeneral(const python::dict& dict)
{
  general_.events = python::extract<int>(dict["events"]);
  python::list part_type = python::extract<python::list>(dict["part_type"]);
  general_.part_type = toStdVector<int>(part_type);
  general_.debug = python::extract<bool>(dict["debug"]);
  general_.output_file = python::extract<std::string>(dict["output_file"]);
}

void
Parameters::
fillGeometry(const python::dict& dict)
{
  // Read parameters common to all geometry types
  std::string type = python::extract<std::string>(dict["geometry_type"]);
  // FIXME: not needed, map::at will throw an exception if not defined
  if(Geometry::type_map_.find(type)==Geometry::type_map_.end())
    throw std::string("Unknown type of geometry");
  geometry_.type = Geometry::type_map_.at(type);
  geometry_.layer = python::extract<int>(dict["geometry_layer"]);

  python::list layers_z = python::extract<python::list>(dict["geometry_layers_z"]);
  geometry_.layers_z = toStdVector<double>(layers_z);
  // Read parameters for internal geometries (infinite hexagons or triangles)
  if(geometry_.type!=Geometry::Type::External) {
    geometry_.small_cell_side = python::extract<double>(dict["geometry_small_cell_side"]);
    geometry_.large_cell_side = python::extract<double>(dict["geometry_large_cell_side"]);
    geometry_.EE_limit_layer = python::extract<int>(dict["geometry_EE_limit_layer"]);
    geometry_.FH_limit_layer = python::extract<int>(dict["geometry_FH_limit_layer"]);
    geometry_.BH_limit_layer = python::extract<int>(dict["geometry_BH_limit_layer"]);
    geometry_.limit_first_zone = python::extract<double>(dict["geometry_limit_first_zone"]);
    geometry_.limit_second_zone = python::extract<double>(dict["geometry_limit_second_zone"]);
    geometry_.eta_min = python::extract<double>(dict["geometry_eta_min"]);
    geometry_.eta_max = python::extract<double>(dict["geometry_eta_max"]);
    geometry_.phi_min = python::extract<double>(dict["geometry_phi_min"]);
    geometry_.phi_max = python::extract<double>(dict["geometry_phi_max"]);
  } else {
    geometry_.file = python::extract<std::string>(dict["geometry_file"]);
  }
}

void
Parameters::
fillShower(const python::dict& dict)
{
  shower_.moliere_radius = python::extract<double>(dict["shower_moliere_radius"]);

  python::dict transverse_parameters_electro = python::extract<python::dict>(dict["shower_transverse_parameters_electro"]);
  shower_.transverse_parameters_electro = toStdMap<std::string,double>(transverse_parameters_electro);
  python::dict transverse_parameters_hadro = python::extract<python::dict>(dict["shower_transverse_parameters_hadro"]);
  shower_.transverse_parameters_hadro = toStdMap<std::string,double>(transverse_parameters_hadro);

  python::dict shower_layers_energy = python::extract<python::dict>(dict["shower_layers_energy"]);
  shower_.map_layers_energy = toStdMapVector<int,double>(shower_layers_energy);
  python::dict alpha = python::extract<python::dict>(dict["shower_alpha"]);
  shower_.map_alpha = toStdMapVector<int,double>(alpha);

  shower_.a_halo = python::extract<double>(dict["a_halo_hadro"]);
  shower_.b_halo = python::extract<double>(dict["b_halo_hadro"]);
  shower_.a_core = python::extract<double>(dict["a_core_hadro"]);
  shower_.b_core = python::extract<double>(dict["b_core_hadro"]);
}

void
Parameters::
fillGeneration(const python::dict& dict)
{
  generation_.fluctuation = python::extract<bool>(dict["generation_fluctuation"]);
  generation_.fluctuation_energy = python::extract<bool>(dict["generation_energy_fluctuation"]);
  generation_.gun_type = python::extract<std::string>(dict["generation_gun_type"]);

  generation_.energy = python::extract<double>(dict["generation_energy"]);
  generation_.E_range_min = python::extract<double>(dict["generation_energy_range_min"]);
  generation_.E_range_max = python::extract<double>(dict["generation_energy_range_max"]);

  generation_.number_of_hits_per_gev = python::extract<int>(dict["generation_number_of_hits_per_gev"]);

  std::string gentype = python::extract<std::string>(dict["generation_calib_type"]);
  if(Generation::calib_type_map_.find(gentype)==Generation::calib_type_map_.end())
    throw std::string("Unknown type of calibration");
  generation_.gentype = Generation::calib_type_map_.at(gentype);

  generation_.sampling = python::extract<double>(dict["generation_mip"]);

  generation_.noise = python::extract<bool>(dict["generation_noise"]);
  generation_.noise_sigma = python::extract<double>(dict["generation_noise_sigma"]);
  generation_.calib_file = python::extract<std::string>(dict["generation_file"]);

  generation_.incident_eta = python::extract<double>(dict["generation_incident_eta"]);
  generation_.incident_phi = python::extract<double>(dict["generation_incident_phi"]);
  generation_.eta_fluctuation = python::extract<bool>(dict["generation_eta_fluctuation"]);
  generation_.phi_fluctuation = python::extract<bool>(dict["generation_phi_fluctuation"]);
  generation_.eta_range_min = python::extract<double>(dict["generation_eta_range_min"]);
  generation_.eta_range_max = python::extract<double>(dict["generation_eta_range_max"]);
  generation_.phi_range_min = python::extract<double>(dict["generation_phi_range_min"]);
  generation_.phi_range_max = python::extract<double>(dict["generation_phi_range_max"]);
}

void
Parameters::
fillDisplay(const python::dict& dict)
{
  display_.events = python::extract<int>(dict["display_events"]);
  display_.layer = python::extract<int>(dict["display_layer"]);
}



void
Parameters::
print() const
{
  std::cout<<"|Configuration parameters\n";
  std::cout<<"|- General\n";
  std::cout<<"|-- Events = "<<general_.events<<"\n";
  std::cout<<"|-- Debug = "<<general_.debug<<"\n";
  std::cout<<"|-- Output file = "<<general_.output_file<<"\n";
  std::cout<<"|- Geometry\n";
  std::cout<<"|-- Type = "<<static_cast<std::underlying_type<Geometry::Type>::type>(geometry_.type)<<"\n";
  std::cout<<"|-- SideLength small= "<<geometry_.small_cell_side<<"\n";
  std::cout<<"|-- SideLength large= "<<geometry_.large_cell_side<<"\n";
  std::cout<<"|-- Limit of the fine cells= "<<geometry_.limit_first_zone<<"\n";
  std::cout<<"|-- Limit of coarse cells= "<<geometry_.limit_second_zone<<"\n";
  std::cout<<"|-- eta|phi window = ("<<geometry_.eta_min<<","<<geometry_.eta_max<<"|"<<geometry_.phi_min<<","<<geometry_.phi_max<<")\n";
  std::cout<<"|-- Layer = "<<geometry_.layer + 1<<"\n";
  std::cout<<"|-- Layers z = [";
  for(const auto& z : geometry_.layers_z) {
    std::cout<<z<<" ";
  }
  std::cout<<"]\n";
  std::cout<<"|-- File = "<<geometry_.file<<"\n";
  std::cout<<"|- Shower\n";
  std::cout<<"|-- Moliere radius = "<<shower_.moliere_radius<<"\n";
  std::cout<<"]\n";
  std::cout<<"|-- Transverse parameters electro = [";
  for(const auto& name_value : shower_.transverse_parameters_electro) {
    std::cout<<name_value.first<<"("<<name_value.second<<") ";
  }
  std::cout<<"]\n";
  std::cout<<"|-- Transverse parameters hadro = [";
  for(const auto& name_value : shower_.transverse_parameters_hadro) {
    std::cout<<name_value.first<<"("<<name_value.second<<") ";
  }
  std::cout<<"|- Generation\n";
  std::cout<<"|-- Energy = "<<generation_.energy<<"\n";
  std::cout<<"|-- Fluctuation = "<<generation_.fluctuation<<"\n";
  std::cout<<"|-- Hits/GeV = "<<generation_.number_of_hits_per_gev<<"\n";
  std::cout<<"|-- Mip energy = ["<< generation_.sampling<<"\n";
  std::cout<<"|-- Noise = "<<generation_.noise<<"\n";
  std::cout<<"|-- Noise sigma = ["<< generation_.noise_sigma <<"\n";
  std::cout<<"|-- Direction = ("<<generation_.incident_eta<<" "<<generation_.incident_phi<<")\n";
  std::cout<<"|-- Eta fluctuation = "<<generation_.eta_fluctuation<<"  range = ("<<generation_.eta_range_min<<","<<generation_.eta_range_max<<")"<<"\n";
  std::cout<<"|-- Phi fluctuation = "<<generation_.phi_fluctuation<<"  range = ("<<generation_.phi_range_min<<","<<generation_.phi_range_max<<")"<<"\n";
  std::cout<<"|- Display\n";
  std::cout<<"|-- Events = "<<display_.events<<"\n";
}