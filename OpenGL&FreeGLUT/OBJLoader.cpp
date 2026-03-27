//
//#include "OBJLoader.h"
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//void LoadOBJ(const char* filename, std::vector<Vertex>& vertices, std::vector<Face>& faces) {
//    std::ifstream file(filename);
//    if (!file.is_open()) {
//        std::cerr << "Could not open the file!" << std::endl;
//        return;
//    }
//
//    std::string line;
//    while (std::getline(file, line)) {
//        std::istringstream stream(line);
//        std::string prefix;
//        stream >> prefix;
//
//        if (prefix == "v") { // Vertex definition
//            Vertex vertex;
//            stream >> vertex.x >> vertex.y >> vertex.z;
//            vertices.push_back(vertex);
//        }
//        else if (prefix == "f") { // Face definition
//            Face face;
//            for (int i = 0; i < 3; ++i) { // Assuming triangles
//                int index;
//                stream >> index;
//                face.vertexIndices[i] = index - 1; // Convert to 0-based index
//            }
//            faces.push_back(face);
//        }
//    }
//
//    file.close();}