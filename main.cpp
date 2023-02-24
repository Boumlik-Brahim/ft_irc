#include "headers/Server.hpp"
#include "headers/Channel.hpp"
#include "headers/Client.hpp"

int main(int argc, char const *argv[])
{
	// (void)argc;
	if (argc != 3)
		return (std::cerr << "ERROR : number of args must be 3", -1);
	for (size_t i = 0; i < strlen(argv[1]); i++) {
        if (!isdigit(argv[1][i])) {
            std::cerr << "ERROR: port number must be a digit";
            return -1;
        }
    }
	if (atoi(argv[1]) < 6660 || atoi(argv[1]) > 6669)
		return (std::cerr << "ERROR : ports range must be between 6660 and 6669", -1);
	if (strlen(argv[2]) < 3)
		return (std::cerr << "ERROR : password must be at least 3 characters", -1);
	for (size_t i = 0; i < strlen(argv[2]); i++) {
        if (!isalnum(argv[2][i])) {
            std::cerr << "ERROR: password must be a digit or alphabetic";
            return -1;
        }
    }
	try
	{
		Server server1("localhost", atoi(argv[1]), argv[2]);
		server1.create_socket();
		server1.bind_socket();
		server1.listen_socket();
		server1.accept_socket();
		server1.close_socket(server1.getSocket_fd());
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return (0);
}