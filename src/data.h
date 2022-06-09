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

#ifndef DATA_H
#define DATA_H

#include <string>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <fstream>

/**
 * \param path of folder
 * 
 * \return path of files
 */
std::vector<std::string> ReadPath (const char* path)
{
  std::vector<std::string> path_;
  struct dirent* d;
  DIR* dr;
  dr = opendir(path);
  if (dr != NULL)
  {
    for (d = readdir (dr); d != NULL; d = readdir (dr))
    {
      std::string path__ = (d->d_name);
      std::string pathT = std::string(path) + '/' + path__;
      path_.push_back (pathT);
    }
    closedir (dr);
  }
  else
  {
    std::cerr << "\nError occurred!" << std::endl;
  }
  return path_;
}

/**
 * 
 */
void WriteFile (const std::string path, std::string context)
{
  std::ofstream file;
  file.open (path, std::ios::trunc | std::ios::out | std::ios::in);
  file <<  context << std::endl;
}

/**
 * 
 */
void ReadFile (const char* path)
{

}

#endif  // DATA_H