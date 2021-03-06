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
 * @file SegmenterLight.cpp
 * @author Andreas Richtsfeld
 * @date January 2012
 * @version 0.1
 * @brief Segment images efficiently
 */

#include "SegmenterLight.h"

#include <stdio.h>
#include <pcl/io/pcd_io.h>

namespace segment
{
  
  /* --------------- SegmenterLight --------------- */

  SegmenterLight::SegmenterLight (std::string _model_path)
  {
    model_path = _model_path;
    useStructuralLevel = true;
    detail = 2;
  }

  SegmenterLight::~SegmenterLight ()
  {
  }

  void
  SegmenterLight::computeNormals (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                             pcl::PointCloud<pcl::Normal>::Ptr &normals_out)
  {
    normals_out.reset (new pcl::PointCloud<pcl::Normal>);
    surface::ZAdaptiveNormals::Parameter za_param;
    za_param.adaptive = true;
    surface::ZAdaptiveNormals nor (za_param);
    nor.setInputCloud (cloud_in);
    nor.compute ();
    nor.getNormals (normals_out);

      // normals_out.reset (new pcl::PointCloud<pcl::Normal>);
      // pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> ne;  
      // pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB> ());

      // // Estimate point normals
      // ne.setSearchMethod (tree);
      // ne.setInputCloud (cloud_in);
      // ne.setKSearch (30);
      // ne.compute (*normals_out);
  }

  void
  SegmenterLight::computePlanes (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                            pcl::PointCloud<pcl::Normal>::Ptr &normals_in,
                            std::vector<surface::SurfaceModel::Ptr> &surfaces_out)
  {
    surface::View view;
    view.normals = normals_in;
    surface::ClusterNormalsToPlanes::Parameter param;
    param.adaptive = true;
    detail = 1;
    if(detail == 1) {
      param.epsilon_c = 0.58;
      param.omega_c = -0.002;
    } else if (detail == 2) {
      param.epsilon_c = 0.62;
      param.omega_c = 0.0;
    } 
    surface::ClusterNormalsToPlanes clusterNormals (param);
    clusterNormals.setInputCloud (cloud_in);
    clusterNormals.setView (&view);
    clusterNormals.setPixelCheck (true, 5);
    // clusterNormals.setPixelCheck (false, 5);
    clusterNormals.compute ();
    surfaces_out = view.surfaces;
  }


  void
  SegmenterLight::computeCustomPlanes (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                            pcl::PointCloud<pcl::Normal>::Ptr &normals_in,
                            std::vector<surface::SurfaceModel::Ptr> &surfaces_out)
  {
    surface::View view;
    view.normals = normals_in;
    surface::FindPlanes::Parameter param;
    param.adaptive = true;
    detail = 1;
    if(detail == 1) {
      param.epsilon_c = 0.58;
      param.omega_c = -0.002;
    } else if (detail == 2) {
      param.epsilon_c = 0.62;
      param.omega_c = 0.0;
    } 
    surface::FindPlanes fp (param);
    fp.setInputCloud (cloud_in);
    fp.setView (&view);
    fp.setPixelCheck (true, 5);
    // clusterNormals.setPixelCheck (false, 5);
    fp.compute ();
    surfaces_out = view.surfaces;
  }

  
  void
  SegmenterLight::computeSurfaces (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                   surface::View & view_in_out)
  {
    surface::View view;
    view.surfaces = view_in_out.surfaces;
    view.normals = view_in_out.normals;
    pcl::on_nurbs::SequentialFitter::Parameter nurbsParams;
    nurbsParams.order = 3;
    nurbsParams.refinement = 0;
    nurbsParams.iterationsQuad = 0;
    nurbsParams.iterationsBoundary = 0;
    nurbsParams.iterationsAdjust = 0;
    nurbsParams.iterationsInterior = 3;
    nurbsParams.forceBoundary = 100.0;
    nurbsParams.forceBoundaryInside = 300.0;
    nurbsParams.forceInterior = 1.0;
    nurbsParams.stiffnessBoundary = 0.1;
    nurbsParams.stiffnessInterior = 0.1;
    nurbsParams.resolution = 16;
    surface::SurfaceModeling::Parameter sfmParams;
    sfmParams.nurbsParams = nurbsParams;
    sfmParams.sigmaError = 0.003;
    sfmParams.kappa1 = 0.008;
    sfmParams.kappa2 = 1.0;
    sfmParams.planePointsFixation = 8000;
    sfmParams.z_max = 0.01;
    surface::SurfaceModeling surfModeling (sfmParams);
    Eigen::Matrix4d pose = Eigen::Matrix4d::Identity ();
    surfModeling.setIntrinsic (525., 525., 320., 240.);
    surfModeling.setExtrinsic (pose);
    surfModeling.setInputCloud (cloud_in);
    surfModeling.setView (&view);
    surfModeling.compute ();
    view_in_out.surfaces = view.surfaces;
  }

