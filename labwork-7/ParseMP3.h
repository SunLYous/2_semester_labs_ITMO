#ifndef LABWORK_7_SUNLYOUS__PARSEMP3_H_
#define LABWORK_7_SUNLYOUS__PARSEMP3_H_

#include "ParentFrame.h"
#include "Information.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstring>
#include <cmath>
#include <unordered_map>

class ParseMP3 {
private:
    std::string frame_check_;
    std::string version_;
    int size_extended_ = 0;
    int size_header_ = 0;
    bool flag_extended_ = false;
    std::vector<Information*> music_;
    std::vector<char> frame_name_;
    struct const_element {
        const std::string kCheckVersion_ = "ID3";
        const int kSizeHeader_ = 10;
        const int kVersion_ = 3;
        const int kFlagVersionAndFlagSizeHeader_ = 3;
        const int kFlagByteHeader_ = 1;
        const int kFlagBitHeader_ = 6;
        const int kSizeFrameName_ = 4;
    };

    enum frame_parse {
        TextFrame_, XXXFrame_, URLFrame_,
        ETCOFrame_, USLTFrame_, SYLTFrame_,
        COMMFrame_, RVA2Frame_, EQU2Frame_,
        PCNTFrame_, RBUFFrame_, POPMFrame_,
        LINKFrame_, POSSFrame_, USERFrame_,
        OWNEFrame_, COMRFrame_, ENCRFrame_,
        GRIDFrame_, PRIVFrame_, SEEKFrame_

    };

    const std::unordered_map<std::string, frame_parse> map_frame{
            {"TALB", TextFrame_},
            {"TBPM", TextFrame_},
            {"TCOM", TextFrame_},
            {"TCON", TextFrame_},
            {"TCOP", TextFrame_},
            {"TDEN", TextFrame_},
            {"TDLY", TextFrame_},
            {"TDOR", TextFrame_},
            {"TDTC", TextFrame_},
            {"TDRL", TextFrame_},
            {"TDTG", TextFrame_},
            {"TENC", TextFrame_},
            {"TEXT", TextFrame_},
            {"TFLT", TextFrame_},
            {"TIPL", TextFrame_},
            {"TIT1", TextFrame_},
            {"TIT2", TextFrame_},
            {"TIT3", TextFrame_},
            {"TKEY", TextFrame_},
            {"TLAN", TextFrame_},
            {"TLEN", TextFrame_},
            {"TMCL", TextFrame_},
            {"TMED", TextFrame_},
            {"TMOO", TextFrame_},
            {"TOAL", TextFrame_},
            {"TOFN", TextFrame_},
            {"TOLY", TextFrame_},
            {"TOPE", TextFrame_},
            {"TOWN", TextFrame_},
            {"TPE1", TextFrame_},
            {"TPE2", TextFrame_},
            {"TPE3", TextFrame_},
            {"TPE4", TextFrame_},
            {"TPOS", TextFrame_},
            {"TPRO", TextFrame_},
            {"TPUB", TextFrame_},
            {"TRCK", TextFrame_},
            {"TRSN", TextFrame_},
            {"TRSO", TextFrame_},
            {"TSOA", TextFrame_},
            {"TSOP", TextFrame_},
            {"TSOT", TextFrame_},
            {"TSRC", TextFrame_},
            {"TSST", TextFrame_},
            {"TXXX", XXXFrame_},
            {"WCOM", URLFrame_},
            {"WCOP", URLFrame_},
            {"WOAF", URLFrame_},
            {"WOAR", URLFrame_},
            {"WOAS", URLFrame_},
            {"WORS", URLFrame_},
            {"WPAY", URLFrame_},
            {"WPUB", URLFrame_},
            {"WXXX", XXXFrame_},
            {"ETCO", ETCOFrame_},
            {"USLT", USLTFrame_},
            {"SYLT", SYLTFrame_},
            {"COMM", COMMFrame_},
            {"RVA2", RVA2Frame_},
            {"EQU2", EQU2Frame_},
            {"PCNT", PCNTFrame_},
            {"RBUF", RBUFFrame_},
            {"POPM", POPMFrame_},
            {"LINK", LINKFrame_},
            {"POSS", POSSFrame_},
            {"USER", USERFrame_},
            {"OWNE", OWNEFrame_},
            {"COMR", COMRFrame_},
            {"ENCR", ENCRFrame_},
            {"GRID", ENCRFrame_},
            {"PRIV", PRIVFrame_},
            {"SEEK", SEEKFrame_}

    };
    void Parse(const std::vector<std::string>& files);

    void CheckFrame(std::ifstream& file);

    static int CheckSizeInformationHeader(std::ifstream& file);

    void AddFrame(std::ifstream& file, const std::string& frame_name, Information* info);

public:
    explicit ParseMP3(const std::vector<std::string>& files, const std::string& frame_check);

    ~ParseMP3() = default;

    std::vector <Information*> getTag();
};

#endif //LABWORK_7_SUNLYOUS__PARSEMP3_H_
