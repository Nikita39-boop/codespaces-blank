#pragma once
#include "qdatetime.h"
#include <string>

class Object
{
private:
	std::string name;
	float coordinateX;
	float coordinateY;
	std::string type;
    QDateTime createDate;
public:
    Object(const std::string& name, float x, float y, const std::string& type, const QDateTime& date)
        :name(name), coordinateX(x), coordinateY(y), type(type), createDate(date){}

	std::string getName() const { return name; };
    float getCoordinateX() const { return coordinateX; }
    float getCoordinateY() const { return coordinateY; }
    std::string getType() const { return type; }
    QDateTime getDate() const { return createDate; }
};

