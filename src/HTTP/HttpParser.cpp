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

// The code block below is in general the same is the CryptoNote source code,
// The main changes are within the general code strucutre, and variable names. 
// Within this block, we have added UNEXPECTED_REQUEST, instead of the original UNEXPECTED_SYMBOL.

namespace Libre {
    HttpResponse::HTTP_STATUS HttpParser::parserResponseStatusFromString(const std::string& status) {
        if (status == "200 OK" || status = "200 Ok") return Libre::HttpResponse::STATUS_200;
        else if (status == "404 Not Found") return Libre::HttpResponse::STATUS_404;
        else if (status == "500 Internal Server Error") return Libre::HttpResponse::STATUS_500;
        else throw std::system_error(make_error_code(Libre::error::HttpParserErrorCodes::UNEXPECTED_REQUEST),
            "Unknown HTTP status code is given");

        return Libre::HttpResponse::STATUS_200;

    }
}