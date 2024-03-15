#include <iostream>
#include "../include/PGMimageProcessor.h"

#define DEFAULT_THRESHOLD 128

using namespace JNRMAT002;

void checkThreshold (int threshold);

int main (int argc, char* argv[]) {
    bool compSizeFound = false; // Check value for if -s command present
    bool thresholdFound = false; // Check value for if -t command present
    int minComponentSize = 0; // Set default to 3 in PGMimageProcessor if compSizeFound = false
    int maxComponentSize = 0; // Set default to imgWidth*imgHeight if compSizeFound = false
    unsigned char threshold; // Threshold value | default set to 128 if no threshold option set in command line. Program terminted if value outside of valid range (0..255)
    int _threshold;
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
            _threshold = atoi(argv[i+1]);
            checkThreshold(_threshold); // Check validity of user input for threshold
            threshold = static_cast<unsigned char>(_threshold);
            
        }

        if (std::string(argv[i]) == "-p") {
            p = true;
        }

        if (std::string(argv[i]) == "-w") {
            w = true;
        }
    }

    inputPGMFile = argv[argc-1];

    PGMimageProcessor o_PGMimageProcessor = PGMimageProcessor();
    o_PGMimageProcessor.setInputFileName(inputPGMFile);
    o_PGMimageProcessor.setWriteStatus(w);
    o_PGMimageProcessor.setPrintStatus(p);

    if (compSizeFound) {
        o_PGMimageProcessor.setMinComponentSize(minComponentSize);
        o_PGMimageProcessor.setMaxComponentSize(maxComponentSize);
    }

    if (thresholdFound) {
        o_PGMimageProcessor.setThreshold(threshold);
    }
    else {
        o_PGMimageProcessor.setThreshold(DEFAULT_THRESHOLD);
    }

    std::cout << std::boolalpha;

    std::cout << o_PGMimageProcessor.getMinComponentSize() << " " << o_PGMimageProcessor.getMaxComponentSize() << " "
    << (int)o_PGMimageProcessor.getThreshold() << " " << o_PGMimageProcessor.getPrintStatus() << " "
    << o_PGMimageProcessor.getWriteStatus() << " " << o_PGMimageProcessor.getInputFileName() << std::endl;

    return 0;
}

// Terminates the program early if the threshold value entered is not in the correct range
void checkThreshold (int threshold) {
    if ( (threshold < 0) || (threshold > 255) ) {
        std::cout << "Please enter a valid threshold value in the 0..255 range." << std::endl;
        exit(0);
    }
}