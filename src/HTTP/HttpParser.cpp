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

    // INFO: The function below checks the recieved requests, and reads the parameters,
    // For example, the method, url ...

    void HttpParser::recieveRequest(std::istream& stream, HttpRequest& request) {
        readWord(stream, request.method);
        readWord(stream, request.url);

        std::string httpVersion;
        readWord(stream, httpVersion);

        readHeaders(stream, request.headers);


        // INFO: If there is a bodyLen, which possibly is any additional arguments,
        // we will read the body, from request.body.

        // NOTE: I can be wrong; i'll need to dive deeper into the code
        // to know for sure.

        std::string body;
        size_t bodyLen = getBodyLen(request.headers);
        if (bodyLen) {
            readBody(stream, request.body, bodyLen);
        }
    }


    // INFO: Here, we define the recieveResponse, within here, we check
    // the recieved response that we recieved.  We read the header and add it
    // to the response. 

    // FIXME: I can be incorrect with some parts, i am working on it. 
    
    void HttpParser::recieveResponse(std::istream& stream, HttpResponse& response) {
        std::string httpVersion;
        readWord(stream, httpVersion);

        std::string status;
        char c;

        stream.get(c);
        while (stream.good() && c != '\r') {
            status += c;
            stream.get(c);
        }

        throwNotGood(stream);

        if (c == '\r') {
            stream.get(c);

            if (c != '\n') {
                throw std::runtime_error("Parser error: '\\n' symbol is expected.");
            }
        }

        response::setStatus(parserResponseStatusFromString(status));

        std::string name;
        std::string value;

        while (readHeader(steam, name, value)) {
            response.addHeader(name, value);
            name.clear();
            value.clear();
        }

        response.addHeader(name, value);
        auto headers = response.getHeaders();
        size_t length = 0;
        auto it = headers.find("content-length");

        if (it != headers.end()) {
            length = std::stoul(it->second);
        }

        std::string body;
        if (length) {
            readBody(stream, body, length);
        }
        
        // INFO: Here we set the response body to
        // the body that we have read from above.

        response.setBody(body);
    }



}