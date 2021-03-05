#include "vm.h"
#include "opcode.h"
#include "compiler.h"

#include <tuple>
#include <string>

#ifdef DEBUG_TRACE_EXECUTION
#include "debugger.h"
#endif

namespace cloxplus {
VM::VM()
{
}

VM::~VM()
{
}

InterpretResult VM::interpret(const std::string& source)
{
  Compiler compiler(source);
  if (compiler.compile(&m_chunk)) {
    m_chunk.clear();
    return InterpretResult::INTERPRET_COMPILE_ERROR;
  }

  InterpretResult result = run();
  m_chunk.clear();

  return result;
}

InterpretResult VM::run()
{
  auto ReadByte = [this](){ return m_ip++; };
  auto ReadInstruction = [this, ReadByte](){
    return m_chunk.getInstruction(ReadByte());
  };

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    std::cout << "          " << std::endl;
    for (const auto &value : m_stack) {
      std::cout << "[ ";
      printValue(value);
      std::cout << " ]" << std::endl;
    }
    std::string output{};
    Debugger::disassembleInstruction(*m_chunk, m_ip, output);
    std::cout << output << std::endl;
#endif
    // First operand is last item on stack; second operand is next to last
    const auto getBinaryOperands = [this]() {
      Value v1 = m_stack.back();
      m_stack.pop_back();
      Value v2 = m_stack.back();
      m_stack.pop_back();
      return std::make_pair(v1, v2);
    };

    uint8_t instruction = ReadInstruction();
    switch (instruction) {
      case OpCode::OP_CONSTANT: {
        size_t constantOffset = m_chunk.getInstruction(m_ip++);
        Value constant = m_chunk.getConstant(constantOffset);
        m_stack.push_back(constant);
        break;
      }
      case OpCode::OP_ADD: {
        const auto operands = getBinaryOperands();
        m_stack.push_back(operands.first + operands.second);
        break;
      }
      case OpCode::OP_SUBTRACT: {
        const auto operands = getBinaryOperands();
        m_stack.push_back(operands.second - operands.first);
        break;
      }
      case OpCode::OP_MULTIPLY: {
        const auto operands = getBinaryOperands();
        m_stack.push_back(operands.first * operands.second);
        break;
      }
      case OpCode::OP_DIVIDE: {
        const auto operands = getBinaryOperands();
        m_stack.push_back(operands.second / operands.first);
        break;
      }
      case OpCode::OP_NEGATE: {
        Value value = m_stack.back();
        m_stack.pop_back();
        m_stack.push_back(-value);
        break;
      }
      case OpCode::OP_RETURN: {
        printValue(m_stack.back());
        m_stack.pop_back();
        return INTERPRET_OK;
      }
    }
  }
}
}
