/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 06:19:02 by tmerrien          #+#    #+#             */
/*   Updated: 2022/07/16 19:24:09 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_PROTOCOL_DEFINES_H
# define FT_IRC_PROTOCOL_DEFINES_H

# include <map>
# include <string>
# include <exception>
# include <sstream>

# include "../Channel/Channel.hpp"
# include "../Client/Client.hpp"
# include "../Utils/utils.hpp"

template <typename T>
class EnumParser
{
	std::map<std::string, T> strEnumMap;
public:
	EnumParser(){};

	T getEnum(const std::string &value)
	{
		typename std::map<std::string, T>::const_iterator it = strEnumMap.find(value);
		if (it  == strEnumMap.end())
			throw std::runtime_error("Enum name does not exist in strEnumMap");
		return it->second;
	}
};

/*
** Error numeric codes
*/

enum numeric_replies_e
{
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHSERV = 402,
	ERR_NOSUCHCHANNEL = 403,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_TOOMANYCHANNELS = 405,
	ERR_WASNOSUCHNICK = 406,
	ERR_TOOMANYTARGETS = 407,
	ERR_NOORIGIN = 409,
	ERR_NORECIPIENT = 411,
	ERR_NOTEXTTOSEND = 412,
	ERR_NOTOPLEVEL = 413,
	ERR_WILDTOPLEVEL = 414,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NOMOTD = 422,
	ERR_NOADMININFO = 423,
	ERR_FILEERROR = 424,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_NICKCOLLISION = 436,
	ERR_USERNOTINCHANNEL = 441,
	ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NOLOGIN = 444,
	ERR_SUMMONDISABLED = 445,
	ERR_USERSDISABLED = 446,
	ERR_NOTREGISTERED = 451,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTRED = 462,
	ERR_NOPERMFORHOST = 463,
	ERR_PASSWDMISMATCH = 464,
	ERR_YOUREBANNEDCREEP = 465,
	ERR_KEYSET = 467,
	ERR_CHANNELISFUL = 471,
	ERR_UNKNOWNMODE = 472,
	ERR_INVITEONLYCHAN = 473,
	ERR_BANNEDFROMCHAN = 474,
	ERR_BADCHANNELKEY = 475,
	ERR_NOPRIVILEGES = 481,
	ERR_CHANOPRIVSNEEDED = 482,
	ERR_CANTKILLSERVER = 483,
	ERR_NOOPERHOST = 491,
	ERR_UMODEUNKNOWNFLAG = 501,
	ERR_USERSDONTMATCH = 502,
	
/*
**	Command numeric responses
*/

	RPL_WELCOME = 001,
	RPL_NONE = 300,
	RPL_USERHOST = 302,
	RPL_ISON = 303,
	RPL_AWAY = 301,
	RPL_UNAWAY = 305,
	RPL_NOWAWAY = 306,
	RPL_WHOISUSER = 311,
	RPL_WHOISSERVER = 312,
	RPL_WHOISOPERATOR = 313,
	RPL_WHOISIDLE = 317,
	RPL_ENDOFWHOIS = 318,
	RPL_WHOISCHANNELS = 319,
	RPL_WHOWASUSER = 314,
	RPL_ENDOFWHOWAS = 369,
	RPL_LISTSTART = 321,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
	RPL_CHANNELMODEIS = 324,
	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,
	RPL_INVITING = 341,
	RPL_SUMMONING = 342,
	RPL_VERSION = 351,
	RPL_WHOREPLY = 352,
	RPL_ENDOFWHO = 315,
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
	RPL_LINKS = 364,
	RPL_ENDOFLINKS = 365,
	RPL_BANLIST = 367,
	RPL_ENDOFBANLIST = 368,
	RPL_INFO = 371,
	RPL_ENDOFINFO = 374,
	RPL_MOTDSTART = 375,
	RPL_MOTD = 372,
	RPL_ENDOFMOTD = 376,
	RPL_YOUREOPER = 381,
	RPL_REHASHING = 382,
	RPL_TIME = 391,
	RPL_USERSSTART = 392,
	RPL_USERS = 393,
	RPL_ENDOFUSERS = 394,
	RPL_NOUSERS = 395,
	RPL_TRACELINK = 200,
	RPL_TRACECONNECTING = 201,
	RPL_TRACEHANDSHAKE = 202,
	RPL_TRACEUNKNOWN = 203,
	RPL_TRACEOPERATOR = 204,
	RPL_TRACEUSER = 205,
	RPL_TRACESERVER = 206,
	RPL_TRACENEWTYPE = 208,
	RPL_TRACELOG = 261,
	RPL_STATSLINKINFO = 211,
	RPL_STATSCOMMANDS = 212,
	RPL_STATSCLINE = 213,
	RPL_STATSNLINE = 214,
	RPL_STATSILINE = 215,
	RPL_STATSKLINE = 216,
	RPL_STATSYLINE = 218,
	RPL_ENDOFSTATS = 219,
	RPL_STATSLLINE = 241,
	RPL_STATSUPTIME = 242,
	RPL_STATSOLINE = 243,
	RPL_STATSHLINE = 244,
	RPL_UMODEIS = 221,
	RPL_LUSERCLIENT = 251,
	RPL_LUSEROP = 252,
	RPL_LUSERUNKNOWN = 253,
	RPL_LUSERCHANNELS = 254,
	RPL_LUSERME = 255,
	RPL_ADMINME = 256,
	RPL_ADMINLOC1 = 257,
	RPL_ADMINLOC2 = 258,
	RPL_ADMINEMAIL = 259,
	
/*
**	Reserved numerics
*/
	
