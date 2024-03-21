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

void PGMimageProcessor::extractPGMData() {
    std::ifstream readPGM(m_inputPGMFile, std::ifstream::binary);
    PGMcount = 0; // Initializing PGMcount to zero before PGM file is read

    // std::cout << m_inputPGMFile << std::endl;

    // Error checking for opening of PGM file
    if (!readPGM) {
        std::cout << "Cannot open file." << std::endl;
        exit(0);
    }

    if (readPGM) {
        
        // readPGM.seekg(0, readPGM.end);
        // int length = readPGM.tellg();
        // readPGM.seekg(0, readPGM.beg);

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

        // ...buffer contains the entire file... rewrite to pixels
        pixels = reinterpret_cast<unsigned char*>(buffer);
    }

    // Printing data in PGM_HEADER vector to validate retrieving of header data from inputPGMFile
    // for (int i = 0; i < PGM_HEADER.size(); i++) {
    //     std::cout << (PGM_HEADER[i]) << "\n";
    // }

    readPGM.close();
}

int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize) {
    
    // std::cout << "Checking output of extractComponents(): " << static_cast<unsigned>(threshold) << " " << minValidSize << " " << static_cast<unsigned>(pixels[0]) << std::endl;
    int numComponents = 0;
    

    for (int i = 0; i < getBufferLength(); i++) {
        if ( (pixels[i] >= threshold) ) {
            pixels[i] = 0;
            ConnectedComponent o_ConnectedComponent = ConnectedComponent(numComponents);
            o_ConnectedComponent.addPixel(pixels[i], i);
            // std::cout << "Check1" << std::endl;
            checkAdjacentPixels(pixels[i], i, o_ConnectedComponent);
            // std::cout << "Check2" << std::endl;
            if (o_ConnectedComponent.getNumPixels() >= minValidSize) {
                numComponents++;
                Components.push_back(o_ConnectedComponent);
                std::cout << o_ConnectedComponent.getNumPixels() << std::endl;
            }
        }
    }

    return numComponents;
}

void PGMimageProcessor::checkAdjacentPixels(unsigned char pixel, int pixelIndex, ConnectedComponent& o_ConnectedComponent) {

    // std::cout << "test" << std::endl;
    int SOUTH = pixelIndex+getImgWidth();
    int NORTH = pixelIndex-getImgWidth();
    int EAST = pixelIndex+1;
    int WEST = pixelIndex-1;

    if ( (SOUTH < getBufferLength()) && (pixels[SOUTH] >= m_threshold) ) {
        pixels[SOUTH] = 0;
        o_ConnectedComponent.addPixel(255, SOUTH);
        checkAdjacentPixels(pixels[SOUTH], SOUTH, o_ConnectedComponent);
    }

    if ( (NORTH > 61) && (pixels[NORTH] >= m_threshold) ) {
        pixels[NORTH] = 0;
        o_ConnectedComponent.addPixel(255, NORTH);
        checkAdjacentPixels(pixels[NORTH], NORTH, o_ConnectedComponent);
    }

    if ( (EAST < getBufferLength()) && (pixels[EAST] >= m_threshold) ) {
        pixels[EAST] = 0;
        o_ConnectedComponent.addPixel(255, EAST);
        checkAdjacentPixels(pixels[EAST], EAST, o_ConnectedComponent);
    }

    if ( (WEST > 61) && (pixels[WEST] >= m_threshold) ) {
        pixels[WEST] = 0;
        o_ConnectedComponent.addPixel(255, WEST);
        checkAdjacentPixels(pixels[WEST], WEST, o_ConnectedComponent);
    }

}

int PGMimageProcessor::filterComponentsBySize(int minComponentSize, int maxComponentSize) {
    int numComponents = Components.size();

    for (int i = 0; i < Components.size(); i++) {
        if ( (Components[i].getNumPixels() <= minComponentSize) || (Components[i].getNumPixels() >= maxComponentSize) ) {
            std::cout << Components[i].getNumPixels() << std::endl;
            Components.erase(Components.begin() + i);
            numComponents--;
        }
    }

    return numComponents;
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

void PGMimageProcessor::writePGM(int bufferLength) {
    std::ofstream writePGM("data/test.pgm", std::ofstream::binary);

    for (int i = 0; i < PGM_HEADER.size(); i++) {
        writePGM << (PGM_HEADER[i]) << "\n";
    }

    for (int i = 0; i < getBufferLength(); i++) {
        if (pixels[i] < 255) {
            pixels[i] = 0;
        }
    }
    
    writePGM.write (reinterpret_cast<char*>(pixels), bufferLength);

    
    writePGM.close();
}