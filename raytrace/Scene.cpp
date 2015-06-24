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
 * $Id: Scene.cpp 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include "Scene.h"

Scene::Scene(std::string &inputFilename) :
	_inputSceneFile( inputFilename ),
  _currentMaterialIndex(0),
	_lineNumber(0),
	_tokenCount(0),
	_length(0),  
	_i(0),
	_j(0)
{

}

Scene::~Scene( ){
  for(std::vector<Material*>::iterator i = _materials.begin( ); i != _materials.end( ); ++i){
    delete (*i);
  }
  _materials.clear( );
  for(std::vector<GeometricObject*>::iterator i = _objects.begin( ); i != _objects.end( ); ++i){
    delete (*i);
  }
  _objects.clear( );
  for(std::vector<Light*>::iterator i = _lights.begin( ); i != _lights.end( ); ++i){
    delete (*i);
  }
  _lights.clear( );

  delete _camera;
}

Camera& Scene::camera( ){
	return *_camera;
}

ViewPlane& Scene::viewPlane( ){
  return _viewPlane;
}

RGBAColor& Scene::backgroundColor( ){
	return( _backgroundColor );
}

size_t Scene::lightCount( ) const{
  return _lights.size( );
}

Light* Scene::lightAtIndex(size_t i){
  if( i >= lightCount( ) ){
    throw std::range_error("Light index out of range");
  }
  return _lights[i];
}

size_t Scene::materialCount( ) const{
  return _materials.size( );
}

Material* Scene::materialAtIndex(size_t i){
  if( i >= materialCount( ) ){
    throw std::range_error("Material index out of range");
  }
  return _materials[i];
}


size_t Scene::objectCount( ) const{
  return _objects.size( );
}

GeometricObject* Scene::objectAtIndex(size_t i){
  if( i >= objectCount( ) ){
    throw std::range_error("Object index out of range");
  }
  return _objects[i];
}

std::string& Scene::inputSceneFile( ){
	return( _inputSceneFile );
}


bool Scene::parse( ){
  bool ret = true;
  _lineNumber = 0;
  _tokenCount = 0;
  
  _inputFileStream.open( _inputSceneFile.c_str( ), std::ios::in );
  if( _inputFileStream.fail( ) ){
    std::cerr << "Error opening \"" << _inputSceneFile << "\" for reading." << std::endl;
    exit( 1 );
  }
  std::cerr << "Starting Parse" << std::endl;

  _stage = (char*)"Camera";
  _parseCamera( );
  
  _stage = (char*)"ViewPlane";
  _parseViewPlane( );

  _stage = (char*)"Lights";
  _parseLights( );

  _stage = (char*)"Background";
  _parseBackground( );

  _stage = (char*)"Materials";
  _parseMaterials( );

  _stage = (char*)"Group";
  _parseGroup( );

  std::cerr << "Ending Parse" << std::endl;

  _inputFileStream.close( );
  
  return( ret );
}


void Scene::write( std::ostream &out ) const {
  out << "Input scene file: " << _inputSceneFile << std::endl;
  out << *_camera << std::endl;
  out << _viewPlane << std::endl;
  out << "Number of Lights: " << lightCount( ) << std::endl;
  out << "Lights:" << std::endl;
  for(unsigned int i = 0; i < lightCount( ); i++ ){
    out << _lights[i];
  }
  out << "Background Color: ";
  _backgroundColor.write_row(out) << std::endl;
  out << "Number of Materials: " << materialCount( ) << std::endl;
  out << "Materials:" << std::endl;
  for(unsigned int i = 0; i < materialCount( ); i++){
    out << _materials[i];
  }
  out << "Group:" << std::endl;
  for(unsigned int i = 0; i < objectCount( ); i++){
    _objects[i]->write(out);
  }
}




void Scene::_nextToken( ){
  if( !_inputFileStream.eof( ) ){
    _advance( );
    if( _areMoreTokens( ) ){
      _nextOnLine( );
    }else{
      do{
        _inputFileStream.getline( _currentLine, sizeof(_currentLine) );
        _lineNumber++;
        _length = std::strlen( _currentLine );
      }while( _length <= 0 );
      _i = 0;
      _j = 0;
      _advance( );
      if( _areMoreTokens( ) ){
        _nextOnLine( );
      }
    }
  }
}


void Scene::_checkToken( const char *str ){
	if( std::strcmp( _currentToken, str ) != 0 ){
    std::cerr << _stage << " parse error at line " << _lineNumber << " token " << _tokenCount << ": " << _currentToken << std::endl;
    std::cerr << "Current line: \'" << _currentLine << "\'" << std::endl;
    std::cerr << "Expected \'" << str << "\'" << std::endl;
		exit( 1 );
	}
}

void Scene::_advance( ){
  if( _currentLine[_j] == ' ' || _currentLine[_j] == '\t' || _currentLine[_j] == '\n' ){
    while( _currentLine[_j] == ' ' || _currentLine[_j] == '\t' || _currentLine[_j] == '\n' ){
      _j++;
    }
    _i = _j;
  }
}

