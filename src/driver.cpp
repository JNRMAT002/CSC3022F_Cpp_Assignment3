#include <iostream>

int setDefaultThreshold ();
void checkThreshold (int threshold);

int main (int argc, char* argv[]) {
    bool compSizeFound = false; // Check value for if -s command present
    bool thresholdFound = false; // Check value for if -t command present
    int minComponentSize = 0; // Set default to 3 in PGMimageProcessor if compSizeFound = false
    int maxComponentSize = 0; // Set default to imgWidth*imgHeight if compSizeFound = false
    int threshold = 0; // Threshold value | default set to 128 if no threshold option set in command line. Program terminted if value outside of valid range (0..255)
    bool p = false;
    bool w = false;

    std::string inputPGMFile;

    // Retreive command line input
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-s") {
            compSizeFound = true;
            minComponentSize = atoi(argv[i+1]);
            maxComponentSize = atoi(argv[i+2]);
        }

        if (std::string(argv[i]) == "-t") {
            thresholdFound = true;
            threshold = atoi(argv[i+1]);
            checkThreshold(threshold);
        }

        if (std::string(argv[i]) == "-p") {
            p = true;
        }

        if (std::string(argv[i]) == "-w") {
            w = true;
        }
    }

    if (!thresholdFound) {
        threshold = setDefaultThreshold();
        std::cout << "Default threshold value set to 128..." << std::endl;
    }

    inputPGMFile = argv[argc-1];

    // std::cout << minComponentSize << " " << maxComponentSize << " " << threshold << " " << p << " " << w << " " << inputPGMFile << std::endl;

    return 0;
}

// Sets default threshold value if the relevant command was not entered
int setDefaultThreshold () {
    return 128;
}

// Terminates the program early if the threshold value entered is not in the correct range
void checkThreshold (int threshold) {
    if ( (threshold < 0) || (threshold > 255) ) {
        std::cout << "Please enter a valid threshold value in the 0..255 range." << std::endl;
        exit(0);
    }
}