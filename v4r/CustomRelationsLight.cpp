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
 * @file StructuralRelationsLight.cpp
 * @author Richtsfeld
 * @date December 2012
 * @version 0.1
 * @brief Calculate patch relations for structural level: Efficient version without fourier and gabor filter.
 */

#include "CustomRelationsLight.h"

namespace surface
{


/************************************************************************************
 * Constructor/Destructor
 */

CustomRelationsLight::CustomRelationsLight()
{
  have_patches = false;
  have_input_cloud = false;
}

CustomRelationsLight::~CustomRelationsLight()
{
}

// ================================= Private functions ================================= //

/**
 * computeNeighbors 
 */
void CustomRelationsLight::computeNeighbors()
{
  // double z_max = 0.03*0.03;
  double z_max = 0.01;

  cv::Mat_<int> patches;
  if(view->havePatchImage) {
    patches = cv::Mat_<int>(pcl_cloud->height, pcl_cloud->width);
    view->patchImage.copyTo(patches);
  }
  else {
    patches = cv::Mat_<int>(pcl_cloud->height, pcl_cloud->width);
    patches.setTo(-1);
    for(unsigned i=0; i<view->surfaces.size(); i++)
      for(unsigned j=0; j<view->surfaces[i]->indices.size(); j++)
        patches.at<int>(view->surfaces[i]->indices[j] / pcl_cloud->width, view->surfaces[i]->indices[j] % pcl_cloud->width) = i;
    patches.copyTo(view->patchImage);
  }
  unsigned nr_patches = view->surfaces.size();


  bool nbgh_matrix3D[nr_patches][nr_patches];
  bool nbgh_matrix2D[nr_patches][nr_patches];
  for(unsigned i=0; i<nr_patches; i++)
    for(unsigned j=0; j<nr_patches; j++) {
      nbgh_matrix3D[i][j] = false;
      nbgh_matrix2D[i][j] = false;
    }
  
  for(int row=1; row<patches.rows; row++) { //1ms
    for(int col=1; col<patches.cols; col++) {
      if(patches.at<int>(row, col) != -1) {
        if(patches.at<int>(row-1, col) != -1) {
          if(patches.at<int>(row, col) != patches.at<int>(row-1, col)) {
            int pos_0 = row*pcl_cloud->width+col;
            int pos_1 = (row-1)*pcl_cloud->width+col;
            double dis = fabs(pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z);
            // double dis = (pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z)*(pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z)
            //   + (pcl_cloud->points[pos_0].x - pcl_cloud->points[pos_1].x)* (pcl_cloud->points[pos_0].x - pcl_cloud->points[pos_1].x)
            //   + (pcl_cloud->points[pos_0].y - pcl_cloud->points[pos_1].y)*(pcl_cloud->points[pos_0].y - pcl_cloud->points[pos_1].y);

            if( dis < z_max) {
              nbgh_matrix3D[patches.at<int>(row-1, col)][patches.at<int>(row, col)] = true;
              nbgh_matrix3D[patches.at<int>(row, col)][patches.at<int>(row-1, col)] = true;
            }
            nbgh_matrix2D[patches.at<int>(row-1, col)][patches.at<int>(row, col)] = true;
            nbgh_matrix2D[patches.at<int>(row, col)][patches.at<int>(row-1, col)] = true;
          }
        }
        if(patches.at<int>(row, col-1) != -1) {
          if(patches.at<int>(row, col) != patches.at<int>(row, col-1)) {
            int pos_0 = row*pcl_cloud->width+col;
            int pos_1 = row*pcl_cloud->width+col-1;
            double dis = fabs(pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z);
            // double dis = (pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z)*(pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z)
            //   + (pcl_cloud->points[pos_0].x - pcl_cloud->points[pos_1].x)* (pcl_cloud->points[pos_0].x - pcl_cloud->points[pos_1].x)
            //   + (pcl_cloud->points[pos_0].y - pcl_cloud->points[pos_1].y)*(pcl_cloud->points[pos_0].y - pcl_cloud->points[pos_1].y);

            if( dis < z_max) {
              nbgh_matrix3D[patches.at<int>(row, col-1)][patches.at<int>(row, col)] = true;
              nbgh_matrix3D[patches.at<int>(row, col)][patches.at<int>(row, col-1)] = true;
            }
            nbgh_matrix2D[patches.at<int>(row, col-1)][patches.at<int>(row, col)] = true;
            nbgh_matrix2D[patches.at<int>(row, col)][patches.at<int>(row, col-1)] = true;
          }
        }
        if(patches.at<int>(row-1, col-1) != -1) {
          if(patches.at<int>(row, col) != patches.at<int>(row-1, col-1)) {
            int pos_0 = row*pcl_cloud->width+col;
            int pos_1 = (row-1)*pcl_cloud->width+col-1;
            double dis = fabs(pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z);
            // double dis = (pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z)*(pcl_cloud->points[pos_0].z - pcl_cloud->points[pos_1].z)
            //   + (pcl_cloud->points[pos_0].x - pcl_cloud->points[pos_1].x)* (pcl_cloud->points[pos_0].x - pcl_cloud->points[pos_1].x)
            //   + (pcl_cloud->points[pos_0].y - pcl_cloud->points[pos_1].y)*(pcl_cloud->points[pos_0].y - pcl_cloud->points[pos_1].y);

            if( dis < z_max) {
              nbgh_matrix3D[patches.at<int>(row-1, col-1)][patches.at<int>(row, col)] = true;
              nbgh_matrix3D[patches.at<int>(row, col)][patches.at<int>(row-1, col-1)] = true;
            }
            nbgh_matrix2D[patches.at<int>(row-1, col-1)][patches.at<int>(row, col)] = true;
            nbgh_matrix2D[patches.at<int>(row, col)][patches.at<int>(row-1, col-1)] = true;
          }
        }
      }
    }
  }

  for(unsigned i=0; i<nr_patches; i++){
    view->surfaces[i]->neighbors2D.clear();
    view->surfaces[i]->neighbors2DNrPixel.clear();
    // for(unsigned j=i+1; j<nr_patches; j++)
    for(unsigned j=0; j<nr_patches; j++)
      if(nbgh_matrix2D[i][j]) {
        view->surfaces[i]->neighbors2D.push_back(j);
        view->surfaces[i]->neighbors2DNrPixel.push_back(0);
      }
  }
  
  for(unsigned i=0; i<nr_patches; i++){
    view->surfaces[i]->neighbors3D.clear();
    // for(unsigned j=i+1; j<nr_patches; j++) {
    for(unsigned j=0; j<nr_patches; j++) {  
      if(nbgh_matrix3D[i][j]) {
        view->surfaces[i]->neighbors3D.push_back(j);
      }
    }

  }


}

void CustomRelationsLight::ConvertPCLCloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud, 
                                                cv::Mat_<cv::Vec3b> &image)
{
  unsigned pcWidth = pcl_cloud->width;
  unsigned pcHeight = pcl_cloud->height;
  unsigned position = 0;
  
  image = cv::Mat_<cv::Vec3b>(pcHeight, pcWidth);

  for (unsigned row = 0; row < pcHeight; row++) {
    for (unsigned col = 0; col < pcWidth; col++) {
      cv::Vec3b &cvp = image.at<cv::Vec3b> (row, col);
      position = row * pcWidth + col;
      const pcl::PointXYZRGB &pt = pcl_cloud->points[position];
      cvp[2] = pt.r;
      cvp[1] = pt.g;
      cvp[0] = pt.b;
    }
  }
}

