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

#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>
#include <iostream>

class Filter
{
private:
	cv::Mat m_image;
	int m_kernelSize;
	double m_sigma;
	double m_theta;
	double m_lamda;
	double m_gamma;
	double m_ps;

public:
	Filter ()
	{
		int m_kernelSize = 31;
		double m_sigma = 1;
		double m_theta = 0;
		double m_lamda = 1;
		double m_gamma = 0.02;
		double m_ps = 0;
	}

	~Filter()
	{
	}
	
	/**
	 * \param input image
   * 
   * \return output image
	 */
	cv::Mat Gabor (cv::Mat inputImage);

	/**
	 * \param input image, kernel size, alpha
	 * 
	 * \return output image
	 */
	cv::Mat Gaussian (cv::Mat inputImage, int xKernel, int yKernel, int a);

	/**
	 * 
	 * 
	 */
	cv::Mat Threshold (cv::Mat inputImage, double threshold, double maxValue, int type);
};

#endif	// FILTER_H