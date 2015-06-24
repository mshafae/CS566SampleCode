/*
 * Thie file has been copied directly from
 * <https://github.com/mshafae/CS484SampleCode/tree/master/GFXMath>
 *
 * This file is incomplete. Students typically complete this
 * exercise in CPSC 484.
 *
 * To complete this file, look for:
 *     // Fill me in!
 * and then fill in the code required.
 *
 */

/*
 * Copyright (c) 2015 Michael Shafae
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
 * $Id: GFXMath.h 5509 2015-02-10 10:04:54Z mshafae $
 *
 */

#pragma clang diagnostic ignored "-Wunused-function"

#ifndef _GFXMATH_H_
#define _GFXMATH_H_
#ifdef WIN32
#pragma once
#define _USE_MATH_DEFINES 1
#endif

#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>

#ifdef __linux__
#ifdef minor
#undef minor
#endif
#ifdef major
#undef major
#endif
#endif

#ifndef IOS_FP_PRECISION
#define IOS_FP_PRECISION 5
#endif

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

#ifndef PI_OVER_ONE_EIGHTY
#define PI_OVER_ONE_EIGHTY 0.01745329251994329547437168059786927188
#endif

#ifndef ONE_EIGHTY_OVER_PI
#define ONE_EIGHTY_OVER_PI 57.29577951308232286464772187173366546631
#endif

template <typename T>
static inline T sqr(T a)
{
  return a * a;
}

template <typename T>
static inline T _pow(T a, unsigned int exponent)
{
  T product = T(1);
  for(int i = 0; i < exponent; i++){
    product *= a;
  }
  return product;
}



#ifndef MSGFX_FP
#define MSGFX_FP

/*
 * One option is to make the Vector and Matrix classes
 * aware of how much precision is really needed. Barring
 * that, let's have a few templated functions that help
 * in determining if two floating point values are equal.
 */

/*
 * These two defines are useful if you want to remember
 * how much precision you'll have with your float or double
 * types. However, 7 decimal places may be overkill for our
 * work. Consider defining your own macro or static variable
 * that defines how much precision you want and need.
 *
 * Single precision floating point numbers have a
 * significand of 24 bits which is about 7 decimal places.
 * Double precision floating point numbers have a
 * significand of 53 bits which is about 16 decimal places.
 */
#define FP_SP_EPSILON 1e-6
#define FP_DP_EPSILON 1e-15

template <typename T>
static bool fpEqual(T a, T b, double epsilon)
{
  return (a == b) || ((a - epsilon) < b && (a + epsilon) > b);
}

template <typename T>
static bool fpNotEqual(T a, T b, double epsilon)
{
  return (a != b) && ((a - epsilon) > b || (a + epsilon) < b);
}

#endif

template <typename T>
static T degreesToRadians(T degrees)
{
  return degrees * static_cast<T>(PI_OVER_ONE_EIGHTY);
}

template <typename T>
static T radiansToDegrees(T radians)
{
  return radians * static_cast<T>(ONE_EIGHTY_OVER_PI);
}

/*
 * See Park & Miller's paper Random Number Generators: Good Ones are 
 * Hard to Find, Communications of the ACM, October 1988, Vol. 31, no. 10
 *
 * In a nutshell, this is Lehmer's parametric multiplicative
 * linear congruential algorithm to generate a series of psuedo random
 * unsigned integers. MS Window's standard library has a broken
 * implementation so it's included here in case someone needs to use
 * it.
 */