bool Scene::_areMoreTokens( ){
  bool ret = false;
  if( _j < _length ){
    ret = true;
  }
  return( ret );
}

void Scene::_nextOnLine( ){
  while( _currentLine[_j] != ' ' && _currentLine[_j] != '\t' && _currentLine[_j] != '\n' && _currentLine[_j] != 0 ){
    _j++;
  }
  _currentLine[_j] = 0;
  size_t tmp = _i;
  if( _i != _j ){
    while( _i <= _j ){
      _currentToken[_i - tmp] = _currentLine[_i];
      _i++;
    }
  }
  _j++;
  _i = _j;
}



void Scene::_parseCamera( ){
  _nextToken( );
  if( std::strcmp( _currentToken, "OrthographicCamera") == 0 ){
    _parseOrthographicCamera( );
  }else if( std::strcmp( _currentToken, "PerspectiveCamera") == 0 ){
    _parsePerspectiveCamera( );
  }else if( std::strcmp( _currentToken, "SimplePerspectiveCamera") == 0 ){
    _parseSimplePerspectiveCamera( );
  }else{
  	_checkToken( "OrthographicCamera | PerspectiveCamera | SimplePerspectiveCamera");
  }
}

void Scene::_parseOrthographicCamera( ){
  float position[3], lookAt[3], up[3];
	_checkToken( "OrthographicCamera" );
	_nextToken( );
	_checkToken( "{" );
	_nextToken( );
	_checkToken( "position" );
	for( int i = 0; i < 3; i++ ){
		_nextToken( );
		position[i] = _parseFloat( );
	}
  Point3 pPosition(position);
  
	_nextToken( );
	_checkToken( "lookAt" );
	for( int i = 0; i < 3; i++ ){
		_nextToken( );
		lookAt[i] = _parseFloat( );
	}
  Point3 pLookAt(lookAt);

	_nextToken( );
	_checkToken( "up" );
	for( int i = 0; i < 3; i++ ){
		_nextToken( );
		up[i] = _parseFloat( );
	}
  Vec3 vUp(up);

	_nextToken( );
	_checkToken( "}" );

  // Fill me in!
}

void Scene::_parsePerspectiveCamera( ){
  assert(1 == 0);
}

void Scene::_parseSimplePerspectiveCamera( ){
  assert(1 == 0);
}

void Scene::_parseViewPlane( ){
	size_t w, h, s;
  double p;
	_nextToken( );
	_checkToken( "ViewPlane");
	_nextToken( );
	_checkToken( "{");
	_nextToken( );
	_checkToken( "width");
	_nextToken( );
	w = _parseInt( );

	_nextToken( );
	_checkToken( "height" );
	_nextToken( );
	h = _parseInt( );

	_nextToken( );
	_checkToken( "pixelsize" );
	_nextToken( );
	p = _parseFloat( );
	
  _nextToken( );
  _checkToken( "sampleCount" );
  _nextToken( );
  s = _parseInt( );

	_nextToken( );
	_checkToken( "}" );

  // Fill me in!
}

void Scene::_parseLights( ){
  _nextToken( );
  _checkToken( "Lights" );
  _nextToken( );
  _checkToken( "{");
  _nextToken( );
  _checkToken( "numLights" );
  _nextToken( );
  int lightCount = _parseInt( );
  for( int i = 0; i < lightCount; i++ ){
    _nextToken( );

    if( std::strcmp( _currentToken, "PointLight") == 0 ){
      _parsePointLight(i);
    }else if( std::strcmp( _currentToken, "DirectionalLight") == 0 ){
      _parseDirectionalLight(i);
    }else if( std::strcmp( _currentToken, "SomeOtherLight") == 0 ){
      assert(0 == 1);
    }else{
      _checkToken("PointLight | DirectionalLight");
    }
  }
  _nextToken( );
  _checkToken("}");
}

