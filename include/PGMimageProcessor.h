// Definition file for PGMimageProcessor (Assignment 3 for CSC3022F, 2024)
// By Matthew January - JNRMAT002

#ifndef PGMimageProcessor_H
#define PGMimageProcessor_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "../include/ConnectedComponent.h"

namespace JNRMAT002 {
    class PGMimageProcessor{
        // Naming all member variables with "m_" to distinguish from function parameters.
        private:
            char * buffer; // Array to hold initial read content of inputPGMFile
            unsigned char* pixels; // Array of unsigned char to hold the data read from inputPGMFile
            unsigned char m_threshold;
            int m_minValidSize = 3; // Default value for component size - use this in extractComponents.
            int m_minComponentSize; // Set by user. Value set by constructor based on user input. Set = minValidSize if not user-specified.
            int m_maxComponentSize; // Set by user. Value set by constructor. Set = imgWidth*imgHeight if not user-specified.
            bool m_p; // Set by user
            bool m_w; // Set by user
            std::string m_inputPGMFile; // Set by user
            int m_imgWidth;
            int m_imgHeight;
            std::string line; // String object used to hold getline() data from inputPGMFile
            bool commentsProcessed = false; // Checker for whether or not all comments in header of inputPGMFile have been processed
            int PGMcount; // Iterator to track position in header of inputPGMFile
            std::vector<std::string> PGM_HEADER; // Vector to hold lines from header of inputPGMFile to make writing easier later
            int compSizeCounter; // Counter to keep track of component size in extractComponents()
            int bufferLength;
            std::vector<ConnectedComponent> Components;

        public:
            // Default constructor
            PGMimageProcessor();
            
            // Destructor.
            ~PGMimageProcessor();

            // Function to extract header from inputPGMFile and to set default maxComponentSize
            void extractPGMData();

            /* process the input image to extract all the connected components,
            based on the supplied threshold (0...255) and excluding any components
            of less than the minValidSize. The final number of components that
            you store in your container (after discarding undersized one)
            must be returned.
            */
            int extractComponents(unsigned char threshold, int minValidSize);

            /* iterate - with an iterator - through your container of connected
            components and filter out (remove) all the components which do not
            obey the size criteria pass as arguments. The number remaining
            after this operation should be returned.
            */
            int filterComponentsBySize(int minComponentSize, int maxComponentSize);

            /* create a new PGM file which contains all current components
            (255=component pixel, 0 otherwise) and write this to outFileName as a
            valid PGM. the return value indicates success of operation
            */
            bool writeComponents(const std::string& outFileName);

            void checkAdjacentPixels(unsigned char pixel, int pixelIndex, ConnectedComponent& o_ConnectedComponent);

            // GETTERS
            int getComponentCount(void) const; // return number of components      
            int getLargestSize(void) const; // return number of pixels in largest component
            int getSmallestSize(void) const; // return number of pixels in smallest component

            // Extra GETTERS to check variables
            std::string getInputFileName(); // Getter method for inputFileName
            int getMinComponentSize(); // Getter method for minComponentSize
            int getMaxComponentSize(); // Getter method for maxComponentSize 
            unsigned char getThreshold(); // Getter method for threshold
            bool getPrintStatus(); // Getter method for print status
            bool getWriteStatus(); // Getter method for write status
            int getImgWidth();
            int getImgHeight();
            int getBufferLength();

            // SETTERS
            void setInputFileName(std::string inputPGMFile); // Getter method for inputFileName
            void setThreshold(unsigned char threshold); // Setter method for threshold
            void setMinComponentSize(int minComponentSize); // Setter method for minComponentSize
            void setMaxComponentSize(int maxComponentSize); // Setter method for maxComponentSize 
            void setPrintStatus(bool p); // Setter method for print status
            void setWriteStatus(bool w); // Setter method for write status
            void setImgWidth(int imgWidth);
            void setImgHeight(int imgHeight);
            void setBufferLength();

            /* print the data for a component to std::cout
            see ConnectedComponent class;
            print out to std::cout: component ID, number of pixels
            */
            // void printComponentData(const ConnectedComponent & theComponent) const;

            // Test function for writing to PGM
            void writePGM(int bufferLength);

    };
}

#endif