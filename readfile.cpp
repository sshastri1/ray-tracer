#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

#include "Transform.h" 

using namespace std;
#include "variables.h" 
#include "readfile.h"


// You may not need to use the following two functions, but it is provided
// here for convenience

// The function below applies the appropriate transform to a 4-vector
void matransform(stack<mat4> &transfstack, GLfloat* values) 
{
  mat4 transform = transfstack.top(); 
  vec4 valvec = vec4(values[0],values[1],values[2],values[3]); 
  vec4 newval = transform * valvec; 
  for (int i = 0; i < 4; i++) values[i] = newval[i]; 
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
  mat4 &T = transfstack.top(); 
  T = T * M; 
}

// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readvals(stringstream &s, const int numvals, GLfloat* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}

void readfile(const char* filename) 
{
  string str, cmd; 
  ifstream in;
  in.open(filename); 
  if (in.is_open()) {

    // I need to implement a matrix stack to store transforms.  
    // This is done using standard STL Templates 
    stack <mat4> transfstack; 
    transfstack.push(mat4(1.0));  // identity

    getline (in, str); 
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str);
        s >> cmd; 
        int i; 
        GLfloat values[10]; 
        const auto& v = values;
        bool validinput;
        if (cmd == "size") {
            validinput = readvals(s, 2, values); 
            if (validinput) {
            }
        } else if (cmd == "maxdepth") {
            validinput = readvals(s, 1, values);
            if (validinput) {
            }
        } else if (cmd == "camera") {
            validinput = readvals(s, 10, values);
            if (validinput) {
            }    
        } else if (cmd == "sphere") {
            validinput = readvals(s, 4, values);
            if (validinput) {
            }        
        } else if (cmd == "maxverts") {
            validinput = readvals(s, 1, values);
            if (validinput) {
            }
        } else if (cmd == "maxvertnorms") {
            validinput = readvals(s, 1, values);
            if (validinput) {
            }
        } else if (cmd == "vertex") {
            validinput = readvals(s, 3, values);
            if (validinput) {
            }
        } else if (cmd == "vertexnormal") {
            validinput = readvals(s, 6, values);
            if (validinput) {
            }
        } else if (cmd == "tri") {
            validinput = readvals(s, 3, values);
            if (validinput) {
            }
        } else if (cmd == "trinormal") {
            validinput = readvals(s, 3, values);
            if (validinput) {
            }        
        } else if (cmd == "translate") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            rightmultiply(Transform::translate(v[0],v[1],v[2]),transfstack);

          }
        } else if (cmd == "scale") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            rightmultiply(Transform::scale(v[0],v[1],v[2]),transfstack);

          }
        } else if (cmd == "rotate") {
          validinput = readvals(s,4,values); 
          if (validinput) {

            rightmultiply(mat4(Transform::rotate(v[0],normalize(vec3(v[1],v[2],v[3])))),transfstack);

          }
        } else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()); 
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n"; 
          } else {
            transfstack.pop(); 
          }
        } 
        else if (cmd == "directional") {
            validinput = readvals(s, 6, values);
            if (validinput) {
            }
        } else if (cmd == "point") {
            validinput = readvals(s, 6, values);
            if (validinput) {
            }
        } else if (cmd == "attenuation") {
            validinput = readvals(s, 3, values);
            if (validinput) {
            }
        } else if (cmd == "ambient") {
          validinput = readvals(s, 4, values); // colors 
          if (validinput) {
            for (i = 0; i < 4; i++) {
              ambient[i] = values[i]; 
            }
          }
        } else if (cmd == "diffuse") {
          validinput = readvals(s, 4, values); 
          if (validinput) {
            for (i = 0; i < 4; i++) {
              diffuse[i] = values[i]; 
            }
          }
        } else if (cmd == "specular") {
          validinput = readvals(s, 4, values); 
          if (validinput) {
            for (i = 0; i < 4; i++) {
              specular[i] = values[i]; 
            }
          }
        } else if (cmd == "emission") {
          validinput = readvals(s, 4, values); 
          if (validinput) {
            for (i = 0; i < 4; i++) {
              emission[i] = values[i]; 
            }
          }
        } else if (cmd == "shininess") {
          validinput = readvals(s, 1, values); 
          if (validinput) {
            shininess = values[0]; 
          }
        }


      }
    }
  }
}