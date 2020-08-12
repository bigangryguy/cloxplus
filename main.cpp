#include "common.h"
#include "chunk.h"

int main(int argc, const char* argv[]) {
    cloxplus::Chunk chunk{};
    chunk.Write(cloxplus::OpCode::OP_RETURN);
    return 0;
}