void CustomRelationsLight::computePatchNorm(std::map<unsigned, pcl::Normal>& PatchMeanN) {
  for (unsigned i=0; i < view->surfaces.size(); i++) {
    // float n_x = 0, n_y = 0, n_z = 0;
    // for (unsigned j = 0; j < view->surfaces[i]->indices.size(); j++) {
    //   pcl::Normal n = view->normals->at(view->surfaces[i]->indices[j] % pcl_cloud->width, view->surfaces[i]->indices[j] / pcl_cloud->width);
    //   n_x += n.normal_x;
    //   n_y += n.normal_y;
    //   n_z += n.normal_z;
    // }
    // float normalizeF = sqrt(n_x*n_x + n_y*n_y + n_z*n_z);
    // n_x /= normalizeF;
    // n_y /= normalizeF;
    // n_z /= normalizeF;
    // PatchMeanN.insert(std::pair<unsigned, pcl::Normal>(i, pcl::Normal(n_x, n_y, n_z)));

    PatchMeanN.insert(std::pair<unsigned, pcl::Normal>(i, pcl::Normal(view->surfaces[i]->coeffs[0], view->surfaces[i]->coeffs[1], view->surfaces[i]->coeffs[2])));
  }
}


// ================================= Public functions ================================= //

void CustomRelationsLight::setInputCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr & _pcl_cloud)
{
  pcl_cloud = _pcl_cloud;
  have_input_cloud = true;
}


