#include "vm.h"
#include "chunk.h"
#include "opcode.h"
#include "value.h"
#include "debugger.h"

namespace cloxplus {
VM::VM()
{
}

VM::~VM()
{
}

InterpretResult VM::interpret(std::unique_ptr<Chunk> chunk)
{
  m_chunk = std::move(chunk);
  m_ip = 0;
  return run();
}

InterpretResult VM::run()
{
  auto ReadByte = [this](){ return m_ip++; };
  auto ReadInstruction = [this, ReadByte](){
    return m_chunk->getInstruction(ReadByte());
  };

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    std::string output{};
    Debugger::disassembleInstruction(*m_chunk, m_ip, output);
    std::cout << output << std::endl;
#endif
    uint8_t instruction = ReadInstruction();
    switch(instruction) {
    case OpCode::OP_CONSTANT: {
      size_t constantOffset = m_chunk->getInstruction(m_ip++);
      Value constant = m_chunk->getConstant(constantOffset);
      printValue(constant);
      break;
    }
    case OpCode::OP_RETURN:
      return INTERPRET_OK;
    }
  }
}
}
