#include "objloader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace neon {

	void tiny_obj_loader_load_obj(std::string inputfile, vector<vec3> &vertices, vector<GLuint> &indices, vector<vec2> &uvs, vector<vec3> &normals) {

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

		//
		// Error Checking
		// 	- Check if the there was an error and print
		//  - check if the ret wsa NULL
		//
		if (!err.empty()) { // `err` may contain warning message.
			std::cerr << err << std::endl;
		}
		if (!ret) {
			exit(1);
		}

		printf("Num Shapes loaded from %s: %lu\n", inputfile.c_str(), shapes.size());

		//
		// VERTICES
		//
		for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
			// printf("  v[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
			// 		  static_cast<const double>(attrib.vertices[3 * v + 0]),
			// 		  static_cast<const double>(attrib.vertices[3 * v + 1]),
			// 		  static_cast<const double>(attrib.vertices[3 * v + 2]));
			vertices.push_back(vec3(attrib.vertices[3 * v + 0],
									attrib.vertices[3 * v + 1],
									attrib.vertices[3 * v + 2]));
		}

		//
		// NORMALS
		//
		for (size_t v = 0; v < attrib.normals.size() / 3; v++) {
			// printf("  n[%ld] = (%f, %f, %f)\n", static_cast<long>(v),
			// 		  static_cast<const double>(attrib.normals[3 * v + 0]),
			// 		  static_cast<const double>(attrib.normals[3 * v + 1]),
			// 		  static_cast<const double>(attrib.normals[3 * v + 2]));
			normals.push_back(vec3(attrib.normals[3*v+0],
								   attrib.normals[3*v+1],
								   attrib.normals[3*v+2]));
		}

		//
		// UVs
		//
		for (size_t v = 0; v < attrib.texcoords.size() / 2; v++) {
			// printf("  uv[%ld] = (%f, %f)\n", static_cast<long>(v),
			// 		  static_cast<const double>(attrib.texcoords[2 * v + 0]),
			// 		  static_cast<const double>(attrib.texcoords[2 * v + 1]));
			uvs.push_back(vec2(attrib.texcoords[2 * v + 0],
							   attrib.texcoords[2 * v + 1]));
		}

		// 
		// INDICES
		//
		// Loop over shapes

		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			// size_t index_offset = 0;

			for(size_t i=0; i < shapes[s].mesh.indices.size(); ++i) {
				// cout << shapes[s].mesh.indices[i].vertex_index << endl;
				indices.push_back(shapes[s].mesh.indices[i].vertex_index);
			}

			// for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			// 	int fv = shapes[s].mesh.num_face_vertices[f];

			// 	// Loop over vertices in the face.
			// 	for (size_t v = 0; v < fv; v++) {
			// 		// access to vertex
			// 		tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
			// 		indices.push_back(3*idx.vertex_index+0);
			// 		indices.push_back(3*idx.vertex_index+1);
			// 		indices.push_back(3*idx.vertex_index+2);
			// 		// float vx = attrib.vertices[3*idx.vertex_index+0];
			// 		// float vy = attrib.vertices[3*idx.vertex_index+1];
			// 		// float vz = attrib.vertices[3*idx.vertex_index+2];

			// 		// float nx = attrib.normals[3*idx.normal_index+0];
			// 		// float ny = attrib.normals[3*idx.normal_index+1];
			// 		// float nz = attrib.normals[3*idx.normal_index+2];

			// 		// float tx = attrib.texcoords[2*idx.texcoord_index+0];
			// 		// float ty = attrib.texcoords[2*idx.texcoord_index+1];
			// 	}
			// 	index_offset += fv;
			// 	// per-face material
			// 	shapes[s].mesh.material_ids[f];
			// }
		}

		// for (size_t s = 0; s < shapes.size(); s++) {
		// 	// Loop over faces(polygon)
		// 	size_t index_offset = 0;
		// 	for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
		// 		int fv = shapes[s].mesh.num_face_vertices[f];

		// 		// Loop over vertices in the face.
		// 		for (size_t v = 0; v < fv; v++) {
		// 			// access to vertex
		// 			tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
		// 			indices.push_back(3*idx.vertex_index+0);
		// 			indices.push_back(3*idx.vertex_index+1);
		// 			indices.push_back(3*idx.vertex_index+2);
		// 			// float vx = attrib.vertices[3*idx.vertex_index+0];
		// 			// float vy = attrib.vertices[3*idx.vertex_index+1];
		// 			// float vz = attrib.vertices[3*idx.vertex_index+2];

		// 			// float nx = attrib.normals[3*idx.normal_index+0];
		// 			// float ny = attrib.normals[3*idx.normal_index+1];
		// 			// float nz = attrib.normals[3*idx.normal_index+2];

		// 			// float tx = attrib.texcoords[2*idx.texcoord_index+0];
		// 			// float ty = attrib.texcoords[2*idx.texcoord_index+1];
		// 		}
		// 		index_offset += fv;
		// 		// per-face material
		// 		shapes[s].mesh.material_ids[f];
		// 	}
		// }
	}

	// split_str - Definition for the split_str function
	void split_str(const string &s, char* delim, vector<string> &v) {
		// to avoid modifying original string
		// first duplicate the original string and return a char pointer then free the memory
		char *dup = strdup(s.c_str());
		char *token = strtok(dup, delim);
		while(token != NULL){
			v.push_back(string(token));
			// the call is treated as a subsequent calls to strtok:
			// the function continues from where it left in previous invocation
			token = strtok(NULL, delim);
		}
		free(dup);
	}

	// load_obj - Definition for the load_obj function
	//
	// Last modified: Sept. 9, 2017
	//
	// NOTE: this function currently is loading the verteces, normals, and uvs
	//		 based on the indices. This means that there is repeat values.
	void load_obj(const char* filename, vector<vec3> &vertices, vector<GLuint> &indices, vector<vec2> &uvs, vector<vec3> &normals) {
		
		// Temporary storage
		std::vector<unsigned int> vertexIndices, uvIndices,normalIndices;
		vector<vec3> temp_vertices;
		vector<vec2> temp_uvs;
		vector<vec3> temp_normals;

		// create file variable
		ifstream in(filename, ios::in);
		if(!in) {
			cerr << "Cannot open " << filename <<endl;
			exit(EXIT_FAILURE);
		} else {
			cout << "Load Obj - Opened .obj file: " << filename << endl;
		}

		string line; // variable to hold each line
		while(getline(in, line)) {
			if (line.length() > 3) { // make sure that the line is not empty

				// Get the object vertices
				if(line.substr(0, 2) == "v ") {
					istringstream s(line.substr(2));
					vec3 v; // Holds a temporary vertex
					s >> v.x; s >> v.y; s >> v.z; // get the x, y, and z of the point
					// cout << v.x << ", " << v.y << ", " << v.z << endl; // get the x, y, and z of the point
					// temp_vertices.push_back(v); // add the vertex to the vertices vector
					// NOTE: Need to do this for the normals and the verteces as well!!
					vertices.push_back(v);
				}
				
				// Get the object vertex normals
				else if (line.substr(0, 3) == "vn ") {
					istringstream s(line.substr(3));
					vec3 n;
					s >> n.x; s >> n.y; s >> n.z; // get x, y, and z. Since it's a vector w = 0.0
					temp_normals.push_back(n);
				}

				// Get the UV's for the mesh
				else if (line.substr(0,3) == "vt ") {
					istringstream s(line.substr(3));
					vec2 u;
					s >> u.x; s >> u.y; // get the x and y coordinate for the uv
					temp_uvs.push_back(u);
				}
				// Get the faces and how they are made up
				else if (line.substr(0, 2) == "f ") {
					string s  = line.substr(2, line.length());
					vector<string> elems_1; // Will contain the strings after "f ", split by spaces (" ")
					char delim_1[2] = " ";
					char delim_2[2] = "/";
					split_str(s, delim_1, elems_1); // split the string by spaces (" ") and get results in elems_2
					for(size_t i=0; i<elems_1.size(); ++i) {
						// cout << "1: " << elems_1[i] << endl;
						vector<string> elems_2; // Will contain the split up numbers (ex/ 1/1/1 -> 1, 1, 1)
						split_str(elems_1[i], delim_2, elems_2); // split the separated strings by the "/" delimiter
																 // and place the results in elems_2
						// cout << "Elem2 size: " << elems_2.size() << endl << endl;
						for(size_t j=0; j<elems_2.size(); ++j) {
							GLuint a  = atoi( elems_2[j].c_str() ) - 1; // convert the numbers into ints
							if(j == 0) {
								// cout << "a: " << a << endl;
								indices.push_back(a);
								vertexIndices.push_back(a);
							}
							else if(j == 1) {
								uvIndices.push_back(a);
							}
							else if(j == 2) {
								normalIndices.push_back(a);
							}
						}	
						// ++count;
					}
					// cout << endl;
				}
				else if(line[0] == '#') {
					// nothing
				}
				else {
					// nothing
				}
			} 
			else { // of the line is empty
				continue;
			}
		}
		// Output the vertices
		// NOTE: (Sept. 9) removed the intialization of vertices from
		//		 this chunk of code and put it up above
		for(unsigned int i=0; i<vertexIndices.size(); ++i) {

			// unsigned int vIndex = vertexIndices[i];
			unsigned int uIndex = uvIndices[i];
			unsigned int nIndex = normalIndices[i];
			
			// Get the attributes thanks to the index
			// vec3 vertex = temp_vertices[ vIndex ];
			vec2 uv = temp_uvs[ uIndex ];
			vec3 normal = temp_normals[ nIndex ];

			// Put the attributes in buffers
			// vertices.push_back(vertex);
			uvs.push_back(uv);
			normals.push_back(normal);
		}
	}
}