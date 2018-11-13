/*=========================================================================
  Copyright (c) GeometryFactory
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
  
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
     
=========================================================================*/
/**
 * @class vtkSEPReader
 * @brief Stanford Exploration Project files reader.
 *
 * This reader takes a .H file that points to a .H@ file and contains 
         all the information to interpret the raw data in the  .H@ file.
*/


#ifndef vtkSEPReader_h
#define vtkSEPReader_h
#include <vtkImageReader.h>
#include <VTK/IO/Image/vtkIOImageModule.h> // For export macro

class vtkCharArray;

class VTKIOIMAGE_EXPORT vtkSEPReader : public vtkImageReader
{
public:
  static vtkSEPReader *New();
  vtkTypeMacro(vtkSEPReader, vtkImageReader);
  /**
   * Is the given file a JPEG file?
   */
  int CanReadFile(const char* fname) VTK_OVERRIDE;
  
protected:
  vtkSEPReader();
  int RequestInformation(vtkInformation *request,
                         vtkInformationVector **inputVector,
                         vtkInformationVector *outputVector) VTK_OVERRIDE;
  
  virtual int ReadHeader();
};

#endif