void CustomRelationsLight::setView(surface::View *_view)
{
  view = _view;
  have_patches = true;
}

std::vector<unsigned>  CustomRelationsLight::computeRelations()
{
printf("StructuralRelationsLight::computeRelations start!\n");
std::vector<unsigned> activeSurface;

  if(!have_input_cloud || !have_patches || view->surfaces.size() > 800) {
    printf("[StructuralRelationsLight::computeRelations] Error: No input cloud and patches available.\n");
    return activeSurface;
  }

  view->relations.clear();
  
  cv::Mat_<cv::Vec3b> matImage;
  ConvertPCLCloud2Image(pcl_cloud, matImage);

  std::vector<ColorHistogram3D> hist3D;
  surface::Texture texture;

  relations.resize(view->surfaces.size());
  
  std::cout<< view->surfaces.size() << "\n";
  // std::cout<< view->normals->size() << "\n";
  std::map<unsigned, pcl::Normal> PatchMeanN;
  for (unsigned i=0; i < view->surfaces.size(); i++) {
    float n_x = 0, n_y = 0, n_z = 0;
    for (unsigned j = 0; j < view->surfaces[i]->indices.size(); j++) {
      pcl::Normal n = view->normals->at(view->surfaces[i]->indices[j] % pcl_cloud->width, view->surfaces[i]->indices[j] / pcl_cloud->width);
      n_x += n.normal_x;
      n_y += n.normal_y;
      n_z += n.normal_z;
    }
    float normalizeF = sqrt(n_x*n_x + n_y*n_y + n_z*n_z);
    n_x /= normalizeF;
    n_y /= normalizeF;
    n_z /= normalizeF;

    PatchMeanN.insert(std::pair<unsigned, pcl::Normal>(i, pcl::Normal(n_x, n_y, n_z)));
  }
  std::vector<int> surfaceState(view->surfaces.size(), 0);


  std::map<unsigned, pcl::PointXYZ> centroid;
  for (unsigned i=0; i < view->surfaces.size(); i++) {
    float x = 0, y = 0, z = 0;
    for (unsigned j = 0; j < view->surfaces[i]->indices.size(); j++) {
      pcl::PointXYZRGB& p = pcl_cloud->points[view->surfaces[i]->indices[j]];
      x += p.x;
      y += p.y;
      z += p.z;
    }
    x /= view->surfaces[i]->indices.size();
    y /= view->surfaces[i]->indices.size();
    z /= view->surfaces[i]->indices.size();
    pcl::PointXYZ tt(x,y,z);
    centroid.insert(std::pair<unsigned, pcl::PointXYZ>(i, tt));
  }  

#pragma omp parallel sections
  {

    #pragma omp section
    {
      computeNeighbors();
    }

    // #pragma omp section 
    // {
    //   for(unsigned i=0; i<view->surfaces.size(); i++) { 
    //     int nr_hist_bins = 4;
    //     double uvThreshold = 0.0f;
    //     hist3D.push_back(ColorHistogram3D(nr_hist_bins, uvThreshold));                               
    //     hist3D[i].setInputCloud(pcl_cloud);
    //     hist3D[i].setIndices(view->surfaces[i]->indices);
    //     hist3D[i].compute();
    //   }
    // }

    // #pragma omp section 
    // {
    //   texture.setInputImage(matImage);
    //   texture.setSurfaceModels(*view);
    //   texture.compute();
    // }      
      
    // #pragma omp section 
    // {
    //   boundary.setInputCloud(pcl_cloud);
    //   boundary.setView(view);
    // }

//     #pragma omp section 
//     {
//       surface::Relation rel;
//       rel.valid = false;
//       relations.clear();
//       for(unsigned i=0; i<view->surfaces.size(); i++)
//         for(unsigned j=0; j<view->surfaces.size(); j++)
//           relations[i].push_back(rel);
//     }
  } // end parallel sections
  
  
  // surface::Relation relations[view->surfaces.size()][view->surfaces.size()];
  
  
  // surface::Relation rel;
  // rel.valid = false;
  // for(unsigned i=0; i<view->surfaces.size(); i++) {
  //   for(unsigned j=i+1; j<view->surfaces.size(); j++) {
  //     relations[i][j] = rel;
  //   }
  // }
  

#pragma omp parallel for
  for(int i=0; i<(int)view->surfaces.size(); i++) {
    for(int j=0; j<(int)view->surfaces[i]->neighbors3D.size(); j++) {
      bool valid_relation = false;
      int p0 = i;
      int p1 = view->surfaces[i]->neighbors3D[j];
            
      if(p0 >= p1)
        continue;
      pcl::Normal n0 = PatchMeanN[p0];
      pcl::Normal n1 = PatchMeanN[p1];
      // double angle = acos(n0.normal_x * n1.normal_x + n0.normal_y * n1.normal_y + n0.normal_z * n1.normal_z);
      // std::cout << angle << "  ";
      double innpro = fabs(n0.normal_x * n1.normal_x + n0.normal_y * n1.normal_y + n0.normal_z * n1.normal_z);
      if (innpro >= 0.1) { continue; }
      
      pcl::PointXYZ c0 = centroid[p0];
      pcl::PointXYZ c1 = centroid[p1];
      double db = sqrt( (c0.x -c1.x)*(c0.x -c1.x) + (c0.y -c1.y)*(c0.y -c1.y) + (c0.z -c1.z)*(c0.z -c1.z));
      double alpha = 0.1;
      float x00 = c0.x + n0.normal_x * alpha, y00 = c0.y + n0.normal_y * alpha, z00 = c0.z + n0.normal_z * alpha;
      float x11 = c1.x + n1.normal_x * alpha, y11 = c1.y + n1.normal_y * alpha, z11 = c1.z + n1.normal_z * alpha;

      double da = sqrt( (x00 - x11)*(x00 - x11) + (y00 - y11)*(y00 - y11) + (z00 - z11)*(z00 - z11));
      if (db > da) { continue; }

      // std::cout << db << "\t" << da << std::endl;

      valid_relation = true;
      surfaceState[p0] = 1;
      surfaceState[p1] = 1;
      
      // if (std::find(activeSurface.begin(), activeSurface.end(), p0) == activeSurface.end()) {
      //   activeSurface.push_back(p0);
      // }
      // if (std::find(activeSurface.begin(), activeSurface.end(), p1) == activeSurface.end()) {
      //   activeSurface.push_back(p1);
      // }
      
      

      // double colorSimilarity = hist3D[p0].compare(hist3D[p1]);
      // double textureRate = texture.compare(p0, p1);
      // double relSize = std::min((double)view->surfaces[p0]->indices.size()/(double)view->surfaces[p1]->indices.size(), 
      //                           (double)view->surfaces[p1]->indices.size()/(double)view->surfaces[p0]->indices.size());
      
      // std::vector<double> boundary_relations;
      // if(!boundary.compare(p0, p1, boundary_relations)) {
      //   valid_relation = false;
      //   printf("[StructuralRelationsLight::computeRelations] Warning: Boundary relation invalid.\n");
      // }
    
      if(valid_relation) {
          // Relation r;
          // // r.groundTruth = -1;
          // // r.prediction = -1;
          // // r.type = 1;                                     // structural level = 1
          // r.id_0 = p0;
          // r.id_1 = p1;

          // // r.rel_value.push_back(colorSimilarity);         // r_co ... color similarity (histogram) of the patch
          // // r.rel_value.push_back(textureRate);             // r_tr ... difference of texture rate
          // // r.rel_value.push_back(relSize);                 // r_rs ... relative patch size difference

          // // r.rel_value.push_back(boundary_relations[0]);     // r_co3 ... color similarity on 3D border
          // // r.rel_value.push_back(boundary_relations[4]);     // r_cu3 ... mean curvature of 3D neighboring points
          // // r.rel_value.push_back(boundary_relations[1]);     // r_di2 ... depth mean value between border points (2D)
          // // r.rel_value.push_back(boundary_relations[2]);     // r_vd2 ... depth variance value
          // // r.rel_value.push_back(boundary_relations[5]);     // r_cu3 ... curvature variance of 3D neighboring points
          // // r.rel_value.push_back(boundary_relations[6]);     // r_3d2 ... relation 3D neighbors / 2D neighbors

          // r.valid = true;
          // relations[p0][p1] = r;
      }
    }
  }

  for (unsigned i =0; i < surfaceState.size(); i++) {
    if (surfaceState[i]) {
      activeSurface.push_back(i);
    }
  }
  // copy relations to view
//   for(unsigned i=0; i<view->surfaces.size(); i++)
//     for(unsigned j=i+1; j<view->surfaces.size(); j++) {
//       if(relations[i][j].valid) {
//         view->relations.push_back(relations[i][j]);
// #ifdef DEBUG
//         printf("r_st_l: [%u][%u]: ", relations[i][j].id_0, relations[i][j].id_1);
//         // for(unsigned ridx=0; ridx<relations[i][j].rel_value.size(); ridx++)
//         //   printf("%4.3f ", relations[i][j].rel_value[ridx]);
//         printf("\n");
// #endif
      // }
    // }
  return  activeSurface;
}