  void
  SegmenterLight::computeObjects (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud_in,
                             surface::View & view_in_out)
  {
    // contour detector
    surface::View view;
    view.width = cloud_in->width;
    view.height = cloud_in->height;
    view.surfaces = view_in_out.surfaces;
    view.normals = view_in_out.normals;
    
    surface::ContourDetector contourDet;
    contourDet.setInputCloud(cloud_in);
    contourDet.setView(&view);
    contourDet.computeContours();
    
    surface::StructuralRelationsLight stRel;
    stRel.setInputCloud(cloud_in);
    stRel.setView(&view);
    stRel.computeRelations();

    // init model path
    std::string svmStructuralModel;
    std::string svmStructuralScaling;
    svmStructuralModel = "PP-Trainingsset.txt.scaled.model";
    svmStructuralScaling = "param.txt";
  
    svm::SVMPredictorSingle svm_structural(model_path, svmStructuralModel);
    svm_structural.setScaling(true, model_path, svmStructuralScaling);
    svm_structural.classify(&view, 1);
    
    gc::GraphCut graphCut;
    #ifdef DEBUG
      graphCut.printResults(true);
    #endif
    if(graphCut.init(&view))
      graphCut.process();
    
     for (unsigned i = 0; i < view.graphCutGroups.size (); i++)
       for (unsigned j = 0; j < view.graphCutGroups[i].size (); j++)
         view_in_out.surfaces[view.graphCutGroups[i][j]]->label = i;

    
  }

