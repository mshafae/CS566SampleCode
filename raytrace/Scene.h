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
 * $Id: Scene.h 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#include <GFXMath.h>
#include <GFXExtra.h>

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "ViewPlane.h"
#include "GeometricObject.h"

#ifndef _SCENE_H_
#define _SCENE_H_

class Scene{
	public:
  Scene( ){ };
  Scene( std::string &inputFilename );
	~Scene( );
  
	// Accessors
	Camera& camera( );
  ViewPlane& viewPlane( );

	RGBAColor& backgroundColor( );

  size_t lightCount( ) const;
  Light* lightAtIndex(size_t i);
  
	size_t materialCount( ) const;
  Material* materialAtIndex(size_t i);
  
  size_t objectCount( ) const;
  GeometricObject* objectAtIndex(size_t i);

	std::string& inputSceneFile( );

	bool parse( );

	// I/O
	void write( std::ostream &out ) const;

  private:
	std::string _inputSceneFile;
	Camera* _camera;
	ViewPlane _viewPlane;
	RGBAColor _backgroundColor;

	std::vector<Material*> _materials;
	size_t _currentMaterialIndex;

  std::vector<Light*> _lights;

	std::vector<GeometricObject*> _objects;

	std::ifstream _inputFileStream;

	// For parsing
	char _currentLine[255];
	char _currentToken[255];

	char *_stage;
	int _lineNumber;
	int _tokenCount;
	size_t _length;
	size_t _i;
	size_t _j;


  void _nextToken( );

  void _checkToken( const char *str );
  void _advance( );
  bool _areMoreTokens( );
  void _nextOnLine( );


	void _parseCamera( );
	void _parseOrthographicCamera( );
	void _parsePerspectiveCamera( );
	void _parseSimplePerspectiveCamera( );

  void _parseLights( );
  void _parsePointLight(uint id);
  void _parseDirectionalLight(uint id);

	void _parseBackground( );

	void _parseViewPlane( );

	void _parseMaterials( );
  void _parsePhongMaterial(uint id);

	void _parseGroup( );
  void _parseMaterialIndex( );
  void _parseSphere(int i);

  float _parseFloat( );
  double _parseDouble( );
  int _parseInt( );

};

std::ostream& operator <<( std::ostream &out, const Scene &s );


#endif
