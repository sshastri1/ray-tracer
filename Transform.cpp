// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	const int size = 3;
	mat3 id = mat3(1.0);
	mat3 skw = mat3(0.0);
	auto fn = [&size](int x) {return [x,&size](int y){ return (x+y+size) % size;};};
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			auto f = fn(1-k);
			skw[i][k] = (f(i)-1)*axis[f(size-1-i)];
		}
	}
	float dg = -degrees*pi/180;
	float ct = cos(dg);
	return ct * id + (1-ct) * outerProduct(axis,axis)+(float)sin(dg)*skw;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 c = (normalize(eye));
	vec3 b = normalize((up)); 
	vec3 a = (cross(b,c));
	eye = rotate(-degrees,a) * eye;
	up = cross(normalize(eye),a);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 c = (normalize(eye-center));
	vec3 b = normalize((up)); 
	vec3 a = (cross(b,c));
	/*mat4 cam = mat4(1.0L);
	for (int i = 0; i < 3; i++)
		cam[i] = vec4(a[i],b[i],c[i],0.0L);*/
	//mat4 cam1 = transpose(mat4(vec4(a,-dot(a,eye)),vec4(b,-dot(b,eye)),vec4(c,-dot(c,eye)),vec4(vec3(0.0L),1.0L)));
	//mat4 cam2 = (mat4(vec4(a,0.0L),vec4(b,0.0L),vec4(c,0.0L),vec4(eye,1.0L)));
	mat4 cam = mat4(a[0],b[0],c[0],0.0L,
					a[1],b[1],c[1],0.0L,
					a[2],b[2],c[2],0.0L,
					dot(-a,eye),dot(-b,eye),dot(-c,eye),1.0L);
	//cam[3] = vec4(dot(-a,eye),dot(-b,eye),dot(-c,eye),1.0L);
	//cam[3] = vec4(-eye,1.0L);
	//mat4 bruh = mat4(vec4(vec3(1),0),vec4(vec3(2),0),vec4(vec3(3),0),vec4(vec3(4),1));
	// You will change this return call
	return cam;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float t = 1/tan(fovy);
  float pr = 2*zFar*zNear;
  float fmn = zFar-zNear;
  /*mat4 id = mat4(1.0);
  vec4 tmp = -id[3];
  id[3] = id[2]; id[2] = tmp;
  mat4 ret = scale(t/aspect,t,pr/(zFar-zNear))*translate(0,0,-(zFar+zNear)/pr)*id;
  ret[2][2] *= -1;
  ret[3][2]*=-1;*/
  mat4 ret;
  vec4 vals = vec4(t/aspect,t,(zFar+zNear)/fmn,0.0);
  for (int i = 0; i < 4; i++){
	  ret[i][i] = vals[i];
  }	
  ret[3][2] = pr/fmn;
  ret[2][3] = -1;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 ret = mat4(1.0);
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 
  vec3 v = vec3(sx,sy,sz);
  for (int i = 0; i < 3; i++)
    ret[i][i]=v[i];
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 ret=mat4(1.0);
  ret[3] = vec4(tx,ty,tz,1.0);
  // YOUR CODE FOR HW2 HERE
  // Implement translation 
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