  pcl::PointCloud<pcl::PointXYZRGBL>::Ptr
  SegmenterLight::processPointCloud (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud)
  {
    surface::View view;
    view.width = pcl_cloud->width;
    view.height = pcl_cloud->height;

    pcl::PointCloud<pcl::PointXYZRGBL>::Ptr result (new pcl::PointCloud<pcl::PointXYZRGBL>);
    pcl::copyPointCloud (*pcl_cloud, *result);

    // calcuate normals
    view.normals.reset (new pcl::PointCloud<pcl::Normal>);
    surface::ZAdaptiveNormals::Parameter za_param;
    za_param.adaptive = true;
    surface::ZAdaptiveNormals nor (za_param);
    nor.setInputCloud (pcl_cloud);
    nor.compute ();
    nor.getNormals (view.normals);

    // adaptive clustering
    surface::ClusterNormalsToPlanes::Parameter param;
    param.adaptive = true;
    if(detail == 1) {
      param.epsilon_c = 0.58;
      param.omega_c = -0.002;
    } else if (detail == 2) {
      param.epsilon_c = 0.62;
      param.omega_c = 0.0;
    } 
    surface::ClusterNormalsToPlanes clusterNormals (param);
    clusterNormals.setInputCloud (pcl_cloud);
    clusterNormals.setView (&view);
    clusterNormals.setPixelCheck (true, 5);
    clusterNormals.compute ();

    // model abstraction
    if(!fast) {
      pcl::on_nurbs::SequentialFitter::Parameter nurbsParams;
      nurbsParams.order = 3;
      nurbsParams.refinement = 0;
      nurbsParams.iterationsQuad = 0;
      nurbsParams.iterationsBoundary = 0;
      nurbsParams.iterationsAdjust = 0;
      nurbsParams.iterationsInterior = 3;
      nurbsParams.forceBoundary = 100.0;
      nurbsParams.forceBoundaryInside = 300.0;
      nurbsParams.forceInterior = 1.0;
      nurbsParams.stiffnessBoundary = 0.1;
      nurbsParams.stiffnessInterior = 0.1;
      nurbsParams.resolution = 16;
      surface::SurfaceModeling::Parameter sfmParams;
      sfmParams.nurbsParams = nurbsParams;
      sfmParams.sigmaError = 0.003;
      sfmParams.kappa1 = 0.008;
      sfmParams.kappa2 = 1.0;
      sfmParams.planePointsFixation = 8000;
      sfmParams.z_max = 0.01;
      surface::SurfaceModeling surfModeling (sfmParams);
      Eigen::Matrix4d pose = Eigen::Matrix4d::Identity ();
      surfModeling.setIntrinsic (525., 525., 320., 240.);
      surfModeling.setExtrinsic (pose);
      surfModeling.setInputCloud (pcl_cloud);
      surfModeling.setView (&view);
      surfModeling.compute ();
    }

    // contour detector
    surface::ContourDetector contourDet;
    contourDet.setInputCloud(pcl_cloud);
    contourDet.setView(&view);
    contourDet.computeContours();
    
    // relations
    surface::StructuralRelationsLight stRel;
    stRel.setInputCloud(pcl_cloud);
    stRel.setView(&view);
    stRel.computeRelations();
 
    // init svm model
    std::string svmStructuralModel;
    std::string svmStructuralScaling;
    if(!fast) {
      svmStructuralModel = "PP-Trainingsset.txt.scaled.model";
      svmStructuralScaling = "param.txt";
    } else {
      svmStructuralModel = "PP-Trainingsset.txt.scaled.model.fast";
      svmStructuralScaling = "param.txt.fast";
    }

    // svm classification
    svm::SVMPredictorSingle svm_structural(model_path, svmStructuralModel);
    svm_structural.setScaling(true, model_path, svmStructuralScaling);
    svm_structural.classify(&view, 1);
    
    // graph cut
    gc::GraphCut graphCut;
    #ifdef DEBUG
      graphCut.printResults(true);
    #endif
    if(graphCut.init(&view))
      graphCut.process();

    // copy results
    for (unsigned i = 0; i < view.graphCutGroups.size (); i++)
      for (unsigned j = 0; j < view.graphCutGroups[i].size (); j++)
        view.surfaces[view.graphCutGroups[i][j]]->label = i;
    for (unsigned i = 0; i < view.surfaces.size (); i++) {
      for (unsigned j = 0; j < view.surfaces[i]->indices.size (); j++) {
        result->points[view.surfaces[i]->indices[j]].label = view.surfaces[i]->label;
      }
    }

    return result;
  }

  
  std::vector<pcl::PointIndices>
  SegmenterLight::processPointCloudV (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud)
  {
    surface::View view;
    view.width = pcl_cloud->width;
    view.height = pcl_cloud->height;
    
    pcl::PointCloud<pcl::PointXYZRGBL>::Ptr result (new pcl::PointCloud<pcl::PointXYZRGBL>);
    pcl::copyPointCloud (*pcl_cloud, *result);

    // calcuate normals
    view.normals.reset (new pcl::PointCloud<pcl::Normal>);
    surface::ZAdaptiveNormals::Parameter za_param;
    za_param.adaptive = true;
    surface::ZAdaptiveNormals nor (za_param);
    nor.setInputCloud (pcl_cloud);
    nor.compute ();
    nor.getNormals (view.normals);

    // adaptive clustering
    surface::ClusterNormalsToPlanes::Parameter param;
    param.adaptive = true;
    if(detail == 1) {
      param.epsilon_c = 0.58;
      param.omega_c = -0.002;
    } else if (detail == 2) {
      param.epsilon_c = 0.62;
      param.omega_c = 0.0;
    } 
    surface::ClusterNormalsToPlanes clusterNormals (param);
    clusterNormals.setInputCloud (pcl_cloud);
    clusterNormals.setView (&view);
    clusterNormals.setPixelCheck (true, 5);
    clusterNormals.compute ();

    // model abstraction
    if(!fast) {
      pcl::on_nurbs::SequentialFitter::Parameter nurbsParams;
      nurbsParams.order = 3;
      nurbsParams.refinement = 0;
      nurbsParams.iterationsQuad = 0;
      nurbsParams.iterationsBoundary = 0;
      nurbsParams.iterationsAdjust = 0;
      nurbsParams.iterationsInterior = 3;
      nurbsParams.forceBoundary = 100.0;
      nurbsParams.forceBoundaryInside = 300.0;
      nurbsParams.forceInterior = 1.0;
      nurbsParams.stiffnessBoundary = 0.1;
      nurbsParams.stiffnessInterior = 0.1;
      nurbsParams.resolution = 16;
      surface::SurfaceModeling::Parameter sfmParams;
      sfmParams.nurbsParams = nurbsParams;
      sfmParams.sigmaError = 0.003;
      sfmParams.kappa1 = 0.008;
      sfmParams.kappa2 = 1.0;
      sfmParams.planePointsFixation = 8000;
      sfmParams.z_max = 0.01;
      surface::SurfaceModeling surfModeling (sfmParams);
      Eigen::Matrix4d pose = Eigen::Matrix4d::Identity ();
      surfModeling.setIntrinsic (525., 525., 320., 240.);
      surfModeling.setExtrinsic (pose);
      surfModeling.setInputCloud (pcl_cloud);
      surfModeling.setView (&view);
      surfModeling.compute ();
    }

    // contour detector
    surface::ContourDetector contourDet;
    contourDet.setInputCloud(pcl_cloud);
    contourDet.setView(&view);
    contourDet.computeContours();
    
    // relations
    surface::StructuralRelationsLight stRel;
    stRel.setInputCloud(pcl_cloud);
    stRel.setView(&view);
    stRel.computeRelations();
 
    // init svm model
    std::string svmStructuralModel;
    std::string svmStructuralScaling;
    if(!fast) {
      svmStructuralModel = "PP-Trainingsset.txt.scaled.model";
      svmStructuralScaling = "param.txt";
    } else {
      svmStructuralModel = "PP-Trainingsset.txt.scaled.model.fast";
      svmStructuralScaling = "param.txt.fast";
    }
    
    // svm classification
    svm::SVMPredictorSingle svm_structural(model_path, svmStructuralModel);
    svm_structural.setScaling(true, model_path, svmStructuralScaling);
    svm_structural.classify(&view, 1);
    
    // graph cut
    gc::GraphCut graphCut;
    #ifdef DEBUG
      graphCut.printResults(true);
    #endif
    if(graphCut.init(&view))
      graphCut.process();

    std::vector<pcl::PointIndices> results;
    results.resize (view.graphCutGroups.size ());
    for (unsigned i = 0; i < view.graphCutGroups.size (); i++)
      for (unsigned j = 0; j < view.graphCutGroups[i].size (); j++)
        for (unsigned k = 0; k < view.surfaces[view.graphCutGroups[i][j]]->indices.size (); k++)
          results[i].indices.push_back(view.surfaces[view.graphCutGroups[i][j]]->indices[k]);
    return results;
  }



