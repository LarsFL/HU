#include "hwlib.hpp"
#include "circle.hpp"
#include "line.cpp"
#include <math.h>
#include <chrono>
using namespace std::chrono;

constexpr hwlib::xy pointOnCircle(int degrees, const hwlib::xy & origin, int radius) {
    float rad = degrees * (3.141592653589793238462643383279f / 180.0f);
    return (hwlib::xy((origin.x + radius * cos(rad)), (origin.y + radius * sin(rad))));
}

constexpr std::array<hwlib::xy, 12> fillHours(int amount, int degrees, const hwlib::xy&origin, int radius) {
    std::array<hwlib::xy, 12> v{hwlib::xy(0,0)};
    for(int i = 0; i < amount; i++) {
        v[i] = pointOnCircle(((360 / 12 * i) + 270), origin, radius);
    }
    return v;
}

constexpr std::array<hwlib::xy, 60> fillMinutes(int amount, int degrees, const hwlib::xy&origin, int radius) {
    std::array<hwlib::xy, 60> v{hwlib::xy(0,0)};
    for(int i = 0; i < amount; i++) {
        v[i] = pointOnCircle(((360 / 60 * i) + 270), origin, radius);
    }
    return v;
}

int main( void ) {
    namespace target = hwlib::target;
    auto scl = target::pin_oc(target::pins::scl);
    auto sda = target::pin_oc(target::pins::sda);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
    auto display = hwlib::glcd_oled_i2c_128x64_direct(i2c_bus, 0x3c);



    display.clear();
    display.write(hwlib::xy((display.size.x / 2), (display.size.y / 2)));
    constexpr int watchSize = 25;
    constexpr hwlib::xy location = hwlib::xy(64, 32);
    auto watch = circle(display, location, watchSize);
    watch.draw();

    constexpr std::array<hwlib::xy, 12> hours = fillHours(12, 360, location, 20);
    constexpr std::array<hwlib::xy, 60> minutes = fillMinutes(60, 360, location, 15);
    // for (;;){
    //     for(int i = 0; i < 12; i++) {
    //             display.clear();
    //             watch.draw();
    //             drawline(display, location.x, location.y, hours[i].x, hours[i].y);
    //             display.flush();
    //             hwlib::wait_ms(1000);
    //     }
    // }

    int minuteCount = 0;
    int hourCount = 0;
    auto base = hwlib::now_us();
    auto now = base + 1200000;

    // drawline(display, location.x, location.y, minutes[0].x, minutes[0].y);
    // display.flush();
    // hwlib::cout << "Hi";

    for (;;) {
        now = hwlib::now_us();
        if (now - base > 2000000) {
            if (minuteCount == 60) {minuteCount = 0; hourCount++;}
            if (hourCount == 12) {hourCount = 0;}
            display.clear();
            watch.draw();
            drawline(display, location.x, location.y, minutes[minuteCount].x, minutes[minuteCount].y);
            display.flush();
            // hwlib::cout << "Now" << hwlib::endl;
            // hwlib::wait_ms(100);
            // hwlib::cout << "Now" << hwlib::endl;
            drawline(display, location.x, location.y, hours[hourCount].x, hours[hourCount].y);
            // hwlib::cout << "Now" << hwlib::endl;
            display.flush();
            minuteCount++;
            base = hwlib::now_us();
        }
    }
}