/*
 * Copyright (c) 2005-2015 Michael Shafae
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $Id: raytrace.cpp 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <stdexcept>
#include <StopWatch.h>
#include "Scene.h"
#include "RayFactory.h"
#include "ShadingRecord.h"
#include "Image.h"
#include "shader.h"
 
std::string gProgramName;

void usage( std::string message = "" ){
  std::cerr << message << std::endl;
  std::cerr << gProgramName << " -i <inputfile> -o <outputfile> -d <depthfile>" << std::endl;
  std::cerr << "          -or-" << std::endl;
  std::cerr << gProgramName << " --input <inputfile> --output <outputfile> --depth <depthfile>" << std::endl;
	
}

std::string dirname(std::string path){
  std::size_t index = path.rfind("/");
  return path.substr(index+1, path.size( ));
}

std::string basename(std::string& filename, std::string& extension){
  std::size_t index = filename.rfind(extension);
  if( index == std::string::npos ){
    throw std::range_error("Could not find " + extension + " in string " + filename);
  }
  return filename.substr(0, index);
}

int main( int argc, char **argv ){
  StopWatch total;
  total.start( );
  gProgramName = dirname(std::string(argv[0]));
  std::string inputFile, outputFile, depthFile;
  char ch;
    static struct option longopts[] = {
    { "input", required_argument, NULL, 'i' },
    { "output", required_argument, NULL, 'o' },
    { "depth", required_argument, NULL, 'd' },
    { "verbose", no_argument, NULL, 'v' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
  };
  while( (ch = getopt_long(argc, argv, "i:o:d:vh", longopts, NULL)) != -1 ){
		switch( ch ){
			case 'i':
				// input file
				inputFile = std::string(optarg);
				break;
			case 'o':
				// image output file
				outputFile = std::string(optarg);
				break;
			case 'd':
				// depth output file
				depthFile = std::string( optarg );
				break;
      case 'v':
        // set your flag here.
        break;
      case 'h':
        usage( );
        break;
			default:
				// do nothing
				break;
		}
	}
	argc -= optind;
	argv += optind;
  if( inputFile == "" ){
    usage( "Must provide an input scene file" );
    exit(1);
  }

  std::string base;
  try{
    std::string ext(".txt");
    base = basename(inputFile, ext);
  }
  catch( std::runtime_error& e ){
    std::cerr << __LINE__ << " :Exception occurred: " << e.what( ) << std::endl;
    exit(1);
  }
  
  base = dirname(base);
  
  if( outputFile == "" ){
    outputFile = base + std::string("-output.png");
    std::cout << "No output file specified, using default: " << outputFile << std::endl;
  }
  
  if( depthFile == "" ){
    depthFile = base + std::string("-depth.png");
    std::cout << "No depth file specified, using default: " << depthFile << std::endl;
  }

  Scene theScene(inputFile);

  theScene.parse();
#ifndef NDEBUG
  std::cout << theScene << std::endl;
#endif

  // Fill me in!
  
	return( 0 );
}
