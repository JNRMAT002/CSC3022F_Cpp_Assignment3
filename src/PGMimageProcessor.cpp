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

        int length = getImgWidth() * getImgHeight();
        buffer = new char[length];
        // read data as a block into buffer:
        readPGM.read ((char *)buffer,length);

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

    

    return 1;
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

void PGMimageProcessor::writePGM(int bufferLength) {
    std::ofstream writePGM("data/test.pgm", std::ofstream::binary);

    for (int i = 0; i < PGM_HEADER.size(); i++) {
        writePGM << (PGM_HEADER[i]) << "\n";
    }
    
    writePGM.write (reinterpret_cast<char*>(pixels), bufferLength);

    
    writePGM.close();
}