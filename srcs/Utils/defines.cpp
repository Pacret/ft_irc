# include "defines.hpp"

template<>
EnumParser<numeric_replies_e>::EnumParser()
{
	strEnumMap["ERR_NOSUCHNICK"] = ERR_NOSUCHNICK;
	strEnumMap["ERR_NOSUCHSERV"] = ERR_NOSUCHSERV;
	strEnumMap["ERR_NOSUCHCHANNEL"] = ERR_NOSUCHCHANNEL;
	strEnumMap["ERR_CANNOTSENDTOCHAN"] = ERR_CANNOTSENDTOCHAN;
	strEnumMap["ERR_TOOMANYCHANNELS"] = ERR_TOOMANYCHANNELS;
	strEnumMap["ERR_WASNOSUCHNICK"] = ERR_WASNOSUCHNICK;
	strEnumMap["ERR_TOOMANYTARGETS"] = ERR_TOOMANYTARGETS;
	strEnumMap["ERR_NOORIGIN"] = ERR_NOORIGIN;
	strEnumMap["ERR_NORECIPIENT"] = ERR_NORECIPIENT;
	strEnumMap["ERR_NOTEXTTOSEND"] = ERR_NOTEXTTOSEND;
	strEnumMap["ERR_NOTOPLEVEL"] = ERR_NOTOPLEVEL;
	strEnumMap["ERR_WILDTOPLEVEL"] = ERR_WILDTOPLEVEL;
	strEnumMap["ERR_UNKNOWNCOMMAND"] = ERR_UNKNOWNCOMMAND;
	strEnumMap["ERR_NOMOTD"] = ERR_NOMOTD;
	strEnumMap["ERR_NOADMININFO"] = ERR_NOADMININFO;
	strEnumMap["ERR_FILEERROR"] = ERR_FILEERROR;
	strEnumMap["ERR_NONICKNAMEGIVEN"] = ERR_NONICKNAMEGIVEN;
	strEnumMap["ERR_ERRONEUSNICKNAME"] = ERR_ERRONEUSNICKNAME;
	strEnumMap["ERR_NICKNAMEINUSE"] = ERR_NICKNAMEINUSE;
	strEnumMap["ERR_NICKCOLLISION"] = ERR_NICKCOLLISION;
	strEnumMap["ERR_USERNOTINCHANNEL"] = ERR_USERNOTINCHANNEL;
	strEnumMap["ERR_NOTONCHANNEL"] = ERR_NOTONCHANNEL;
	strEnumMap["ERR_USERONCHANNEL"] = ERR_USERONCHANNEL;
	strEnumMap["ERR_NOLOGIN"] = ERR_NOLOGIN;
	strEnumMap["ERR_SUMMONDISABLED"] = ERR_SUMMONDISABLED;
	strEnumMap["ERR_USERSDISABLED"] = ERR_USERSDISABLED;
	strEnumMap["ERR_NOTREGISTERED"] = ERR_NOTREGISTERED;
	strEnumMap["ERR_NEEDMOREPARAMS"] = ERR_NEEDMOREPARAMS;
	strEnumMap["ERR_ALREADYREGISTRED"] = ERR_ALREADYREGISTRED;
	strEnumMap["ERR_NOPERMFORHOST"] = ERR_NOPERMFORHOST;
	strEnumMap["ERR_PASSWDMISMATCH"] = ERR_PASSWDMISMATCH;
	strEnumMap["ERR_YOUREBANNEDCREEP"] = ERR_YOUREBANNEDCREEP;
	strEnumMap["ERR_KEYSET"] = ERR_KEYSET;
	strEnumMap["ERR_CHANNELISFUL"] = ERR_CHANNELISFUL;
	strEnumMap["ERR_UNKNOWNMODE"] = ERR_UNKNOWNMODE;
	strEnumMap["ERR_INVITEONLYCHAN"] = ERR_INVITEONLYCHAN;
	strEnumMap["ERR_BANNEDFROMCHAN"] = ERR_BANNEDFROMCHAN;
	strEnumMap["ERR_BADCHANNELKEY"] = ERR_BADCHANNELKEY;
	strEnumMap["ERR_NOPRIVILEGES"] = ERR_NOPRIVILEGES;
	strEnumMap["ERR_CHANOPRIVSNEEDED"] = ERR_CHANOPRIVSNEEDED;
	strEnumMap["ERR_CANTKILLSERVER"] = ERR_CANTKILLSERVER;
	strEnumMap["ERR_NOOPERHOST"] = ERR_NOOPERHOST;
	strEnumMap["ERR_UMODEUNKNOWNFLAG"] = ERR_UMODEUNKNOWNFLAG;
	strEnumMap["ERR_USERSDONTMATCH"] = ERR_USERSDONTMATCH;

	strEnumMap["RPL_WELCOME"] = RPL_WELCOME;
	strEnumMap["RPL_NONE"] = RPL_NONE;
	strEnumMap["RPL_USERHOST"] = RPL_USERHOST;
	strEnumMap["RPL_ISON"] = RPL_ISON;
	strEnumMap["RPL_AWAY"] = RPL_AWAY;
	strEnumMap["RPL_UNAWAY"] = RPL_UNAWAY;
	strEnumMap["RPL_NOWAWAY"] = RPL_NOWAWAY;
	strEnumMap["RPL_WHOISUSER"] = RPL_WHOISUSER;
	strEnumMap["RPL_WHOISSERVER"] = RPL_WHOISSERVER;
	strEnumMap["RPL_WHOISOPERATOR"] = RPL_WHOISOPERATOR;
	strEnumMap["RPL_WHOISIDLE"] = RPL_WHOISIDLE;
	strEnumMap["RPL_ENDOFWHOIS"] = RPL_ENDOFWHOIS;
	strEnumMap["RPL_WHOISCHANNELS"] = RPL_WHOISCHANNELS;
	strEnumMap["RPL_WHOWASUSER"] = RPL_WHOWASUSER;
	strEnumMap["RPL_ENDOFWHOWAS"] = RPL_ENDOFWHOWAS;
	strEnumMap["RPL_LISTSTART"] = RPL_LISTSTART;
	strEnumMap["RPL_LIST"] = RPL_LIST;
	strEnumMap["RPL_LISTEND"] = RPL_LISTEND;
	strEnumMap["RPL_CHANNELMODEIS"] = RPL_CHANNELMODEIS;
	strEnumMap["RPL_NOTOPIC"] = RPL_NOTOPIC;
	strEnumMap["RPL_TOPIC"] = RPL_TOPIC;
	strEnumMap["RPL_INVITING"] = RPL_INVITING;
	strEnumMap["RPL_SUMMONING"] = RPL_SUMMONING;
	strEnumMap["RPL_VERSION"] = RPL_VERSION;
	strEnumMap["RPL_WHOREPLY"] = RPL_WHOREPLY;
	strEnumMap["RPL_ENDOFWHO"] = RPL_ENDOFWHO;
	strEnumMap["RPL_NAMREPLY"] = RPL_NAMREPLY;
	strEnumMap["RPL_ENDOFNAMES"] = RPL_ENDOFNAMES;
	strEnumMap["RPL_LINKS"] = RPL_LINKS;
	strEnumMap["RPL_ENDOFLINKS"] = RPL_ENDOFLINKS;
	strEnumMap["RPL_BANLIST"] = RPL_BANLIST;
	strEnumMap["RPL_ENDOFBANLIST"] = RPL_ENDOFBANLIST;
	strEnumMap["RPL_INFO"] = RPL_INFO;
	strEnumMap["RPL_ENDOFINFO"] = RPL_ENDOFINFO;
	strEnumMap["RPL_MOTDSTART"] = RPL_MOTDSTART;
	strEnumMap["RPL_MOTD"] = RPL_MOTD;
	strEnumMap["RPL_ENDOFMOTD"] = RPL_ENDOFMOTD;
	strEnumMap["RPL_YOUREOPER"] = RPL_YOUREOPER;
	strEnumMap["RPL_REHASHING"] = RPL_REHASHING;
	strEnumMap["RPL_TIME"] = RPL_TIME;
	strEnumMap["RPL_USERSSTART"] = RPL_USERSSTART;
	strEnumMap["RPL_USERS"] = RPL_USERS;
	strEnumMap["RPL_ENDOFUSERS"] = RPL_ENDOFUSERS;
	strEnumMap["RPL_NOUSERS"] = RPL_NOUSERS;
	strEnumMap["RPL_TRACELINK"] = RPL_TRACELINK;
	strEnumMap["RPL_TRACECONNECTING"] = RPL_TRACECONNECTING;
	strEnumMap["RPL_TRACEHANDSHAKE"] = RPL_TRACEHANDSHAKE;
	strEnumMap["RPL_TRACEUNKNOWN"] = RPL_TRACEUNKNOWN;
	strEnumMap["RPL_TRACEOPERATOR"] = RPL_TRACEOPERATOR;
	strEnumMap["RPL_TRACEUSER"] = RPL_TRACEUSER;
	strEnumMap["RPL_TRACESERVER"] = RPL_TRACESERVER;
	strEnumMap["RPL_TRACENEWTYPE"] = RPL_TRACENEWTYPE;
	strEnumMap["RPL_TRACELOG"] = RPL_TRACELOG;
	strEnumMap["RPL_STATSLINKINFO"] = RPL_STATSLINKINFO;
	strEnumMap["RPL_STATSCOMMANDS"] = RPL_STATSCOMMANDS;
	strEnumMap["RPL_STATSCLINE"] = RPL_STATSCLINE;
	strEnumMap["RPL_STATSNLINE"] = RPL_STATSNLINE;
	strEnumMap["RPL_STATSILINE"] = RPL_STATSILINE;
	strEnumMap["RPL_STATSKLINE"] = RPL_STATSKLINE;
	strEnumMap["RPL_STATSYLINE"] = RPL_STATSYLINE;
	strEnumMap["RPL_ENDOFSTATS"] = RPL_ENDOFSTATS;
	strEnumMap["RPL_STATSLLINE"] = RPL_STATSLLINE;
	strEnumMap["RPL_STATSUPTIME"] = RPL_STATSUPTIME;
	strEnumMap["RPL_STATSOLINE"] = RPL_STATSOLINE;
	strEnumMap["RPL_STATSHLINE"] = RPL_STATSHLINE;
	strEnumMap["RPL_UMODEIS"] = RPL_UMODEIS;
	strEnumMap["RPL_LUSERCLIENT"] = RPL_LUSERCLIENT;
	strEnumMap["RPL_LUSEROP"] = RPL_LUSEROP;
	strEnumMap["RPL_LUSERUNKNOWN"] = RPL_LUSERUNKNOWN;
	strEnumMap["RPL_LUSERCHANNELS"] = RPL_LUSERCHANNELS;
	strEnumMap["RPL_LUSERME"] = RPL_LUSERME;
	strEnumMap["RPL_ADMINME"] = RPL_ADMINME;
	strEnumMap["RPL_ADMINLOC1"] = RPL_ADMINLOC1;
	strEnumMap["RPL_ADMINLOC2"] = RPL_ADMINLOC2;
	strEnumMap["RPL_ADMINEMAIL"] = RPL_ADMINEMAIL;
}

namespace ft_irc
{
	std::string format_prefix(std::string sender, std::string const & code, std::string receiver)
	{
		std::ostringstream					os;
		EnumParser<numeric_replies_e>	enumParser;

		os << ":" + sender + " ";
		os << enumParser.getEnum(code);
		os << " " + receiver + " ";
		return (os.str());
	}
}