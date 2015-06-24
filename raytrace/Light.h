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
 * $Id: Light.h 5856 2015-06-06 22:48:38Z mshafae $
 *
 */

#include <iostream>

#include <GFXMath.h>
#include <GFXExtra.h>

#ifndef _LIGHT_H_
#define _LIGHT_H_


enum{
  LIGHT_NULL = 0,
  LIGHT_PHONG_POINT
};

class Light{
public:
  Light(const uint id = 0, const uint type = LIGHT_NULL);
  virtual ~Light( );

  Light& operator =(const Light& m);

  size_t id( ) const {
    return _id;
  }

  size_t type( ) const{
    return _type;
  }
  
  virtual Point3 position( ) const = 0;

  virtual std::ostream& write( std::ostream &out ) const {
    out << "Light (" << _type << ") " << _id << ":" << std::endl;
    return out;
  };
protected:
  uint _id;
  uint _type;
};

class PhongPointLight: public Light{
public:
  PhongPointLight( );

  PhongPointLight(const uint id, const Point3& position, const RGBAColor& ambient,
    const RGBAColor& diffuse, const RGBAColor& specular, const float const_atten,
    const float linear_atten, const float quadratic_atten);

  ~PhongPointLight( );

  Point3 position( ) const{
    return _position;
  }

  RGBAColor ambient( ) const{
    return _ambient;
  }

  RGBAColor diffuse( ) const{
    return _diffuse;
  }

  RGBAColor specular( ) const{
    return _specular;
  }

  float attenuation(float distance);
  
  std::ostream& write( std::ostream &out ) const {
    out << "PhongPointLight (" << _type << ") " << _id << ":" << std::endl;
    out << "\tposition: " << _position << std::endl;
    out << "\tambient color: " << _ambient << std::endl;
    out << "\tdiffuse color: " << _diffuse << std::endl;
    out << "\tspecular color: " << _specular << std::endl;
    out << "\tconstant atten: " << _const_atten << std::endl;
    out << "\tlinear atten: " << _linear_atten << std::endl;
    out << "\tquadratic atten: " << _quadratic_atten << std::endl;
    return out;
  };


private:
  Point3 _position;
  RGBAColor _ambient;
  RGBAColor _diffuse;
  RGBAColor _specular;
  float _const_atten;
  float _linear_atten;
  float _quadratic_atten;
};

std::ostream& operator <<( std::ostream &out, const Light &l );

#endif

