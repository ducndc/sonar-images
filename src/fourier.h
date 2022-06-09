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

#ifndef FOURIER_H
#define FILTER_H

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

class Fourier
{
private:

public:
  /**
   * 
   * \param input image
   * \return fourier matix
   *  
   */
	cv::Mat Fourier2d (cv::Mat inputImage);

  /**
   *
   * \param input image
   * \return inverse fourier matix
   */
	cv::Mat InverseFourier2d (cv::Mat inputImage);
};

#endif  // FOURIER_H