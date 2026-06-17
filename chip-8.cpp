#include <iostream>
#include "chip-8.h"

void Chip8::cycle() {
    while (running) {  
        fetch();
        decode();
        execute();
    }
}

void Chip8::fetch() {
    current_instruction = memory[program_counter] << 8 | memory[program_counter + 1];
    program_counter += 2;
}

void Chip8::decode() {
    opcode = (current_instruction & 0xF000) >> 12;
    difference = current_instruction & 0x7;

    switch (opcode) {
        case JP_ADDR: {
            jump = opcode & 0xFFF;
            break;
        }

        case COND1_REG_IMM: {
            operand_x = registers[opcode & 0xF00];
            immediate = opcode & 0xFF;
            break;
        }

        case COND2_REG_IMM: {
            operand_x = registers[opcode & 0xF00];
            immediate = opcode & 0xFF;
            break;
        }

        case COND3_REG_REG: {
            operand_x = registers[opcode & 0xF00];
            operand_y = registers[opcode & 0xFF];
            break;
        }

        case CONST1: {
            reg_addrx = opcode & 0xF00;
            immediate = opcode & 0xFF;
            break;
        }

        case CONST2: {
            reg_addrx = opcode & 0xF00;
            immediate = opcode & 0xFF;
            break;
        }

        case BITOP_ASSIGN_MATH: {
            switch (difference) {
                case ASSIGN: {
                    reg_addrx = opcode & 0xF00;
                    operand_y = registers[opcode & 0xFF];
                    break;
                }
                
                case BITOP1: {
                    reg_addrx = opcode & 0xF00;
                    operand_x = registers[opcode & 0xF00];
                    operand_y = registers[opcode & 0xFF];
                    break;
                }

                case BITOP2: {
                    reg_addrx = opcode & 0xF00;
                    operand_x = registers[opcode & 0xF00];
                    operand_y = registers[opcode & 0xFF];
                    break;
                }

                case BITOP3: {
                    reg_addrx = opcode & 0xF00;
                    operand_x = registers[opcode & 0xF00];
                    operand_y = registers[opcode & 0xFF];
                    break;
                }

                default: {

                }
            }

            break;
        }

        default: {
            break;
        }
    }
}

void Chip8::execute() {
    switch (opcode) {
        case JP_ADDR: {
            jp_addr();
            break;
        }

        case COND1_REG_IMM: {
            cond1_reg_imm();
            break;
        }

        case COND2_REG_IMM: {
            cond2_reg_imm();
            break;
        }

        case COND3_REG_REG: {
            cond3_reg_reg();
            break;
        }

        case CONST1: {
            const1();
            break;
        }

        case CONST2: {
            const2();
            break;
        }

       case BITOP_ASSIGN_MATH: {
            switch (difference) {
                case ASSIGN: {
                    assign();
                    break;
                }

                case BITOP1: {
                    bitop1();
                    break;
                }

                case BITOP2: {
                    bitop2();
                    break;
                }

                case BITOP3: {
                    bitop3();
                    break;
                }

                default: {

                }
            }

            break;
        }

        default: {
            break;
        }
    }
}

void Chip8::display_clear() {

}

void Chip8::jp_addr() {
    program_counter = jump;
}

void Chip8::subroutine_call() {

}

void Chip8::cond1_reg_imm() {
    if (immediate == operand_x) {
        program_counter += 2;
    }
}

void Chip8::cond2_reg_imm() {
    if (immediate != operand_x) {
        program_counter += 2;
    }
}

void Chip8::cond3_reg_reg() {
    if (operand_x == operand_y) {
        program_counter += 2;
    }
}

void Chip8::const1() {
    registers[reg_addrx] = immediate;
}

void Chip8::const2() {
    registers[reg_addrx] += immediate;
}

void Chip8::assign() {
    registers[reg_addrx] = operand_y;
}

void Chip8::bitop1() {
    registers[reg_addrx] = operand_x | operand_y;
}

void Chip8::bitop2() {
    registers[reg_addrx] = operand_x & operand_y;
}

void Chip8::bitop3() {
    registers[reg_addrx] = (!operand_x & operand_y) | (!operand_y & operand_x);
}