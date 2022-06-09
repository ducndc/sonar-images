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

#include "fourier.h"

cv::Mat 
Fourier::Fourier2d (cv::Mat inputImage)
{
	cv::Mat padded;
	int m = cv::getOptimalDFTSize (inputImage.rows);
	int n = cv::getOptimalDFTSize (inputImage.cols);
	cv::copyMakeBorder (inputImage, padded, 0, m-inputImage.rows, 0, n-inputImage.cols,
	 	cv::BORDER_CONSTANT, cv::Scalar::all (0));

	cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros (padded.size (), CV_32F)};
	cv::Mat complexInputImage;
	cv::merge (planes, 2, complexInputImage);
	cv::dft (complexInputImage, complexInputImage);

	cv::split (complexInputImage, planes);
	cv::magnitude (planes[0], planes[1], planes[0]);
	cv::Mat magInputImage = planes[0];

	magInputImage += cv::Scalar::all (1);
	cv::log (magInputImage, magInputImage);

	magInputImage = magInputImage (cv::Rect (0, 0, magInputImage.cols & -2, magInputImage.rows & -2));

	int cx = magInputImage.cols/2;
	int cy = magInputImage.rows/2;

	cv::Mat q0(magInputImage, cv::Rect (0, 0, cx, cy));
	cv::Mat q1(magInputImage, cv::Rect (cx, 0, cx, cy));
	cv::Mat q2(magInputImage, cv::Rect (0, cy, cx, cy));
	cv::Mat q3(magInputImage, cv::Rect (cx, cy, cx, cy));

	cv::Mat tmp;
	q0.copyTo (tmp);
	q3.copyTo (q0);
	tmp.copyTo (q3);

	q1.copyTo (tmp);
	q2.copyTo (q1);
	tmp.copyTo (q2);

	cv::normalize (magInputImage, magInputImage, 0, 1, cv::NORM_MINMAX);

	return magInputImage;
}

cv::Mat 
Fourier::InverseFourier2d (cv::Mat inputImage)
{
	cv::Mat outputImage;
	cv::idft (inputImage, outputImage);
	return outputImage;
}