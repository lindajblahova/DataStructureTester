#pragma once

#include "structures/array/array.h"

using namespace structures;

class Scenarios {

public:

	Scenarios(char druh);
	int getOperacia(int index);
	~Scenarios();

private:
	Array<int>* operations;



};