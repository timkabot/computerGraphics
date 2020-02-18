#pragma once


#include "read_obj.h"


class Projection : public ReadObj
{
public:
	Projection(unsigned short width, unsigned short height, std::string obj_file);
	virtual ~Projection();

	void DrawScene();

protected:
	virtual void DrawTriangle(float4 triangle[3], color color);

	float x_center = width / 2.0;
	float y_center = height / 2.0;
};