// This should be a Singleton but it's not.
class LPMRandom{
public:
  LPMRandom( unsigned int seed = 1 ){
    if(seed < 1 || seed >= m){
      seed = 1234557890;
    }
    this->seed = seed;
  };
  void reseed(unsigned int s){
    seed = s;
  }
  unsigned int operator ()(void){
    return _rand( );
  }
  operator int( ){
    return static_cast<int>(_rand( ));
  }
  operator float( ){
    // invM = 1 / m
    float invM = 0.0000000004656612875245797;
    return _rand( ) * invM;
  }
  operator double( ){
    // invM = 1 / m
    double invM = 0.0000000004656612875245797;
    return _rand( ) * invM;
  }
  float frand( ){
    return static_cast<float>(*this);
  }
  double drand( ){
    return static_cast<double>(*this);
  }
  int irand( ){
    return static_cast<int>(*this);
  }
private:
  unsigned int seed;
  // The multiplier -- 7**5 = 16807
  const static unsigned int a = 16807;
  // The modulo -- a large prime number
  const static unsigned int m = 2147483647;
  // quotient -- m div a
  const static unsigned int q = 127773;
  // remainder -- m mod a
  const static unsigned int r = 2836;
  unsigned int _rand( ){
    unsigned int lo, hi;
    int test;
    hi = seed / q;
    lo = seed % q;
    test = a * lo - r * hi;
    if( test < 0 ){
      test += m;
    }
    seed = test % m;
    return seed;
  }
}; // end class LPMRandom

template <typename T, const int length>
class VecN{
public:
  typedef class VecN<T,length> this_t;
  typedef T component_t;

  VecN( ){};

  VecN(const VecN& rhs){
    assign(rhs);
  }
  
  VecN(const VecN* rhs){
    assign(rhs);
  }
  
  VecN(const T* array){
    assign(array);
  }
  
  VecN(T const & s){
    for( int i = 0; i < length; i++ ){
      data[i] = s;
    }
  }
  
  VecN& operator =(const VecN& rhs){
    assign(rhs);
    return *this;
  }

  VecN& operator =(const VecN* rhs){
    assign(rhs);
    return *this;
  }
  
  VecN& operator =(const T& s){
    assign(s);
    return *this;
  }
  
  VecN operator +(const VecN& rhs) const{
    VecN sum;
    // Fill me in!
    return sum;
  }
  
  VecN& operator +=(const VecN& rhs){
    return *this = *this + rhs;
  }

  VecN operator -( ) const{
    VecN rv;
    // Fill me in!
    return rv;
  }
  
  VecN operator -(const VecN& rhs) const{
    VecN difference;
    // Fill me in!
    return difference;
  }
  
  VecN& operator -=(const VecN& rhs){
    return *this = *this - rhs;
  }
  
  VecN operator *(const T& s) const{
    VecN rv;
    // Fill me in!
    return rv;
  }
  
  VecN operator *=(const T& s){
    assign(*this * s);
    return *this;
  }
  
  VecN operator /(const T& s) const{
    VecN rv;
    // Fill me in!
    return rv;
  }
  
  VecN operator /=(const T& s){
    assign(*this / s);
    return *this;
  }
  
  T& operator [](unsigned int i){
    if( i < length ){
      return data[i];
    }else{
      throw( "Index out of range" );
    }
  }
  
  const T& operator [](unsigned int i) const{
    if( i < length ){
      return data[i];
    }else{
      throw( "Index out of range" );
    }
  }
  
  bool operator ==(const VecN& rhs) const{
    bool rv = false;
    // Fill me in!
    return rv;
  }
  
  bool operator !=(const VecN& rhs) const{
    bool rv = false;
    // Fill me in!
    return rv;
  }
  
  static int size( ){
    return length;
  }
  
  operator T*( ){
    return &data[0];
  }

  operator const T*( ) const{
    return &data[0];
  }
  
  std::ostream& write( std::ostream &out ) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION)
      << "(";
    for( int i = 0; i < length; i++ ){
      if( i < (length - 1) ){
        out << " " << data[i] << std::endl;
      }else{
        out << " " << data[i] << " )" << std::endl;
      }
    }
    out.unsetf( std::ios::fixed );
    return( out );
  }
  
  std::ostream& write_row( std::ostream &out) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION)
      << "(";
    for( int i = 0; i < length; i++ ){
      if( i < (length - 1) ){
        out << data[i] << ", ";
      }else{
        out << data[i] << ")" << std::endl;
      }
    }
    out.unsetf( std::ios::fixed );
    return( out );
  }
  
  std::ostream& description( std::ostream &out = std::cerr ) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION) <<
      "<Vec"<< length << " " << this << "> ";
    out << "(";
    for( int i = 0; i < length; i++ ){
      if( i < (length - 1) ){
        out << data[i] << ", ";
      }else{
        out << data[i] << ")" << std::endl;
      }
    }
    out.unsetf( std::ios::fixed );
    return( out );
  }
  
  
