/**
 *  Copyright (C) 2012  
 *    Andreas Richtsfeld, Johann Prankl, Thomas Mörwald
 *    Automation and Control Institute
 *    Vienna University of Technology
 *    Gusshausstraße 25-29
 *    1170 Vienn, Austria
 *    ari(at)acin.tuwien.ac.at
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/
 */

/**
 * @file Texture.cpp
 * @author Richtsfeld
 * @date October 2012
 * @version 0.1
 * @brief Calculate texture feature to compare surface texture.
 */

#include "Centroid.h"

namespace surface
{

/************************************************************************************
 * Constructor/Destructor
 */

Centroid::Centroid()
{
  have_cloud = false;
  have_surfaces = false;
}

Centroid::~Centroid()
{
}

// ================================= Private functions ================================= //

// ================================= Public functions ================================= //


void Centroid::setInputCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr & _pcl_cloud)
{
  pcl_cloud = _pcl_cloud;
  have_cloud = true;
}


void Centroid::setSurfaceModels(surface::View & _view)
{
  view = _view;
  have_surfaces = true;
}

void Centroid::compute(std::map<unsigned,  pcl::PointXYZ>& centroid) {
  for (unsigned i=0; i < view.surfaces.size(); i++) {
    float x = 0, y = 0, z = 0;
    for (unsigned j = 0; j < view.surfaces[i]->indices.size(); j++) {
      pcl::PointXYZRGB& p = pcl_cloud->points[view.surfaces[i]->indices[j]];
      x += p.x;
      y += p.y;
      z += p.z;
    }
    x /= view.surfaces[i]->indices.size();
    y /= view.surfaces[i]->indices.size();
    z /= view.surfaces[i]->indices.size();
    pcl::PointXYZ tt(x,y,z);
    centroid.insert(std::pair<unsigned, pcl::PointXYZ>(i, tt));
  }
}


}





