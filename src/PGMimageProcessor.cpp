// Implementation file for PGMimageProcessor (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#include "../include/PGMimageProcessor.h"

using namespace JNRMAT002;

PGMimageProcessor::PGMimageProcessor() {
    std::cout << "Creating PGMimageProcessor object..." << std::endl;
}

PGMimageProcessor::~PGMimageProcessor() {
    delete[] buffer;
}

// Program structured so that none of the following constructors (copy, move, copy assignment, move assignment) are used.
// PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other) {

// }

// PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& other) {

// }

// PGMimageProcessor& PGMimageProcessor::operator =(const PGMimageProcessor& other){
//     return *this;
// }

// PGMimageProcessor& PGMimageProcessor::operator =(PGMimageProcessor&& other) {
//     return *this;
// }

void PGMimageProcessor::extractPGMData() {
    std::ifstream readPGM(m_inputPGMFile, std::ifstream::binary);
    PGMcount = 0; // Initializing PGMcount to zero before PGM file is read


    // Error checking for opening of PGM file
    if (!readPGM) {
        std::cout << "Cannot open file." << std::endl;
        exit(0);
    }

    if (readPGM) {

        while (std::getline(readPGM, line)) {
            if (line[0] == '#') {
                line = "# Rewritten by Matthew January for CSC3022F 2024 Assignment 3";
            }

            PGM_HEADER.push_back(line);
            // std::cout << line << " ";

            if ( (line != "P5") && (line[0] != '#') ) {
                commentsProcessed = true;
                PGMcount++;
            }

            if (PGMcount == 1) {
                std::stringstream ss;
                ss << line;
                int imgWidth, imgHeight;
                ss >> imgWidth;
                ss >> imgHeight;

                setImgWidth(imgWidth);
                setImgHeight(imgHeight);

                // std::cout << dimensions.second << " ";
            }

            if ( (commentsProcessed) && (PGMcount == 2) ) {
                break;
            }
        }

        setBufferLength();;
        buffer = new char[getBufferLength()];
        // read data as a block into buffer:
        readPGM.read ((char *)buffer, getBufferLength());

        // ...buffer contains the entire file... rewrite to pixels (which is of type unsigned char)
        pixels = reinterpret_cast<unsigned char*>(buffer);
    }

    readPGM.close();
}

int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize) {
    int numComponents = 0;
    

    for (int i = 0; i < getBufferLength(); i++) {
        if ( (pixels[i] >= threshold) ) {
            pixels[i] = 255;
            ConnectedComponent o_ConnectedComponent;
            o_ConnectedComponent.setCompID(numComponents);
            o_ConnectedComponent.addPixel(pixels[i], i);
            pixels[i] = 0;
            checkAdjacentPixels(pixels[i], i, o_ConnectedComponent);
            if (o_ConnectedComponent.getNumPixels() >= minValidSize) {
                numComponents++;
                Components.push_back(o_ConnectedComponent);
                // std::cout << o_ConnectedComponent.getCompID() << " " << o_ConnectedComponent.getNumPixels() << std::endl;
            }
        }
        else {
            pixels[i] = 0;
        }
    }

    return numComponents;
}

void PGMimageProcessor::checkAdjacentPixels(unsigned char pixel, int pixelIndex, ConnectedComponent& o_ConnectedComponent) {

    int SOUTH = pixelIndex+getImgWidth();
    int NORTH = pixelIndex-getImgWidth();
    int EAST = pixelIndex+1;
    int WEST = pixelIndex-1;

    if ( (SOUTH < getBufferLength()) && (pixels[SOUTH] >= m_threshold) ) {
        pixels[SOUTH] = 255;
        o_ConnectedComponent.addPixel(pixels[SOUTH], SOUTH);
        pixels[SOUTH] = 0;
        checkAdjacentPixels(pixels[SOUTH], SOUTH, o_ConnectedComponent);
    }

    if ( (NORTH >= 0) && (pixels[NORTH] >= m_threshold) ) {
        pixels[NORTH] = 255;
        o_ConnectedComponent.addPixel(pixels[NORTH], NORTH);
        pixels[NORTH] = 0;
        checkAdjacentPixels(pixels[NORTH], NORTH, o_ConnectedComponent);
    }

    if ( (EAST < getBufferLength()) && (pixels[EAST] >= m_threshold) ) {
        pixels[EAST] = 255;
        o_ConnectedComponent.addPixel(pixels[EAST], EAST);
        pixels[EAST] = 0;
        checkAdjacentPixels(pixels[EAST], EAST, o_ConnectedComponent);
    }

    if ( (WEST >= 0) && (pixels[WEST] >= m_threshold) ) {
        pixels[WEST] = 255;
        o_ConnectedComponent.addPixel(pixels[WEST], WEST);
        pixels[WEST] = 0;
        checkAdjacentPixels(pixels[WEST], WEST, o_ConnectedComponent);
    }

}