std::vector<int>  CustomRelationsLight::computeFineRelations()
{
printf("StructuralRelationsLight::computeRelations start!\n");
std::vector<int> activeSurface;

  if(!have_input_cloud || !have_patches || view->surfaces.size() > 800) {
    printf("[StructuralRelationsLight::computeRelations] Error: No input cloud and patches available.\n");
    return activeSurface;
  }

  view->relations.clear();
  
  cv::Mat_<cv::Vec3b> matImage;
  ConvertPCLCloud2Image(pcl_cloud, matImage);

 
  surface::FitSize fs;
  surface::Centroid ct;

  relations.resize(view->surfaces.size());
  
  std::cout<< view->surfaces.size() << "\n";
  // std::cout<< view->normals->size() << "\n";
  std::map<unsigned, pcl::Normal> PatchMeanN;
  std::vector<int> surfaceState(view->surfaces.size(), 0);



  std::map<unsigned, pcl::PointXYZ> centroid;

  std::map<unsigned, int> sizeFit;



#pragma omp parallel sections
  {

    #pragma omp section
    {
      computeNeighbors();
    }
   
    #pragma omp section 
    {
      fs.setInputCloud(pcl_cloud);
      fs.setSurfaceModels(*view);
      fs.compute(sizeFit);
    }      
      
    #pragma omp section 
    {
      ct.setInputCloud(pcl_cloud);
      ct.setSurfaceModels(*view);
      ct.compute(centroid);
    }      
    
    #pragma omp section 
    {
     computePatchNorm(PatchMeanN);
    }
      
  } // end parallel sections
  
  
  bool relations[view->surfaces.size()][view->surfaces.size()];
  
  
  for(unsigned i=0; i<view->surfaces.size(); i++) {
    for(unsigned j=0; j<view->surfaces.size(); j++) {
      relations[i][j] = false;
    }
  }
  

#pragma omp parallel for
  for(int i=0; i<(int)view->surfaces.size(); i++) {
    for(int j=0; j<(int)view->surfaces[i]->neighbors3D.size(); j++) {
      int p0 = i;
      int p1 = view->surfaces[i]->neighbors3D[j];
      

      if(p0 > p1) {
        continue;
      }
      if (!sizeFit[p0]||!sizeFit[p1]) {
        continue;
      }
      pcl::Normal n0 = PatchMeanN[p0];
      pcl::Normal n1 = PatchMeanN[p1];
      // double angle = acos(n0.normal_x * n1.normal_x + n0.normal_y * n1.normal_y + n0.normal_z * n1.normal_z);
      // std::cout << angle << "  ";
      double innpro = fabs(n0.normal_x * n1.normal_x + n0.normal_y * n1.normal_y + n0.normal_z * n1.normal_z);
      if (innpro >= 0.18) { continue; }
      
      pcl::PointXYZ c0 = centroid[p0];
      pcl::PointXYZ c1 = centroid[p1];
      double db = sqrt( (c0.x -c1.x)*(c0.x -c1.x) + (c0.y -c1.y)*(c0.y -c1.y) + (c0.z -c1.z)*(c0.z -c1.z));
      double alpha = 0.1;
      float x00 = c0.x + n0.normal_x * alpha, y00 = c0.y + n0.normal_y * alpha, z00 = c0.z + n0.normal_z * alpha;
      float x11 = c1.x + n1.normal_x * alpha, y11 = c1.y + n1.normal_y * alpha, z11 = c1.z + n1.normal_z * alpha;

      double da = sqrt( (x00 - x11)*(x00 - x11) + (y00 - y11)*(y00 - y11) + (z00 - z11)*(z00 - z11));
      if (db > da) { continue; }

      // std::cout << db << "\t" << da << std::endl;

      // surfaceState[p0] = p0+1;
      // surfaceState[p1] = p1+1;
      surfaceState[p0] = 1;
      surfaceState[p1] = 1;
      
      relations[p0][p1] = true;
      
    }
  }

  //BFS to find all the connected componnet
  std::vector<std::vector<int> > component;
  // unsigned cid = 0;
  for  (unsigned i = 0; i < surfaceState.size(); i++) {

    if (surfaceState[i] != 1) {  // 0 means background; 1 denotes foreground but unknown componet; 2 means determined component
      continue;
    }
    std::vector<int> v;
    v.clear();
    std::queue<int> que;
    que.push(i);
    surfaceState[i] = 2;
    while (!que.empty()) {
      int ele = que.front();
      que.pop();
      v.push_back(ele);
      // find ele's neighbor's
      for (unsigned j = 0; j < surfaceState.size(); j++) {
        if (surfaceState[j] != 1) {
          continue;
        }
        if (relations[ele][j] || relations[j][ele]) {
          que.push(j);
          surfaceState[j] = 2;
        }
      }
    }
    component.push_back(v); 

  }
 
  for (unsigned i = 0; i < component.size(); i++) {
    for (unsigned j= 0; j < component[i].size(); j++) {
      surfaceState[ component[i][j] ] = i + 1;

    }

  }

  // for(unsigned i=0; i<view->surfaces.size(); i++)
  //   for(unsigned j=i+1; j<view->surfaces.size(); j++) {
  //     if(relations[i][j]) {
  //       printf("r_st_l: [%u][%u]: ", i, j);
  //       printf("\n");
  //     }
  //   }

  return  surfaceState;
}

