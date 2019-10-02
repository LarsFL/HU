#include <thread>
#include <iostream>
// using namespace std;
#include <mutex>
#include <unistd.h>

    int mood = 1; // 0: Happy, 1: Mad
    bool blinking = false;
    bool mouth = false;
    const int blinkCount = 1000000000;
    const int moodCount = 300000000;
    const std::string eyebrow_normal[2] {
        "          ________           ",
        "          | -  - |           ",
    };
    const std::string eyebrow_angry[2] {
        "          ________           ",
        "          | ^  ^ |           ",
    };

    const std::string eyes_closed[1] = {
        "          | _  _ |           "
    };
    const std::string eyes_open[1] = {
        "          | 0  0 |           "
    };

    const std::string mouth_normal[2] = {
        "          | ---- |           ",
        "          --------           "
    };
    const std::string mouth_talk[2] = {
        "          |  []  |           ",
        "          --------           "
    };
    const std::string body_happy[17]={
        "      -----------------     ",
        "      |  |         |  |     ",
        "      |  |         |  |     ",
        "      |  |         |  |     ",
        "      |  |         |  |     ",
        "      |  |         |  |     ",
        "         |    o    |        ",
        "         |         |        ",
        "         |         |        ",
        "         -----------        ",
        "        /           \\      ",
        "       /             \\     ",
        "      /               \\    ",
        "     /                 \\   ",
        "    /                   \\  ",
        "   /                     \\ ",
        "  /                       \\",
        };

    const std::string body_angry[17]={
        "---------------------------",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |    o    |        ",
        "         |         |        ",
        "         |         |        ",
        "         -----------        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        "         |         |        ",
        };       



void printCharacter() {
    while (1) {
    std::cout << "\033[2J";
    usleep(100000);
        if (mood == 1) {
            for (const std::string line : eyebrow_normal) {
                std::cout << line << std::endl;
            }
        } else {
            for (const std::string line : eyebrow_angry) {
                std::cout << line << std::endl;
            }
        }
        if (blinking) {
            for (const std::string line : eyes_closed) {
                std::cout << line << std::endl;
            }
        } else {
            for (const std::string line : eyes_open) {
                std::cout << line << std::endl;
            }
        }

        if (!blinking && (mood == 0)) {
            for (const std::string line : mouth_talk) {
                std::cout << line << std::endl;
            }
        } else {
            for (const std::string line : mouth_normal) {
                std::cout << line << std::endl;
            }
        }

        if (mood == 1) {
            for (const std::string line : body_angry) {
                std::cout << line << std::endl;
            }
        } else {
            for (const std::string line : body_happy) {
                std::cout << line << std::endl;
            }
        }
    }
    }

void blink() {
    int blinker = 0;
    while (1) {
        if (blinker > blinkCount) {
            blinker = 0;
            if (blinking) {
                blinking = false;
            } else {
                blinking = true;
            }
        } else {
            blinker++;
        }
    }
}

void changeMood() {
    int mooder = 0;
    while (1) {
        if (mooder > moodCount) {
            mooder = 0;
            if (mood == 0) {
                mood = 1;
            } else {
                mood = 0;
            }
        } else {
            mooder++;
        }
    }
}

int main(int argc, char **argv) {
    std::thread print(printCharacter);
    std::thread blinker(blink);
    std::thread mood(changeMood);
    print.join();
    blinker.join();
    mood.join();
    return 0;
}
