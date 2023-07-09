#ifndef LABWORK_7_SUNLYOUS__PARSECOMMAND_H_
#define LABWORK_7_SUNLYOUS__PARSECOMMAND_H_

#include "ParseMP3.h"

#include <string>
#include <vector>

class ParseCommand {
private:
    std::vector<std::string> command_information_;
    std::string frame_view;
public:
ParseCommand(int count_element, char** command);
    std::vector<std::string> getPathToFiles();
    std::string getFrameCheck();
};

#endif //LABWORK_7_SUNLYOUS__PARSECOMMAND_H_
