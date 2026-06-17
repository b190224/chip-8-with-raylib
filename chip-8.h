#pragma once
#ifndef CHIP_8
#define CHIP_8

#include <cstdint>
#include <array>

#define GENERAL_REGISTER_COUNT 8
#define STACK_MEMORY 64
#define MAIN_MEMORY 4096

#define JP_ADDR 0x1000
#define COND1_REG_IMM 0x3000
#define COND2_REG_IMM 0x4000
#define COND3_REG_REG 0x5000
#define CONST1 0x6000
#define CONST2 0x7000
#define BITOP_ASSIGN_MATH 0x8000

#define ASSIGN 0x0
#define BITOP1 0x1
#define BITOP2 0x2
#define BITOP3 0x3

class Chip8 {
    public:
        Chip8() = default;

        void cycle();

    private:
        void fetch();
        void decode();
        void execute();

        void display_clear();
        void jp_addr();
        void subroutine_call();
        void cond1_reg_imm();
        void cond2_reg_imm();
        void cond3_reg_reg();
        void const1();
        void const2();
        void assign();
        void bitop1();
        void bitop2();
        void bitop3();

    private:
        bool running = true;
        uint8_t sound_timer {};
        uint8_t delay_timer {};
        uint8_t stack_pointer {};
        uint16_t index_register {};
        uint16_t program_counter {};
        uint16_t current_instruction {};
        uint16_t jump {};
        uint8_t opcode {};
        int8_t operand_x {};
        int8_t operand_y {};
        uint8_t reg_addrx{};
        uint8_t reg_addry {};
        uint8_t difference {};
        int8_t immediate {};
        std::array<int8_t, GENERAL_REGISTER_COUNT> registers {};
        std::array<uint8_t, STACK_MEMORY> stack {};
        std::array<uint8_t, MAIN_MEMORY> memory {};
};

#endif