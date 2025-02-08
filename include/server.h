#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
  Server();
  void handle_request(const std::string &request);
  std::string get_last_response() const;

private:
  std::string last_response;
};

#endif // SERVER_H
