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

#include "map.h"
#include "data.h"
#include "basic-process.h"

void 
Map3D::Write3DPointCloud (const std::string file)
{
  
}

/**
 * \param coordinate of AUV 
 * \param depth -500 m
 */
void
Map3D::MapGeneration (cv::Mat inputImage, float xAUV, float yAUV, float zAUV)
{
  std::string dataXYZ;
  float distanceReference = GetDistance (inputImage.rows, inputImage.cols/2, inputImage.rows/2, 0);
  int O[2] = {inputImage.rows, inputImage.cols/2};
  for (int i = 0; i < inputImage.rows; ++i)
  {
    for (int j = 0; j < inputImage.cols; ++j)
    {
      if (inputImage.at<uchar>(i, j) <= 180)
      {
        continue;
      }
      float distance = GetDistance (O[0], O[1], i, j);
      distance = PixelToMeter (distance, distanceReference);
      float a = (inputImage.cols/2 - j);
      float b = (inputImage.rows - i);
      float thetaJ = std::atan (a / b);
      float yLocal = std::sin (thetaJ) * distance;
      float zLocal = std::sin ((Degree2Radian (GAMMA_ANGLE) + Degree2Radian (SPREAD_ANGLE)/ 2)) * distance;

      float t  = (float)inputImage.at<uchar>(i, j) / 255;
      zLocal = zLocal - (t)*zLocal;

      float xLocal = distance * std::sqrt (1 - std::sin (Degree2Radian (GAMMA_ANGLE) + Degree2Radian (SPREAD_ANGLE) / 2)
                      * std::sin (Degree2Radian (GAMMA_ANGLE) + Degree2Radian (SPREAD_ANGLE) / 2) 
                      - std::sin (thetaJ)*std::sin (thetaJ));
      float xPoint = xAUV + xLocal;
      float yPoint = yAUV + yLocal;
      float zPoint = zAUV - zLocal;

      if (zPoint < DEPTH)
      {
        zPoint = DEPTH;
      }
      dataXYZ += std::to_string (yPoint) + " " + std::to_string (xPoint) 
                  + " " + std::to_string (zPoint)
                  + "\n";
    }
  } 
  WriteFile ("../map/xyz1.txt", dataXYZ);
}

/**
 * SLAM 
 */
void 
Map3D::MapSLAM (cv::Mat inputImage, float xAUV, float yAUV, float zAUV)
{
  std::string dataXYZ;
  float distanceReference = GetDistance (inputImage.rows, inputImage.cols/2, inputImage.rows/2, 0);
  int O[2] = {inputImage.rows, inputImage.cols/2};
  for (int i = 0; i < inputImage.rows; ++i)
  {
    for (int j = 0; j < inputImage.cols; ++j)
    {
      if (inputImage.at<uchar>(i, j) <= 180)
      {
        continue;
      }
      float distance = GetDistance (O[0], O[1], i, j);
      distance = PixelToMeter (distance, distanceReference);
      float a = (inputImage.cols/2 - j);
      float b = (inputImage.rows - i);
      float thetaJ = std::atan (a / b);
      float yLocal = std::sin (thetaJ) * distance;
      float zLocal = std::sin ((Degree2Radian (GAMMA_ANGLE) + Degree2Radian (SPREAD_ANGLE)/ 2)) * distance;

      float t  = (float)inputImage.at<uchar>(i, j) / 255;
      zLocal = zLocal - (t)*zLocal;

      float xLocal = distance * std::sqrt (1 - std::sin (Degree2Radian (GAMMA_ANGLE) + Degree2Radian (SPREAD_ANGLE) / 2)
                      * std::sin (Degree2Radian (GAMMA_ANGLE) + Degree2Radian (SPREAD_ANGLE) / 2) 
                      - std::sin (thetaJ)*std::sin (thetaJ));
      float xPoint = xAUV + xLocal;
      float yPoint = yAUV + yLocal;
      float zPoint = zAUV - zLocal;

      if (zPoint < DEPTH)
      {
        zPoint = DEPTH;
      }
      dataXYZ += std::to_string (yPoint) + " " + std::to_string (xPoint) 
                  + " " + std::to_string (zPoint)
                  + "\n";
    }
  } 
  WriteFile ("../map/xyz.txt", dataXYZ);
}