#pragma once
#include "elements/Doodle.h"

class Global {
public:
	static const int PAD_NUM = 2;

	static float highest_pad[PAD_NUM];
	static float offset;
	static Doodle* doodle;
};