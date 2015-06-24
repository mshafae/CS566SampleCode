/* Your Name Here
 * somebody at something dot TLD
 * CS 484
 * September 20xx
 *
 */
/*
 * Copyright (c) 2005-2013 Michael Shafae
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
 * $Id: Scene.h 4419 2013-09-12 04:16:46Z mshafae $
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "Camera.h"
#include "Image.h"
#include "Material.h"
#include "Group.h"

#ifndef _SCENE_H_
#define _SCENE_H_

using namespace std;

class Scene{
	public:
		Scene( string inputFilename = "", string outputFilename = "", string depthFilename = "" );
		~Scene( );

		// Accessors
		Camera& camera( );
		Pixel& backgroundColor( );
		int numberOfMaterials( );
		void setCurrentMaterial( int i );
		Material* currentMaterial( );
		Group* group( );
		string& inputSceneFile( );
		string& outputFile( );
		string& depthFile( );
		
		void setInputSceneFile( string file );
		void setOutputFile( string file );
		void setDepthFile( string file );

		bool hasInputSceneFilePath( );
		bool hasOutputFilePath( );
		bool hasDepthFilePath( );

		bool parse( );

		// I/O
		void write( std::ostream &out ) const;

	private:
		string myInputSceneFile;
		string myOutputFile;
		string myDepthFile;
		Camera myCamera;
		Pixel myBackgroundColor;
		int myNumberOfMaterials;
		Material **materials;
		Material *myCurrentMaterial;
		Group *myGroup;
		ifstream inputFileStream;

		// For parsing
		char currentLine[255];
		char currentToken[255];
		int lineNumber;
		int tokenCount;
    int length;
    int i;
    int j;
		void nextToken( );
		void parseCamera( );
    void parseOrthographicCamera( );
		void nextOnLine( );
		bool areMoreTokens( );
		void advance( );
		void checkToken( const char *str, const char *stage  );
		void parseBackground( );
		float parseFloat( );
    double parseDouble( );
		int parseInt( );
		// Finish these...
		void parseViewPlane( );
		void parseMaterials( );
		void parseGroup( );
};

std::ostream& operator <<( std::ostream &out, const Scene &s );


#endif
