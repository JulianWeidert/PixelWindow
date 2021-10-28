// SoftwareRenderer.cpp : Defines the entry point for the application.
//

#include <iostream>

#include <functional>
#include <vector>
#include <algorithm>
#include <exception>

#include "PixelWindow/PixelWindow.h"

int main(void){
   
    int width = 640;
    int height = 480;
    int color = 0;

    sr::PixelWindow w = sr::PixelWindow(width, height, "Hello World");
    w.addResizeCallback([&color](int width, int height) {
        color = 0x00 << 24 | (width % 256) << 16 | (height % 256) << 8 | 0xFF;
    });

    int cpyCount = 0;
    double accTime = 0;
    while (w.isActive()) {
        double begin = glfwGetTime();
        
        w.beginFrame();
        w.setBackgroundColor(color);
        w.endFrame();

        double end = glfwGetTime();
        accTime += (end - begin);
        cpyCount++;
       
        if (accTime > 1.0) {
            int bytesPerFrame = w.getWidth() * w.getHeight() * 4;
            int transferPerSecondMB = (cpyCount / accTime) * bytesPerFrame / 10e5;
            std::cout << transferPerSecondMB << " " << cpyCount << std::endl;
            accTime = 0.0;
            cpyCount = 0;
        }


        w.pollEvents();
    }

    return 0;
}
