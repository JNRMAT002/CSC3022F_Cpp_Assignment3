#ifndef PGMimageProcessor_H
#define PGMimageProcessor_H

#include <iostream>

namespace JNRMAT002 {
    class PGMimageProcessor{
        private:
            unsigned char threshold;
            int minValidSize = 3; // Default value for component size - use this in extractComponents
            int minComponentSize; // Set by user. Value set by constructor based on user input. Set = minValidSize if not user-specified.
            int maxComponentSize; // Set by user. Value set by constructor. Set = imgWidth*imgHeight if not user-specified.
            bool p;
            bool w;
            int imgWidth;
            int imgHeight;
            
        public:
            PGMimageProcessor(); // Constructor for when user inputs all possible options
            ~PGMimageProcessor(); // Destructor

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
            bool writeComponents(const std::string & outFileName);

            // GETTERS
            int getComponentCount(void) const; // return number of components      
            int getLargestSize(void) const; // return number of pixels in largest component
            int getSmallestSize(void) const; // return number of pixels in smallest component

            // SETTERS
            void setMinComponentSize(); // Setter method for minComponentSize
            void setMaxComponentSize(); // Setter method for maxComponentSize 
            void setThreshold(); // Setter method for threshold
            void setPrintStatus();
            void setWriteStatus();

            /* print the data for a component to std::cout
            see ConnectedComponent class;
            print out to std::cout: component ID, number of pixels
            */
            // void printComponentData(const ConnectedComponent & theComponent) const;

    };
}

#endif