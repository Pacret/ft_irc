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
# include <ctime>
# include <stdexcept>

# include "../Utils/utils.hpp"
# include "../Client/Client.hpp"
# include "../Client/Bot.hpp"
# include "../Channel/Channel.hpp"
# include "../Utils/parser_utils.hpp"
# include "../Utils/defines.hpp"

# define PING_WAIT 1
# define PING_DELTA 15

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
	Bot *						_bot;

	void	_send_motd(Client *client);

	bool	_isOperator(Client * client) const;
	void	_removeOperator(Client * client);
	void	_addOperator(Client * client);

	bool	_not_enough_params(Client * client, struct parse_t * command, unsigned int minSize);
	bool	_no_such_channel(Client * client, std::string & chanName);

	std::string	_format_response(std::string sender, parse_t & command);

	Client *	_get_client_by_nickname(std::string &nick_name);
	std::string	_get_client_channellist(Client * client) const;


public:
	std::string					server_name;
	std::string					version_name;
	std::string					port;
	std::vector<std::string>	config;
	servop_t					opConfig;
	std::map<std::string, std::string>	conf_file;
	std::string conf_file_inline;
	std::vector<std::string>	motd;

	Context();
	Context(std::string & server_name, const std::string &port, const std::string &password);
	~Context();

	void	sendToClient(Client *client, const std::string & msg, Client * sender = 0);

	Action	parse_command(Client *client, struct parse_t *command);

	// RFC  4.1 Connection Registration
	Action	pass_command(Client *client, struct parse_t *command);
	Action	nick_command(Client *client, struct parse_t *command);
	Action	user_command(Client *client, struct parse_t *command);
	Action	oper_command(Client *client, struct parse_t *command);
	Action	quit_command(Client *client, struct parse_t *command);

	// RFC 4.2 Channel operations
	Action	join_command(Client *client, struct parse_t *command);
	Action	part_command(Client *client, struct parse_t *command);
	Action	mode_command(Client *client, struct parse_t *command);
	Action	user_mode_command(Client *client, struct parse_t *command);
	Action	chan_mode_command(Client *client, struct parse_t *command, Channel * chan);
	Action	topic_command(Client *client, struct parse_t *command);
	Action	names_command(Client *client, struct parse_t *command);
	Action	list_command(Client *client, struct parse_t *command);
	Action	invite_command(Client *client, struct parse_t *command);
	Action	kick_command(Client *client, struct parse_t *command);

	// RFC 4.3 Server queries and commands
	Action	version_command(Client *client, struct parse_t *command);
	Action	time_command(Client *client, parse_t *p);

	// RFC 4.4 Sending messages
	Action	priv_msg_command(Client *client, struct parse_t *p);
	Action	notice_command(Client *client, struct parse_t *p);

	// RFC 4.5 User-based queries
	Action	whois_command(Client *client, struct parse_t *command);

	// RFC 4.6 Miscellaneous messages
	Action	pong_command(Client *client, struct parse_t *p);
	Action	ping_command(Client *client, struct parse_t *p);

	std::string		nbr_invisible(Client *client);
	std::string		nbr_visible(Client *client);

	void		setPort(const std::string &port);
	void		setPassword(const std::string &password);
	std::string	getPassword() const;

	Client *	getClient(int clientFd);
	void		addClient(int fd, struct sockaddr_in address);
	void		deleteClient(Client * client);
	void		removeClientFromChannel(Client *client, Channel *channel);

	void		initServBot();
	void		clean();
};

#endif