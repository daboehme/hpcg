//@HEADER
// ************************************************************************
// 
//               Mantevo: A collection of mini-applications for HPC
//                 Copyright (2008) Sandia Corporation
// 
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
// 
// This library is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
//  
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA
// Questions? Contact Michael A. Heroux (maherou@sandia.gov) 
// 
// ************************************************************************
//@HEADER

/*!
 @file YAML_Doc.hpp

 HPCG YAML classes
 */

// Changelog
//
// Version 0.1
// - Initial version.
//
/////////////////////////////////////////////////////////////////////////

#ifndef YAML_DOC_HPP
#define YAML_DOC_HPP
#include <string>
#include "YAML_Element.hpp"

//! The Mantevo YAML_Doc class for the uniform collecting and reporting of performance data for mini-applications

/*!

The YAML_Doc class works in conjuction with the YAML_Element class to facilitate easy collecting and reporting of YAML-formatted
data that can be then registered with the Mantevo results collection website.

\code

//EXAMPLE CODE FOR GENERATING YAML

  YAML_Doc doc("hpcg","0.1");
  doc.add("final_residual",1.4523e-13);
  doc.add("time","4.893"); 
 
//note: the following line will remove the data (4.890) associated with "time"
  doc.get("time")->add("total",4.243);

//note:  the following line will likewise remove the data (1.243) associated with "time"
  doc.get("time")->get("total")->add("time",2.457);
  doc.get("time")->get("total")->add("flops",4.88e5);
  doc.get("time")->add("ddot",1.243);
  doc.get("time")->add("sparsemv","");
  doc.get("time")->get("sparsemv")->add("time",0.3445);
  doc.get("time")->get("sparsemv")->add("overhead","");
  doc.get("time")->get("sparsemv")->get("overhead")->add("time",0.0123);
  doc.get("time")->get("sparsemv")->get("overhead")->add("percentage",0.034);
  cout << doc.generateYAML() << endl; 
  return 0;

\endcode

Below is the output generated by the above code:

\verbatim

final_residual: 1.4523e-13
time: 
  total:
    time: 2.457
    flops: 4.88e5
  ddot: 1.243
  sparsemv:
    time: 0.3445
    overhead:
      time: 0.0123
      percentage: 0.034

\endverbatim

\note {No value is allowed to be attached to a key that has children.  If children are added to a key, the value is simply set to "".}

*/
class YAML_Doc: public YAML_Element {
  public:
  //! Constructor: accepts mini-application name and version as strings, optionally accepts directory and file name for printing results.
  /*!
    The sole constructor for this class accepts and name and version number for the mini-application as well as optional directory 
    and file name information for results that are generated by the generateYAML() method.
    \param miniApp_Name (in) string containing name of the mini-application
    \param miniApp_Version (in) string containing the version of the mini-application
    \param destination_Directory (in, optional) path of diretory where results file will be stored, relative to current working directory. 
           If this value is not supplied, the results file will be stored in the current working directory.  If the directory does not exist
	   it will be created.
    \param destination_FileName (in, optional) root name of the results file.  A suffix of ".yaml" will be automatically appended.  If no
           file name is specified the filename will be constructed by concatenating the miniAppName + miniAppVersion + ".yaml" strings.
  */
  YAML_Doc(const std::string& miniApp_Name, const std::string& miniApp_Version, const std::string& destination_Directory = "", const std::string& destination_FileName = "");
  //! Destructor
  ~YAML_Doc();
  //! Generate YAML results to standard out and to a file using specified directory and filename, using current directory and miniAppName + miniAppVersion + ".yaml" by default
  std::string generateYAML();

protected:
  std::string miniAppName; //!< the name of the application that generated the YAML output
  std::string miniAppVersion; //!< the version of the application that generated the YAML output
  std::string destinationDirectory; //!< the destination directory for the generated the YAML output
  std::string destinationFileName; //!< the filename for the generated the YAML output
};
#endif // YAML_DOC_HPP

