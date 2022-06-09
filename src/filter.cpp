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

cv::Mat 
Filter::Gaussian (cv::Mat inputImage, int xKernel, int yKernel, int a)
{
	cv::GaussianBlur (inputImage, m_image, cv::Size (xKernel, yKernel), a);
	return m_image;
}

cv::Mat
Filter::Gabor (cv::Mat inputImage)
{
	cv::Mat kernel = cv::getGaborKernel (cv::Size (m_kernelSize, m_kernelSize), m_sigma, m_theta, m_lamda, m_gamma, m_ps);
  cv::filter2D(inputImage, m_image, CV_32F, kernel);
  return m_image;
}

cv::Mat 
Filter::Threshold (cv::Mat inputImage, double threshold, double maxValue, int type)
{
  cv::threshold (inputImage, m_image, threshold, maxValue, type);
  return m_image;
}