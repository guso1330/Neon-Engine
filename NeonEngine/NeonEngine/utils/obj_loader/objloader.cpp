// #include "objloader.h"

// #define TINYOBJLOADER_IMPLEMENTATION
// #include "tiny_obj_loader.h"
// #include <ctime>

// using namespace std;

// namespace neon {

// 	void tiny_obj_loader_load_obj(std::string inputfile, vector<vec3> &vertices, vector<unsigned int> &indices, vector<vec2> &uvs, vector<vec3> &normals, vector<Index> &Index_Obj) {
// 		clock_t begin = clock();

// 		tinyobj::attrib_t attrib;
// 		std::vector<tinyobj::shape_t> shapes;
// 		std::vector<tinyobj::material_t> materials;

// 		std::string err;
// 		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());

// 		//
// 		// Error Checking
// 		// 	- Check if the there was an error and print
// 		//  - check if the ret was NULL
// 		//
// 		if (!err.empty()) { // `err` may contain warning message.
// 			printf("\n");
// 			std::cerr << err << std::endl;
// 		}
// 		if (!ret) {
// 			system("PAUSE");
// 		}
// 		else {
// 			printf("\nLoaded %s with %lu shapes\n", inputfile.c_str(), shapes.size());

// 			//
// 			// VERTICES
// 			//
// 			for (size_t v = 0; v < attrib.vertices.size() / 3; v++) {
// 				vertices.push_back(vec3(attrib.vertices[3 * v + 0],
// 					attrib.vertices[3 * v + 1],
// 					attrib.vertices[3 * v + 2]));
// 			}

// 			//
// 			// NORMALS
// 			//
// 			for (size_t v = 0; v < attrib.normals.size() / 3; v++) {
// 				normals.push_back(vec3(attrib.normals[3 * v + 0],
// 					attrib.normals[3 * v + 1],
// 					attrib.normals[3 * v + 2]));
// 			}

// 			//
// 			// UVs
// 			//
// 			for (size_t v = 0; v < attrib.texcoords.size() / 2; v++) {
// 				uvs.push_back(vec2(attrib.texcoords[2 * v + 0],
// 					attrib.texcoords[2 * v + 1]));
// 			}

// 			// std::cout << "sizes of model loader: " << vertices.size() << " " << normals.size() << " " << uvs.size() << std::endl;

// 			// 
// 			// INDICES
// 			//
// 			// Loop over shapes
// 			// TODO: handle negative indices
// 			for (size_t s = 0; s < shapes.size(); s++) {
// 				for (size_t i = 0; i < shapes[s].mesh.indices.size(); ++i) {
// 					Index temp_index;
// 					temp_index.has_vi = temp_index.has_ui = temp_index.has_ni = false;
// 					if(vertices.size() != 0) {
// 						temp_index.vertex_index = shapes[s].mesh.indices[i].vertex_index;
// 						temp_index.has_vi = true;
// 					}
// 					if(uvs.size() != 0) {
// 						temp_index.uv_index = shapes[s].mesh.indices[i].texcoord_index;
// 						temp_index.has_ui = true;
// 					}
// 					if(normals.size() != 0) {
// 						temp_index.normal_index = shapes[s].mesh.indices[i].normal_index;
// 						temp_index.has_ni = true;
// 					}
// 					indices.push_back(temp_index.vertex_index);
// 					Index_Obj.push_back(temp_index);
// 				}
// 			}
// 		}

// 		clock_t end = clock();
// 		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
// 		printf("Time of tiny_obj_loader_load_obj: %lf\n\n", elapsed_secs);
// 	}

// 	// split_str - Definition for the split_str function
// 	void split_str(const string &s, char* delim, vector<string> &v) {
// 		// to avoid modifying original string
// 		// first duplicate the original string and return a char pointer then free the memory
// 		char *dup = strdup(s.c_str());
// 		char *token = strtok(dup, delim);
// 		while(token != NULL){
// 			v.push_back(string(token));
// 			// the call is treated as a subsequent calls to strtok:
// 			// the function continues from where it left in previous invocation
// 			token = strtok(NULL, delim);
// 		}
// 		free(dup);
// 	}

// 	// load_obj - Definition for the load_obj function
// 	//
// 	// Last modified: Sept. 9, 2017
// 	//
// 	// NOTE: this function currently is loading the verteces, normals, and uvs
// 	//		 based on the indices. This means that there is repeat values.
// 	void load_obj(const char* filename, vector<vec3> &vertices, vector<GLuint> &indices, vector<vec2> &uvs, vector<vec3> &normals) {
		
