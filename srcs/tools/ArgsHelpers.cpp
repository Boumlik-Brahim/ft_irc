#include "../../headers/Server.hpp"

void checkChnlNames(std::vector<std::string> tmpArgs)
{
	for (size_t i = 0; i < tmpArgs.size(); i++)
	{
		if (tmpArgs.at(i).at(0) != '#')
			errorHandler(403, tmpArgs.at(i));
	}
}

std::vector<std::string> splitBySeparator(std::string args, std::string sep)
{
    std::vector<std::string> newArgs;
    size_t pos = 0;
    while ((pos = args.find(sep)) != std::string::npos)
    {
        newArgs.push_back(args.substr(0, pos));
        args.erase(0, pos + 1);
    }
    newArgs.push_back(args.substr(0, pos));
    return newArgs;
}

void checkMultiArgs(Message &msg)
{
	std::vector<std::string> 			tmpArgs;
	
	if (msg.getArguments().at(0).find(',') != std::string::npos)
	{
		tmpArgs = splitBySeparator(msg.getArguments().at(0), ",");
		msg.setMultiArgs(tmpArgs);
		msg.erase(msg.getArguments().begin());
		if (msg.getArguments().size())
		{
			if (msg.getArguments().at(0).find(',') != std::string::npos)
			{
				tmpArgs = splitBySeparator(msg.getArguments().at(0), ",");
				msg.setArguments(tmpArgs);
			}
		}
	}
}

void parseMessageFormat(Message &msg, char **data)
{
	std::vector<std::string> args;
	std::string tmp;
	
	msg.setCommand(data[0]);
	free(data[0]);
	for (int i = 1; data[i]; i++)
	{
		if (data[i][0] == ':')
		{
			for (; data[i]; i++)
			{
				tmp += data[i];
				free(data[i]);
				if (data[i + 1])
					tmp += ' ';
			}
			args.push_back(tmp);
			break;
		}
		else
		{
			args.push_back(data[i]);
			free(data[i]);
		}
	}
	free(data);
	msg.setArguments(args);
}