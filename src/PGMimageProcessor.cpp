// Implementation file for PGMimageProcessor (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#include "../include/PGMimageProcessor.h"

using namespace JNRMAT002;

PGMimageProcessor::PGMimageProcessor() {
    std::cout << "Creating PGMimageProcessor object..." << std::endl;
}

PGMimageProcessor::~PGMimageProcessor() {

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

// SETTERS
// Setter method for inputPGMFile
void PGMimageProcessor::setInputFileName(std::string inputPGMFile) {
    m_inputPGMFile = inputPGMFile;
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