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
 * @file SegmenterLightTest.cpp
 * @author Andreas Richtsfeld
 * @date January 2013
 * @version 0.1
 * @brief Test program for the SegmenterLight.
 */


#include "SegmenterLightTest.h"

namespace segment
{

double timespec_diff(struct timespec *x, struct timespec *y)
{
  if(x->tv_nsec < y->tv_nsec)
  {
    int nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
    y->tv_nsec -= 1000000000 * nsec;
    y->tv_sec += nsec;
  }
  if(x->tv_nsec - y->tv_nsec > 1000000000)
  {
    int nsec = (y->tv_nsec - x->tv_nsec) / 1000000000;
    y->tv_nsec += 1000000000 * nsec;
    y->tv_sec -= nsec;
  }
  return (double)(x->tv_sec - y->tv_sec) +
    (double)(x->tv_nsec - y->tv_nsec)/1000000000.;
}
  
void SegmenterLightTest::ConvertPCLCloud2Image(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &pcl_cloud, 
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

void SegmenterLightTest::ConvertPCLCloud2CvVec(const pcl::PointCloud<pcl::PointXYZRGBL>::Ptr &pcl_cloud, 
                                               std::vector<cv::Vec4f> &cvCloud/*,
                                               bool random_colors*/)
{
  int pcWidth = pcl_cloud->width;
  int pcHeight = pcl_cloud->height;
  int position = 0;

  std::map<int, float> label2color;
  for(int i=0; i<pcl_cloud->points.size(); i++) {
    if (label2color.find(pcl_cloud->points[i].label) == label2color.end()) {
    	label2color[pcl_cloud->points[i].label] = GetRandomColor();
    } 
 
  }

  label2color[255] = 	182672;

  // for (std::map<int, float>::const_iterator it = label2color.begin(); it != label2color.end(); it++) {
  // 	std::cout << it->first << "\t" << it->second << "\n";
  // }
  
  for (int row = 0; row < pcHeight; row++) {
    for (int col = 0; col < pcWidth; col++) {
      cv::Vec4f p;
      position = row * pcWidth + col;
      p[0] = pcl_cloud->points[position].x;
      p[1] = pcl_cloud->points[position].y;
      p[2] = pcl_cloud->points[position].z;
      p[3] = label2color[pcl_cloud->points[position].label];
      cvCloud.push_back(p);
    }
  }
}

 void SegmenterLightTest::ConvertPCLCloud2ColorSeg(const pcl::PointCloud<pcl::PointXYZRGBL>::Ptr &in,
                             pcl::PointCloud<pcl::PointXYZRGB>::Ptr &out) {
 
 	out.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    out->points.resize(in->width*in->height);
    out->is_dense = false;


    std::map<int, float> label2color;
    for(int i=0; i<in->points.size(); i++) {
      if (label2color.find(in->points[i].label) == label2color.end()) {
      	label2color[in->points[i].label] = GetRandomColor();
      } 
    }


    for (unsigned row = 0; row < in->height; row++) {
      for (unsigned col = 0; col < in->width; col++) {
        int idx = row * in->width + col;
        pcl::PointXYZRGBL &pt = in->points[idx];
        pcl::PointXYZRGB &npt = out->points[idx];
        npt.x = pt.x;
        npt.y = pt.y;
        npt.z = pt.z;
        npt.rgb = label2color[pt.label];
      }
    }


 }


/* --------------- PreSegmenter --------------- */

SegmenterLightTest::SegmenterLightTest() :viewer2("Simple")
{
  z_min = 0.3;
  z_max = 4.5;
  database_path = "/media/Daten/OSD/";
  rgbd_filename = "points2/test%1d.pcd";
  data_live = false;
  startIdx = 0;
  endIdx = 65;  
  overall_runtime = 0;
  user_stages = 1;
}

SegmenterLightTest::~SegmenterLightTest()
{
}

void SegmenterLightTest::init()
{
  bool load_models = false;   // load models from file
  bool data_depth = false;    // load depth data instead of pcd data
  std::string sfv_filename = "test_model%1d.sfv";
  
  // init kinect data reader
  kinect = new KinectData();
  kinect->setDatabasePath(database_path); 
  if(data_live) {
    // kinect->setReadDataLive();
    std::cout << "Use openni2_grabber instead \n";
  } 
  else
    kinect->setReadDataFromFile(rgbd_filename, rgbd_filename, startIdx, endIdx, data_depth);
  if(load_models)
    kinect->setReadModelsFromFile(sfv_filename, startIdx, endIdx);
}

void SegmenterLightTest::process()
{
  pcl_cloud_labeled.reset(new pcl::PointCloud<pcl::PointXYZRGBL>);
  kinect->getImageData(pcl_cloud);
  //   if(pcl_cloud.get() == 0)
  //   pcl_cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
  // if (pcl::io::loadPCDFile("/home/lwt1104/Downloads/OSD-0.2/pcd/test11.pcd", *pcl_cloud) == -1){
  //    std::cout << "error " <<  "~/Downloads/OSD-0.2/pcd/test11.pcd" << "\n";
  // }
                  
  static struct timespec start, current;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);

  segment::SegmenterLight seg("");
  seg.setFast(true);
  seg.setDetail(2);
  // seg.viewer_cloud,showCloud(pcl_cloud);
  pcl_cloud_labeled = seg.processStages(pcl_cloud, user_stages);
  
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &current);
  double runtime = segment::timespec_diff(&current, &start);
  printf("[processPointCloud] Runtime SegmenterLight: %4.3f\n", runtime);
  overall_runtime += runtime;
  printf("[processPointCloud] Runtime SegmenterLight OVERALL: %4.3f\n", overall_runtime);
}



 void SegmenterLightTest::cloud_cb_ (const  pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
 {
    static unsigned count = 0;
    if (++count == 20)
    {

      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_rgb (new pcl::PointCloud<pcl::PointXYZRGB>);
      pcl::copyPointCloud (*cloud, *cloud_rgb);
      segment::SegmenterLight seg("");
      seg.setFast(true);
      seg.setDetail(2);
      pcl_cloud_labeled = seg.processStages(cloud_rgb, user_stages);

      cv::Mat_<cv::Vec3b> kImage = cv::Mat_<cv::Vec3b>::zeros(480, 640);
      ConvertPCLCloud2Image(cloud_rgb, kImage);
      cv::imshow("Debug image", kImage);
      cvWaitKey(15);

      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_colored(new pcl::PointCloud<pcl::PointXYZRGB>);
      ConvertPCLCloud2ColorSeg(pcl_cloud_labeled, cloud_colored);
      // viewer2.showCloud(cloud_rgb);

      viewer2.showCloud(cloud_colored);
     
      count = 0;
    }
}

void SegmenterLightTest::run(std::string _rgbd_filename,
                       int _startIdx, int _endIdx, 
                       bool _live)
{
  bool processed = false;
  database_path = "";
  rgbd_filename = _rgbd_filename;
  startIdx = _startIdx;
  endIdx = _endIdx;
  data_live = _live;
  init();

  
  if (data_live) {
  	// create a new grabber for OpenNI devices
    pcl::Grabber* interface = new pcl::io::OpenNI2Grabber();

    // make callback function from member function
    boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f =
      boost::bind (&SegmenterLightTest::cloud_cb_, this, _1);

    // connect callback function for desired signal. In this case its a point cloud with color values
    boost::signals2::connection c = interface->registerCallback (f);

    // start receiving point clouds
    interface->start ();

    // wait until user quits program with Ctrl-C, but no busy-waiting -> sleep (1);
    while (!viewer2.wasStopped()) {
      boost::this_thread::sleep (boost::posix_time::seconds (1));
    }

    // stop the grabber
    interface->stop ();

  	return;
  }
   

  // ######################## Setup TomGine ########################
  int width = 640;
  int height = 480;
  surface::View view;
  
#ifdef V4R_TOMGINE
  TomGine::tgTomGineThread dbgWin(width, height, "TomGine Render Engine");
#endif
  cv::Mat R = (cv::Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
  cv::Mat t = (cv::Mat_<double>(3, 1) << 0, 0, 0);
  cv::Vec3d rotCenter(0, 0, 1.0);

  cv::Mat intrinsic;
  intrinsic = cv::Mat::zeros(3, 3, CV_64F);
  view.intrinsic = Eigen::Matrix3d::Zero();
  intrinsic.at<double> (0, 0) = intrinsic.at<double> (1, 1) = view.intrinsic(0, 0) = view.intrinsic(1, 1) = 525;
  intrinsic.at<double> (0, 2) = view.intrinsic(0, 2) = 320;
  intrinsic.at<double> (1, 2) = view.intrinsic(1, 2) = 240;
  intrinsic.at<double> (2, 2) = view.intrinsic(2, 2) = 1.;

#ifdef V4R_TOMGINE
//   dbgWin.SetClearColor(0.0, 0.0, 0.0);
// //   dbgWin.SetCoordinateFrame();
//   dbgWin.SetCamera(intrinsic);
//   dbgWin.SetCamera(R, t);
//   dbgWin.SetRotationCenter(rotCenter);
//   dbgWin.SetInputSpeeds(0.5, 0.5, 0.5);
//   dbgWin.Update();
#endif

  cv::Mat_<cv::Vec3b> kImage = cv::Mat_<cv::Vec3b>::zeros(480, 640);
  cv::imshow("Debug image", kImage);
  
  bool do_it = true;
  bool single_image = true;
  bool win_done = true;
  while(do_it) {
    if(!single_image) {
      process();
      ConvertPCLCloud2Image(pcl_cloud, kImage);
      cv::imshow("Debug image", kImage); 
      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_colored(new pcl::PointCloud<pcl::PointXYZRGB>);
      ConvertPCLCloud2ColorSeg(pcl_cloud_labeled, cloud_colored);
      viewer2.showCloud(cloud_colored);

      cvWaitKey(10);
#ifdef V4R_TOMGINE
      // dbgWin.SetImage(kImage);
      // dbgWin.Update();
#endif
      win_done = false;
    }

    int key = cvWaitKey(50);
    
    if((char) key == 'h') {
      printf("[SegmenterLightTest] Print help:\n");
      printf("  Debug window:\n");
      printf("    \'h\' - Print this help.\n");
      printf("    \'F9\' - Process single data file.\n");
      printf("    \'F10\' - Process data file sequence. \n");
      printf("    \'5\' - Show results.\n");
      printf("    \'q\' - Quit.\n");
      printf("  TomGine Render Engine:\n");
      printf("    \'z\' - To initial position.\n");
      printf("    \'i\' - Enable/disable background image.\n");
      printf("    \'t\' - Enable/disable text annotation.\n");
      printf("    \'p\' - Enable/disable displaying of point cloud.\n");
      printf("    \'F11\' - Save sceenshot.\n");
      printf("    \'q\' - Quit.\n");
    }
    
    if (key == 65478 || key == 1114054)  { // F9
      printf("[SegmenterLightTest] Process single image.\n");
      process();
      // viewer2.showCloud(pcl_cloud);

      ConvertPCLCloud2Image(pcl_cloud, kImage);
      cv::imshow("Debug image", kImage);

      pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_colored(new pcl::PointCloud<pcl::PointXYZRGB>);
      ConvertPCLCloud2ColorSeg(pcl_cloud_labeled, cloud_colored);
      viewer2.showCloud(cloud_colored);

#ifdef V4R_TOMGINE
     // dbgWin.SetImage(kImage);
     // dbgWin.Update();
#endif
      win_done = false;
      processed = true;
    }
    if (key == 65479 || key == 1114055)  { // F10
      printf("[SegmenterLightTest] Process images countiniously.\n");
      single_image = false;
      processed = true;

    }

    if((char) key == 'q') {
        printf("[SegmenterLightTest] Quit.\n");
        do_it = false;
    }
    
//     if((char) key == '5' || !win_done) {
//     	std::cout << "Press 5" << std::endl;
// #ifdef V4R_TOMGINE
//       // dbgWin.Clear();
//       // std::vector<cv::Vec4f> vec_cloud;
//       // ConvertPCLCloud2CvVec(pcl_cloud_labeled, vec_cloud);

//       // dbgWin.AddPointCloud(vec_cloud);
//       // dbgWin.Update();
// #endif
//       win_done = true;
//     }
  }
}

} // end segment


void printUsage(char *av)
{
  printf("Usage: %s [options] \n"
    " Options:\n"
    "   [-h] ... show this help.\n"
    "   [-f rgbd_filename] ... specify rgbd-image path and filename\n"
    "   [-idx start end] ... start and end index of files\n"
    "   [-l] ... live image from Kinect\n", av);
  std::cout << " Example: " << av << " -f /media/Daten/OSD-0.2/pcd/test%1d.pcd -idx 0 10" << std::endl;
}


int main(int argc, char *argv[])
{
  std::string rgbd_filename = "points2/test%1d.pcd";
  int startIdx = 0;
  int endIdx = 65;
  bool live = false;
  
  int user_stages = 1;
  pcl::console::parse_argument (argc, argv, "-stage", user_stages);

  for(int i=1; i<argc; i++) {
    if(strcmp (argv[i], "-h") == 0) {
      printUsage(argv[0]);
      exit(0);
    }
    if(strcmp (argv[i], "-l") == 0)
      live = true;
    if(i+1 < argc) {
      if(strcmp (argv[i], "-f") == 0)
        rgbd_filename = argv[i+1];
      if(strcmp (argv[i], "-idx") == 0) {
        startIdx = atoi(argv[i+1]);
        if(i+2 < argc)
          endIdx = atoi(argv[i+2]);
      }
    }
    else 
      printUsage(argv[0]);
  }
    
  segment::SegmenterLightTest seg;
  seg.set_user_stages(user_stages);
  seg.run(rgbd_filename, startIdx, endIdx, live);

}


