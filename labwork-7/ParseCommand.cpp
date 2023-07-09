#include "ParseCommand.h"

ParseCommand::ParseCommand(int count_element, char** command) {
    std::string commands;
    for (int i = 1; i < count_element; i++) {
        commands = command[i];
        if (commands == "--input" || commands == "-i") {
            command_information_.emplace_back(command[i + 1]);
        }
        if (commands == "--multi" || commands == "-m") {
            for (int j = i + 1; j < count_element; j++) {
                command_information_.emplace_back(command[j]);
            }
            return;
        }
        if (commands == "--compare" || commands == "-c") {

            for (int j = i + 1; j < count_element; j++) {
                command_information_.emplace_back(command[j]);
            }
            return;
        }
        if (commands == "--frame" || commands == "-f") {
            frame_view = command[i + 1];
            i++;
        }
    }
}
std::string ParseCommand::getFrameCheck() {
    return frame_view;
}

std::vector<std::string> ParseCommand::getPathToFiles() {
    return command_information_;
}

