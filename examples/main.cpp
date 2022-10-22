
#include <iostream>

#include <functional>
#include <vector>
#include <algorithm>
#include <exception>

#include "PixelWindow/PixelWindow.h"


int main(void) {

	pw::PixelWindow w = pw::PixelWindow(640, 480, "Hello SoftwareRenderer", false);

	while (w.isActive()) {

		w.makeCurrent();
		w.pollEvents();

		w.beginFrame();
		w.setBackgroundColor(0);

		w.setPixel(100, 100, 0xFFFF0000);

		w.endFrame();

	}

    return 0;
}