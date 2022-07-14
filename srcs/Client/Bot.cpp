#include "Bot.hpp"

Bot::Bot(std::string name, Channel * chan)
{
	this->nick = name;
	this->channelSet.insert(chan);
	this->fd = -1;
	this->defaultChanName = chan->get_name();
}

Bot::~Bot()
{}

//raw_msg = ":<sender nickmask> PRIVMSG <channelName or botNick> :<real msg>\r\n"
//raw_msg = ":<sender nickmask> JOIN :<channelName>\r\n"
void	Bot::onMessageReceive(Client * sender, std::string raw_msg)
{
	Channel *					chan;
	std::size_t					pos = raw_msg.find_last_of(":");
	std::vector<std::string>	head;
	std::string					comment;
	
	if (!sender || pos == std::string::npos || pos == 0)
		return ;
	head = string_split(raw_msg.substr(0, pos - 1), " ");
	comment = raw_msg.substr(pos + 1, raw_msg.size() - 2);

	if (head.size() == 3 && head[0][0] == ':' && head[1] == "PRIVMSG")
	{
		if (head[2] == this->nick)
			privmsg_handler(sender, comment);
		else
		{
			chan = _getChannel(head[2]);
			if (!chan)
				return ;
			privmsg_handler(sender, comment, chan);
		}
	}
	else if (head.size() == 2 && head[0][0] == ':' && head[1] == "JOIN")
	{
		chan = _getChannel(comment);
		if (!chan)
			return ;
		join_handler(sender, chan);
	}
}

void	Bot::join_handler(Client * sender, Channel * chan)
{
	std::ostringstream			reply;

	reply << ":" + this->nick + " PRIVMSG " + chan->get_name() + " :";
	reply << "Hey " + sender->nick + "! ";
	reply << "Welcome to the channel! I'm your server bot, " + this->nick + " :)";
	reply << "\r\n";

	chan->broadcastToClients(this, reply.str());
}

void	Bot::privmsg_handler(Client * sender, std::string msg, Channel * chan)
{
	std::ostringstream			reply;

	//Set up bot's reply header
	reply << ":" + this->nick + " PRIVMSG ";
	if (chan)
		reply << chan->get_name() + " :";
	else
		reply << sender->nick + " :";

	//Generate a response according to the received message
	msg = string_to_lower(msg);
	if (msg.compare(0, 5, "hello") || msg.compare(0, 2, "hi") || msg.compare(0, 3, "hey"))
		reply << "Hello " + sender->nick + "! \n";
	
	if (msg.find("mode i"))
		reply << "User mode i marks a user as invisible. ";
	else if (msg.find("mode o"))
		reply << "User mode o marks a user as server operator. ";
	else if (msg.find("file") && msg.find("transfer"))
	{
		reply << "To send and receive files:\n";
		reply << "- /dcc send <receiver_nick> <file1> [<file2>] ... [<fileN>]\n";
		reply << "- /dcc get <sender_nick> [<file>]\n";
		reply << "\nTo check and change default upload and download path\n";
		reply << "- /set dcc_upload_path [<path>]\n";
		reply << "- /set dcc_download_path [<path>]\n";
	}
	else if (msg.find("nickmask"))
	{
		reply << "Nickmask standard format: <nick>!<username>@<host>\n";
		reply << "Your nickmask is " + sender->get_nickmask() + ".";
	}

	if (msg.find("thank"))
		reply << "You are welcome! ";
	else if (msg.find("bye"))
		reply << "Bye bye, " + sender->nick + "! Have a nice day!";

	reply << "\r\n";
	if (chan)
		chan->broadcastToClients(this, reply.str());
	else if (send(sender->fd, reply.str().c_str(), reply.str().size(), 0) == -1)
		{}; // !!!error handler!!!
}

Channel *	Bot::_getChannel(std::string channelName)
{
	std::set<Channel *>::iterator	it = this->channelSet.begin();
	std::set<Channel *>::iterator	ite = this->channelSet.end();

	for (; it != ite; it++)
	{
		if ((*it)->get_name() == channelName)
			return (*it);
	}
	return 0;
}