  pcl::PointCloud<pcl::PointXYZRGBL>::Ptr
  SegmenterLight::processStages (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud, int user_stages)
  {
    surface::View view;
    view.width = pcl_cloud->width;
    view.height = pcl_cloud->height;
    int stages = 0;

    pcl::PointCloud<pcl::PointXYZRGBL>::Ptr result (new pcl::PointCloud<pcl::PointXYZRGBL>);
    pcl::copyPointCloud (*pcl_cloud, *result);

    // calcuate normals
    computeNormals(pcl_cloud, view.normals);

    // adaptive clustering  1
    if (stages < user_stages) {
      computeCustomPlanes (pcl_cloud, view.normals, view.surfaces);
      stages++;
    }
    // model abstraction  2
    if (stages < user_stages) {
      computeSurfaces(pcl_cloud, view);
      stages++;
    }
    // object level result  3
    if (stages < user_stages) {
      computeObjects(pcl_cloud, view);
      stages++;
      for (unsigned i = 0; i < view.surfaces.size (); i++) {
        for (unsigned j = 0; j < view.surfaces[i]->indices.size (); j++) {
          result->points[view.surfaces[i]->indices[j]].label = view.surfaces[i]->label;
        }
      }

    } else {
      for (unsigned i = 0; i < view.surfaces.size (); i++) {
        for (unsigned j = 0; j < view.surfaces[i]->indices.size (); j++) {
          result->points[view.surfaces[i]->indices[j]].label = i+1;
        }
      }
//      std::cout << "\n";
     // std::cout << "stage surface number: "<< view.surfaces.size () << std::endl;
    }
 



    return result;
  }

