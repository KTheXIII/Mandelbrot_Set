#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <iostream>

#include "Engine.hpp"

class Mandelbrot : public EN::Application {
   public:
    Mandelbrot(){
        GetWindow().SetTitle("Mandelbrot set");
    };

    ~Mandelbrot(){

    };
};

int main(int argc, char const* argv[]) {
    EN::Application* app = new Mandelbrot();
    app->Run();
    return 0;
}
