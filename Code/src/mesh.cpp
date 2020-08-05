/// @file     mesh.cpp
/// @author   Erik ZORZIN
/// @date     27JAN2020
/// @brief    Declaration of a "mesh" class.

#include "mesh.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// "mesh" class /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::mesh()
{

}

void mesh::init (
                 neutrino*   loc_baseline,                                                          ///< Neutrino baseline.
                 std::string loc_file_name                                                          ///< GMSH .msh file name.
                )
{
  baseline  = loc_baseline;                                                                         // Getting Neutrino baseline...
  baseline->action ("initializing GMSH...");                                                        // Printing message...
  gmsh::initialize ();                                                                              // Initializing GMSH...
  gmsh::model::add ("neutrino");                                                                    // Adding a new GMSH model (named "neutrino")...
  gmsh::option::setNumber ("General.Terminal", 1);                                                  // Allowing GMSH to write on stdout...
  gmsh::open (loc_file_name.c_str ());                                                              // Opening GMSH model from file...

  gmsh::model::getEntities (entities);                                                              // Getting all entities...
  nodes     = 0;                                                                                    // Resetting nodes number...

  for(i = 0; i < entities.size (); i++)
  {
    dim    = entities[i].first;                                                                     // Getting entity dimension...
    tag    = entities[i].second;                                                                    // Getting entity tag...
    gmsh::model::mesh::getNodes (nodeTags, nodeCoords, nodeParams, dim, tag);                       // Getting entity mesh nodes...

    nodes += nodeTags.size ();                                                                      // Accumulating nodes number...
  }

  simplexes = 0;                                                                                    // Resetting simplexes number...
  complexes = 0;
  strides   = 0;

  gmsh::model::mesh::getElements (elemTypes, elemTags, elemNodeTags, dim, tag);                     // Getting entity mesh elements...

  for(i = 0; i < elemTypes.size (); i++)
  {
    // Getting element properties:
    gmsh::model::mesh::getElementProperties (
                                             elemTypes[i],
                                             elemName,
                                             d,
                                             order,
                                             numNodes,
                                             param,
                                             numPrimaryNodes
                                            );

    strides++;

    for(j = 0; j < elemTags[i].size (); j++)
    {
      simplexes++;                                                                                  // Incrementing Neutrino simplex index...
    }
  }

  baseline->done ();                                                                                // Printing message...
}

void mesh::read_msh (
                     float4G* loc_node,                                                             // GMSH node coordinates.
                     int1*    loc_simplex,                                                          // GMSH simplex: node index list.
                     int1*    loc_simplex_stride,                                                   // GMSH simplex: strides.
                     int1*    loc_complex,                                                          // GMSH complex: simplex index list.
                     int1*    loc_complex_stride                                                    // GMSH complex: strides.
                    )
{
  gmsh::model::getEntities (entities);                                                              // Getting all entities...
  i_node = 0;                                                                                       // Resetting Neutrino node index...

  for(i = 0; i < entities.size (); i++)
  {
    dim = entities[i].first;                                                                        // Getting entity dimension...
    tag = entities[i].second;                                                                       // Getting entity tag...
    gmsh::model::mesh::getNodes (nodeTags, nodeCoords, nodeParams, dim, tag);                       // Getting entity mesh nodes...

    for(j = 0; j < nodeTags.size (); j++)
    {
      loc_node->data[k].x = (cl_float)nodeCoords[3*j + 0];                                          // Setting "x" coordinate...
      loc_node->data[k].y = (cl_float)nodeCoords[3*j + 1];                                          // Setting "y" coordinate...
      loc_node->data[k].z = (cl_float)nodeCoords[3*j + 2];                                          // Setting "z" coordinate...
      loc_node->data[k].w = (cl_float)1.0;                                                          // Setting "w" coordinate...

      nodeList.push_back (nodeTags[j]);                                                             // Filling full node array...

      std::cout << "index: "
                << i_node
                << " node tag: "
                << nodeTags[j]
                << " --> coordinates: "
                << nodeCoords[3*j + 0]
                << ", "
                << nodeCoords[3*j + 1]
                << ", "
                << nodeCoords[3*j + 2]
                << std::endl;

      i_node++;                                                                                     // Incrementing Neutrino node index...
    }

    gmsh::model::mesh::getElements (elemTypes, elemTags, elemNodeTags, dim, tag);                   // Getting entity mesh elements...
    i_simplex = 0;                                                                                  // Resetting Neutrino simplex index...

    for(j = 0; j < elemTypes.size (); j++)
    {
      // Getting element properties:
      gmsh::model::mesh::getElementProperties (
                                               elemTypes[j],
                                               elemName,
                                               d,
                                               order,
                                               numNodes,
                                               param,
                                               numPrimaryNodes
                                              );

      for(k = 0; k < elemTags[j].size (); k++)
      {
        loc_simplex_stride->data[i_simplex] = numNodes;                                             // Setting simplex data stride...

        std::cout << "simplex: "
                  << elemTags[j][k]
                  << " --> nodes: ";

        for(n = 0; n < numNodes; n++)
        {
          std::cout << elemNodeTags[j][numNodes*k + n] << " ";

          // Finding the index corresponding to each node tag in the full node array:
          loc_simplex->data[i_simplex] = std::distance (
                                                        nodeList.begin (),
                                                        std::find (
                                                                   nodeList.begin (),
                                                                   nodeList.end (),
                                                                   elemNodeTags[j][numNodes*k + n]
                                                                  )
                                                       );
          i_simplex++;                                                                              // Incrementing Neutrino simplex index...
        }

        std::cout << std::endl;
      }
    }
  }

  nodeList.clear ();                                                                                // Clearing full node array...
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DESTRUCTOR ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
mesh::~mesh()
{
  gmsh::finalize ();                                                                                // Finalizing GMSH...
}