// template <size_t rows, size_t cols>
std::vector<std::vector<unsigned> > findConnectedComponets(bool** relations, int rows, int cols) {
  std::vector<std::vector<unsigned> > component;

  return component;
}


std::vector<int> CustomRelationsLight::findTableTopObjects() {


  printf("table topc objects start!\n");
  std::vector<int> activeSurface;

  if(!have_input_cloud || !have_patches || view->surfaces.size() > 800) {
    printf("[StructuralRelationsLight::computeRelations] Error: No input cloud and patches available.\n");
    return activeSurface;
  }

  view->relations.clear();
  
  cv::Mat_<cv::Vec3b> matImage;
  ConvertPCLCloud2Image(pcl_cloud, matImage);

  std::vector<int> surfaceState(view->surfaces.size(), 0);


  relations.resize(view->surfaces.size());
  
  std::cout<< view->surfaces.size() << "\n";
  // std::cout<< view->normals->size() << "\n";
 #pragma omp parallel sections
  {

    #pragma omp section
    {
      computeNeighbors();
    }
  
  } // end parallel sections
  
  
  bool relations[view->surfaces.size()][view->surfaces.size()];
  
  std::cout << "locate table top " << std::endl;

  int max_size = 0;
  int max_index = -1;
  for(unsigned i=0; i<view->surfaces.size(); i++) {
    // std::cout << view->surfaces[i]->indices.size() << std::endl;
    if (view->surfaces[i]->indices.size() > max_size) {
       max_size = view->surfaces[i]->indices.size();
       max_index = i;
    }
  }
  
  // surfaceState[max_index] = 1;
  int table_index = max_index;
  std::vector<unsigned> touch_surfaces(view->surfaces[table_index]->neighbors2D.size(), 0);

  std::cout << view->surfaces[table_index]->neighbors2D.size() << std::endl;
  // //BFS to find all the connected componnet
  for  (unsigned i = 0; i < touch_surfaces.size(); i++) {

    if (touch_surfaces[i] != 0) {  // 0 means unassigned; 
      continue;
    }
    std::queue<int> que;
    que.push(view->surfaces[table_index]->neighbors2D[i]);
    touch_surfaces[i] = 1;
    while (!que.empty()) {
      int ele = que.front();
      que.pop();
      surfaceState[ele] = i+1;
      std::cout << ele <<std::endl;

      // find ele's neighbor's
      for (unsigned j = 0; j < view->surfaces[ele]->neighbors2D.size(); j++) {
        unsigned nb = view->surfaces[ele]->neighbors2D[j];
        int pos = find(view->surfaces[table_index]->neighbors2D.begin(), view->surfaces[table_index]->neighbors2D.end(), nb)-view->surfaces[table_index]->neighbors2D.begin();
        if (pos >= view->surfaces[table_index]->neighbors2D.size() || touch_surfaces[pos]) {
          continue;
        }

        que.push(nb);
        touch_surfaces[pos] = 1;
      }
    }

  }
 
  // for (unsigned i = 0; i < component.size(); i++) {
  //   for (unsigned j= 0; j < component[i].size(); j++) {
  //     surfaceState[ component[i][j] ] = i + 1;

  //   }

  // }


  return  surfaceState;


}


} // end surface models





