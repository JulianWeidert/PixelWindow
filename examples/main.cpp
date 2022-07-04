
#include <iostream>

#include <functional>
#include <vector>
#include <algorithm>
#include <exception>

#include "PixelWindow/PixelWindow.h"


int main(void) {

	pw::PixelWindow w1 = pw::PixelWindow(640, 480, "Hello SoftwareRenderer");
	pw::PixelWindow w2 = pw::PixelWindow(640, 480, "Hello SoftwareRenderer");

	while (w1.isActive() || w2.isActive()) {

		if (!w1.isActive()) w1.forceClose();
		if (!w2.isActive()) w2.forceClose();

		w1.makeCurrent();
		w1.pollEvents();

		w2.makeCurrent();
		w2.pollEvents();
	}

    return 0;
}