// Implementation file for PGMimageProcessor (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#include "../include/PGMimageProcessor.h"

using namespace JNRMAT002;

PGMimageProcessor::PGMimageProcessor(std::string inputPGMFile, int minComponentSize, int maxComponentSize, unsigned char threshold, bool p, bool w) {
    m_inputPGMFile = inputPGMFile;
    m_minComponentSize = minComponentSize;
    m_maxComponentSize = maxComponentSize;
    m_threshold = threshold;
    m_p = p;
    m_w = w;
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
// Setter method for threshold
void PGMimageProcessor::setThreshold() {

}

// Setter method for minComponentSize
void PGMimageProcessor::setMinComponentSize() {

}

// Setter method for maxComponentSize
void PGMimageProcessor::setMaxComponentSize() {

}

// Setter method for print status
void PGMimageProcessor::setPrintStatus() {

}

// Setter method for write status
void PGMimageProcessor::setWriteStatus() {

}