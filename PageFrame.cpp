#include <iostream>
#include <vector>
#include <iomanip>

// This class simulates a page frame table, commonly used in memory management.
class PageFrameTable {
private:
    // We're using a vector as our table. Initially, all values are set to -1.
    std::vector<int> table;
    const int PAGE_SIZE = 256;  // Standard size for pages.

public:
    // Constructor: sets up our table with the specified number of pages.
    explicit PageFrameTable(size_t numPages) : table(numPages, -1) {}

    // Sets a page frame mapping: links a page number with a frame number.
    void setPageFrameMapping(int pageNumber, int frameNumber) {
        // Checking if the page number is valid before setting the mapping.
        if (pageNumber >= 0 && pageNumber < table.size()) {
            table[pageNumber] = frameNumber;
        } else {
            // Oops, that page number is out of range.
            std::cerr << "Error: Page number out of bounds." << std::endl;
        }
    }

    // Gets the frame number associated with a page number.
    int getFrameNumber(int pageNumber) const {
        // Simple lookup: returns the frame number or -1 if it's not found.
        if (pageNumber >= 0 && pageNumber < table.size()) {
            return table[pageNumber];
        } else {
            // No mapping found: we've got a page fault.
            return -1;
        }
    }

    // Converts a logical address to a physical one and shows the details.
    void translateAddressAndPrintDetails(unsigned int logicalAddress) {
        // Breaking down the logical address to find the page number and offset.
        unsigned int pageNumber = logicalAddress / PAGE_SIZE;
        unsigned int offset = logicalAddress % PAGE_SIZE;
        int frameNumber = getFrameNumber(pageNumber);

        // Displaying the conversion details.
        std::cout << "Logical Address: 0x" << std::hex << std::setw(4) << std::setfill('0') << logicalAddress
                  << " => Page Number: 0x" << std::hex << std::setw(2) << std::setfill('0') << pageNumber
                  << ", Offset: 0x" << std::hex << std::setw(2) << std::setfill('0') << offset;

        // Finally, show the physical address or a page fault message.
        if (frameNumber != -1) {
            unsigned int physicalAddress = (frameNumber * PAGE_SIZE) + offset;
            std::cout << " => Physical Address: 0x" << std::hex << std::setw(4) << std::setfill('0') << physicalAddress << std::endl;
        } else {
            std::cerr << " - Page fault: Page not in memory!" << std::endl;
        }
    }
};

int main() {
    // Set up a page frame table for our simulation, here with 256 pages.
    PageFrameTable table(256);

    // Establishing some page-to-frame mappings for demonstration purposes.
    table.setPageFrameMapping(0x3A, 13);
    table.setPageFrameMapping(0xAB, 43);
    table.setPageFrameMapping(0x56, 21);

    // Time to translate some logical addresses and show what happens.
    unsigned int logicalAddresses[] = {0x3A7F, 0xABCD, 0x5678};
    for (unsigned int logicalAddress : logicalAddresses) {
        table.translateAddressAndPrintDetails(logicalAddress);
    }

    // All done here.
    return 0;
}