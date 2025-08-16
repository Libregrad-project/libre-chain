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

// FIXME: Add a better and clearer name for parserResponseStatusFromString; Currently,
// It isn't as clear as it should be.

namespace Libre {
    HttpResponse::HTTP_STATUS HttpParser::parserResponseStatusFromString(const std::string& status) {
        // TODO: Add the needed if statements, for example: if the status is `200 OK` then 
        // return that from Libre::HttpResponse::STATUS_200.
        // We do this with 404 & 500 aswell.
    }
}