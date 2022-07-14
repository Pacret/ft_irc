#ifndef BOT_HPP
# define BOT_HPP

# include "Client.hpp"
# include "../Channel/Channel.hpp"
# include "../Utils/utils.hpp"

class Bot : public Client
{
private:
	Channel *	_getChannel(std::string channelName);

public:
	std::string	defaultChanName;

	Bot(std::string name, Channel * chan);
	~Bot();

	void	onMessageReceive(Client * sender, std::string raw_msg);

	void	join_handler(Client * sender, Channel * chan);
	void	privmsg_handler(Client * sender, std::string msg, Channel * chan = 0);
};

#endif