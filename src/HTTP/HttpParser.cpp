#include "HttpParser.h"

#include <algorithm>

// INFO: If the stream is not good, and the stream is EOF, then return the 
// END_OF_STREAM Error Code. 

// If any other Error shows up, then we simply throw STREAM_NOT_GOOD.
// With the current implementation, there can be hunderds of different errors,
// We will need to add more statements later on. Not just a unclear STREAM_NOT_GOOD.

// TODO: Add more statements, for cleaner debugging.

void throwNotGood(std::istream& stream) {
    if (!stream.good()) {
        if (stream.eof()) {
            throw std::system_error(make_error_code(Libre::error::HttpParserErrorCodes::END_OF_STREAM));
        } else {
            throw std::system_error(make_error_code(Libre::error::HttpParserErrorCodes::STREAM_NOT_GOOD));
        }
    }
}