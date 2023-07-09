#include "ParseMP3.h"

void ParseMP3::Parse(const std::vector<std::string>& files) {
    const_element MP3;
    char byte;
    for (const auto& k : files) {
        std::ifstream file;
        file.open(k, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
            std::cout << "File not found" << std::endl;
            return;
        }
        for (int i = 0; i < MP3.kVersion_; i++) {
            file >> byte;
            version_ += byte;
        }
        if (version_ == MP3.kCheckVersion_) {
            version_.clear();
            std::cout << "File is mp3" << std::endl;
            for (int i = 0; i < MP3.kFlagVersionAndFlagSizeHeader_; i++) {
                file >> byte;
                if (i == MP3.kFlagByteHeader_) {
                    std::bitset<8> flag(byte);
                    if (flag[MP3.kFlagBitHeader_] == 1) {
                        flag_extended_ = true;
                    }
                }
            }
            size_header_ = CheckSizeInformationHeader(file);
            if (!flag_extended_) {
                CheckFrame(file);
            } else {
                size_extended_ = CheckSizeInformationHeader(file);
                file.seekg(size_extended_, std::ios::cur);
                CheckFrame(file);
            }
        } else {
            std::cout << "File is not mp3" << std::endl;
            return;
        }
    }
}

void ParseMP3::CheckFrame(std::ifstream& file) {
    const_element MP3;
    char byte;

    std::string name_frame;
    Information* info = new Information();
    int size_file = size_header_ - (MP3.kSizeHeader_);
    for (int i = 0; i < size_file; i++) {
        file.get(byte);
        if (frame_name_.size() == MP3.kSizeFrameName_) {
            frame_name_.erase(frame_name_.begin());
            frame_name_.push_back(byte);
        } else {
            frame_name_.push_back(byte);
        }
        if (frame_name_.size() == MP3.kSizeFrameName_) {
            for (int j = 0; j < MP3.kSizeFrameName_; j++) {
                name_frame += frame_name_[j];
            }
            AddFrame(file, name_frame, info);
            name_frame.clear();
        }
    }
    if (!frame_check_.empty()) {
        info->CheckFrame(frame_check_);
    } else {
        info->PrintAll();
    }
    music_.push_back(info);
}

int ParseMP3::CheckSizeInformationHeader(std::ifstream& file) {
    char buffer[4];
    file.read(buffer, 4);
    int size = 0;
    for (char i : buffer) {
        size <<= 7;
        size |= i & 0x7F;
    }
    return size;
}

ParseMP3::ParseMP3(const std::vector<std::string>& files, const std::string& frame_check) {
    frame_check_ = frame_check;
    Parse(files);
}

void ParseMP3::AddFrame(std::ifstream& file, const std::string& frame_name, Information* info) {
    ParentFrame* frame;
    if (map_frame.find(frame_name) != map_frame.end()) {
        switch (map_frame.at(frame_name)) {
            case TextFrame_: {
                frame = new TextFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case XXXFrame_: {
                frame = new XXXFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case URLFrame_: {
                frame = new URLFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case ETCOFrame_: {
                frame = new ETCOFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case USLTFrame_: {
                frame = new USLTFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case SYLTFrame_: {
                frame = new SYLTFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case COMMFrame_: {
                frame = new COMMFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case RVA2Frame_: {
                frame = new RVA2Frame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case EQU2Frame_: {
                frame = new EQU2Frame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case PCNTFrame_: {
                frame = new PCNTFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case POPMFrame_: {
                frame = new POPMFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case RBUFFrame_: {
                frame = new RBUFFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case LINKFrame_: {
                frame = new LINKFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case POSSFrame_: {
                frame = new POSSFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case USERFrame_: {
                frame = new USERFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case OWNEFrame_: {
                frame = new OWNEFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case COMRFrame_ : {
                        frame = new COMRFrame(frame_name);
                        frame->Parse(file, info);
                        delete frame;
                        break;
            }
            case ENCRFrame_: {
                frame = new ENCRFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case GRIDFrame_: {
                frame = new ENCRFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case PRIVFrame_: {
                frame = new PRIVFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
            case SEEKFrame_: {
                frame = new SEEKFrame(frame_name);
                frame->Parse(file, info);
                delete frame;
                break;
            }
        }
    }
}

std::vector<Information*> ParseMP3::getTag() {
    return music_;
}