// 		// Temporary storage
// 		std::vector<unsigned int> vertexIndices, uvIndices,normalIndices;
// 		vector<vec3> temp_vertices;
// 		vector<vec2> temp_uvs;
// 		vector<vec3> temp_normals;

// 		// create file variable
// 		ifstream in(filename, ios::in);
// 		if(!in) {
// 			cerr << "Cannot open " << filename <<endl;
// 			exit(EXIT_FAILURE);
// 		} else {
// 			cout << "Load Obj - Opened .obj file: " << filename << endl;
// 		}

// 		string line; // variable to hold each line
// 		while(getline(in, line)) {
// 			if (line.length() > 3) { // make sure that the line is not empty

// 				// Get the object vertices
// 				if(line.substr(0, 2) == "v ") {
// 					istringstream s(line.substr(2));
// 					vec3 v; // Holds a temporary vertex
// 					s >> v.x; s >> v.y; s >> v.z; // get the x, y, and z of the point
// 					// cout << v.x << ", " << v.y << ", " << v.z << endl; // get the x, y, and z of the point
// 					// temp_vertices.push_back(v); // add the vertex to the vertices vector
// 					// NOTE: Need to do this for the normals and the verteces as well!!
// 					vertices.push_back(v);
// 				}
				
// 				// Get the object vertex normals
// 				else if (line.substr(0, 3) == "vn ") {
// 					istringstream s(line.substr(3));
// 					vec3 n;
// 					s >> n.x; s >> n.y; s >> n.z; // get x, y, and z. Since it's a vector w = 0.0
// 					temp_normals.push_back(n);
// 				}

// 				// Get the UV's for the mesh
// 				else if (line.substr(0,3) == "vt ") {
// 					istringstream s(line.substr(3));
// 					vec2 u;
// 					s >> u.x; s >> u.y; // get the x and y coordinate for the uv
// 					temp_uvs.push_back(u);
// 				}
// 				// Get the faces and how they are made up
// 				else if (line.substr(0, 2) == "f ") {
// 					string s  = line.substr(2, line.length());
// 					vector<string> elems_1; // Will contain the strings after "f ", split by spaces (" ")
// 					char delim_1[2] = " ";
// 					char delim_2[2] = "/";
// 					split_str(s, delim_1, elems_1); // split the string by spaces (" ") and get results in elems_2
// 					for(size_t i=0; i<elems_1.size(); ++i) {
// 						// cout << "1: " << elems_1[i] << endl;
// 						vector<string> elems_2; // Will contain the split up numbers (ex/ 1/1/1 -> 1, 1, 1)
// 						split_str(elems_1[i], delim_2, elems_2); // split the separated strings by the "/" delimiter
// 																 // and place the results in elems_2
// 						// cout << "Elem2 size: " << elems_2.size() << endl << endl;
// 						for(size_t j=0; j<elems_2.size(); ++j) {
// 							GLuint a  = atoi( elems_2[j].c_str() ) - 1; // convert the numbers into ints
// 							if(j == 0) {
// 								// cout << "a: " << a << endl;
// 								indices.push_back(a);
// 								vertexIndices.push_back(a);
// 							}
// 							else if(j == 1) {
// 								uvIndices.push_back(a);
// 							}
// 							else if(j == 2) {
// 								normalIndices.push_back(a);
// 							}
// 						}	
// 						// ++count;
// 					}
// 					// cout << endl;
// 				}
// 				else if(line[0] == '#') {
// 					// nothing
// 				}
// 				else {
// 					// nothing
// 				}
// 			} 
// 			else { // of the line is empty
// 				continue;
// 			}
// 		}
// 		// Output the vertices
// 		// NOTE: (Sept. 9) removed the intialization of vertices from
// 		//		 this chunk of code and put it up above
// 		for(unsigned int i=0; i<vertexIndices.size(); ++i) {

// 			// unsigned int vIndex = vertexIndices[i];
// 			unsigned int uIndex = uvIndices[i];
// 			unsigned int nIndex = normalIndices[i];
			
// 			// Get the attributes thanks to the index
// 			// vec3 vertex = temp_vertices[ vIndex ];
// 			vec2 uv = temp_uvs[ uIndex ];
// 			vec3 normal = temp_normals[ nIndex ];

// 			// Put the attributes in buffers
// 			// vertices.push_back(vertex);
// 			uvs.push_back(uv);
// 			normals.push_back(normal);
// 		}
// 	}
// }