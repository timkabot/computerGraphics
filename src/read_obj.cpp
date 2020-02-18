#include "read_obj.h"


#include <fstream>
#include <sstream>

#include <algorithm>
#define pb push_back
ObjParser::ObjParser(std::string filename):
	filename(filename)
{
}


ObjParser::~ObjParser()
{

}
using namespace std;
int ObjParser::Parse()
{
	ifstream my_file(filename, ifstream::in);
	
	if (my_file.fail()) return 1;

	string line;
	char empty = ' ';
	string	face_sign = "f ",
		vertex_sign = "v ";

	while (getline(my_file, line)) {
		//VERTEXES
		if (line.rfind(vertex_sign, 0) == 0) {
			float4 vertex{ 0, 0, 0, 1 };
			vector < string > tokens = Split(line, empty);
			for (int i = 1; i < tokens.size(); ++i)	vertex[i - 1] = stof(tokens[i]);
			vertexes.pb(vertex);
		}
		else if (line.rfind(face_sign, 0) == 0){
		//FACES
			vector<string> tokens = Split(line, empty);
			vector<int> indexes;

			for (int i = 1; i < tokens.size(); ++i){
				vector<string> index_data = Split(tokens[i], empty);
				int index = stoi(index_data[0]);
				if (index>0)	--index;
				else  index += vertexes.size();
				indexes.pb(index);
			}

			for (int i = 0; i < indexes.size() - 2; ++i)
			{
				face temp_face;
				for (int j = 0; j < 3; ++j) temp_face.vertexes[j] = vertexes[indexes[i + j]];
				faces.push_back(temp_face);
			}
		}
	}

	return 0;
}

const vector<face>& ObjParser::GetFaces()
{
	return faces;
}

vector<string> ObjParser::Split(const std::string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
	{
		tokens.pb(token);
	}
	return tokens;
}


ReadObj::ReadObj(unsigned short width, unsigned short height, std::string obj_file): LineDrawing(width, height)
{
	parser = new ObjParser(obj_file);
}

ReadObj::~ReadObj()
{
	delete parser;
}

void ReadObj::DrawScene()
{
	parser->Parse();

	float x_center = width / 2.0;
	float y_center = height / 2.0;

	float radius = min(x_center, y_center) - 1;

	for (auto face : parser->GetFaces())
	{
		for (int j = 0; j < 3; ++j) {
			color temp_color;
			if (j == 0) temp_color = color(255, 0, 0);
			else if(j == 1) temp_color = color(0, 255, 0);
			else temp_color = color(0, 0, 255);
			DrawLine(
				static_cast<unsigned short>(x_center + radius * face.vertexes[j].x),
				static_cast<unsigned short>(y_center + radius * face.vertexes[j].y),
				static_cast<unsigned short>(x_center + radius * face.vertexes[(j + 1) % 3].x),
				static_cast<unsigned short>(y_center + radius * face.vertexes[(j + 1) % 3].y),
				temp_color
			);
		}
	}

}