protected:
  T data[length];

  inline void assign(const VecN& rhs){
    for( int i = 0; i < length; i++ ){
      data[i] = rhs.data[i];
    }
  }

  inline void assign(const T& s){
    for( int i = 0; i < length; i++ ){
      data[i] = s;
    }
  }
  
  inline void assign(const T* array){
    for( int i = 0; i < length; i++ ){
      data[i] = array[i];
    }
  }
  
  
  inline void assign(const VecN* rhs){
    for( int i = 0; i < length; i++ ){
      data[i] = rhs->data[i];
    }
  }

}; // end class VecN

template <typename T>
class TVec1 : public VecN<T, 1>{
public:
  typedef VecN<T, 1> base;
  TVec1( ) : base( ){ }
  TVec1(const base& v) : base(v){ }
  explicit TVec1(const base* v) : base(v){ }
  explicit TVec1(T x){
    base::data[0] = x;
  }
}; // end class TVec1

template <typename T>
class TVec2 : public VecN<T, 2>{
public:
  typedef VecN<T, 2> base;
  TVec2( ) : base( ){ }
  TVec2(const base& v) : base(v){ }
  explicit TVec2(const base* v) : base(v){ }
  explicit TVec2(T x, T y){
    base::data[0] = x;
    base::data[1] = y;
  }
  base perp( ){
    // Fill me in!
    return base(0, 0);
  }
}; // end class TVec2

template <typename T>
class TVec3 : public VecN<T, 3>{
public:
  typedef VecN<T, 3> base;
  TVec3( ) : base( ){ }
  TVec3(const base& v) : base(v){ }
  explicit TVec3(const base* v) : base(v){ }
  explicit TVec3(T x, T y, T z){
    base::data[0] = x;
    base::data[1] = y;
    base::data[2] = z;
  }
  
  explicit TVec3(const TVec2<T>& v, T z){
    base::data[0] = v[0];
    base::data[1] = v[1];
    base::data[2] = z;
  }
}; // end class TVec3

template <typename T>
class TVec4 : public VecN<T, 4>{
public:
  typedef VecN<T, 4> base;
  TVec4( ) : base( ){ }
  TVec4(const base& v) : base(v){ }
  explicit TVec4(const base* v) : base(v){ }
  explicit TVec4(T x, T y, T z, T w){
    base::data[0] = x;
    base::data[1] = y;
    base::data[2] = z;
    base::data[3] = w;
  }
  
  explicit TVec4(const TVec2<T>& v, T z, T w){
    base::data[0] = v[0];
    base::data[1] = v[1];
    base::data[2] = z;
    base::data[3] = w;
  }
  
  explicit TVec4(const TVec3<T>& v, T w){
    base::data[0] = v[0];
    base::data[1] = v[1];
    base::data[2] = v[2];
    base::data[3] = w;
  }
}; // end class TVec4

template <typename T, int length>
static const VecN<T, length> operator *(T lhs, const VecN<T, length>& rhs){
  return rhs * lhs;
}

template <typename T>
static const TVec1<T> operator /(T lhs, const TVec1<T>& rhs){
  return TVec1<T>(lhs / rhs[0]);
}

template <typename T>
static const TVec2<T> operator /(T lhs, const TVec2<T>& rhs){
  return TVec2<T>(lhs / rhs[0], lhs / rhs[1]);
}

template <typename T>
static const TVec3<T> operator /(T lhs, const TVec3<T>& rhs){
  return TVec3<T>(lhs / rhs[0], lhs / rhs[1], lhs / rhs[2]);
}

template <typename T>
static const TVec4<T> operator /(T lhs, const TVec4<T>& rhs){
  return TVec4<T>(lhs / rhs[0], lhs / rhs[1], lhs / rhs[2], lhs / rhs[3]);
}

template <typename T, int length>
static T dot(const VecN<T, length>& a, const VecN<T, length>& b){
  T rv = static_cast<T>(0);
  // Fill me in!
  return rv;
}

