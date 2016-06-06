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

#include "FitSize.h"

namespace surface
{

/************************************************************************************
 * Constructor/Destructor
 */

FitSize::FitSize()
{
  have_cloud = false;
  have_surfaces = false;
}

FitSize::~FitSize()
{
}

// ================================= Private functions ================================= //

// ================================= Public functions ================================= //


void FitSize::setInputCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr & _pcl_cloud)
{
  pcl_cloud = _pcl_cloud;
  have_cloud = true;
}


void FitSize::setSurfaceModels(surface::View & _view)
{
  view = _view;
  have_surfaces = true;
}

void FitSize::compute(std::map<unsigned, int>& sizeFit) {
//  std::map<unsigned, int> sizeFit;
  for (unsigned i=0; i < view.surfaces.size(); i++) {
    if (view.surfaces[i]->indices.size() < 200) {
      sizeFit.insert(std::pair<unsigned, int>(i, 0));
      continue;
    }
    float xmin = 100, xmax = -100, ymin = 100, ymax = -100, zmin = 100, zmax = -100;
//    std::cout << view.surfaces[i]->indices.size() << "\t";
    for (unsigned j = 0; j < view.surfaces[i]->indices.size(); j++) {
      pcl::PointXYZRGB& p = pcl_cloud->points[view.surfaces[i]->indices[j]];
      xmin = std::min(xmin, p.x);
      xmax = std::max(xmax, p.x);
      ymin = std::min(ymin, p.y);
      ymax = std::max(ymax, p.y);
      zmin = std::min(zmin, p.z);
      zmax = std::max(zmax, p.z);
    }
 //   std::cout << xmax - xmin << "\t" << ymax - ymin << "\t"  << zmax - zmin << "\n"; 
    if(xmax - xmin > 1 || ymax - ymin > 1 || zmax - zmin > 1) {
      sizeFit.insert(std::pair<unsigned, int>(i, 0));
    } else {
      sizeFit.insert(std::pair<unsigned, int>(i, 1));
    }
    
  }  
}


}





