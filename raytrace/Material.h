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
 * $Id: Material.h 5861 2015-06-08 17:46:13Z mshafae $
 *
 */

#include <iostream>
#include <GFXMath.h>
#include <GFXExtra.h>
 
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

enum{
  MATERIAL_NULL = 0,
  MATERIAL_PHONG
};

class Material{
public:
  Material( );
  Material(const uint id, const uint type);
  virtual ~Material( );

  size_t id( ) const {
    return _id;
  }

  size_t type( ) const{
    return _type;
  }
  
  virtual std::ostream& write( std::ostream &out ) const {
    out << "Material (" << _type << ") " << _id << ":" << std::endl;
    return out;
  };
protected:
  uint _id;
  uint _type;
};

class PhongMaterial : public Material{
public:
  PhongMaterial( );
  PhongMaterial(uint id, const RGBAColor& ambient, const RGBAColor& diffuse, const RGBAColor& specular, const float shininess);

  ~PhongMaterial( ){ };

  RGBAColor ambient( ){
    return _ambient;
  }

  RGBAColor diffuse( ){
    return _diffuse;
  }
  
  RGBAColor specular( ){
    return _specular;
  }
  
  float shininess( ){
    return _shininess;
  }
  
  std::ostream& write( std::ostream &out ) const {
    out << "Material (Phong:" << _type << ") " << _id << ":" << std::endl;
    out << "\tAmbient color: ";
    _ambient.write_row(out) << std::endl;
    out << "\tDiffuse color: ";
    _diffuse.write_row(out) << std::endl;
    out << "\tSpecular color: ";
    _specular.write_row(out) << std::endl;
    out << "\tShininess: " << _shininess << std::endl;
    return out;

  };
protected:
  RGBAColor _ambient;
  RGBAColor _diffuse;
  RGBAColor _specular;
  float _shininess;
};

std::ostream& operator <<( std::ostream &out, const Material &m );

#endif
