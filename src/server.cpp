#include "server.h"

Server::Server() : last_response("") {}

void Server::handle_request(const std::string &request) {
  last_response = "Processed: " + request;
}

std::string Server::get_last_response() const { return last_response; }