template <typename T, int length>
static T squaredLength(const VecN<T, length>& v){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T, int length>
static T length(const VecN<T, length>& v){
  return sqrt(squaredLength(v));
}

template <typename T, int _length>
static VecN<T, _length> normalize(const VecN<T, _length>& v){
  VecN<T, _length> rv;
  // Fill me in!
  return rv;
}

template <typename T, int length>
static T distance(const VecN<T, length>& a, const VecN<T, length>& b){
  T rv;
  // Fill me in!
  return rv;
}

template <typename T>
static T angleInRadians(const TVec2<T>& a, const TVec2<T>& b){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T>
static T angleInRadians(const TVec3<T>& a, const TVec3<T>& b){
  T rv(0);
  // Fill me in!
  return rv;
}

template <typename T>
static T angle(const TVec2<T>& a, const TVec2<T>& b){
  // In degrees!
  return radiansToDegrees(angleInRadians(a, b));
}

template <typename T>
static T angle(const TVec3<T>& a, const TVec3<T>& b){
  // In degrees!
  return radiansToDegrees(angleInRadians(a, b));
}


template <typename T>
static VecN<T, 3> cross(const VecN<T, 3>& a, const VecN<T, 3>& b){
  // Fill me in!
  return TVec3<T>(0, 0, 0);
}

template <typename T, int length>
std::ostream& operator <<( std::ostream &out, const VecN<T, length> &v ){
  return(v.write_row( out ));
}

typedef TVec1<float> Vec1;
typedef TVec1<double> Vec1d;
typedef TVec1<int> Vec1i;

typedef TVec2<float> Vec2;
typedef TVec2<double> Vec2d;
typedef TVec2<int> Vec2i;

typedef TVec3<float> Vec3;
typedef TVec3<double> Vec3d;
typedef TVec3<int> Vec3i;

typedef TVec4<float> Vec4;
typedef TVec4<double> Vec4d;
typedef TVec4<int> Vec4i;


template <typename T, const int w, const int h>
class MatNM{
public:
  typedef class MatNM<T, w, h> this_t;
  typedef class VecN<T, h> vec_t;
  
  MatNM( ) {};
  
  MatNM(const MatNM& rhs){
    assign(rhs);
  }
  
  explicit MatNM(const T s){
    assign(s);
  }
  
  explicit MatNM(const vec_t& v){
    assign(v);
  }
  
  explicit MatNM(const T* array){
    assign(array);
  }  
  
  MatNM& operator =(const this_t& rhs){
    assign(rhs);
    return *this;
  }
  
  MatNM operator +(const this_t& rhs) const{
    this_t sum;
    // Fill me in!
    return sum;
  }
  
  this_t& operator +=(const this_t& rhs){
    return (*this = *this + rhs);
  }
  
  this_t operator -( ) const{
    this_t rv;
    // Fill me in!
    return rv;
  }
  
  this_t operator -(const this_t& rhs) const{
    this_t difference;
    // Fill me in!
    return difference;
  }
  
  this_t& operator -=(const this_t& rhs){
    return (*this = *this - rhs);
  }
      
  this_t operator *(const T& rhs) const{
    this_t product;
    // Fill me in!
    return product;
  }
  
  this_t& operator *=(const T& rhs){
    return (*this = *this * rhs);
  }
  
  this_t operator *(const this_t& rhs){
    this_t product;
    // Fill me in!
    return product;
  }
  
  
  this_t& operator *=(const this_t& rhs){
    return (*this = *this * rhs);
  }
  
  this_t operator /(const T& rhs) const{
    this_t quotient;
    // Fill me in!
    return quotient;
  }
  
  this_t& operator /=(const T& rhs){
    return (*this = *this / rhs);
  }
  
  bool operator ==(const this_t& rhs) const{
    bool rv = false;
    // Fill me in!
    return rv;
  }
  
  bool operator !=(const this_t& rhs) const{
    return( ! (*this == rhs));
  }
  
  const T operator ()(const size_t& col_i, const size_t& row_j) const{
    return cols[col_i][row_j];
  }
  
  T& operator ()(const size_t& col_i, const size_t& row_j){
    return cols[col_i][row_j];
  }
  
  vec_t& column(const size_t& col_i){
    if( col_i < w ){
      return cols[col_i];
    }else{
      throw( "Index out of range" );
    }
  }
  
  vec_t& operator [](const size_t& col_i){
    return column(col_i);
  }
  
  const vec_t& column(const size_t& col_i) const{
    if( col_i < w ){
      return cols[col_i];
    }else{
      throw( "Index out of range" );
    }
  }
  
  const vec_t& operator[](const size_t& col_i) const{
    return column(col_i);
  }
    
  VecN<T, w> row(const size_t& row_j) const{
    T vals[w];
    for(int i = 0; i < w; i++){
      vals[i] = cols[i][row_j];
    }
    return VecN<T, h>(vals);
  }
  
  operator T*( ){
    return &cols[0][0];
  }
  
  operator const T*( ) const{
    return &cols[0][0];
  }
    
  MatNM<T, h, w> transpose( ) const{
    MatNM<T, h, w> rv;
    // Fill me in!
    return rv;
  }
    
  static int width(void){
    return w;
  }
  
  static int height(void){
    return h;
  }
  
  std::ostream& write(std::ostream& out) const{
    out.setf( std::ios::fixed );
    out << std::setprecision(IOS_FP_PRECISION);
    for(int i = 0; i < h; i++){
      out << row(i); 
    }
    out.unsetf( std::ios::fixed );
    return(out);
  }
  
  std::ostream& description(std::ostream &out = std::cerr) const{
    out << "<Mat" << w << "x" << h << " " << this << ">" << std::endl;
    for( int i = 0; i < h; i++ ){
      out << row(i) << std::endl; 
    }
    return(out);
  }
protected:
  VecN<T, h> cols[w];
  
  void assign(const MatNM& rhs){
    for(int i = 0; i < w; i++){
      cols[i] = rhs.cols[i]; 
    }
  }
  
  void assign(const T s){
    for(int i = 0; i < w; i++){
      cols[i] = vec_t(s); 
    }
  }
  
  void assign(const vec_t& v){
    for(int i = 0; i < w; i++){
      cols[i] = v; 
    }
  }
  
  void assign(const T* a){
    for(int i = 0; i < w; i++){
      cols[i] = vec_t(a+(i*h)); 
    }
  }  
}; // end class MatNM

template <typename T, const int w>
class MatN : public MatNM<T, w, w>{
public:
  typedef MatNM<T, w, w> base;
  typedef MatN<T, w> this_t;
  
  MatN( ) : base( ) {}
  MatN(const base& m) : base(m) {}
  MatN(const T* array) : base(array) {}
  MatN(const VecN<T, w>& v) : base(v) {}
  
  void identity( ){
    // Fill me in!
  }
    
}; // end class MatN

template <typename T>
class TMat2 : public MatN<T, 2>{
public:
  typedef MatN<T, 2> base;
  typedef TMat2<T> this_t;
  TMat2( ) : base( ) {}
  TMat2(const this_t& m) : base(m) {}
  TMat2(const base& m) : base(m) {}
  TMat2(const MatNM<T, 2, 2>& m) : base(m) {}
  TMat2(const T* array) : base(array) {}
  TMat2(const VecN<T, 2>& v) : base(v) {}
  TMat2(const VecN<T, 2>& a, const VecN<T, 2>& b){
    base::cols[0] = a;
    base::cols[1] = b;
  }
  TMat2(const T& a, const T& b, const T& c, const T& d){
    base::cols[0] = TVec2<T>(a, b);
    base::cols[1] = TVec2<T>(c, d);
  }

  T determinant( ){
    // Fill me in!
    return T(0);
  }
  
  T minor(unsigned int col_i, unsigned int row_j){
    // Fill me in!
    return T(-1);
  }
  
  T cofactor(unsigned int col_i, unsigned int row_j){
    // Fill me in!
    return T(0);
  }
  
  this_t adjugate( ){
    this_t m;
    // Fill me in!
    return m;
  }
  
  this_t inverse( ){
    this_t m;
    // Fill me in!
    return m;
  }
  
}; // end class TMat2


template <typename T>
class TMat3 : public MatN<T, 3>{
public:
  typedef MatN<T, 3> base;
  typedef TMat3<T> this_t;
  TMat3( ) : base( ) {}
  TMat3(const this_t& m) : base(m) {}
  TMat3(const base& m) : base(m) {}
  TMat3(const MatNM<T, 3, 3>& m) : base(m) {}
  TMat3(const T* array) : base(array) {}
  TMat3(const MatN<T, 2> m){
    base::cols[0] = m[0];
    base::cols[1] = m[1];
    base::cols[2] = base::vec_t(0, 0, 0);
  }
  TMat3(const VecN<T, 3>& v) : base(v) {}
  TMat3(const VecN<T, 3>& a, const VecN<T, 3>& b, const VecN<T, 3>& c){
    base::cols[0] = a;
    base::cols[1] = b;
    base::cols[2] = c;
  }
  TMat3(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i){
    base::cols[0] = TVec3<T>(a, b, c);
    base::cols[1] = TVec3<T>(d, e, f);
    base::cols[2] = TVec3<T>(g, h, i);
  }
  
  T determinant( ){
    // Fill me in!
    return 0.0;
  }
  
  T minor(unsigned int col_i, unsigned int row_j){
    // Fill me in!
    return T(-1);
  }
  
  T cofactor(unsigned int col_i, unsigned int row_j){
    // Fill me in!
    return T(0);
  }
  
  this_t adjugate( ){
    this_t m;
    // Fill me in!
    return m;
  }
  
  this_t inverse( ){
    this_t m;
    // Fill me in!
    return m;
  }

}; // end class TMat3

template <typename T>
class TMat4 : public MatN<T, 4>{
public:
  typedef MatN<T, 4> base;
  typedef TMat4<T> this_t;
  TMat4( ) : base( ) {}
  TMat4(const this_t& m) : base(m) {}
  TMat4(const base& m) : base(m) {}
  TMat4(const MatNM<T, 4, 4>& m) : base(m) {}
  TMat4(const T* array) : base(array) {}
  TMat4(const MatN<T, 3> m){
    base::cols[0] = m[0];
    base::cols[1] = m[1];
    base::cols[2] = m[2];
    base::cols[3] = base::vec_t(0, 0, 0, 0);
  }
  TMat4(const VecN<T, 4>& v) : base(v) {}
  TMat4(const VecN<T, 4>& a, const VecN<T, 4>& b, const VecN<T, 4>& c, const VecN<T, 4>& d){
    base::cols[0] = a;
    base::cols[1] = b;
    base::cols[2] = c;
    base::cols[3] = d;
  }
  TMat4(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j, const T& k, const T& l, const T& m, const T& n, const T& o, const T& p){
    base::cols[0] = TVec4<T>(a, b, c, d);
    base::cols[1] = TVec4<T>(e, f, g, h);
    base::cols[2] = TVec4<T>(i, j, k, l);
    base::cols[3] = TVec4<T>(m, n, o, p);
  }
  
  this_t transpose( ) const{
    return base::transpose( );
  }
  
  T determinant( ){
    // Fill me in!
    return T(0);
  }
  
  T minor(unsigned int col_i, unsigned int row_j){
    // Fill me in!
    return T(-1);
  }
  
  T cofactor(unsigned int col_i, unsigned int row_j){
    // Fill me in!
    return T(0);
  }
  
  this_t adjugate( ){
    this_t m;
    // Fill me in!
    return m;
  }
  
  this_t inverse( ){
    this_t m;
    // Fill me in!
    return m;
  }

private:
  TVec4<T> _cross4(const TVec4<T>& u, const TVec4<T>& v, const TVec4<T>& w){
    T a, b, c, d, e, f;
    a = (v[0] * w[1]) - (v[1] * w[0]);
    b = (v[0] * w[2]) - (v[2] * w[0]);
    c = (v[0] * w[3]) - (v[3] * w[0]);
    d = (v[1] * w[2]) - (v[2] * w[1]);
    e = (v[1] * w[3]) - (v[3] * w[1]);
    f = (v[2] * w[3]) - (v[3] * w[2]);

    TVec4<T> n = TVec4<T>(
      (u[1] * f) - (u[2] * e) + (u[3] * d), 
    - (u[0] * f) + (u[2] * c) - (u[3] * b), 
      (u[0] * e) - (u[1] * c) + (u[3] * a), 
    - (u[0] * d) + (u[1] * b) - (u[2] * a)
    );
    return n;
  }
  
}; // end class TMat4

typedef TMat2<float> Mat2;
typedef TMat2<int> iMat2;
typedef TMat2<unsigned int> uMat2;
typedef TMat2<double> dMat2;

typedef TMat3<float> Mat3;
typedef TMat3<int> iMat3;
typedef TMat3<unsigned int> uMat3;
typedef TMat3<double> dMat3;

typedef TMat4<float> Mat4;
typedef TMat4<int> iMat4;
typedef TMat4<unsigned int> uMat4;
typedef TMat4<double> dMat4;

template <typename T, const int w, const int h>
std::ostream& operator <<( std::ostream &out, const MatNM<T, w, h> &m ){
  return(m.write( out ));
}

template <typename T, const int w1, const int h1, const int w2, const int h2>
MatNM<T, w1, h2> operator *(const MatNM<T, w1, h1>& lhs, const MatNM<T, w2, h2>& rhs){
  MatNM<T, w1, h2> product;
  // Fill me in!
  return product;
}

template <typename T, const int w>
static const VecN<T, w> operator *(const MatNM<T, w, w>& lhs, VecN<T, w> rhs){
  VecN<T, w> product;
  // Fill me in!
  return product;
}

template <typename T, const int w, const int h>
static const MatNM<T, w, h> operator *(T lhs, const MatNM<T, w, h>& rhs){
  return rhs * lhs;
}


class ViewPort{
  ViewPort( unsigned int width = 0, unsigned int height = 0 ) : _width(width), _height(height) {}
  unsigned int width( ){
    return _width;
  }
  unsigned int height( ){
    return _height;
  }
protected:
  unsigned int _width;
  unsigned int _height;
};

static Mat4 frustum(float left, float right, float bottom, float top, float near, float far){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 perspective(float fovy_in_Y_direction, float aspect, float near, float far){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 ortho(float left, float right, float bottom, float top, float near, float far){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 rotate(float angleInDegrees, float axis_x, float axis_y, float axis_z){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 rotate(float angleInDegrees, const Vec3& axis){
  return rotate(angleInDegrees, axis[0], axis[1], axis[2]);
}

static Mat4 scale(float s){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 scale(float x, float y, float z){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 scale(const Vec3& v){
  float x = v[0];
  float y = v[1];
  float z = v[2];
  return scale(x, y, z);
}

static Mat4 translate(float x, float y, float z){
  Mat4 m;
  // Fill me in!  
  return m;
}

static Mat4 translate(const Vec3& v){
  float x = v[0];
  float y = v[1];
  float z = v[2];
  return translate(x, y, z);
}

static Mat4 lookat(const Vec3& eye, const Vec3& center, const Vec3& up){
  Mat4 m;
  // Fill me in!  
  return m;
}

static bool project(const Vec3& objCoord, const Mat4& projection, const Mat4& modeling, ViewPort& vp, Vec3* winCoord){
  // Fill me in!
  return false;
}

static bool unproject(const Vec3& winCoord, const Mat4& projection, const Mat4& modeling, ViewPort& vp, Vec3* objCoord){
  // Fill me in!
  return false;
}

static bool unproject4(const Vec3& winCoord, float clipw, const Mat4& projection, const Mat4& modeling, ViewPort& vp, float near, float far, Vec4* objCoord){
  // Fill me in!
  return false;
}

template <typename T>
TVec3<T> reflect(TVec3<T>& direction, TVec3<T>& normal){
  // Fill me in!
  return TVec3<T>(0, 0);
}

template <typename T>
TVec4<T> reflect(TVec4<T>& direction, TVec4<T>& normal){
  // Fill me in!
  return TVec4<T>(0, 0);
}

#endif // End GFXMath.h
