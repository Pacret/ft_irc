/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbonilla <pbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 06:19:02 by tmerrien          #+#    #+#             */
/*   Updated: 2022/06/23 20:19:05 by pbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_PROTOCOL_DEFINES_H
# define FT_IRC_PROTOCOL_DEFINES_H

using namespace std;

# include "../Server/Server.hpp"
# include "../Channel/Channel.hpp"
# include "../Client/Client.hpp"


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
	RR_UNKNOWNCOMMAND = 421,
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
	inline string to_string(int code)
	{
		stringstream sstream;

		sstream << code;
		return (sstream.str());
	};
	
	inline string ERR_NOSUCHNICK(string nick) {return (nick + " :No such nick/channel");}
	inline string ERR_NOSUCHSERVER(string serv) {return (serv + " :No such server");}
	inline string ERR_NOSUCHCHANNEL(string chan) {return (chan + " :No such channel");}
	inline string ERR_CANNOTSENDTOCHAN(string chan) {return (chan + " :Cannot send to channel");}

	inline string ERR_TOOMANYCHANNELS(string chan) {return (chan + " :You have joined too many channels");}
	inline string ERR_WASNOSUCHNICK(string nick) {return (nick + " :There was no such nickname");}
	inline string ERR_TOOMANYTARGETS(string target) {return (target + " :Duplicate recipients. No message delivered");} 
	inline string ERR_NOORIGIN() {return (":No origin specified");}
	inline string ERR_NORECIPIENT(string cmd) {return (":No recipient given (" + cmd + ")");}
	inline string ERR_NOTEXTTOSEND() {return (":No text to send");}
	inline string ERR_NOTOPLEVEL(string mask) {return (mask + " :No toplevel domain specified");}
	inline string ERR_WILDTOPLEVEL(string mask) {return (mask + " :Wildcard in toplevel domain");}

	inline string ERR_UNKNOWNCOMMAND(string cmd) {return (cmd + " :Unknown command");}
	inline string ERR_NOMOTD() {return (":MOTD File is missing");}
	inline string ERR_NOADMININFO(string serv) {return (serv + " :No administrative info available");}
	inline string ERR_FILEERROR(string& file_op, string& file) {return (":File error doing "+ file_op + " on " + file);}
	inline string ERR_NONICKNAMEGIVEN() {return (":No nickname given");}
	inline string ERR_NICKNAMEINUSE(string nick) {return (nick + " :Nickname is already in use");}
	inline string ERR_NICKCOLLISION(string nick) {return (nick + " :Nickname collision KILL");}
	inline string ERR_USERNOTINCHANNEL(string nick, string chan) {return (nick + " " + chan + " :They aren't on that channel");}
	inline string ERR_NOTONCHANNEL(string chan) {return (chan + " :You're not on that channel");}

	inline string ERR_USERONCHANNEL(string nick, string chan) {return (nick + " " + chan + " :is already on channel");}
	inline string ERR_NOLOGIN(string user) {return (user + " :User not logged in");}
	inline string ERR_SUMMONDISABLED() {return (":SUMMON has been disabled");}
	inline string ERR_USERSDISABLED() {return (":USERS has been disabled");}
	inline string ERR_NOTREGISTERED() {return (":You have not registered");}
	inline string ERR_NEEDMOREPARAMS(string cmd) {return (cmd + " :Not enough parameters");}
	inline string ERR_ALREADYREGISTRED() {return (":You may not reregister");}
	inline string ERR_NOPERMFORHOST() {return (":Your host isn't among the privileged");}
	inline string ERR_PASSWDMISMATCH() {return (":Password incorrect");}
	inline string ERR_YOUREBANNEDCREEP() {return (":You are banned from this server");}
	inline string ERR_KEYSET(string chan) {return (chan + " :Channel key already set");}

	inline string ERR_CHANNELISFULL(string chan) {return (chan + " :Cannot join channel (+l)");}
	inline string ERR_UNKNOWNMODE(string charac) {return (charac + " :is unknown mode char to me");}
	inline string ERR_INVITEONLYCHAN(string chan) {return (chan + " :Cannot join channel (+i)");}
	inline string ERR_BANNEDFROMCHAN(string chan) {return (chan + " :Cannot join channel (+b)");}
	inline string ERR_BADCHANNELKEY(string chan) {return (chan + " :Cannot join channel (+k)");}
	inline string ERR_NOPRIVILEGES() {return (":Permission Denied- You're not an IRC operator");}
	inline string ERR_CHANOPRIVSNEEDED(string chan) {return (chan + " :You're not channel operator");}
	inline string ERR_CANTKILLSERVER() {return (":You cant kill a server!");}
	inline string ERR_NOOPERHOST() {return (":No O-lines for your host");}
	inline string ERR_UMODEUNKNOWNFLAG() {return (":Unknown MODE flag");}
	inline string ERR_USERSDONTMATCH() {return (":Cant change mode for other users");}

	//
	//
	//

	inline string RPL_WELCOME(std::string nick, std::string host) {return (" :Welcome to the Internet Relay Network " + nick + "! " + nick + "@" + host);}
	inline string RPL_NONE() {return ("");}
	inline string RPL_USERHOST(string reply) {return (":" + reply);}
	inline string RPL_ISON(string reply) {return (":" + reply);}
	inline string RPL_AWAY(string nick, string msg) {return (nick + " :" + msg);}
	
	inline string RPL_UNAWAY() {return (":You are no longer marked as being away");}
	inline string RPL_NOWAWAY() {return (":You have been marked as being away");}
	inline string RPL_WHOISUSER(Client& cli, string host) {return (cli.get_nick() + " " + cli.get_username() + " " + host + " * :" + cli.get_rn());}
	inline string RPL_WHOISSERVER(string nick, Server& serv) {return (nick + " " + serv.get_name() + " :" + serv.get_info());}
	inline string RPL_WHOISOPERATOR(string nick) {return (nick + " :is an IRC operator");}
	inline string RPL_WHOISIDLE(string nick, string sec) {return (nick + " " + sec + " :seconds idle");}
	inline string RPL_ENDOFWHOIS(string nick) {return (nick + " :End of /WHOIS list");}
	inline string RPL_WHOISCHANNELS(string nick, string chan_info) {return (nick + " :" + chan_info);}
	inline string RPL_WHOWASUSER(Client& cli, string host) {return (cli.get_nick() + " " + cli.get_username() + " " + host + " * " + " :" + cli.get_rn());}
	inline string RPL_ENDOFWHOWAS(string nick) {return (nick + " :End of WHOWAS");}
	inline string RPL_LISTSTART() {return ("Channel :Users  Name");}
	inline string RPL_LIST(Channel& chan) {return (chan.get_name() + " " + ft_irc::to_string(chan.get_nbrUsers()) + " :" + chan.get_topic());}
	inline string RPL_LISTEND() {return (":End of /LIST");}
	inline string RPL_CHANNELMODEIS(Channel& chan) {return (chan.get_name() + " " + chan.get_mode() + " " + chan.get_mode_params() + " :Cannot send to channel");}
	inline string RPL_NOTOPIC(string chan) {return (chan + " :No topic is set");}
	inline string RPL_TOPIC(Channel& chan) {return (chan.get_name() + " :" + chan.get_topic());}
	inline string RPL_INVITING(string chan, string nick) {return (chan + " " + nick);}
	inline string RPL_SUMMONING(string user) {return (user + " :Summoning user to IRC");}
	inline string RPL_VERSION(string version, string debug_lvl, string server, string comment) {return (version + "." + debug_lvl + " " + server + " :" + comment);}
	inline string RPL_WHOREPLY(string chan, string user, string host, string server, string nick, string status, string hopCount, string rn) {return (chan + " " + user + " " + host + " " + server + " " + nick + " " + status + " :" + hopCount + " " + rn);}
	inline string RPL_ENDOFWHO(string name) {return (name + " :End of /WHO list");}
	inline string RPL_NAMREPLY(string channelWithType, string nicknames) {return (channelWithType + " " + nicknames);}
	inline string RPL_ENDOFNAMES(string chan) {return (chan + " :End of /NAMES list");}
	inline string RPL_LINKS(string mask, string server, string hopCount, string serverInfo) {return (mask + " " + server + " " + " :" + hopCount + " " + serverInfo);}
	inline string RPL_ENDOFLINKS(string mask) {return (mask + " :End of /LINKS list");}

	inline string RPL_BANLIST(string chan, string banid) {return (chan + " " + banid);}
	inline string RPL_ENDOFBANLIST(string chan) {return (chan + " :End of channel ban list");}
	inline string RPL_INFO(string info) {return (":" + info);}
	inline string RPL_ENDOFINFO() {return (":End of /INFO list");}
	inline string RPL_MOTDSTART(string server) {return (":- " + server + " Message of the day");}
	inline string RPL_MOTD(string text) {return (":- " + text);}
	inline string RPL_ENDOFMOTD() {return (":End of /MOTD commandl");}
	inline string RPL_YOUREOPER() {return (":You are now an IRC operator");}
	inline string RPL_REHASHING(string configFile) {return (configFile + " :Rehashing");}
	inline string RPL_TIME(string server, string time) {return (server + " :" + time);}
	inline string RPL_USERSSTART() {return (":UserID   Terminal  Host");}
	inline string RPL_USERS(string username, string ttyline, string hostname) {return (":" + username + " " + ttyline + " " + hostname);}
	inline string RPL_ENDOFUSERS() {return (":End of users");}
	inline string RPL_NOUSERS() {return (":Nobody logged in");}
	inline string RPL_TRACELINK(string versionDebugLvl, string destination, string nextServ) {return ("Link " + versionDebugLvl + " " + destination + " " + nextServ);}
	inline string RPL_TRACECONNECTING(string class_, string server) {return ("Try. " + class_ + " " + server);};
	
	inline string RPL_LUSERCLIENT(string nbr_users, string nbr_invs) {return (":There are " + nbr_users + " users and " + nbr_invs + " invisible on 1 servers");}
	inline string RPL_LUSERUNKNOWN(string nbr_unk) {return (nbr_unk + " :unknow connection(s)");}
	inline string RPL_LUSERCHANNELS(string nbr_channel) {return (nbr_channel + " :channels formed");}
	inline string RPL_LUSERME(string nbr_clients) {return (":I have " + nbr_clients + " and 1 servers");}

}
#endif