	RPL_TRACECLASS = 209,
	RPL_SERVICEINFO = 231,
	RPL_SERVICE = 233,
	RPL_SERVLISTEND = 235,
	RPL_WHOISCHANOP = 316,
	RPL_CLOSING = 362,
	RPL_INFOSTART = 373,
	ERR_YOUWILLBEBANNED = 466,
	ERR_NOSERVICEHOST = 492,
	RPL_STATSQLINE = 217,
	RPL_ENDOFSERVICES = 232,
	RPL_SERVLIST = 234,
	RPL_KILLDONE = 361,
	RPL_CLOSEEND = 363,
	RPL_MYPORTIS = 384,
	ERR_BADCHANMASK = 476,
};

namespace ft_irc
{
	std::string	format_prefix(std::string sender, std::string const & code, std::string receiver);
	
	// 
	// ERRORS
	// 

	inline std::string ERR_NOSUCHNICK(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :No such nick/channel" + "\r\n");}
	inline std::string ERR_NOSUCHSERVER(std::string sender, std::string receiver, std::string serv) {return (format_prefix(sender, __func__, receiver) + serv + " :No such server" + "\r\n");}
	inline std::string ERR_NOSUCHCHANNEL(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :No such channel" + "\r\n");}
	inline std::string ERR_CANNOTSENDTOCHAN(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Cannot send to channel" + "\r\n");}

	inline std::string ERR_TOOMANYCHANNELS(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :You have joined too many channels" + "\r\n");}
	inline std::string ERR_WASNOSUCHNICK(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :There was no such nickname" + "\r\n");}
	inline std::string ERR_TOOMANYTARGETS(std::string sender, std::string receiver, std::string target) {return (format_prefix(sender, __func__, receiver) + target + " :Duplicate recipients. No message delivered" + "\r\n");} 
	inline std::string ERR_NOORIGIN(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":No origin specified" + "\r\n");}
	inline std::string ERR_NORECIPIENT(std::string sender, std::string receiver, std::string cmd) {return (format_prefix(sender, __func__, receiver) + ":No recipient given (" + cmd + ")" + "\r\n");}
	inline std::string ERR_NOTEXTTOSEND(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":No text to send" + "\r\n");}
	inline std::string ERR_NOTOPLEVEL(std::string sender, std::string receiver, std::string mask) {return (format_prefix(sender, __func__, receiver) + mask + " :No toplevel domain specified" + "\r\n");}
	inline std::string ERR_WILDTOPLEVEL(std::string sender, std::string receiver, std::string mask) {return (format_prefix(sender, __func__, receiver) + mask + " :Wildcard in toplevel domain" + "\r\n");}

	inline std::string ERR_UNKNOWNCOMMAND(std::string sender, std::string receiver, std::string cmd) {return (format_prefix(sender, __func__, receiver) + cmd + " :Unknown command" + "\r\n");}
	inline std::string ERR_NOMOTD(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":MOTD File is missing" + "\r\n");}
	inline std::string ERR_NOADMININFO(std::string sender, std::string receiver, std::string serv) {return (format_prefix(sender, __func__, receiver) + serv + " :No administrative info available" + "\r\n");}
	inline std::string ERR_FILEERROR(std::string sender, std::string receiver, std::string& file_op, std::string& file) {return (format_prefix(sender, __func__, receiver) + ":File error doing "+ file_op + " on " + file + "\r\n");}
	inline std::string ERR_NONICKNAMEGIVEN(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":No nickname given" + "\r\n");}
	inline std::string ERR_NICKNAMEINUSE(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :Nickname is already in use" + "\r\n");}
	inline std::string ERR_NICKCOLLISION(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :Nickname collision KILL" + "\r\n");}
	inline std::string ERR_USERNOTINCHANNEL(std::string sender, std::string receiver, std::string nick, std::string chan) {return (format_prefix(sender, __func__, receiver) + nick + " " + chan + " :They aren't on that channel" + "\r\n");}
	inline std::string ERR_NOTONCHANNEL(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :You're not on that channel" + "\r\n");}

	inline std::string ERR_USERONCHANNEL(std::string sender, std::string receiver, std::string nick, std::string chan) {return (format_prefix(sender, __func__, receiver) + nick + " " + chan + " :is already on channel" + "\r\n");}
	inline std::string ERR_NOLOGIN(std::string sender, std::string receiver, std::string user) {return (format_prefix(sender, __func__, receiver) + user + " :User not logged in" + "\r\n");}
	inline std::string ERR_SUMMONDISABLED(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":SUMMON has been disabled" + "\r\n");}
	inline std::string ERR_USERSDISABLED(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":USERS has been disabled" + "\r\n");}
	inline std::string ERR_NOTREGISTERED(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":You have not registered" + "\r\n");}
	inline std::string ERR_NEEDMOREPARAMS(std::string sender, std::string receiver, std::string cmd) {return (format_prefix(sender, __func__, receiver) + cmd + " :Not enough parameters" + "\r\n");}
	inline std::string ERR_ALREADYREGISTRED(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":You may not reregister" + "\r\n");}
	inline std::string ERR_NOPERMFORHOST(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":Your host isn't among the privileged" + "\r\n");}
	inline std::string ERR_PASSWDMISMATCH(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":Password incorrect" + "\r\n");}
	inline std::string ERR_YOUREBANNEDCREEP(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":You are banned from this server" + "\r\n");}
	inline std::string ERR_KEYSET(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Channel key already set" + "\r\n");}

	inline std::string ERR_CHANNELISFULL(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Cannot join channel (+l)" + "\r\n");}
	inline std::string ERR_UNKNOWNMODE(std::string sender, std::string receiver, std::string charac) {return (format_prefix(sender, __func__, receiver) + charac + " :is unknown mode char to me" + "\r\n");}
	inline std::string ERR_INVITEONLYCHAN(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Cannot join channel (+i)" + "\r\n");}
	inline std::string ERR_BANNEDFROMCHAN(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Cannot join channel (+b)" + "\r\n");}
	inline std::string ERR_BADCHANNELKEY(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Cannot join channel (+k)" + "\r\n");}
	inline std::string ERR_NOPRIVILEGES(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":Permission Denied- You're not an IRC operator" + "\r\n");}
	inline std::string ERR_CHANOPRIVSNEEDED(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :You're not channel operator" + "\r\n");}
	inline std::string ERR_CANTKILLSERVER(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":You cant kill a server!" + "\r\n");}
	inline std::string ERR_NOOPERHOST(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":No O-lines for your host" + "\r\n");}
	inline std::string ERR_UMODEUNKNOWNFLAG(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":Unknown MODE flag" + "\r\n");}
	inline std::string ERR_USERSDONTMATCH(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":Cant change mode for other users" + "\r\n");}
	inline std::string ERR_BADCHANMASK(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :Invalid channel name" + "\r\n");};
	inline std::string ERR_ERRONEUSNICKNAME(std::string sender, std::string receiver, std::string nick_b) {return (format_prefix(sender, __func__, receiver) + nick_b + " :Erroneus nickname" + "\r\n");};
	
	//
	// REPLIES
	//

	inline std::string RPL_WELCOME(std::string sender, std::string receiver, std::string nick, std::string user, std::string host) {return (format_prefix(sender, __func__, receiver) + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + "\r\n");}
	inline std::string RPL_NONE(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + "" + "\r\n");}
	inline std::string RPL_USERHOST(std::string sender, std::string receiver, std::string reply) {return (format_prefix(sender, __func__, receiver) + ":" + reply + "\r\n");}
	inline std::string RPL_ISON(std::string sender, std::string receiver, std::string reply) {return (format_prefix(sender, __func__, receiver) + ":" + reply + "\r\n");}
	inline std::string RPL_AWAY(std::string sender, std::string receiver, std::string nick, std::string msg) {return (format_prefix(sender, __func__, receiver) + nick + " :" + msg + "\r\n");}
	
	inline std::string RPL_UNAWAY(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":You are no longer marked as being away" + "\r\n");}
	inline std::string RPL_NOWAWAY(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":You have been marked as being away" + "\r\n");}
	inline std::string RPL_WHOISUSER(std::string sender, std::string receiver, Client& cli, std::string host) {return (format_prefix(sender, __func__, receiver) + cli.nick + " " + cli.get_username() + " " + host + " * :" + cli.get_rn() + "\r\n");}
	inline std::string RPL_WHOISSERVER(std::string sender, std::string receiver, std::string nick, std::string server_name, std::string info) {return (format_prefix(sender, __func__, receiver) + nick + " " + server_name + " :" + info + "\r\n");}
	inline std::string RPL_WHOISOPERATOR(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :is an IRC operator" + "\r\n");}
	inline std::string RPL_WHOISIDLE(std::string sender, std::string receiver, std::string nick, std::string sec) {return (format_prefix(sender, __func__, receiver) + nick + " " + sec + " :seconds idle" + "\r\n");}
	inline std::string RPL_ENDOFWHOIS(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :End of /WHOIS list" + "\r\n");}
	inline std::string RPL_WHOISCHANNELS(std::string sender, std::string receiver, std::string nick, std::string chan_info) {return (format_prefix(sender, __func__, receiver) + nick + " :" + chan_info + "\r\n");}
	inline std::string RPL_WHOWASUSER(std::string sender, std::string receiver, Client& cli, std::string host) {return (format_prefix(sender, __func__, receiver) + cli.nick + " " + cli.get_username() + " " + host + " * " + " :" + cli.get_rn() + "\r\n");}
	inline std::string RPL_ENDOFWHOWAS(std::string sender, std::string receiver, std::string nick) {return (format_prefix(sender, __func__, receiver) + nick + " :End of WHOWAS" + "\r\n");}
	inline std::string RPL_LISTSTART(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + "Channel :Users Name" + "\r\n");}
	inline std::string RPL_LIST(std::string sender, std::string receiver, Channel& chan) {return (format_prefix(sender, __func__, receiver) + chan.get_name() + " " + int_to_string(chan.get_nbrUsers()) + " :" + chan.get_topic() + "\r\n");}
	inline std::string RPL_LISTEND(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + ":End of /LIST" + "\r\n");}
	inline std::string RPL_CHANNELMODEIS(std::string sender, std::string receiver, Channel& chan) {return (format_prefix(sender, __func__, receiver) + chan.get_name() + " " + chan.get_mode() + "\r\n");}
	inline std::string RPL_UMODEIS(std::string sender, std::string receiver, Client & client) {return (format_prefix(sender, __func__, receiver) + client.get_mode() + "\r\n");}
	inline std::string RPL_NOTOPIC(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :No topic is set" + "\r\n");}
	inline std::string RPL_TOPIC(std::string sender, std::string receiver, Channel& chan) {return (format_prefix(sender, __func__, receiver) + chan.get_name() + " :" + chan.get_topic() + "\r\n");}
	inline std::string RPL_INVITING(std::string sender, std::string receiver, std::string chan, std::string nick) {return (format_prefix(sender, __func__, receiver) + chan + " " + nick + "\r\n");}
	inline std::string RPL_SUMMONING(std::string sender, std::string receiver, std::string user) {return (format_prefix(sender, __func__, receiver) + user + " :Summoning user to IRC" + "\r\n");}
	inline std::string RPL_VERSION(std::string sender, std::string receiver, std::string version, std::string debug_lvl, std::string server, std::string comment) {return (format_prefix(sender, __func__, receiver) + version + "." + debug_lvl + " " + server + " :" + comment + "\r\n");}
	inline std::string RPL_WHOREPLY(std::string sender, std::string receiver, std::string chan, std::string user, std::string host, std::string server, std::string nick, std::string status, std::string hopCount, std::string rn) {return (format_prefix(sender, __func__, receiver) + chan + " " + user + " " + host + " " + server + " " + nick + " " + status + " :" + hopCount + " " + rn + "\r\n");}
	inline std::string RPL_ENDOFWHO(std::string sender, std::string receiver, std::string name) {return (format_prefix(sender, __func__, receiver) + name + " :End of /WHO list" + "\r\n");}
	inline std::string RPL_NAMREPLY(std::string sender, std::string receiver, std::string chan, std::string nicknames) {return (format_prefix(sender, __func__, receiver) + "= " + chan + " :" + nicknames + "\r\n");}
	inline std::string RPL_ENDOFNAMES(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :End of /NAMES list" + "\r\n");}
	inline std::string RPL_LINKS(std::string sender, std::string receiver, std::string mask, std::string server, std::string hopCount, std::string serverInfo) {return (format_prefix(sender, __func__, receiver) + mask + " " + server + " " + " :" + hopCount + " " + serverInfo + "\r\n");}
	inline std::string RPL_ENDOFLINKS(std::string sender, std::string receiver, std::string mask) {return (format_prefix(sender, __func__, receiver) + mask + " :End of /LINKS list" + "\r\n");}

	inline std::string RPL_BANLIST(std::string sender, std::string receiver, std::string chan, std::string banid) {return (format_prefix(sender, __func__, receiver) + chan + " " + banid + "\r\n");}
	inline std::string RPL_ENDOFBANLIST(std::string sender, std::string receiver, std::string chan) {return (format_prefix(sender, __func__, receiver) + chan + " :End of channel ban list" + "\r\n");}
	inline std::string RPL_INFO(std::string sender, std::string receiver, std::string info) {return (format_prefix(sender, __func__, receiver) + ":" + info + "\r\n");}
	inline std::string RPL_ENDOFINFO(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + " :End of /INFO list" + "\r\n");}
	inline std::string RPL_MOTDSTART(std::string sender, std::string receiver, std::string server) {return (format_prefix(sender, __func__, receiver) + " :" + server + " Message of the day" + "\r\n");}
	inline std::string RPL_MOTD(std::string sender, std::string receiver, std::string text) {return (format_prefix(sender, __func__, receiver) + " :" + text + "\r\n");}
	inline std::string RPL_ENDOFMOTD(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + " :End of /MOTD command" + "\r\n");}
	inline std::string RPL_YOUREOPER(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + " :You are now an IRC operator" + "\r\n");}
	inline std::string RPL_REHASHING(std::string sender, std::string receiver, std::string configFile) {return (format_prefix(sender, __func__, receiver) + configFile + " :Rehashing" + "\r\n");}
	inline std::string RPL_TIME(std::string sender, std::string receiver, std::string server, std::string time) {return (format_prefix(sender, __func__, receiver) + server + " :" + time + "\r\n");}
	inline std::string RPL_USERSSTART(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + " :UserID   Terminal  Host" + "\r\n");}
	inline std::string RPL_USERS(std::string sender, std::string receiver, std::string username, std::string ttyline, std::string hostname) {return (format_prefix(sender, __func__, receiver) + ":" + username + " " + ttyline + " " + hostname + "\r\n");}
	inline std::string RPL_ENDOFUSERS(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + " :End of users" + "\r\n");}
	inline std::string RPL_NOUSERS(std::string sender, std::string receiver) {return (format_prefix(sender, __func__, receiver) + " :Nobody logged in" + "\r\n");}
	inline std::string RPL_TRACELINK(std::string sender, std::string receiver, std::string versionDebugLvl, std::string destination, std::string nextServ) {return (format_prefix(sender, __func__, receiver) + "Link " + versionDebugLvl + " " + destination + " " + nextServ + "\r\n");}
	inline std::string RPL_TRACECONNECTING(std::string sender, std::string receiver, std::string class_, std::string server) {return (format_prefix(sender, __func__, receiver) + "Try. " + class_ + " " + server + "\r\n");};
	
	inline std::string RPL_LUSERCLIENT(std::string sender, std::string receiver, std::string nbr_users, std::string nbr_invs) {return (format_prefix(sender, __func__, receiver) + " :There are " + nbr_users + " users and " + nbr_invs + " invisible on 1 servers" + "\r\n");}
	inline std::string RPL_LUSERUNKNOWN(std::string sender, std::string receiver, std::string nbr_unk) {return (format_prefix(sender, __func__, receiver) + nbr_unk + " :unknow connection(s)" + "\r\n");}
	inline std::string RPL_LUSERCHANNELS(std::string sender, std::string receiver, std::string nbr_channel) {return (format_prefix(sender, __func__, receiver) + " " + nbr_channel + " :channels formed" + "\r\n");}
	inline std::string RPL_LUSERME(std::string sender, std::string receiver, std::string nbr_clients) {return (format_prefix(sender, __func__, receiver) + " :I have " + nbr_clients + " clients and 1 servers" + "\r\n");}
}
#endif
