/*=========================================================================
  Copyright (c) GeometryFactory
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "SEP_header.h"

#include "vtkSEPReader.h"

#include "vtkCell.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkCharArray.h"
#include "vtkDataSet.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkInformationStringKey.h"
#include "vtkInformationVector.h"
#include "vtkMultiBlockDataSet.h"
#include "vtkNew.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPointSet.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"
#include "vtkStringArray.h"
#include "vtkUnstructuredGridWriter.h"

#include <boost/filesystem.hpp>

#include <iostream>
#include <string>

vtkStandardNewMacro(vtkSEPReader);

//----------------------------------------------------------------------------
// Description:
vtkSEPReader::vtkSEPReader()
{
  this->SetNumberOfInputPorts(0);
}


//-----------------------------------------------------------------------------
int vtkSEPReader::CanReadFile(const char *filename)
{
  std::string title(filename);
  std::string extension = title.substr(title.length()-2, 2);
  if (extension == ".H"
      || extension == "HH")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//-----------------------------------------------------------------------------
int vtkSEPReader::RequestInformation(vtkInformation *request,
                                      vtkInformationVector **inputVector,
                                      vtkInformationVector *outputVector)
{
  if (!this->ReadHeader()) return 0;

  return this->Superclass::RequestInformation(request,
                                              inputVector, outputVector);
}

//-----------------------------------------------------------------------------
int vtkSEPReader::ReadHeader()
{
  CGAL::SEP_header header(this->FileName);
  boost::filesystem::path headerFile(this->FileName);
  boost::filesystem::path dataFile(header.string_field("in"));
#if BOOST_FILESYSTEM_VERSION == 2
  dataFile = boost::filesystem::complete(dataFile, 
                                         boost::filesystem::complete(
                                           headerFile.parent_path()));
#else
  dataFile = boost::filesystem::absolute(dataFile, 
                                         boost::filesystem::absolute(
                                           headerFile.parent_path()));
#endif
  std::vector<char> un_const;
  for(std::size_t i=0; i<dataFile.string().length(); ++i)
  {
    un_const.push_back(dataFile.string()[i]);
  }
  this->SetFileName(un_const.data());
  this->HeaderSize = 0;
  this->DataScalarType = VTK_FLOAT;
  if(header.string_field("data_format") == "native_float" ||
     header.string_field("data_format") == "\"native_float\"")
  {
#ifdef VTK_WORDS_BIGENDIAN
    this->SwapBytes = 1;
#else
    this->SwapBytes = 0;
#endif
  }
  else
  {
#ifdef VTK_WORDS_BIGENDIAN
    this->SwapBytes = 0;
#else
    this->SwapBytes = 1;
#endif
  }
  this->FileDimensionality = header.dimension();
  
  for (size_t i = 0; (i < 3); ++i)
  {
    this->DataOrigin[i] = header.o(i+1);
    this->DataSpacing[i] = header.d(i+1);
    this->DataExtent[2*i] = 0;
    this->DataExtent[2*i + 1] = header.n(i+1)-1;
  }
  return 1;
}
