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
 * @file Texture.h
 * @author Richtsfeld
 * @date October 2012
 * @version 0.1
 * @brief Calculate texture feature to compare surface texture.
 */

#ifndef FITSIZE
#define FIZSIZE

#include <vector>
#include <stdio.h>
#include "SurfaceModel.hpp"

namespace surface
{


class FitSize
{
public:
  
protected:

private:

  bool have_cloud;
  bool have_surfaces;
  
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr pcl_cloud;                     ///< Input cloud
  surface::View view;                                                   ///< Surface models
  void sortLength(float x, float y, float z, float& l1, float& l2, float& l3);

public:
  FitSize();
  ~FitSize();
  
  /** Set input point cloud **/
  void setInputCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &_pcl_cloud);


  /** Set input surface patches **/
  void setSurfaceModels(surface::View & _view);

  /** Compute if size fit **/
  void compute(std::map<unsigned, int>& sizeFit);
  
  int fitCubeSize(std::vector<int> ind);
  
};

/*************************** INLINE METHODES **************************/
}

#endif

