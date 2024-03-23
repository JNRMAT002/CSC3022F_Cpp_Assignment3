// Implementation file for ConnectedComponent (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#include "../include/ConnectedComponent.h"

using namespace JNRMAT002;

ConnectedComponent::ConnectedComponent(int compID) {
    // std::cout << "Creating component number " << compID << "." << std::endl;
    m_numPixels = 0;
    setCompID(compID);
}

ConnectedComponent::~ConnectedComponent() {

}

// GETTERS
const int ConnectedComponent::getNumPixels() const {
    return m_numPixels;
}
const int ConnectedComponent::getCompID() const {
    return m_compID;
}
const std::vector<std::pair<unsigned char, int>> ConnectedComponent::getCompPixels() const {
    return compPixels;
}

// SETTERS
void ConnectedComponent::setNumPixels() {
    m_numPixels++;
}
void ConnectedComponent::setCompID(int compID) {
    m_compID = compID;
}
void ConnectedComponent::addPixel(unsigned char pixel, int index) {
    // Add to vector here
    compPixels.push_back(std::make_pair(pixel, index));
    setNumPixels();
}