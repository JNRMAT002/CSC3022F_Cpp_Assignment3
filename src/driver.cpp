#include <iostream>
#include "../include/PGMimageProcessor.h"
#include "../include/ConnectedComponent.h"

#define DEFAULT_THRESHOLD 128
#define DEFAULT_MIN_SIZE 3

using namespace JNRMAT002;

// Terminates the program early if the threshold value entered is not in the correct range.
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
            checkThreshold(_threshold); // Check validity of user input for threshold | function in driver
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

    // Create PGMimageProcessor object (using default constructor).
    PGMimageProcessor o_PGMimageProcessor = PGMimageProcessor();

    // Setting value of threshold - first check whether user specified threshold in command line.
    if (thresholdFound) {
        o_PGMimageProcessor.setThreshold(threshold);
    }
    else {
        o_PGMimageProcessor.setThreshold(DEFAULT_THRESHOLD);
    }

    // Set name of Input PGM File, print status, and write status.
    o_PGMimageProcessor.setInputFileName(inputPGMFile);
    o_PGMimageProcessor.setWriteStatus(w);
    o_PGMimageProcessor.setPrintStatus(p);

    // Extract data of inputPGMFile here
    o_PGMimageProcessor.extractPGMData();
    
    // Setting values of component sizes - first check whether user specified component sizes in command line.
    if (compSizeFound) {
        o_PGMimageProcessor.setMinComponentSize(minComponentSize);
        o_PGMimageProcessor.setMaxComponentSize(maxComponentSize);
    } else {
        o_PGMimageProcessor.setMinComponentSize(DEFAULT_MIN_SIZE);
        o_PGMimageProcessor.setMaxComponentSize(o_PGMimageProcessor.getImgWidth() * o_PGMimageProcessor.getImgHeight());
    }

    // Extract components from pixel buffer here
    int numComponents = o_PGMimageProcessor.extractComponents(o_PGMimageProcessor.getThreshold(), DEFAULT_MIN_SIZE);
    std::cout << "Number of components found in initial extraction: " << numComponents << std::endl;

    numComponents = o_PGMimageProcessor.filterComponentsBySize(o_PGMimageProcessor.getMinComponentSize(), o_PGMimageProcessor.getMaxComponentSize());
    std::cout << "Number of components after filtering by size criteria: " << numComponents << std::endl;

    if (w) {
        if (o_PGMimageProcessor.writeComponents("data/test.pgm")) {
            std::cout << "Output of component data written to output file successfully." << std::endl;
        }
    }

    std::cout << std::boolalpha;

    // std::cout << o_PGMimageProcessor.getMinComponentSize() << " " << o_PGMimageProcessor.getMaxComponentSize() << " "
    // << (int)o_PGMimageProcessor.getThreshold() << " " << o_PGMimageProcessor.getPrintStatus() << " "
    // << o_PGMimageProcessor.getWriteStatus() << " " << o_PGMimageProcessor.getInputFileName() << std::endl;

    return 0;
}

void checkThreshold (int threshold) {
    if ( (threshold < 0) || (threshold > 255) ) {
        std::cout << "Please enter a valid threshold value in the 0..255 range." << std::endl;
        exit(0);
    }
}