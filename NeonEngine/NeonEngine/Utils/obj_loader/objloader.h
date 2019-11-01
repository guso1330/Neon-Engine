// #pragma once

// #include <glad/glad.h>
// #include <glm/vec2.hpp>
// #include <glm/vec3.hpp>

// #include <iostream>
// #include <stdio.h>
// #include <vector>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <cstring>
// #include <typeinfo>
// #include <tuple>

// using namespace std;
// using namespace glm;

// namespace Neon {

// 	// TODO: figure out a better way of doing this.
// 	// 		 Storing so much for just a mesh might
// 	//		 be a bad idea.
// 	struct Index {
// 		unsigned int vertex_index;
// 		unsigned int uv_index;
// 		unsigned int normal_index;

// 		bool has_vi;
// 		bool has_ui;
// 		bool has_ni;

// 		unsigned int index;

// 		bool operator == (const Index& rhs) const
// 		{
// 			return (vertex_index == rhs.vertex_index) && 
// 				   (uv_index == rhs.uv_index) && 
// 				   (normal_index == rhs.normal_index);
// 		}

// 		// WARNING: requires C++ 11 for std::tie
// 		bool operator < (const Index& ind) const
// 		{
// 			return std::tie(vertex_index, uv_index, normal_index, index) < std::tie(ind.vertex_index, ind.uv_index, ind.normal_index, ind.index);
// 			// return index < ind.index;
// 		}
// 	};

// 	void tiny_obj_loader_load_obj(string inputfile, vector<vec3> &vertices, vector<unsigned int> &indices, vector<vec2> &uvs, vector<vec3> &normals, vector<Index> &Index_Obj);

// 	//******************************************************************
// 	//
// 	//  Function:   load_obj
// 	//
// 	//  * NOTE:		Currently, only tested with .obj files from autodesk
// 	//				maya 2016.
// 	//
// 	//  Purpose:    Given a .obj file, this function loads in objects
// 	//				by parsing the file and pulling its vertex and
// 	//				normal information.
// 	//
// 	//  Parameters: filename - the filename (location)
// 	//				vertices - a vector to the hold the vertices of the obj
// 	//				normals - a vector to hold the object normals
// 	//				elements - the elements of the object
// 	//
// 	//	Adapted from: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
// 	//******************************************************************
// 	void load_obj(const char* filename, vector<vec3> &vertices, vector<GLuint> &indices, vector<vec2> &uvs, vector<vec3> &normals);

// 	//******************************************************************
// 	//
// 	//  Function:   split_str
// 	//
// 	//  Purpose:    This function takes a string and a delimiter and splits
// 	//				the string into sections then inserts them into a vector<string>
// 	//
// 	//  Parameters: s - a string that is to be splitted
// 	//				delim - is the the string delimiter
// 	//				v - is the vector to place the elements
// 	//
// 	//******************************************************************
// 	void split_str(const string &s, char* delim, vector<string> &v);
// }

// /********************************************************************************************/
// /* From https://stackoverflow.com/questions/19195183/how-to-properly-hash-the-custom-struct */
// /********************************************************************************************/
// template <class T>
// inline void hash_combine(std::size_t & s, const T & v)
// {
// 	std::hash<T> h;
// 	s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
// }

// template<>
// struct hash<Neon::Index>
// {
// 	std::size_t operator()(Neon::Index const& i) const 
// 	{
// 		std::size_t res = 0;
// 		hash_combine(res,i.vertex_index);
// 		hash_combine(res,i.uv_index);
// 		hash_combine(res,i.normal_index);
// 	 	return res;
// 	}
// };