#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <iostream>
#include <map>
#include <string>

#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Libre {

class HttpParser {
public:
	HttpParser() {};

	void recieveRequest(std::istream& stream, HttpRequest& request);
	void recieveResponse(std::istream& stream, HttpResponse& response);

	// FIXME: Change the name of parseResponseStatusFromString, it's currently
	// way to long. We want a clear and easy to read-code.

	static HttpResponse::HTTP_STATUS parseResponseStatusFromString(const std::string& status);

private:
	void readWord(std::istream& stream, std::string& word);
	void readHeaders(std::istream& stream, HttpRequest::Headers &headers);
	bool readHeader(std::istream& stream, std::string& name, std::string& value);
	size_t getBodyLen(const HttpRequest::Headers& headers);
	void readBody(std::istream& stream, std::string& body, const size_t bodyLen);	
  }; // Namespace
}

#endif