int PGMimageProcessor::filterComponentsBySize(int minComponentSize, int maxComponentSize) {
    // int numComponents = Components.size();

    for (int i = 0; i < Components.size(); i++) {
        if ( (Components[i].getNumPixels() < minComponentSize) || (Components[i].getNumPixels() > maxComponentSize) ) {
            // std::cout << Components[i].getCompID() << " " << Components[i].getNumPixels() << std::endl;
            // int currID = Components[i].getCompID();
            // Components[i+1].setCompID(currID);

            // Components[i].setCompID(-1);
            Components.erase(Components.begin() + i);
            // numComponents--;
        }
    }
    // std::cout << Components[1].getCompID() << std::endl;
    for (int i = 0; i < Components.size(); i++) {
        Components[i].setCompID(i);
        if (getPrintStatus()) {
            printComponentData(Components[i]);
        }
    }

    return Components.size();
}

bool PGMimageProcessor::writeComponents(const std::string& outFileName) {
    std::ofstream writePGM(outFileName, std::ofstream::binary);

    if (writePGM.is_open()) {

        for (int i = 0; i < PGM_HEADER.size(); i++) {
            writePGM << (PGM_HEADER[i]) << "\n";
        }

        for (int i = 0; i < Components.size(); i++) {
            std::vector<std::pair<unsigned char, int>> compPixels = Components[i].getCompPixels();
            // std::cout << Components[i].getNumPixels() << std::endl;
            // std::cout << (int)compPixels[0].first << " " << compPixels[0].second << std::endl;
            // std::cout << compPixels.size() << std::endl;

            for (int j = 0; j < compPixels.size(); j++) {
                
                pixels[compPixels[j].second] = compPixels[j].first;
                // std::cout << (int)pixels[Components[i].getCompPixels()[j].second] << std::endl;
            }
        }

        writePGM.write (reinterpret_cast<char*>(pixels), bufferLength);

        writePGM.close();
        return true;

    }
    else {
        std::cerr << "Error opening " << outFileName << "." << std::endl;
    }

    return false;    
}

void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const {

    std::cout << "Component ID: " << theComponent.getCompID() << ". Number of pixels in Component: " << theComponent.getNumPixels() << "." << std::endl;;

    
}

// Extra GETTERS
// Getter method for inputFileName
std::string PGMimageProcessor::getInputFileName() {
    return m_inputPGMFile;
}

// Getter method for minComponentSize
int PGMimageProcessor::getMinComponentSize() {
    return m_minComponentSize;
}

// Getter method for maxComponentSize
int PGMimageProcessor::getMaxComponentSize() {
    return m_maxComponentSize;
}

// Getter method for threshold
unsigned char PGMimageProcessor::getThreshold() {
    return m_threshold;
}

// Getter method for print status
bool PGMimageProcessor::getPrintStatus() {
    return m_p;
}

// Getter method for write status
bool PGMimageProcessor::getWriteStatus() {
    return m_w;
}

int PGMimageProcessor::getImgWidth() {
    return m_imgWidth;
}

int PGMimageProcessor::getImgHeight() {
    return m_imgHeight;
}

int PGMimageProcessor::getBufferLength() {
    return bufferLength;
}

// SETTERS
// Setter method for inputPGMFile
void PGMimageProcessor::setInputFileName(std::string inputPGMFile) {
    std::string imageFileDir = "data/";
    m_inputPGMFile = imageFileDir + inputPGMFile;
}

// Setter method for threshold
void PGMimageProcessor::setThreshold(unsigned char threshold) {
    m_threshold = threshold;
}

// Setter method for minComponentSize
void PGMimageProcessor::setMinComponentSize(int minComponentSize) {
    m_minComponentSize = minComponentSize;
}

// Setter method for maxComponentSize
void PGMimageProcessor::setMaxComponentSize(int maxComponentSize) {
    m_maxComponentSize = maxComponentSize;
}

// Setter method for print status
void PGMimageProcessor::setPrintStatus(bool p) {
    m_p = p;
}

// Setter method for write status
void PGMimageProcessor::setWriteStatus(bool w) {
    m_w = w;
}

void PGMimageProcessor::setImgWidth(int imgWidth) {
    m_imgWidth = imgWidth;
}

void PGMimageProcessor::setImgHeight(int imgHeight) {
    m_imgHeight = imgHeight;
}

void PGMimageProcessor::setBufferLength() {
    bufferLength = m_imgWidth*m_imgHeight;
}