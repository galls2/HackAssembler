#include <iostream>
#include "hack_assembler.h"

int main(int argc, char* argv[]) {
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <input_asm_file_path> <out_hack_file_path>" << std::endl;
        return 1;
    }

    const std::string input_asm_file_path = argv[1];
    const std::string out_hack_file_path = argv[2];

    HackAssembler assembler;
    assembler.assemble(input_asm_file_path, out_hack_file_path);
}

