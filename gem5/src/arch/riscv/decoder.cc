/*
 * Copyright (c) 2012 Google
 * Copyright (c) The University of Virginia
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "arch/riscv/decoder.hh"
#include "arch/riscv/types.hh"
#include "base/bitfield.hh"
#include "debug/Decode.hh"

namespace gem5
{

namespace RiscvISA
{

void Decoder::reset()
{
    aligned = true;
    mid = false;
    emi = 0;
}

void
Decoder::moreBytes(const PCStateBase &pc, Addr fetchPC)
{
    // The MSB of the upper and lower halves of a machine instruction.
    constexpr size_t max_bit = sizeof(machInst) * 8 - 1;
    constexpr size_t mid_bit = sizeof(machInst) * 4 - 1;

    auto inst = letoh(machInst);
    DPRINTF(Decode, "Requesting bytes 0x%08x from address %#x\n", inst,
            fetchPC);

    bool aligned = pc.instAddr() % sizeof(machInst) == 0;
    if (aligned) {
        emi = inst;
        if (compressed(emi))
            emi = bits(emi, mid_bit, 0);
        outOfBytes = !compressed(emi);
        instDone = true;
    } else {
        if (mid) {
            assert(bits(emi, max_bit, mid_bit + 1) == 0);
            replaceBits(emi, max_bit, mid_bit + 1, inst);
            mid = false;
            outOfBytes = false;
            instDone = true;
        } else {
            emi = bits(inst, max_bit, mid_bit + 1);
            mid = !compressed(emi);
            outOfBytes = true;
            instDone = compressed(emi);
        }
    }
}

StaticInstPtr
Decoder::decode(ExtMachInst mach_inst, Addr addr)
{
    DPRINTF(Decode, "Decoding instruction 0x%08x at address %#x\n",
            mach_inst, addr);

    StaticInstPtr &si = instMap[mach_inst];
    if (!si)
        si = decodeInst(mach_inst);

    DPRINTF(Decode, "Decode: Decoded %s instruction: %#x\n",
            si->getName(), mach_inst);
    
    //owen++++
    /*
    uint64_t rs1, rs2, opcode;
    opcode = mach_inst & 0x7F;
    std::string beq = "beq";
    std::string bne = "bne";
    std::string bge = "bge";
    std::string bgeu = "bgeu";
    std::string blt = "blt";
    std::string bltu = "bltu";
    if (opcode == 0x63) {
        rs1 = (mach_inst >> 15) & 0x1F;
        rs2 = (mach_inst >> 20) & 0x1F;
        if (si->getName() == beq) {
            printf("This is a beq x%ld, x%ld\n", rs1, rs2);
        }
        else if (si->getName() == bne) {
            printf("This is a bne x%ld, x%ld\n", rs1, rs2);
        }
        else if (si->getName() == bge) {
            printf("This is a bge x%ld, x%ld\n", rs1, rs2);
        }
        else if (si->getName() == bgeu) {
            printf("This is a bgeu x%ld, x%ld\n", rs1, rs2);
        }
        else if (si->getName() == blt) {
            printf("This is a blt x%ld, x%ld\n", rs1, rs2);
        }
        else if (si->getName() == bltu) {
            printf("This is a bltu x%ld, x%ld\n", rs1, rs2);
        }
    }
    */
    //owen++++
    
    return si;
}

StaticInstPtr
Decoder::decode(PCStateBase &_next_pc)
{
    if (!instDone)
        return nullptr;
    instDone = false;

    auto &next_pc = _next_pc.as<PCState>();

    if (compressed(emi)) {
        next_pc.npc(next_pc.instAddr() + sizeof(machInst) / 2);
        next_pc.compressed(true);
    } else {
        next_pc.npc(next_pc.instAddr() + sizeof(machInst));
        next_pc.compressed(false);
    }

    return decode(emi, next_pc.instAddr());
}

} // namespace RiscvISA
} // namespace gem5
