// Definition file for ConnectedComponent (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#ifndef ConnectedComponent_H
#define ConnectedComponent_H

#include <iostream>
#include <vector>

namespace JNRMAT002 {
    class ConnectedComponent{
        // Naming all member variables with "m_" to distinguish from function parameters.
        private:
            int m_numPixels; // Number of pixels in a component
            int m_compID; // Unique integer ID for a component
            std::vector<std::pair<unsigned char, int>> compPixels; // Storing a vector of pairs - pair is <pixel, index buffer>
        public:
            // Constructor
            ConnectedComponent(int compID);

            // Copy Constructor
            // ConnectedComponent(const ConnectedComponent& other);

            // Move Constructor
            // ConnectedComponent(ConnectedComponent&& other);

            // Copy Assignment Operator
            // ConnectedComponent& operator =(const ConnectedComponent& other);

            // Move Assignment Operator
            // ConnectedComponent& operator =(ConnectedComponent&& other);

            // Destructor
            ~ConnectedComponent();

            // GETTERS
            const int getNumPixels() const;
            const int getCompID() const;
            const std::vector<std::pair<unsigned char, int>> getCompPixels() const;

            // SETTERS
            void setNumPixels();
            void setCompID(int compID);
            void addPixel(unsigned char pixel, int index);

    };
}

#endif