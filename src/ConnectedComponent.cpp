// Implementation file for ConnectedComponent (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#include "../include/ConnectedComponent.h"

using namespace JNRMAT002;

ConnectedComponent::ConnectedComponent(int compID) {
    // std::cout << "Creating component number " << compID << "." << std::endl;
    m_numPixels = 0;
    setCompID(compID);
}

// // Program structured so that none of the following constructors (copy, move, copy assignment, move assignment) are used.
// ConnectedComponent::ConnectedComponent(const ConnectedComponent& other) {
//     int m_numPixels = other.m_numPixels;
//     int m_compID = other.m_compID;

//     for (int i = 0; i < compPixels.size(); i++) {
//         compPixels[i].first = other.compPixels[i].first;
//         compPixels[i].second = other.compPixels[i].second;
//     }
//     // std::vector<std::pair<unsigned char, int>> compPixels;
// }

// ConnectedComponent::ConnectedComponent(ConnectedComponent&& other) {

// }

// ConnectedComponent& ConnectedComponent::operator =(const ConnectedComponent& other){
//     return *this;
// }

// ConnectedComponent& ConnectedComponent::operator =(ConnectedComponent&& other) {
//     return *this;
// }

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