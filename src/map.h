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

#ifndef MAP_H
#define MAP_H

#include <opencv2/opencv.hpp>
#include <opencv2/viz.hpp>

class Map3D
{
private:
  float R[3] = {0, 0, 0};

public:
  /**
   * \param file     Filename with extension. Supported formats: PLY, XYZ and OBJ.
   * \param cloud    Supported depths: CV_32F and CV_64F. Supported channels: 3 and 4.
   * \param colors   Used by PLY format only. Supported depth: CV_8U. Supported channels: 1, 3 and 4.
   * \param normals  Used by PLY and OBJ format only. Supported depths: CV_32F and CV_64F. Supported channels: 3 and 4.
   * \param binary   Used only for PLY format.
   */
  void Write3DPointCloud (const std::string file);

  /**
   * \param 
   */
  void MapGeneration (cv::Mat inputImage, float xAUV, float yAUV, float zAUV);
  /**
   * 
   */
  void MapSLAM (cv::Mat inputImage, float xAUV, float yAUV, float zAUV);
};

#endif  // MAP_H