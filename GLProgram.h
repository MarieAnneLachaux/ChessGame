// --------------------------------------------------------------------------
// OpenGL Program Class
// Copyright(C) 2007-2015
// Tamy Boubekeur
// --------------------------------------------------------------------------

#define GLEW_STATIC 1
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Opengl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Exception {
 public:
  inline Exception (const std::string & msg) : _msg ("Open GL Exception: " + msg) {}
  inline const std::string & msg () const { return _msg; }
 protected:
  std::string _msg;
};

/// Throws an expection if an error occurred.
void checkGLExceptions ();

class Shader {
public:
  Shader (const std::string & name, GLuint _type);
  virtual ~Shader ();
  inline GLuint id () const { return _id; }
  inline const std::string & name () const { return _name; }
  inline GLenum type () const { return _type; }
  inline const std::string & source () const { return _source; }
  inline const std::string & filename () const { return _filename; }
  void setSource (const std::string & source);
  void compile ();
  void loadFromFile (const std::string & filename);
  void reload ();
 protected:
  std::string infoLog ();
 private:
  GLuint _id;
  std::string _name;
  GLuint _type;
  std::string _filename;
  std::string _source;
};

class Program {
public:
  Program (const std::string & name);
  virtual ~Program ();
  inline GLuint id () const { return _id; }
  std::string name () const { return _name; }
  void attach (Shader * shader);
  void detach (Shader * shader);
  void link ();
  void use ();
  static void stop ();
  GLint getUniformLocation (const std::string & uniformName);
    void setUniform1u(GLint location, GLint value);
  void setUniform1f (GLint location, float value);
  void setUniform1f (const std::string & name, float value);
  void setUniform2f (GLint location, float value0, float value1);
  void setUniform2f (const std::string & name, float value0, float value1);
  void setUniform3f (GLint location, float value0, float value1, float value2);
  void setUniform3f (const std::string & name, float value0, float value1, float vlaue2);
  void setUniform4f (GLint location, float value0, float value1, float value2, float value3);
  void setUniform4f (const std::string & name, float value0, float value1, float value2, float value3);
  void setUniformMatrix4fv (GLint location, const float * values);
  void setUniformMatrix4fv (const std::string & name, const float * values);
  void setUniformNf (GLint location, unsigned int numValues, const float * values);
  void setUniformNf (const std::string & name, unsigned int numValues, const float * values);
  void setUniform1i (GLint location, int value);
  void setUniform1i (const std::string & name, int value);
  void setUniformNi (GLint location, unsigned int numValues, const int * values);
  void setUniformNi (const std::string & name, unsigned int numValues, const int * values);
    GLint getAttribLocation (const std::string & uniformName);
    void setAttrib1f(GLint location, float o);
    void setAttrib3f(GLint location, float r, float g, float b);
    void setAttrib2f(GLint location, float vtX, float vtY);
  void reload ();
  // generate a simple program, with only vertex and fragment shaders.
  static Program * genVFProgram (const std::string & name,
				 const std::string & vertexShaderFilename,
				 const std::string & fragmentShaderFilename);
 protected:
  std::string infoLog ();
 private:
  GLuint _id;
  std::string _name;
  std::vector<Shader*>_shaders;
};
