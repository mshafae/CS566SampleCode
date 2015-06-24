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
 * $Id: GeometricObject.h 5869 2015-06-09 10:02:58Z mshafae $
 *
 */

#include <GFXMath.h>
#include <GFXExtra.h>

#include "Material.h"
#include "ShadingRecord.h"

#ifndef _GEOMETRIC_OBJECT_H_
#define _GEOMETRIC_OBJECT_H_

enum{
  GEOMETRY_NULL = 0,
  GEOMETRY_SPHERE,
  GEOMETRY_PLANE,
  GEOMETRY_TRIANGLE
};

class GeometricObject{  
public:
  GeometricObject( const uint id, const uint type, Material* material );
  
  virtual ~GeometricObject( );

  GeometricObject& operator =(const GeometricObject& obj);

  uint id( ) const { return _id;};

  uint type( ) const { return _type;};

  Material* material( ) const { return _material;};

  virtual bool intersect(const Ray& r, const Interval& interval, ShadingRecord& sr) const = 0;

  virtual std::ostream& write( std::ostream &out ) const {
    out << "Geometric Object (" << _type << ") " << _id << ":" << std::endl;
    return out;
  };
protected:
  uint _id;
  uint _type;
  Material* _material;
};

class Sphere : public GeometricObject{
public:
  Sphere(const uint id, Material* material, const float radius, const Point3& center);

  ~Sphere( );

  Sphere& operator =(const Sphere& s);

  bool intersect(const Ray& r, const Interval& interval, ShadingRecord& sr);

  std::ostream& write( std::ostream &out ) const {
    out << "Sphere " << _id << ":" << std::endl;
    out << "\tMaterial: " << material( ) << std::endl;
    out << "\tRadius: " << _radius << std::endl;
    out << "\tCenter: ";
    _center.write_row(out) << std::endl;
    return out;
  };

private:
  float _radius;
  Point3 _center;
};

std::ostream& operator <<( std::ostream &out, const GeometricObject &obj );
#endif
