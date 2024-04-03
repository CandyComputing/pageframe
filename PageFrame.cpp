#include <iostream>
#include <vector>
#include <iomanip>



//Data structure for the page frame table
class PageFrameTable {

private:

    // using a vector table and setting up page size
    std::vector<int> table; 
    const int PAGE_SIZE = 256; 

public:
    //constructor implementation
    explicit PageFrameTable(size_t numPages) : table(numPages, -1) {}

    // Setter and getter
    void setPageFrameMapping(int pageNumber, int frameNumber) {
        if (pageNumber >= 0 && pageNumber < table.size()) {
            table[pageNumber] = frameNumber;
        } else {
            std::cerr << "Error: Page number out of bounds." << std::endl;
        }
    }

    // getter
    int getFrameNumber(int pageNumber) const {
        if (pageNumber >= 0 && pageNumber < table.size()) {
            return table[pageNumber];
        } else {
            return -1; // Page fault
        }
    }

    // Translates a logical address to a physical address and outputs page number and offset
    void translateAddressAndPrintDetails(unsigned int logicalAddress) {
        unsigned int pageNumber = logicalAddress / PAGE_SIZE;
        unsigned int offset = logicalAddress % PAGE_SIZE;
        int frameNumber = getFrameNumber(pageNumber);

        // Output the page number and offset
        std::cout << "Logical Address: 0x" << std::hex << std::setw(4) << std::setfill('0') << logicalAddress
                  << " => Page Number: 0x" << std::hex << std::setw(2) << std::setfill('0') << pageNumber
                  << ", Offset: 0x" << std::hex << std::setw(2) << std::setfill('0') << offset;

        if (frameNumber == -1) {
            std::cerr << " - Page fault: Page " <<pageNumber << " is not in memory!" << std::endl;
        } else {
            unsigned int physicalAddress = (frameNumber * PAGE_SIZE) + offset;
            std::cout << " => Physical Address: 0x" << std::hex << std::setw(4) << std::setfill('0') << physicalAddress << std::endl;
        }
    }
};

int main() {
    PageFrameTable table(256); // Size adjusted if necessary, assuming 256 for demonstration

    // Assuming we are mapping these specific pages to arbitrary frames
    table.setPageFrameMapping(0x3A, 13); // Map page 0x3A to frame 0d (13 = od in Hex)
    table.setPageFrameMapping(0xAB, 16+16+11); // Map page 0xAB to frame 0d (16+16+11 = 2b in Hex)
    table.setPageFrameMapping(0x56, 16+5); // Map page 0x56 to frame 0d (16+5 = 15 in Hex)

    // Logical addresses provided
    unsigned int logicalAddresses[] = {0x3A7F, 0xABCD, 0x5678};

    // Translate each address and print the details
    for (unsigned int logicalAddress : logicalAddresses) {
        table.translateAddressAndPrintDetails(logicalAddress);
    }

    return 0;
}