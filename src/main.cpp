/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2022 HUST
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Chung Duc Nguyen Dang <duc.ndc172484@sis.hust.edu.vn>
 */

#include "filter.h"
#include "data.h"
#include "fourier.h"
#include "basic-process.h"
#include "map.h"
#include <string>

int 
main (int argc, char** argv)
{
  cv::Mat image, image1;
  Filter filter;
  Map3D map;
  // Read the image file
  if (argv[1] == NULL)
  {
    Fourier fourier2d;
    image = cv::imread ("../images/dataset/sonar1.jpg", cv::IMREAD_GRAYSCALE);
    //image1 = cv::imread ("../images/sonar_reference.png", cv::IMREAD_GRAYSCALE);
/*    cv::Point2d crossPowerSpectrum = PhaseCorrelate (image, image1);
    std::cout << crossPowerSpectrum << std::endl;*/
    //cv::Mat newImage = K_Means (image, 2);
    image = filter.Threshold (image, 240, 255, 3);
    cv::imshow ("threshold", image);
    cv::waitKey (0);
    map.MapGeneration (image, 58.20, 95.43, -30);
    map.MapSLAM (image, 58.20, 95.43, -30);


    return 0;
  }
  else
  {
    std::vector<std::string> pathList = ReadPath (argv[1]);
    for (int i = 0; i < (int)pathList.size (); ++i)
    {
      std::cout << pathList[i] << std::endl;
      cv::Mat img = cv::imread (pathList[i], cv::IMREAD_GRAYSCALE);
      if (img.empty ())
      {
        continue;
      }
      cv::Mat imageResult = CropImage (img, 150, 110, 750, 520);
      std::string path = "../images/dataset/sonar" + std::to_string (i) + ".jpg";
      cv::imwrite (path, imageResult);
    }  
    return 0;
  }
  // Check for failure
  if (image.empty ())
  {
    std::cerr << "Could not open or find the image" << std::endl;
    std::cin.get (); //wait for any key press
    return -1;
  }
}