void Scene::_parsePointLight(uint id){
  float vec[4];
  _checkToken( "PointLight");
  _nextToken( );
  _checkToken( "{");
  _nextToken( );
  _checkToken("position");
  for( int i = 0; i < 3; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  Point3 position(vec);

  _nextToken( );
  _checkToken("ambientColor");
  for( int i = 0; i < 4; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  RGBAColor ambient(vec);

  _nextToken( );
  _checkToken( "diffuseColor");
  for( int i = 0; i < 4; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  RGBAColor diffuse(vec);

  _nextToken( );
  _checkToken("specularColor");
  for( int i = 0; i < 4; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  RGBAColor specular(vec);
  _nextToken( );
  _checkToken("constant_attenuation");
  _nextToken( );
  float constant_attenuation = _parseFloat( );

  _nextToken( );
  _checkToken("linear_attenuation");
  _nextToken( );
  float linear_attenuation = _parseFloat( );

  _nextToken( );
  _checkToken("quadratic_attenuation");
  _nextToken( );
  float quadratic_attenuation = _parseFloat( );

  _nextToken( );
  _checkToken( "}");

  // Fill me in!
}

void Scene::_parseDirectionalLight(uint id){
  assert(1 == 0);
}

void Scene::_parseBackground( ){
	unsigned char vec[3];
	_nextToken( );
	_checkToken( "Background" );
	_nextToken( );
	_checkToken( "{");
	
	_nextToken( );
	_checkToken( "color" );
	for( int i = 0; i < 3; i++ ){
		_nextToken( );
		vec[i] = _parseFloat( );
	}
	
	_nextToken( );
	_checkToken( "}" );

  // Fill me in!
}

void Scene::_parseMaterials( ){
  _nextToken( );
  _checkToken( "Materials" );
  _nextToken( );
  _checkToken( "{");
  _nextToken( );
  _checkToken( "numMaterials" );
  _nextToken( );
  int materialCount = _parseInt( );
  for( int i = 0; i < materialCount; i++ ){
    _nextToken( );

    if( std::strcmp( _currentToken, "PhongMaterial") == 0 ){
      _parsePhongMaterial(i);
    }else if( std::strcmp( _currentToken, "SomeOtherMaterial") == 0 ){
      assert(0 == 1);
    }else if( std::strcmp( _currentToken, "AnotherMaterial") == 0 ){
      assert(0 == 1);
    }else{
      _checkToken( "PhongMaterial | tbd");
    }
  }
  _nextToken( );
  _checkToken("}");
}

void Scene::_parsePhongMaterial(uint id){
  float vec[4];
  _checkToken( "PhongMaterial");
  _nextToken( );
  _checkToken( "{");
  _nextToken( );
  _checkToken("ambientColor");
  for( int i = 0; i < 4; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  RGBAColor ambient(vec);
  _nextToken( );
  _checkToken( "diffuseColor");
  for( int i = 0; i < 4; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  RGBAColor diffuse(vec);
  _nextToken( );
  _checkToken("specularColor");
  for( int i = 0; i < 4; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  RGBAColor specular(vec);
  _nextToken( );
  _checkToken("shininess");
  float shininess = _parseFloat( );
  _nextToken( );
  float indexOfRefraction = 10;
  if( std::strcmp(_currentToken, "indexOfRefraction") == 0 ){
    indexOfRefraction = _parseFloat( );
  }
  _nextToken( );
  _checkToken( "}");

  // Fill me in!
}

void Scene::_parseGroup( ){
	_nextToken( );
	_checkToken( "Group" );
	_nextToken( );
	_checkToken( "{");
	_nextToken( );
	_checkToken( "numObjects" );
  _nextToken( );
  int objectCount = _parseInt( );
  int i = 0;
  _nextToken( );
  while( i < objectCount ){
    if( std::strcmp( _currentToken, "MaterialIndex") == 0 ){
      _parseMaterialIndex( );
    }else if( std::strcmp( _currentToken, "Group") == 0 ){
      assert(0 == 1);
      _parseGroup( );
      i += 1;
    }else if( std::strcmp( _currentToken, "Transform") == 0 ){
      assert(0 == 1);
    }else if( std::strcmp( _currentToken, "Sphere") == 0 ){
      _parseSphere(i);
      i += 1;
    }else if( std::strcmp( _currentToken, "Plane") == 0 ){
      assert(0 == 1);
      i += 1;
    }else if( std::strcmp( _currentToken, "Triangle") == 0 ){
      assert(0 == 1);
      i += 1;
    }else if( std::strcmp( _currentToken, "TriangleMesh") == 0 ){
      assert(0 == 1);
      i += 1;
    }else{
      _checkToken( "Group | tbd");
    }
    _nextToken( );
  }
}

void Scene::_parseMaterialIndex( ){
  _checkToken( "MaterialIndex");
  _nextToken( );
  _currentMaterialIndex = _parseInt( );
}

void Scene::_parseSphere(int i){
  float vec[3];
  _checkToken( "Sphere");
  _nextToken( );
  _checkToken( "{" );
  _nextToken( );
  _checkToken( "center" );
  for( int i = 0; i < 3; i++ ){
    _nextToken( );
    vec[i] = _parseFloat( );
  }
  Point3 center(vec[0], vec[1], vec[2]);
  _nextToken( );
  _checkToken( "radius" );
  _nextToken( );
  float radius = _parseFloat( );
  _nextToken( );
  _checkToken("}");

  // Fill me in!
}


float Scene::_parseFloat( ){
  char *endptr;
  float ret = std::strtof( _currentToken, &endptr );
  return( ret );
}

double Scene::_parseDouble( ){
  char *endptr;
  double ret = std::strtod( _currentToken, &endptr );
  return( ret );
}

int Scene::_parseInt( ){
  char *endptr;
  int ret = strtol( _currentToken, &endptr, 10 );
  return( ret );
}



std::ostream& operator <<( std::ostream &out, const Scene &s ){
	s.write( out );
	return( out );
}
