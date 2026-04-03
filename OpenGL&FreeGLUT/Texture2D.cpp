#include "Texture2D.h"
#include <fstream>
#include <iostream>
using namespace std;


Texture2D::Texture2D()
{
   
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}
bool Texture2D::Load(const char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file" << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //Seek to end of file
	fileSize = (int)inFile.tellg(); //Get current position in file - The End, this gives us total file size
	tempTextureData = new char[fileSize]; //Create a new array to store data
	inFile.seekg(0, ios::beg); //Seek back to beginning of file
	inFile.read(tempTextureData, fileSize); //Read in all the data in one go
	inFile.close(); //Close the file

	cout << path << " loaded." << endl;

	glGenTextures(1, &_ID); //Get next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture into the ID
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData); //Specify details of our texture image
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filter
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] tempTextureData; //Clears the data
	return true;
}
//bool Texture2D::Load(const char* path, int width, int height)
//{
//    _width = width;
//    _height = height;
//
//    std::ifstream inFile(path, std::ios::binary);
//    if (!inFile.good())
//    {
//        std::cerr << "Can't open texture file: " << path << std::endl;
//        return false;
//    }
//
//    // 1. Calculate size (Assuming RGB - 3 bytes)
//    int fileSize = width * height * 3;
//    unsigned char* tempTextureData = new unsigned char[fileSize];
//
//    // 2. Read the data and close
//    inFile.read(reinterpret_cast<char*>(tempTextureData), fileSize);
//
//    // Check if the file actually had enough data
//    if (inFile.gcount() < fileSize) {
//        std::cerr << "Warning: Texture file " << path << " is smaller than expected!" << std::endl;
//    }
//    inFile.close();
//
//    // 3. Bind and Set Alignment (CRITICAL)
//    glBindTexture(GL_TEXTURE_2D, _ID);
//
//    // This tells OpenGL to read pixels 1 byte at a time (fixes alignment issues)
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//    // 4. Build Mipmaps
//    // Parameter 2: Internal Format (3 for RGB)
//    // Parameter 5: Format of your data (GL_RGB)
//    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
//
//    // 5. Set Filtering
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    // Optional: Helps if your texture coordinates go slightly outside 0.0-1.0
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//    delete[] tempTextureData;
//
//    std::cout << path << " loaded successfully (" << width << "x" << height << ")\n";
//    return true;
//}