  pcl::PointCloud<pcl::PointXYZRGBL>::Ptr
  SegmenterLight::locateBox (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud){
    pcl::PointCloud<pcl::PointXYZRGBL>::Ptr result (new pcl::PointCloud<pcl::PointXYZRGBL>);
    pcl::copyPointCloud (*pcl_cloud, *result);

    surface::View view;
    view.width = pcl_cloud->width;
    view.height = pcl_cloud->height;
    computeNormals(pcl_cloud, view.normals);
    computeCustomPlanes (pcl_cloud, view.normals, view.surfaces);

    surface::CustomRelationsLight ctRel;
    ctRel.setInputCloud(pcl_cloud);
    ctRel.setView(&view);
    // std::vector<unsigned> activeSurface = ctRel.computeFineRelations();
    // for (unsigned i = 0; i < activeSurface.size(); i++) {
    //   std::cout << activeSurface[i] << "\t" ;
    // }
    // std::cout << std::endl;

    // for (unsigned i = 0; i < activeSurface.size (); i++) {
    //   for (unsigned j = 0; j < view.surfaces[activeSurface[i]]->indices.size (); j++) {
    //     result->points[view.surfaces[activeSurface[i]]->indices[j]].label = activeSurface[i]+1;
    //   }
    // }
    

    std::vector<int> surfaceState = ctRel.computeFineRelations();
    for (unsigned i = 0; i < view.surfaces.size (); i++) {
      if (surfaceState[i]) {
        // std::cout << surfaceState[i] << std::endl;
        for (unsigned j = 0; j < view.surfaces[i]->indices.size(); j++) {
          result->points[view.surfaces[i]->indices[j]].label = surfaceState[i];
        }
      }
      
    }


    return result;
  }


  pcl::PointCloud<pcl::PointXYZRGBL>::Ptr
  SegmenterLight::locateCandidate (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud){
    pcl::PointCloud<pcl::PointXYZRGBL>::Ptr result (new pcl::PointCloud<pcl::PointXYZRGBL>);
    pcl::copyPointCloud (*pcl_cloud, *result);

    surface::View view;
    view.width = pcl_cloud->width;
    view.height = pcl_cloud->height;
    computeNormals(pcl_cloud, view.normals);
    computeCustomPlanes (pcl_cloud, view.normals, view.surfaces);

    surface::CustomRelationsLight ctRel;
    ctRel.setInputCloud(pcl_cloud);
    ctRel.setView(&view);
    // std::vector<unsigned> activeSurface = ctRel.computeFineRelations();
    // for (unsigned i = 0; i < activeSurface.size(); i++) {
    //   std::cout << activeSurface[i] << "\t" ;
    // }
    // std::cout << std::endl;

    // for (unsigned i = 0; i < activeSurface.size (); i++) {
    //   for (unsigned j = 0; j < view.surfaces[activeSurface[i]]->indices.size (); j++) {
    //     result->points[view.surfaces[activeSurface[i]]->indices[j]].label = activeSurface[i]+1;
    //   }
    // }

    std::vector<int> surfaceState = ctRel.findTableTopObjects();
    for (unsigned i = 0; i < view.surfaces.size (); i++) {
      if (surfaceState[i]) {
        // std::cout << surfaceState[i] << std::endl;
        for (unsigned j = 0; j < view.surfaces[i]->indices.size(); j++) {
          result->points[view.surfaces[i]->indices[j]].label = surfaceState[i];
        }
      }
      
    }


    return result;
  }


} // end segment
