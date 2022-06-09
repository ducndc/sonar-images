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

#ifndef BASIC_PROCESS_H
#define BASIC_PROCESS_H

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "parameter.h"

cv::Mat CropImage (cv::Mat inputImage, int x, int y, int dx, int dy);
cv::Mat CarterToPolar (cv::Mat inputImage);
cv::Mat Contours (cv::Mat inputImage);
cv::Point2d PhaseCorrelate (cv::Mat inputReference, cv::Mat inputCompare);
cv::Mat K_Means (cv::Mat Input, int K);

/**
 * \param input image, x, y, dx, dy
 * 
 * \return croped image
 */
cv::Mat 
CropImage (cv::Mat inputImage, int x, int y, int dx, int dy)
{
	cv::Rect myROI(x, y, dx, dy);
	cv::Mat cropImage = inputImage (myROI);
	return cropImage;
}

/**
 * \param input image
 * 
 * \return output images
 */
cv::Mat 
CarterToPolar (cv::Mat inputImage)
{
	cv::Mat outputImage;
	cv::Mat rot = cv::getRotationMatrix2D(cv::Point2f ((inputImage.cols-1)/2, (inputImage.rows-1)/2), 90, 1.0);
	cv::Mat rotatedImage;
	cv::warpAffine(inputImage, rotatedImage, rot, cv::Size (500, 750));
	cv::warpPolar (inputImage, outputImage, cv::Size (),  cv::Point2f (inputImage.cols,inputImage.rows/2), 450, cv::WARP_INVERSE_MAP);
	return outputImage;
}

/**
 * \param input image
 * 
 * \return drawed image
 */
cv::Mat
Contours (cv::Mat inputImage)
{
	int thresh = 150;
	cv::Mat outputImage;
	cv::Canny (inputImage, outputImage, thresh, 160);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours (outputImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	cv::Mat drawing = cv::Mat::zeros (outputImage.size (), CV_8UC3);
	for (size_t i = 0; i < contours.size (); ++i)
	{
		cv::Scalar color = cv::Scalar (255, 255, 255);
		if (cv::contourArea (contours[i]) < 1100)
		{
			continue;
		}
		cv::drawContours (drawing, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0);
	}
	return drawing;
}

/**
 * \param src1		Source floating point array (CV_32FC1 or CV_64FC1)
 * \param src2		Source floating point array (CV_32FC1 or CV_64FC1)
 * \param window	Floating point array with windowing coefficients to reduce edge effects (optional).
 * 
 * \return detected phase shift (sub-pixel) between the two arrays.
 */
cv::Point2d 
PhaseCorrelate (cv::Mat inputReference, cv::Mat inputCompare)
{
	cv::Mat reference64f;
	cv::Mat compare64f;
	inputReference.convertTo (reference64f, CV_64F);
	inputCompare.convertTo (compare64f, CV_64F);
	cv::Point2d resultCrossPowerSpectrum;
	cv::Mat window;
	resultCrossPowerSpectrum = cv::phaseCorrelate (reference64f, compare64f, window);
	return resultCrossPowerSpectrum;
}

/**
 * \param 
 */
template <typename T> T 
GetDistance (const cv::Point a, const cv::Point b)
{
	T xDiff = a.x - b.x;
	T yDiff = a.y - b.y;
	return std::sqrt ((xDiff * xDiff) + (yDiff * yDiff));
}

/**
 * 
 */
template <typename T> T
GetDistance (const T x, const T y, const T x1, const T y1)
{
	T xDiff = x - x1;
	T yDiff = y - y1;
	return std::sqrt ((xDiff * xDiff) + (yDiff * yDiff));
}

/**
 * \param
 * 
 */
template <typename T> T 
PixelToMeter (T distance, T distanceReference)
{
	return distance/distanceReference * SONAR_RANGE;
}

/**
 * \param
 * 
 */
float 
Degree2Radian (float degree)
{
	return degree * PI / 180;
}

/**
 * \param
 * 
 */
float 
Radian2Degree (float radian)
{
	return radian * 180 / PI;
}

/**
 * 
 */
cv::Mat 
K_Means (cv::Mat Input, int K) 
{
	cv::Mat samples (Input.rows * Input.cols, Input.channels (), CV_32F);
	for (int y = 0; y < Input.rows; y++)
		for (int x = 0; x < Input.cols; x++)
			for (int z = 0; z < Input.channels (); z++)
				if (Input.channels () == 3) 
					{
						samples.at<float>(y + x * Input.rows, z) = Input.at<cv::Vec3b>(y, x)[z];
					}
				else 
					{
						samples.at<float>(y + x * Input.rows, z) = Input.at<uchar>(y, x);
					}

	cv::Mat labels;
	int attempts = 5;
	cv::Mat centers;
	cv::kmeans (samples, K, labels, cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, 
							cv::KMEANS_PP_CENTERS, centers);


	cv::Mat new_image (Input.size (), Input.type ());
	for (int y = 0; y < Input.rows; y++)
		for (int x = 0; x < Input.cols; x++)
			{
				int cluster_idx = labels.at<int>(y + x * Input.rows, 0);
				if (Input.channels () == 3) 
					{
						for (int i = 0; i < Input.channels (); i++) 
							{
								new_image.at<cv::Vec3b>(y, x)[i] = centers.at<float>(cluster_idx, i);
							}
					}
				else 
					{
						new_image.at<uchar>(y, x) = centers.at<float>(cluster_idx, 0);
					}
			}
	cv::imshow("clustered image", new_image);
	cv::waitKey(0);
	return new_image;
}



#endif	// BASIC_PROCESS_H