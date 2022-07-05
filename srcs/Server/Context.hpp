#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <sys/socket.h>
# include <sys/types.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <map>
# include <vector>
# include <set>
# include <string>

# include "../Utils/utils.hpp"
# include "../Client/Client.hpp"
# include "../Channel/Channel.hpp"
# include "../Utils/parser_utils.hpp"
# include "../Utils/defines.hpp"

enum Action
{
	KILL_CONNECTION,
	CLOSE_SERVER,
	NOPE
};

typedef struct servop_s
{
	std::string	host;
	std::string	password;
	std::string	username;
}	servop_t;

class Context
{
private:
	typedef int				clientSocket;
	typedef std::string		channelName;
	typedef std::string		commandType;

	std::map<clientSocket, Client *>									_clients;
	std::map<channelName, Channel *>									_channels;
	std::map<commandType, Action(Context::*)(Client *, struct parse_t *)>	_commands;

	std::string					_password;
	std::set<Client *>			_operatorList;
	std::vector<std::string>	_motd;

	void	_send_motd(Client *client);

	bool	_isOperator(Client * client) const;
	void	_removeOperator(Client * client);
	void	_addOperator(Client * client);

	bool	_not_enough_params(Client & client, struct parse_t * command, unsigned int minSize);
	bool	_no_such_channel(Client & client, std::string & chanName);

	std::string	_format_response(std::string sender, parse_t & command);

	Client *	_get_client_by_nickname(string &nick_name);

public:
	std::string					server_name;
	std::string					port;
	std::vector<std::string>	config;
	servop_t					opConfig;

	Context();
	Context(std::string & server_name, const std::string &port, const std::string &password);
	~Context();

	void	sendToClient(int clientSocket, const std::string & msg);

	Action	parse_command(Client *client, struct parse_t *command);

	Action	pass_command(Client *client, struct parse_t *command);
	Action	nick_command(Client *client, struct parse_t *command);
	Action	user_command(Client *client, struct parse_t *command);
	Action	oper_command(Client *client, struct parse_t *command);
	Action	quit_command(Client *client, struct parse_t *command);


	Action	join_command(Client *client, struct parse_t *command);
	Action	kick_command(Client *client, struct parse_t *command);
	Action	part_command(Client *client, struct parse_t *command);
	Action	priv_msg_command(Client *client, parse_t *p);

	Action	mode_command_dummy(Client *c, struct parse_t*p);

	void		setPort(const std::string &port);
	void		setPassword(const std::string &password);
	std::string	getPassword() const;

	Client *	getClient(int clientFd);
	void		addClient(int fd, struct sockaddr_in address);
	void		deleteClient(Client * client);

};

#endif