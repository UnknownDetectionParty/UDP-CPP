#pragma once

#include "stdafx.h"

class MathHelper
{
public:
	static double radtodeg(double x) {
		return x * 180.0 / M_PI;
	}

	static double degtorad(double x) {
		return x * M_PI / 180.0;
	}

	static double distance(double x, double y) {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	static double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
		return distance(y1 - y2, distance(x1 - x2, z1 - z2));
	}

	static double direction(double x1, double y1, double x2, double y2) {
		return radtodeg(atan2(y2 - y1, x2 - x1));
	}

	static double * direction(double x1, double y1, double z1, double x2, double y2, double z2) {
		double dx = x2 - x1;
		double dy = y2 - y1;
		double dz = z2 - z1;
		double yaw = radtodeg(atan2(dz, dx)) - 90;
		double pitch = -radtodeg(atan2(dy, distance(dx, dz)));
		return new double[2] { yaw, pitch };
	}
};