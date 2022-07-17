/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:34:45 by tyuan             #+#    #+#             */
/*   Updated: 2022/07/17 15:34:47 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	comment = raw_msg.substr(pos + 1, raw_msg.size() - pos - 3);

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
	std::size_t					tmp_size;

	//Set up bot's reply header
	reply << ":" + this->nick + " PRIVMSG ";
	if (chan)
		reply << chan->get_name() + " :";
	else
		reply << sender->nick + " :";
	tmp_size = reply.str().size();

	//Generate a response according to the received message
	msg = string_to_lower(msg);
	if (msg.compare(0, 5, "hello") == 0 || msg.compare(0, 2, "hi") == 0 || msg.compare(0, 3, "hey") == 0)
		reply << "Hello " + sender->nick + "! ";
	
	if (msg.find("mode i") != std::string::npos)
		reply << "User mode i marks a user as invisible. ";
	else if (msg.find("mode o") != std::string::npos)
		reply << "User mode o marks a user as server operator. ";
	else if (msg.find("file") != std::string::npos
				&& msg.find("transfer") != std::string::npos)
	{
		reply << "1. To send and receive files: ";
		reply << "- /dcc send <receiver_nick> <file1> [<file2>] ... [<fileN>] ";
		reply << "- /dcc get <sender_nick> [<file>] ";
		reply << " 2. To check and change default upload and download path ";
		reply << "- /set dcc_upload_path [<path>] ";
		reply << "- /set dcc_download_path [<path>] ";
	}
	else if (msg.find("nickmask") != std::string::npos)
	{
		reply << "Nickmask standard format: <nick>!<username>@<host> ";
		reply << "Your nickmask is " + sender->get_nickmask() + ".";
	}

	if (msg.find("thank") != std::string::npos)
		reply << "You are welcome! ";
	else if (msg.find("bye") != std::string::npos)
		reply << "Bye bye, " + sender->nick + "! Have a nice day!";

	//No reply if no Q&A match
	if (reply.str().size() == tmp_size)
		return ;

	reply << "\r\n";
	if (chan)
		chan->broadcastToClients(this, reply.str());
	else if (send(sender->fd, reply.str().c_str(), reply.str().size(), 0) == -1)
		throw std::runtime_error("Error: send");
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
