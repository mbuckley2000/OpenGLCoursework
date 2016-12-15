#pragma once

#include <stdio.h>
#include <array>
#include <vector>
#include <cstring>
#include <glm/glm.hpp>

// Very, VERY simple OBJ loader.
// Ignores everything except vertices and faces.
//
// Originally writen by Yongliang Yang using GLM,
// modified by Andrew Chinery to use Eigen, and
// modified by Christian Richardt to use plain C++11.
inline bool load_obj(const char *path, std::vector<glm::vec3> &vertices, std::vector<std::array<int, 4>> &faces)
{
	printf("Loading OBJ file '%s' ... ", path);

	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Could not open file. Is the path correct?\n");
		return false;
	}

    /*
     *  std::vector<std::array<int, 3>> faces;
        std::vector<glm::vec3> vertices;
     */


	while (true)
	{
		char lineHeader[128];

		// Read the first word of the line.
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break;  // EOF = End Of File. Quit the loop.

		// Parse the line.
        if (strcmp(lineHeader, "v") == 0) //It's a vertex
		{
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);   //&vertex[0] etc
			vertices.push_back(vertex);
		} else if (strcmp(lineHeader, "f") == 0) //It's a face
		{
            std::array<int, 4> face;
            fscanf(file, "%i %i %i\n", &face[0], &face[1], &face[2]);
            face[0]--;
            face[1]--;
            face[2]--; //Adjust to make index start at 0
            faces.push_back(face);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char ignored[1024];
			fgets(ignored, 1024, file);
		}
	}
    printf("Done.\n");

	return true;
}