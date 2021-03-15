classMaker.exe reads a file including basic class info and automaticaly creates a .h and .cpp file with getters, setters, and even a parametrized constructor for the class.

This program reads formatted data, here is how the data is formatted based off the sample class. types, names, and the class name should have NO SPACES in them. The program reads word by word.

Frog                        //start with the class name
#include <string>           //include extra libraries here
#include <vector>
int id                      //data members are listed in the format DATATYPE DATANAME
float weight
float length
char gender
std::string name            //this program does not automaticly use namespace std
std::vector<int> intList    //it should work with template stuff

to use this either use the following line in the command prompt with both the exe and the class data in the same folder
classMaker.exe classData

or drag the class data onto classMaker.exe

or give class data a unique file extention and choose, always open with classMaker.exe for ultimate ease of access

SAMPLE INPUT FILE: ClassData
Frog
#include <string>
#include <vector>
int id
float weight
float length
char gender
std::string name
std::vector<int> intList

SAMPLE OUTPUT FILE: Frog.h
#ifndef FROG_H
#define FROG_H

#include <string>
#include <vector>

class Frog{
private:
	int id;
	float weight;
	float length;
	char gender;
	std::string name;
	std::vector<int> intList;
public:
	Frog(int id, float weight, float length, char gender, std::string name, std::vector<int> intList);

	int GetId();
	void SetId(int id);

	float GetWeight();
	void SetWeight(float weight);

	float GetLength();
	void SetLength(float length);

	char GetGender();
	void SetGender(char gender);

	std::string GetName();
	void SetName(std::string name);

	std::vector<int> GetIntList();
	void SetIntList(std::vector<int> intList);

};
#endif

SAMPLE OUTPUT FILE: Frog.cpp
#include "Frog.h"

Frog::Frog(int id, float weight, float length, char gender, std::string name, std::vector<int> intList){
	this->id = id;
	this->weight = weight;
	this->length = length;
	this->gender = gender;
	this->name = name;
	this->intList = intList;
}

int Frog::GetId(){
	return id;
}
void Frog::SetId(int id){
	this->id = id;
}

float Frog::GetWeight(){
	return weight;
}
void Frog::SetWeight(float weight){
	this->weight = weight;
}

float Frog::GetLength(){
	return length;
}
void Frog::SetLength(float length){
	this->length = length;
}

char Frog::GetGender(){
	return gender;
}
void Frog::SetGender(char gender){
	this->gender = gender;
}

std::string Frog::GetName(){
	return name;
}
void Frog::SetName(std::string name){
	this->name = name;
}

std::vector<int> Frog::GetIntList(){
	return intList;
}
void Frog::SetIntList(std::vector<int> intList){
	this->intList = intList;
}

